/**
 * a-la fgrep utility only in parallel
 * grep input lines for precompiled patterns
 * @author Denis Kokarev
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <stdarg.h>
#include <getopt.h>
#include "die.h"
#include "par.hh"
#include "act.h"

constexpr int STREAMS = 6;
constexpr int STRSZ = 1<<18;

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
				memcpy(res[0].buf-STRSZ, res[stages-1].buf+STREAMS*STRSZ-STRSZ, STRSZ);
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

class ParallelFgrep: public ParallelExec {
	const char *ibuf;
	int ibufsz;
	MATCH *match;
	unsigned *nmatch;
	ACT *act;
	struct DSTATE {
		unsigned node;
		int lbeg;	// position where last line started
	} first_state, last_state;
	virtual void exec_slice(int n) override {
		MATCH *m = match+STRSZ*n;
		MATCH *res(m);
		DSTATE state;
		const char *begin = ibuf+STRSZ*n;
		const char *end = ibuf+STRSZ*(n+1);
		const char *next_end = ibuf+STRSZ*(n+2);
		const char *ibuf_end = ibuf+ibufsz;
		const char *p;
		if (n == 0) {
			p = begin;
			state = first_state;
		} else {
			for (p=begin; p<end && p<ibuf_end && *p!='\n'; ++p);
			if (p == end)
				die("Lines cannot be longer than %d", int(STRSZ));
			++p;
			state = DSTATE {ACT_ROOT, int(p-begin)};
		}
		while (p < next_end && p < ibuf_end) {
			state.node = act_next_char(act->nodes, state.node, *p);
			unsigned result_node = state.node;
			int unused;
			if (act_next_match(act->nodes, &result_node, &unused)) {
				while (p < next_end && p < ibuf_end && *p != '\n')
					++p;
				if (p == next_end)
					die("Lines cannot be longer than %d", int(STRSZ));
				*res++ = MATCH {state.lbeg, unsigned(p-begin-state.lbeg)};
				++p;
				state.lbeg = p-begin;
				state.node = ACT_ROOT;
				if (p >= end)
					break;
			} else {
				++p;
				if (*p == '\n') {
					if (p >= end) {
						break;
					} else {
						++p;
						state.lbeg = p-begin;
						state.node = ACT_ROOT;
					}
				}
			}
		}
		if (n == nthreads-1) {
			state.lbeg -= STRSZ;
			last_state = state;
		}
		nmatch[n] = res-m;
	}
public:
	ParallelFgrep(ACT *act):ParallelExec(STREAMS),ibuf(nullptr),match(nullptr),nmatch(nullptr),act(act) {
		first_state = DSTATE {ACT_ROOT, 0};
	}
	void operator()(const char *_ibuf, int _ibufsz, MATCH *_match, unsigned *_nmatch, unsigned &rowsz) {
		ibuf = _ibuf;
		ibufsz = _ibufsz;
		match = _match;
		nmatch = _nmatch;
		exec();
		rowsz = STRSZ;
		first_state = last_state;
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
	ParallelFgrep detect;
	virtual void *next(void *arg) override {
		TRESULT &r = res[batch%stages];
		r.in = *(ReadStage::TRESULT*)arg;
		detect(r.in.buf, r.in.sz, r.match, r.nmatch, r.match_row_sz);
		return &r;
	}
public:
	DetectStage(ReadStage &parent, ACT *act):PipeStageExec(parent),detect(act) {
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

static void usage(char *cmd) {
	printf("Match the input strings with actcomp precompiled automata,\n");
	printf("works similar to fgrep\n");
	printf("@author Denis Kokarev, at&t\n");
	printf("Usage:\n");
	printf("\t%s patterns.bin <input.txt >filtered.txt\n", cmd);
	printf("patterns.bin - precompiled patterns.txt file, see `actcomp -h`\n");
}

int main(int argc, char **argv) {
	int c;
	opterr = 0;
	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
			usage(argv[0]);
			return(0);
		default:
			die("unknown cmd line argument");
		}
	}
	if (argc-optind < 1) {
		usage(argv[0]);
		die("run as `%s patterns.bin <file`", argv[0]);
	}
	ACT act;
	int rc = act_attach_mmap(&act, argv[optind]);
	if (rc != 0)
		die("couldn't use specified patterns file %s, act_attach_mmap() error code %d", argv[optind], rc);
	{
		ReadStage read(stdin);
		DetectStage detect(read, &act);
		for (auto it:PipeOutput(detect)) {
			DetectStage::TRESULT *r = (DetectStage::TRESULT*)it;
			prn(r->in.buf, r->match, r->nmatch, r->match_row_sz);
		}
	}
	rc = act_detach_mmap(&act);
	if (rc != 0)
		die("act_detach_mmap() error code %d", rc);
}
