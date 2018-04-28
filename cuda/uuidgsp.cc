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
#include <vector>
#include "uuidmatch.h"
#include "die.h"

constexpr int STREAMS = 8;
constexpr int STRSZ = 1<<16;

struct MATCH {
	int pos;
	unsigned sz;
};

/**
 * when you need to parallelize the processing of one batch
 */
class ParallelExec {
protected:
	int nthreads;
private:
	int tick;
	// pre-spawn this many threads
	std::vector<std::thread> threads;
	int cnt;
	// threads wait on this cv to start the batch
	std::mutex mtx_begin;
	std::condition_variable cv_begin;
	// threads notify this cv at the end of batch
	std::mutex mtx_end;
	std::condition_variable cv_end;
	void threads_go() {
		std::lock_guard<std::mutex> lck(mtx_begin);
		tick++;
		cnt += nthreads;
		cv_begin.notify_all();
	}
	void threads_wait() {
		std::unique_lock<std::mutex> lck(mtx_end);
		while (cnt > 0)
			cv_end.wait(lck);
	}
	void threads_done() {
		std::lock_guard<std::mutex> lck(mtx_begin);
		tick++;
		cnt--; // go below 0 to finish
		cv_begin.notify_all();
	}
	static void run_thread(ParallelExec *th, int n) {
		th->run(n);
	}
	void run(int n) {
		int local_tick = 0;
		while (true) {
			// wait for new data from producer
			{
				std::unique_lock<std::mutex> lck(mtx_begin);
				while (tick == local_tick)
					cv_begin.wait(lck);
				local_tick = tick;
			}
			if (cnt > 0) {
				// process this batch and notify producer
				exec_slice(n);
				{
					std::lock_guard<std::mutex> lck(mtx_end);
					cnt--;
					cv_end.notify_one();
				}
			} else {
				// quit
				break;
			}
		}
	}
protected:
	virtual void exec_slice(int n) = 0;
public:
	ParallelExec(int nthreads):nthreads(nthreads),tick(0),threads(nthreads),cnt(0) {
		for (int i=0; i<nthreads; i++)
			threads[i] = std::thread(run_thread, this, i);
	}
	~ParallelExec() {
		threads_done();
		for (auto &t: threads)
			t.join();
	}
	void exec() {
		threads_go();
		threads_wait();
	}
};

/**
 * when you need to parallelize the execution conveyor of many steps
 */
class PipeStageExec;
class PipeOutputIterator;

class PipeHeadExec {
	friend PipeStageExec;
	friend PipeOutputIterator;
public:
	int batch;
private:
	bool go;
	bool done;
	bool abort;
	int depth;
	void *last_arg;
	std::mutex mtx;
	std::condition_variable cv;
	void thread_wait_go() {
		std::unique_lock<std::mutex> lck(mtx);
		while (!go)
			cv.wait(lck);
	}
	void thread_notify_go() {
		std::lock_guard<std::mutex> lck(mtx);
		go = true;
		cv.notify_one();
	}
	void thread_notify_abort() {
		std::lock_guard<std::mutex> lck(mtx);
		go = true;
		abort = true;
		cv.notify_one();
	}
	void thread_wait_done() {
		std::unique_lock<std::mutex> lck(mtx);
		while (go)
			cv.wait(lck);
	}
	void thread_notify_done() {
		std::lock_guard<std::mutex> lck(mtx);
		go = false;
		cv.notify_one();
	}
	virtual void run() {
		while (!done && !abort) {
			thread_wait_go();
			if (abort)
				break;
			last_arg = next();
			done = (last_arg == nullptr);
			batch++;
			thread_notify_done();
		}
	}
	virtual void *next() = 0;
public:
	PipeHeadExec() {
		batch = 0;
		go = false;
		done = false;
		abort = false;
		depth = 0;
		last_arg = nullptr;
	}
};

class PipeStageExec: public PipeHeadExec {
	friend PipeOutputIterator;
private:
	PipeHeadExec &parent;
	std::thread thread;
	static void run_thread(PipeHeadExec *th) {
		th->run();
	}
	virtual void run() override {
		void *parent_last_arg = nullptr;
		while (!done && !abort) {
			thread_wait_go();
			if (abort)
				break;
			if (!parent.done) {
				parent.thread_notify_go();
				// idle until conveyor is filled
				if (batch >= depth)
					last_arg = next(parent_last_arg);
				parent.thread_wait_done();
				parent_last_arg = parent.last_arg;
			} else {
				last_arg = nullptr;
				done = true;
			}
			batch++;
			thread_notify_done();
		}
	}
protected:
	virtual void *next() override final {
		return nullptr;
	}
	virtual void *next(void *arg) = 0;
public:
	PipeStageExec(PipeHeadExec &parent):PipeHeadExec(),parent(parent) {
		depth = parent.depth+1;
		thread = std::thread(run_thread, &parent);
	};
	~PipeStageExec() {
		parent.thread_notify_abort();
		thread.join();
	}
};

class PipeOutputIterator {
	PipeStageExec &tail;
	void *value;
public:
	PipeOutputIterator(PipeStageExec &tail):tail(tail),value(nullptr) {
	}
	bool operator==(const PipeOutputIterator &b) const {
		return value == b.value;
	}
	bool operator!=(const PipeOutputIterator &b) const {
		return value != b.value;
	}
	PipeOutputIterator &seek_begin() {
		while (!tail.parent.done && tail.parent.batch<=tail.parent.depth) {
			tail.parent.thread_notify_go();
			tail.parent.thread_wait_done();
		}
		value = tail.parent.last_arg;
		tail.parent.thread_notify_go();
		return *this;
	}
	PipeOutputIterator &seek_end() {
		value = nullptr;
		return *this;
	}
	void operator++() {
		tail.parent.thread_wait_done();
		value = tail.parent.last_arg;
		if (!tail.parent.done) {
			tail.parent.thread_notify_go();
		} else {
			value = nullptr;
		}
	}
	void *operator*() const {
		return value;
	}
};

class PipeOutput: public PipeStageExec {
protected:
	virtual void *next(void *arg) override final {
		return nullptr;
	};
	PipeOutputIterator begin_it;
	PipeOutputIterator end_it;
public:
	PipeOutput(PipeHeadExec &parent):PipeStageExec(parent),
									 begin_it(PipeOutputIterator(*this)),
									 end_it(PipeOutputIterator(*this)) {
	}
	PipeOutputIterator &begin() {
		return begin_it.seek_begin();
	}
	PipeOutputIterator &end() {
		return end_it.seek_end();
	}
};

// pipeline element carries only pointers allocated by pipe head
struct DETECT {
	char *ibuf;
	int ibufsz;
	MATCH *obuf;
	unsigned *nmatch;
};

// owns all the data buffers for the pipeline
class ReadStage: public PipeHeadExec {
	static constexpr int stages = 3;
	FILE *fin;
	DETECT in[stages];
	std::unique_ptr<char[]> up_ibuf;
	std::unique_ptr<MATCH[]> up_obuf;
	std::unique_ptr<unsigned[]> up_nmatch;
	virtual void *next() override {
		if (!feof(fin)) {
			if (batch%stages == 0)
				memcpy(in[0].ibuf-UMPATLEN, in[stages-1].ibuf+STREAMS*STRSZ-UMPATLEN, UMPATLEN);
			in[batch&1].ibufsz = fread(in[batch&1].ibuf, 1, STREAMS*STRSZ, fin);
			if (in[batch&1].ibufsz < 0)
				die("Read error");
			return &in[batch&1];
		} else {
			return nullptr;
		}
	}
public:
	ReadStage(FILE *fin):PipeHeadExec(),
						 fin(fin),
						 up_ibuf(new char[STRSZ*STREAMS*stages+STRSZ]),
						 up_obuf(new MATCH[STRSZ*STREAMS*stages]),
						 up_nmatch(new unsigned[STREAMS*stages]) {
		in[0] = {up_ibuf.get()+STRSZ, 0, up_obuf.get(), up_nmatch.get()};
		for (int i=1; i<stages; i++)
			in[i] = {in[i-1].ibuf+STRSZ*STREAMS, 0, in[i-1].obuf+STRSZ*STREAMS, in[i-1].nmatch+STRSZ*STREAMS};
		memset(in[stages-1].ibuf+STREAMS*STRSZ-UMPATLEN, 0, UMPATLEN);
	}
};

class DetectStage: public ParallelExec, public PipeStageExec {
	static constexpr int stages = 2;
	DETECT in[stages];
	DETECT d;
	UMSTATE first_umstate, last_umstate;
	virtual void exec_slice(int n) override {
		const char *s = d.ibuf+STRSZ*n;
		MATCH *out = d.obuf+STRSZ*n;
		MATCH *res(out);
		UMSTATE umstate;
		if (n == 0)
			umstate = first_umstate;
		else
			um_init(&umstate);
		int i;
		int sz = std::min(STRSZ, d.ibufsz-STRSZ*n);
		if (sz > 0) {
			for (i=0; i<sz; i++,s++)
				if (um_match(&umstate, *s))
					*res++ = MATCH {i-UMPATLEN+1, UMPATLEN};
			if (n == nthreads-1) {
				last_umstate = umstate;
			} else {
				while (umstate != 0 && i<sz+UMPATLEN) {
					if (um_match(&umstate, *s)) {
						*res++ = MATCH {i-UMPATLEN+1, UMPATLEN};
						break;
					}
					i++;
					s++;
				}
			}
		}
		d.nmatch[n] = res-out;
	}
	virtual void *next(void *arg) override {
		d = in[batch%stages] = *(DETECT*)arg; 
		exec();
		return &in[batch%stages];
	}
public:
	DetectStage(PipeHeadExec &parent):ParallelExec(STREAMS),PipeStageExec(parent) {
		um_init(&first_umstate);
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

int main(int argc, char **argv) {
	ReadStage read(stdin);
	DetectStage detect(read);
	for (auto it:PipeOutput(detect)) {
		DETECT *d = (DETECT*)it;
		prn(d->ibuf, d->obuf, d->nmatch, STRSZ);
	}
}
