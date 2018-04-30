#include <memory>
#include "gtest/gtest.h"
#include "par.hh"

/**
 * Usage example
 */

// an argument to drag through pipeline
struct PIPE_ELEMENT {
	int num;
	int category;
	const char *label;
};

class GenStage: public PipeHeadExec {
private:
	int limit;
	static constexpr int stages = 2;
	PIPE_ELEMENT el[stages];
	virtual void *next() override {
		if (batch < limit) {
			el[batch%stages] = PIPE_ELEMENT {batch, -1, nullptr};
			return el+batch%stages;
		} else {
			return nullptr;
		}
	}
public:
	GenStage(int limit):PipeHeadExec(),limit(limit) {
	}
};

class CategorizeStage: public PipeStageExec {
private:
	static constexpr int stages = 2;
	PIPE_ELEMENT el[stages];
	virtual void *next(void *arg) override {
		int stage = batch%stages;
		el[stage].num = ((PIPE_ELEMENT*)arg)->num;
		el[stage].category = el[stage].num&1;
		return &el[stage];
	}
public:
	using PipeStageExec::PipeStageExec;
};

class LabelStage: public PipeStageExec {
private:
	static constexpr int stages = 2;
	const char *label[2] {"even", "odd"};
	PIPE_ELEMENT el[stages];
	char slabel[stages][5];	// we'll copy the string values for labels
	virtual void *next(void *arg) override {
		int stage = batch%stages;
		PIPE_ELEMENT *parent_el = (PIPE_ELEMENT*)arg;
		el[stage] = *parent_el;
		strncpy(slabel[stage], label[parent_el->category], 5); // use copy to excercise memory
		el[stage].label = slabel[stage];
		return &el[stage];
	}
public:
	using PipeStageExec::PipeStageExec;
};

TEST(ParTest, Simple) {
	constexpr int n = 10;
	GenStage generate(n);
	CategorizeStage categorize(generate);
	LabelStage label(categorize);
	int cnt = 0;
	for (auto pel:PipeOutput(label)) {
		PIPE_ELEMENT *el = (PIPE_ELEMENT*)pel;
		fprintf(stdout, "line num=%d, category=%d, label=%s\n", el->num, el->category, el->label);
		cnt++;
	}
	EXPECT_TRUE(cnt == n);	// must get exactly n lines
}

TEST(ParTest, Volume) {
	constexpr int64_t n = 10000;
	GenStage generate(n);
	CategorizeStage categorize(generate);
	LabelStage label(categorize);
	int64_t num_sum = 0;
	int64_t cat_sum = 0;
	for (auto pel:PipeOutput(label)) {
		PIPE_ELEMENT *el = (PIPE_ELEMENT*)pel;
		num_sum += el->num;
		cat_sum += el->category;
		if (el->num&1)
			EXPECT_TRUE(el->category == 1 && !strcmp(el->label, "odd"));
		else
			EXPECT_TRUE(el->category == 0 && !strcmp(el->label, "even"));
	}
	EXPECT_TRUE(num_sum == n*(n-1)/2 && cat_sum == n/2);
}

TEST(ParTest, Idle) {
	{
		GenStage generate(1000);
		CategorizeStage categorize(generate);
		LabelStage label(categorize);
	}
	EXPECT_TRUE("creation and teardown without execution");
}

// produce 100 batches of 1M elements each
class GenValues: public ParallelExec, public PipeHeadExec {
protected:
	int limit;
	int sz;
public:
	struct TRESULT {
		std::unique_ptr<int[]> n;
		int sz;
	};
protected:
	static constexpr int stages = 2;
	TRESULT res[stages];
	virtual void exec_slice(int n) override {
		TRESULT &r = res[batch%stages];
		int sz = r.sz;
		int blocksz = (sz+nthreads-1)/nthreads;
		int upto = std::min(blocksz*(n+1), sz);
		for (int i=blocksz*n; i<upto; i++)
			r.n[i] = batch*sz+i;
	}
	void *next() override {
		if (batch < limit) {
			TRESULT &r = res[batch%stages];
			r = TRESULT { std::unique_ptr<int[]>(new int[sz]), sz};
			exec();
			return &r;
		} else {
			return nullptr;
		}
	}
public:
	GenValues(int limit, int sz, int nthreads):ParallelExec(nthreads),PipeHeadExec(),limit(limit),sz(sz) {
	}
};

// add a fixed delta to every number
class AddValues: public ParallelExec, public PipeStageExec {
public:
	using TRESULT = GenValues::TRESULT;
protected:
	int inc;
	static constexpr int stages = 2;
	TRESULT res[stages];
	virtual void exec_slice(int n) override {
		TRESULT &r = res[batch%stages];
		int blocksz = (r.sz+nthreads-1)/nthreads;
		int upto = std::min(blocksz*(n+1),r.sz);
		for (int i=blocksz*n; i<upto; i++)
			r.n[i] += inc;
	}
	void *next(void *arg) override {
		TRESULT *ra = (TRESULT*)arg;
		TRESULT &r = res[batch%stages];
		r.n = std::move(ra->n);
		r.sz = ra->sz;
		exec();
		return &r;
	}
public:
	AddValues(int inc, int nthreads, PipeHeadExec &parent):ParallelExec(nthreads),PipeStageExec(parent),inc(inc) {
	}
};

// accumulate the buffer
class Accumulate: public ParallelExec, public PipeStageExec {
public:
	static constexpr int nth = 4;
	struct TSUM {
		int64_t sum[nth];
	};
protected:
	static constexpr int stages = 2;
	TSUM res[stages];
	AddValues::TRESULT *arg;
	virtual void exec_slice(int n) override {
		TSUM &r = res[batch%stages];
		int blocksz = (arg->sz+nthreads-1)/nthreads;
		int upto = std::min(blocksz*(n+1),arg->sz);
		for (int i=blocksz*n; i<upto; i++)
			r.sum[n] += arg->n[i];
	}
	void *next(void *a) override {
		arg = (AddValues::TRESULT*)a;
		TSUM &r = res[batch%stages];
		for (int j=0; j<nthreads; j++)
			r.sum[j] = 0;
		exec();
		return &r;
	}
public:
	#if 1
	Accumulate(PipeHeadExec &parent):ParallelExec(nth),PipeStageExec(parent) {
	}
	#endif
};

TEST(ParTest, ParallelConveyor) {
	int64_t limit = 100;
	int64_t sz = 1000013;
	GenValues gen(limit, sz, 7);
	AddValues add_one(1, 3, gen);
	AddValues add_minus_one(-1, 5, add_one);
	Accumulate acc(add_minus_one);
	int64_t sum = 0;
	for (auto pel:PipeOutput(acc)) {
		Accumulate::TSUM *el = (Accumulate::TSUM*)pel;
		for (int i=0; i<acc.nth; i++)
			sum += el->sum[i];
	}
	EXPECT_TRUE(limit*sz*(limit*sz-1)/2 == sum);
}
