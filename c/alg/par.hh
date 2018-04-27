#include <thread>
#include <mutex>
#include <condition_variable>

class PipeStageExec;
class PipeTailExec;

class PipeHeadExec {
	friend PipeStageExec;
	friend PipeTailExec;
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
	void thread_wait_go();
	void thread_notify_go();
	void thread_notify_abort();
	void thread_wait_done();
	void thread_notify_done();
	virtual void run();
	virtual void *get() = 0;
public:
	PipeHeadExec();
};

class PipeStageExec: public PipeHeadExec {
	friend PipeTailExec;
private:
	PipeHeadExec &parent;
	std::thread thread;
	virtual void run() override;
	virtual void *get() override final;
protected:
	virtual void *map(void *arg) = 0;
public:
	PipeStageExec(PipeHeadExec &parent);
	~PipeStageExec();
};

class PipeTailExec: public PipeStageExec {
private:
	virtual void *map(void *arg) override final;
protected:
	virtual void proc(void *arg) = 0;
public:
	using PipeStageExec::PipeStageExec;
	virtual void run() override;
};
