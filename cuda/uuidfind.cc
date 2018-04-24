/**
 * similar to uuidgrep, only
 * extracting UUIDs from stream of ASCII strings
 * use STREAMS parallel threads for speed
 * @author Denis Kokarev
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "uuidmatch.h"
#include "die.h"

constexpr int STREAMS = 8;
constexpr int STRSZ = 1<<20;
constexpr char SFILL = ' ';

struct MATCH {
	unsigned pos;
	unsigned sz;
};

class Detect {
	const char *ibuf;
	MATCH *obuf;
	unsigned *nmatch;
	int batch;
	int cnt;
	// producer notifies, consumer waits
	std::mutex mtx_producer;
	std::condition_variable cv_producer;
	// consumer notifies, producer waits
	std::mutex mtx_consumer;
	std::condition_variable cv_consumer;
	// pre-spawn this many threads
	std::thread threads[STREAMS];
protected:
	void threads_go() {
		std::lock_guard<std::mutex> lck(mtx_producer);
		batch++;
		cnt += STREAMS;
		cv_producer.notify_all();
	}
	void threads_wait() {
		std::unique_lock<std::mutex> lck(mtx_consumer);
		while (cnt > 0)
			cv_consumer.wait(lck);
	}
	void threads_done() {
		std::lock_guard<std::mutex> lck(mtx_producer);
		batch++;
		cnt--; // go below 0
		cv_producer.notify_all();
	}
	unsigned match_one_stream(const char *s, unsigned s_sz, MATCH *out) {
		MATCH *res(out);
		UMSTATE umstate;
		um_init(&umstate);
		for (unsigned i=0; i<s_sz; i++,s++)
			if (um_match(&umstate, *s))
				*res++ = MATCH {i-UMPATLEN+1, UMPATLEN};
		return res-out;
	}
	static void match_thread(Detect *d, int n) {
		int batch = 0;
		while (true) {
			// wait for new data from producer
			{
				std::unique_lock<std::mutex> lck(d->mtx_producer);
				while (d->batch == batch)
					d->cv_producer.wait(lck);
				batch = d->batch;
			}
			const char *in = d->ibuf+STRSZ*n;
			MATCH *out = d->obuf+STRSZ*n;
			if (d->cnt > 0) {
				// process this batch and notify producer
				d->nmatch[n] = d->match_one_stream(in, STRSZ, out);
				{
					std::lock_guard<std::mutex> lck(d->mtx_consumer);
					d->cnt--;
					d->cv_consumer.notify_one();
				}
			} else {
				break;
			}
		}
	}
public:
	Detect():ibuf{nullptr},obuf{nullptr},nmatch{nullptr},batch{0},cnt{0} {
		for (int i=0; i<STREAMS; ++i)
			threads[i] = std::thread(match_thread, this, i);
	}
	~Detect() {
		threads_done();
		for (auto &t: threads)
			t.join();
	}
	void operator()(const char *_ibuf, MATCH *_obuf, unsigned *_nmatch, unsigned &rowsz) {
		ibuf = _ibuf;
		obuf = _obuf;
		nmatch = _nmatch;
		threads_go();
		threads_wait();
		rowsz = STRSZ;
	}
};

void prn(const char *ibuf, const MATCH *obuf, const unsigned *nmatch, const unsigned rowsz) {
	for (int stream=0; stream<STREAMS; stream++) {
		unsigned sz = nmatch[stream];
		const MATCH *mm = obuf+rowsz*stream;
		const char *s = ibuf+STRSZ*stream;
		for (unsigned i=0; i<sz; i++) {
			if ((fwrite(s+mm[i].pos, 1, mm[i].sz, stdout)) != (int)mm[i].sz)
				die("Write error");
			if (fputc('\n', stdout) != '\n')
				die("Write error");
		}
	}
}

inline int rfindnl(const char *buf, int sz) {
	int over = 0;
	while (sz > 0 && buf[sz-1] != '\n')
		sz--, over++;
	return over;
}

enum {
	SA_OK = 0,
	SA_INVALID,
	SA_NOT_READY
};

class PipeStage {
protected:
	std::mutex mtx;
	std::condition_variable cv;
	PipeStage *parent;
	std::thread parent_thread;
	bool go;
protected:
	int batchno;
	bool done;
	void run_thread() {
		bool parent_done = false;
		while (!done) {
			done |= parent_done;
			{
				std::unique_lock<std::mutex> lck(mtx);
				while (!go)
					cv.wait(lck);
			}
			if (parent) {
				if (!parent_done) {
					std::lock_guard<std::mutex> lck(parent->mtx);
					parent->go ^= 1;
					parent->cv.notify_one();
				}
				done |= batch();
				if (!parent_done) {
					std::unique_lock<std::mutex> lck(parent->mtx);
					while (parent->go)
						parent->cv.wait(lck);
				}
				parent_done = parent->done;
			} else {
				done |= batch();
			}
			batchno++;
			{
				std::lock_guard<std::mutex> lck(mtx);
				go ^= 1;
				cv.notify_one();
			}
		}
	}
	static void run_thread_static(PipeStage *stage) {
		stage->run_thread();
	}
public:
	PipeStage(PipeStage *parent):parent(parent),go(false),batchno(0),done(false) {
		if (parent)
			parent_thread = std::thread(run_thread_static, parent);
	}
	virtual ~PipeStage() {
		if (parent)
			parent_thread.join();
	}
	void run() {
		while (!done) {
			if (parent) {
				bool parent_done = parent->done;
				done |= parent_done;
				if (!parent_done) {
					std::lock_guard<std::mutex> lck(parent->mtx);
					parent->go ^= 1;
					parent->cv.notify_one();
				}
				done |= batch();
				if (!parent_done) {
					std::unique_lock<std::mutex> lck(parent->mtx);
					while (parent->go)
						parent->cv.wait(lck);
				}
			} else {
				done |= batch();
			}
			batchno++;
		}
	}
	// all stages, except the very first return false
	// the very first parent returns true, when the src
	// data feed is over
	virtual bool batch() = 0;
	virtual int arg(int ith, int bn, void **res) = 0;
};

struct BUF {
	size_t sz;
	void *buf;
};

class PipeStageRead: public PipeStage {
	static constexpr int depth = 2;
	static constexpr int buf_sz = 65536;
	FILE *fin;
	std::unique_ptr<char[]> up_buf[depth];
	BUF buf[depth];
public:
	PipeStageRead(FILE *fin):PipeStage(nullptr),
							 fin(fin),
							 up_buf {std::unique_ptr<char[]>(new char[buf_sz]), std::unique_ptr<char[]>(new char[buf_sz])},
							 buf{{0,up_buf[0].get()}, {0,up_buf[1].get()}} {
	}
	virtual int arg(int ith, int bn, void **res) override {
		if (ith >= depth) {
			return SA_INVALID;
		} else if (ith > bn) {
			return SA_NOT_READY;
		} else {
			*res = &buf[(bn+depth-ith)%depth];
			return SA_OK;
		}
	}
	virtual bool batch() override {
		//fprintf(stderr, "read batchno=%d\n", batchno);
		if (feof(fin)) {
			return true;
		} else {
			int rc = fread(buf[batchno%depth].buf, 1, buf_sz, fin);
			if (rc < 0)
				die("read error");
			buf[batchno%depth].sz = rc;
			return rc != buf_sz;
		}
	}
};

class PipeStageWrite: public PipeStage  {
	FILE *fout;
public:
	PipeStageWrite(PipeStage *parent, FILE *fout):PipeStage(parent), fout(fout) {
	}
	virtual int arg(int ith, int bn, void **res) override {
		return SA_INVALID;
	}
	virtual bool batch() override {
		//fprintf(stderr, "write batchno=%d\n", batchno);
		BUF *read_buf;
		int sa_res = parent->arg(1, batchno, (void**)&read_buf);
		int rc;
		switch (sa_res) {
		case SA_OK:
			rc = fwrite(read_buf->buf, 1, read_buf->sz, fout);
			if (rc != read_buf->sz)
				die("write error");
			break;
		case SA_INVALID:
			die("PipeRead.arg returns SA_INVALID");
		}
		return false;
	}
};

int main(int argc, char **argv) {
	PipeStageRead read(stdin);
	PipeStageWrite write(&read, stdout);
	write.run();
	return 0;
}
