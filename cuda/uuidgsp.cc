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
#include "uuidmatch.h"
#include "die.h"
#include "par.hh"

constexpr int STREAMS = 4;
constexpr int STRSZ = 1<<20;

struct MATCH {
	int pos;
	unsigned sz;
};

// owns input the data buffers for the pipeline
class ReadStage: public PipeHeadExec {
public:
	struct TRESULT {
		char *buf;
		int sz;
	};
private:
	static constexpr int stages = 3; // need to drag the input over 3 pipe segments
	FILE *fin;
	TRESULT res[stages];
	std::unique_ptr<char[]> up_buf;
private:
	virtual void *next() override {
		if (!feof(fin)) {
			if (batch%stages == 0) // wrap the remaining line around
				memcpy(res[0].buf-UMPATLEN, res[stages-1].buf+STREAMS*STRSZ-UMPATLEN, UMPATLEN);
			TRESULT &r = res[batch%stages];
			r.sz = fread(r.buf, 1, STREAMS*STRSZ, fin);
			if (r.sz < 0)
				die("Read error");
			return &r;
		} else {
			return nullptr;
		}
	}
public:
	ReadStage(FILE *fin):PipeHeadExec(),
						 fin(fin),
						 up_buf(new char[STRSZ*STREAMS*stages+STRSZ]) {
		res[0] = {up_buf.get()+STRSZ, 0};
		for (int i=1; i<stages; i++)
			res[i] = {res[i-1].buf+STRSZ*STREAMS, 0};
	}
};

class Detect: public ParallelExec {
	const char *ibuf;
	int ibufsz;
	MATCH *match;
	unsigned *nmatch;
	UMSTATE first_umstate, last_umstate;
	virtual void exec_slice(int n) override {
		const char *s = ibuf+STRSZ*n;
		MATCH *m = match+STRSZ*n;
		MATCH *res(m);
		UMSTATE umstate;
		if (n == 0)
			umstate = first_umstate;
		else
			um_init(&umstate);
		int i;
		int sz = std::min(STRSZ, ibufsz-STRSZ*n);
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
		nmatch[n] = res-m;
	}
public:
	Detect():ParallelExec(STREAMS),ibuf(nullptr),match(nullptr),nmatch(nullptr) {
		um_init(&first_umstate);
	}
	void operator()(const char *_ibuf, int _ibufsz, MATCH *_match, unsigned *_nmatch, unsigned &rowsz) {
		ibuf = _ibuf;
		ibufsz = _ibufsz;
		match = _match;
		nmatch = _nmatch;
		exec();
		rowsz = STRSZ;
		first_umstate = last_umstate;
	}
};

class DetectStage: public PipeStageExec {
public:
	struct TRESULT {
		ReadStage::TRESULT in;
		unsigned match_row_sz;
		MATCH *match;
		unsigned *nmatch;
	};
private:
	static constexpr int stages = 2;
	std::unique_ptr<MATCH> up_match[stages];
	std::unique_ptr<unsigned> up_nmatch[stages];
	TRESULT res[stages];
	Detect detect;
	virtual void *next(void *arg) override {
		TRESULT &r = res[batch%stages];
		r.in = *(ReadStage::TRESULT*)arg;
		detect(r.in.buf, r.in.sz, r.match, r.nmatch, r.match_row_sz);
		return &r;
	}
public:
	DetectStage(ReadStage &parent):PipeStageExec(parent),detect() {
		for (int i=0; i<stages; i++) {
			up_match[i] = std::unique_ptr<MATCH>(new MATCH[STRSZ*STREAMS]);
			up_nmatch[i] = std::unique_ptr<unsigned>(new unsigned[STREAMS*stages]);
			res[i] = {ReadStage::TRESULT {nullptr, 0}, 0, up_match[i].get(), up_nmatch[i].get()};
		}
	}
};

void prn(const char *ibuf, const MATCH *match, const unsigned *nmatch, const unsigned match_row_sz) {
	for (int stream=0; stream<STREAMS; stream++) {
		unsigned sz = nmatch[stream];
		const MATCH *mm = match+match_row_sz*stream;
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
		DetectStage::TRESULT *r = (DetectStage::TRESULT*)it;
		prn(r->in.buf, r->match, r->nmatch, r->match_row_sz);
	}
}
