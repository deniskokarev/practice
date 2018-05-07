#ifndef __PAR_HH__
#define __PAR_HH__

/**
 * Parallel execution primitives
 * @author Denis Kokarev
 */
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

/**
 * Simple parallel execution. Start n threads and have them all run their exec_slice()
 * in the loop. All exec_slice()es executed once for every exec() command
 * Derive your class, add data fields and overload exec_slice(n).
 * Threads created at constructor and joined at destructor.
 */
class ParallelExec {
protected:
	int nthreads;
private:
	// marching tick for threads
	int tick;
	// pre-spawn this many threads
	std::vector<std::thread> threads;
	// number of active threads on this batch
	int active_cnt;
	// threads wait on this cv to start the batch
	std::mutex mtx_begin;
	std::condition_variable cv_begin;
	// threads notify this cv at the end of batch
	std::mutex mtx_end;
	std::condition_variable cv_end;
	void threads_go();
	void threads_wait();
	void threads_done();
	static void run_thread(ParallelExec *th, int n);
	void run(int n);
protected:
	virtual void exec_slice(int n) = 0;
	ParallelExec(int nthreads);
	~ParallelExec();
	void exec();
};

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
 * Each conveyor element may use 'batch' counter to determine which copy
 * of the result to work on this iteration
 */
class PipeStageExec;
class PipeOutputIterator;

class PipeHeadExec {
	friend PipeStageExec;
	friend PipeOutputIterator;
protected:
	int batch;
private:
	bool go;
	bool done;
	bool abort;
	int depth;
	void *last_arg;
	std::mutex mtx;
	std::condition_variable cv;
	void thread_wait_go();
	void thread_notify_go();
	void thread_notify_abort();
	void thread_wait_done();
	void thread_notify_done();
	virtual void run();
	virtual void *next() = 0;
public:
	PipeHeadExec();
};

class PipeStageExec: public PipeHeadExec {
	friend PipeOutputIterator;
private:
	PipeHeadExec &parent;
	std::thread thread;
	static void run_thread(PipeHeadExec *th);
	virtual void run() override;
	virtual void *next() override final;
protected:
	virtual void *next(void *arg) = 0;
public:
	PipeStageExec(PipeHeadExec &parent);
	~PipeStageExec();
};

class PipeOutput;

class PipeOutputIterator {
	friend PipeOutput;
protected:
	PipeStageExec &tail;
	void *value;
	PipeOutputIterator &seek_begin();
	PipeOutputIterator &seek_end();
public:
	PipeOutputIterator(PipeStageExec &tail);
	bool operator==(const PipeOutputIterator &b) const;
	bool operator!=(const PipeOutputIterator &b) const;
	void operator++();
	void *operator*() const;
};

class PipeOutput: public PipeStageExec {
protected:
	virtual void *next(void *arg) override final;
	PipeOutputIterator begin_it;
	PipeOutputIterator end_it;
public:
	PipeOutput(PipeHeadExec &parent);
	PipeOutputIterator &begin();
	PipeOutputIterator &end();
};

#endif // __PAR_HH__
