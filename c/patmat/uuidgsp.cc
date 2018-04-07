/**
 * similar to uuidgrep, only
 * extracting UUIDs from stream of ASCII strings
 * use STREAMS parallel threads for speed
 * @author Denis Kokarev
 */
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include "die.h"
#include <memory>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "uuidmatch.h"

constexpr int STREAMS = 8;
constexpr int STRSZ = 1<<20;
constexpr char SFILL = ' ';

struct MATCH {
	unsigned pos;
	unsigned sz;
};

unsigned match_one_stream(const char *s, unsigned s_sz, MATCH *out) {
	MATCH *res(out);
	UMSTATE umstate;
	um_init(&umstate);
	for (unsigned i=0; i<s_sz; i++,s++)
		if (um_match(&umstate, *s))
			*res++ = MATCH {i-UMPATLEN+1, UMPATLEN};
	return res-out;
}

struct THARG {
	const char *ibuf;
	MATCH *obuf;
	unsigned *o_sz;
	// producer notifies, consumer waits
	std::mutex mtx_producer;
	std::condition_variable cv_producer;
	// consumer notifies, producer waits
	std::mutex mtx_consumer;
	std::condition_variable cv_consumer;
	volatile int batch;
	volatile int cnt;
};

void match_thread(THARG *t, int n) {
	const char *in = t->ibuf+STRSZ*n;
	MATCH *out = t->obuf+STRSZ*n;
	int batch = 0;
	while (true) {
		// wait for new data from producer
		{
			std::unique_lock<std::mutex> lck(t->mtx_producer);
			while (t->batch == batch)
				t->cv_producer.wait(lck);
			batch = t->batch;
		}
		if (t->cnt > 0) {
			// process this batch and notify producer
			t->o_sz[n] = match_one_stream(in, STRSZ, out);
			{
				std::lock_guard<std::mutex> lck(t->mtx_consumer);
				t->cnt--;
				t->cv_consumer.notify_one();
			}
		} else {
			break;
		}
	}
	//fprintf(stderr, "done thread %d\n", n);
}

void threads_go(THARG *t) {
	std::lock_guard<std::mutex> lck(t->mtx_producer);
	t->batch++;
	t->cnt += STREAMS;
	t->cv_producer.notify_all();
}

void threads_wait(THARG *t) {
	std::unique_lock<std::mutex> lck(t->mtx_consumer);
	while (t->cnt > 0)
		t->cv_consumer.wait(lck);
}

void threads_done(THARG *t) {
	std::lock_guard<std::mutex> lck(t->mtx_producer);
	t->batch++;
	t->cnt--; // go below 0
	t->cv_producer.notify_all();
}

void prn(const char *ibuf, const MATCH *obuf, const unsigned *o_sz) {
	int rc;
	for (int stream=0; stream<STREAMS; stream++) {
		unsigned sz = o_sz[stream];
		//fprintf(stderr, "stream: %d, sz: %d\n", stream, sz);
		const MATCH *mm = obuf+STRSZ*stream;
		const char *s = ibuf+STRSZ*stream;
		for (unsigned i=0; i<sz; i++) {
			//fprintf(stderr, "\tpos: %d, sz: %d\n", mm[i].pos, mm[i].sz);
			if ((rc=fwrite(s+mm[i].pos, 1, mm[i].sz, stdout)) != (int)mm[i].sz)
				die("Write error");
			if (fputc('\n', stdout) != '\n')
				die("Write error");
		}
	}
}

static int rfindnl(const char *buf, int sz) {
	int over = 0;
	while (sz > 0 && buf[sz-1] != '\n')
		sz--, over++;
	return over;
}

int main(int argc, char **argv) {
	int over = 0;
	std::unique_ptr<char[]> up_ibuf(new char[STRSZ*(STREAMS+1)]);
	std::unique_ptr<MATCH[]> up_obuf(new MATCH[STRSZ*(STREAMS+1)]);
	char *ibuf = up_ibuf.get();
	MATCH *obuf = up_obuf.get();
	unsigned o_sz[STREAMS];
	std::thread threads[STREAMS];
	THARG tharg {ibuf, obuf, o_sz};
	for (int i=0; i<STREAMS; ++i)
		threads[i] = std::thread(match_thread, &tharg, i);
	int batch = 0;
	// read input and scatter it into STREAMS channels
	while (!feof(stdin)) {
		int ns = 0;
		char *buf = ibuf;
		char *next_buf = buf+STRSZ;
		memcpy(buf, buf+STREAMS*STRSZ, over);
		while (ns < STREAMS) {
			int rsz = STRSZ-over;
			int rc = fread(buf+over, 1, rsz, stdin);
			if (rc == rsz) {
				over = rfindnl(buf, STRSZ);
				if (over == STRSZ)
					die("Line size may not exceed %d", STRSZ);
				memcpy(next_buf, buf+STRSZ-over, over);
				memset(buf+STRSZ-over, SFILL, over);
				buf = next_buf;
				next_buf = buf+STRSZ;
				ns++;
			} else if (rc < 0) {
				die("read error");
			} else {
				memset(buf+over+rc, SFILL, STRSZ-over-rc);
				ns++;
				break;
			}
		}
		if (ns < STREAMS)
			memset(ibuf+STRSZ*ns, SFILL, (STREAMS-ns)*STRSZ); // fill up all unused channels
		threads_go(&tharg);
		//fprintf(stderr, "batch wait: %d\n", batch);
		threads_wait(&tharg);
		prn(ibuf, obuf, o_sz);
		batch++;
	}
	threads_done(&tharg);
	for (auto &t: threads)
		t.join();
}
