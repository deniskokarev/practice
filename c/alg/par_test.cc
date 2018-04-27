#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>

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
	virtual void *next() override final {
		return nullptr;
	}
protected:
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
	virtual void *next(void *arg) override {
		int stage = batch%stages;
		PIPE_ELEMENT *parent_el = (PIPE_ELEMENT*)arg;
		el[stage] = *parent_el;
		el[stage].label = label[parent_el->category];
		return &el[stage];
	}
public:
	using PipeStageExec::PipeStageExec;
};

int main(int argc, char **argv) {
	GenStage generate(1);
	CategorizeStage categorize(generate);
	LabelStage label(categorize);
	for (auto pel:PipeOutput(label)) {
		PIPE_ELEMENT *el = (PIPE_ELEMENT*)pel;
		fprintf(stdout, "num=%d, category=%d, label=%s\n", el->num, el->category, el->label);
	}
}
