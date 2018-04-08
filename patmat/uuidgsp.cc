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

int main(int argc, char **argv) {
	int over = 0;
	std::unique_ptr<char[]> up_ibuf(new char[STRSZ*(STREAMS+1)]); // +1 to carry over the remaining of the line
	std::unique_ptr<MATCH[]> up_obuf(new MATCH[STRSZ*(STREAMS)]);
	char *ibuf = up_ibuf.get();
	MATCH *obuf = up_obuf.get();
	unsigned nmatch[STREAMS];
	Detect detect;
	// read input and scatter it into STREAMS channels
	while (!feof(stdin)) {
		int ns = 0;
		char *buf = ibuf;
		memcpy(buf, buf+STREAMS*STRSZ, over);
		while (ns < STREAMS) {
			int rsz = STRSZ-over;
			int rc = fread(buf+over, 1, rsz, stdin);
			if (rc == rsz) {
				over = rfindnl(buf, STRSZ);
				if (over == STRSZ)
					die("Line size must be less than %d", STRSZ);
				char *next_buf = buf+STRSZ;
				memcpy(next_buf, buf+STRSZ-over, over);
				memset(buf+STRSZ-over, SFILL, over);
				buf = next_buf;
				ns++;
			} else if (rc < 0) {
				die("read error");
			} else {
				// we didn't get full block - must be eof
				memset(buf+over+rc, SFILL, STRSZ-over-rc);
				ns++;
				memset(ibuf+STRSZ*ns, SFILL, (STREAMS-ns)*STRSZ); // fill up all unused channels
				break;
			}
		}
		//////// run the batch
		unsigned rowsz;
		detect(ibuf, obuf, nmatch, rowsz);
		prn(ibuf, obuf, nmatch, rowsz);
	}
}
