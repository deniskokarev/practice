/**
 * @author Denis Kokarev
 */
#include "par.hh"

/**
 * Simple parallel execution.
 * Derive from it and overload exec_slice(n). To run all the slices in parallel use exec()
 * Threads created at constructor and joined at destructor.
 */
void ParallelExec::threads_go() {
	std::lock_guard<std::mutex> lck(mtx_begin);
	tick++;
	active_cnt += nthreads;
	cv_begin.notify_all();
}

void ParallelExec::threads_wait() {
	std::unique_lock<std::mutex> lck(mtx_end);
	while (active_cnt > 0)
		cv_end.wait(lck);
}

void ParallelExec::threads_done() {
	std::lock_guard<std::mutex> lck(mtx_begin);
	tick++;
	active_cnt--; // go below 0 to finish
	cv_begin.notify_all();
}

void ParallelExec::run_thread(ParallelExec *th, int n) {
	th->run(n);
}

void ParallelExec::run(int n) {
	int local_tick = 0;
	int local_active_cnt;
	while (true) {
		// wait for new data from producer
		{
			std::unique_lock<std::mutex> lck(mtx_begin);
			while (tick == local_tick)
				cv_begin.wait(lck);
			local_tick = tick;
			local_active_cnt = active_cnt;
		}
		if (local_active_cnt > 0) {
			// process this batch and notify producer
			exec_slice(n);
			{
				std::lock_guard<std::mutex> lck(mtx_end);
				active_cnt--;
				cv_end.notify_one();
			}
		} else {
			// quit
			break;
		}
	}
}

ParallelExec::ParallelExec(int nthreads):nthreads(nthreads),tick(0),threads(nthreads),active_cnt(0) {
	for (int i=0; i<nthreads; i++)
		threads[i] = std::thread(run_thread, this, i);
}

ParallelExec::~ParallelExec() {
	threads_done();
	for (auto &t: threads)
		t.join();
}

void ParallelExec::exec() {
	threads_go();
	threads_wait();
}

/**
 * Parallel conveyor primitives
 * PipeHeadExec > PipeStageExec > PipeOutput -+
 *                                            +-> PipeOutputIterator
 *
 * Derive your own Head and Stages. Arguments are passed by reference. Therefore
 * each converor element is responsible for storing at least 2 instances of results
 * so that the next stage can always access the previously obtained result. 1 instance
 * of the result for prior execution and 1 for current execution thus
 * allowing parallel operation. If the result needs to be passed to the stage after the
 * following then 3 instances of the result have to be stored.
 *
 * PipeHeadExec requires overloading void *next() method which returns a pointer
 * to next portion of the data or nullptr
 * 
 * PipeStageExec requires overloading void *next(void *arg) method
 *
 * PipeOutput is used to obtain PipeOutputIterator. Every increment
 * on PipeOutputIterator advances all members of the converor. Iterator holds
 * the result of last void *next(void *arg) of the conveyor pipeline
 *
 * Each conveyor element may use 'batch' variable to determine which copy
 * of the result to work on this iteration
 */
void PipeHeadExec::thread_wait_go() {
	std::unique_lock<std::mutex> lck(mtx);
	while (!go)
		cv.wait(lck);
}

void PipeHeadExec::thread_notify_go() {
	std::lock_guard<std::mutex> lck(mtx);
	go = true;
	cv.notify_one();
}

void PipeHeadExec::thread_notify_abort() {
	std::lock_guard<std::mutex> lck(mtx);
	go = true;
	abort = true;
	cv.notify_one();
}

void PipeHeadExec::thread_wait_done() {
	std::unique_lock<std::mutex> lck(mtx);
	while (go)
		cv.wait(lck);
}

void PipeHeadExec::thread_notify_done() {
	std::lock_guard<std::mutex> lck(mtx);
	go = false;
	cv.notify_one();
}

void PipeHeadExec::run() {
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

PipeHeadExec::PipeHeadExec() {
	batch = 0;
	go = false;
	done = false;
	abort = false;
	depth = 0;
	last_arg = nullptr;
}

void PipeStageExec::run_thread(PipeHeadExec *th) {
	th->run();
}

void PipeStageExec::run() {
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

void *PipeStageExec::next() {
	return nullptr;
}

PipeStageExec::PipeStageExec(PipeHeadExec &parent):PipeHeadExec(),parent(parent) {
	depth = parent.depth+1;
	thread = std::thread(run_thread, &parent);
}

PipeStageExec::~PipeStageExec() {
	parent.thread_notify_abort();
	thread.join();
}

PipeOutputIterator::PipeOutputIterator(PipeStageExec &tail):tail(tail),value(nullptr) {
}

bool PipeOutputIterator::operator==(const PipeOutputIterator &b) const {
	return value == b.value;
}

bool PipeOutputIterator::operator!=(const PipeOutputIterator &b) const {
	return value != b.value;
}

PipeOutputIterator &PipeOutputIterator::seek_begin() {
	while (!tail.parent.done && tail.parent.batch<=tail.parent.depth) {
		tail.parent.thread_notify_go();
		tail.parent.thread_wait_done();
	}
	value = tail.parent.last_arg;
	tail.parent.thread_notify_go();
	return *this;
}

PipeOutputIterator &PipeOutputIterator::seek_end() {
	value = nullptr;
	return *this;
}

void PipeOutputIterator::operator++() {
	tail.parent.thread_wait_done();
	value = tail.parent.last_arg;
	if (!tail.parent.done) {
		tail.parent.thread_notify_go();
	} else {
		value = nullptr;
	}
}

void *PipeOutputIterator::operator*() const {
	return value;
}

void *PipeOutput::next(void *arg) {
	return nullptr;
}

PipeOutput::PipeOutput(PipeHeadExec &parent):PipeStageExec(parent),
											 begin_it(PipeOutputIterator(*this)),
											 end_it(PipeOutputIterator(*this))
{
}

PipeOutputIterator &PipeOutput::begin() {
	return begin_it.seek_begin();
}

PipeOutputIterator &PipeOutput::end() {
	return end_it.seek_end();
}
