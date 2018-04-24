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
constexpr int STRSZ = 1<<20;

struct MATCH {
	int pos;
	unsigned sz;
};

class ParallelExec {
protected:
	int nthreads;
	int batch;
private:
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
		batch++;
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
		batch++;
		cnt--; // go below 0 to finish
		cv_begin.notify_all();
	}
	static void run_thread(ParallelExec *th, int n) {
		th->run(n);
	}
	void run(int n) {
		int local_batch = 0;
		while (true) {
			// wait for new data from producer
			{
				std::unique_lock<std::mutex> lck(mtx_begin);
				while (batch == local_batch)
					cv_begin.wait(lck);
				local_batch = batch;
			}
			if (cnt > 0) {
				// process this batch and notify producer
				exec_batch_slice(n);
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
public:
	ParallelExec(int nthreads):nthreads(nthreads),batch(0),threads(nthreads),cnt(0) {
		for (int i=0; i<nthreads; i++)
			threads[i] = std::thread(run_thread, this, i);
	}
	~ParallelExec() {
		threads_done();
		for (auto &t: threads)
			t.join();
	}
	void exec_batch() {
		threads_go();
		threads_wait();
	}
	virtual void exec_batch_slice(int n) = 0;
};

class Detect: public ParallelExec {
	const char *ibuf;
	int ibufsz;
	MATCH *obuf;
	unsigned *nmatch;
	UMSTATE last_umstate;
	virtual void exec_batch_slice(int n) override {
		const char *s = ibuf+STRSZ*n;
		MATCH *out = obuf+STRSZ*n;
		MATCH *res(out);
		UMSTATE umstate;
		if (n == 0)
			umstate = last_umstate;
		else
			um_init(&umstate);
		int i;
		int sz = std::min(STRSZ, ibufsz-STRSZ*n);
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
		nmatch[n] = res-out;
	}
public:
	Detect():ParallelExec(STREAMS),ibuf{nullptr},obuf{nullptr},nmatch{nullptr} {
		um_init(&last_umstate);
	}
	void operator()(const char *_ibuf, int _ibufsz, MATCH *_obuf, unsigned *_nmatch, unsigned &rowsz) {
		ibuf = _ibuf;
		ibufsz = _ibufsz;
		obuf = _obuf;
		nmatch = _nmatch;
		exec_batch();
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

int main(int argc, char **argv) {
	std::unique_ptr<char[]> up_ibuf(new char[STRSZ*(STREAMS+1)]); // +1 to carry over the remaining of the line
	std::unique_ptr<MATCH[]> up_obuf(new MATCH[STRSZ*(STREAMS)]);
	char *ibuf = up_ibuf.get();
	MATCH *obuf = up_obuf.get();
	unsigned nmatch[STREAMS];
	Detect detect;
	memset(ibuf+(STRSZ-UMPATLEN), 0, UMPATLEN);
	while (!feof(stdin)) {
		memcpy(ibuf+(STRSZ-UMPATLEN), ibuf+STREAMS*STRSZ+(STRSZ-UMPATLEN), UMPATLEN);
		int sz = fread(ibuf+STRSZ, 1, STREAMS*STRSZ, stdin);
		//////// run the batch
		unsigned rowsz;
		detect(ibuf+STRSZ, sz, obuf, nmatch, rowsz);
		prn(ibuf+STRSZ, obuf, nmatch, rowsz);
	}
}
