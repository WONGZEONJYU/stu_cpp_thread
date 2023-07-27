#ifndef _XTHREAD_POOL_H
#define _XTHREAD_POOL_H
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <atomic>
#include <memory>
#include "xtask.h"

class XThreadPool
{
	XThreadPool(const XThreadPool&) = delete;
	XThreadPool& operator=(const XThreadPool&) = delete;

public:
	explicit XThreadPool() = default;
	/*@parm num thread_num*/
	void Init(int num);
	/*Call init before calling start*/
	void Start();
	/*Add Task @parm task pointer */

	void Stop();

	void AddTask(XTask* task);

	bool is_exit() const { return is_exit_; }

	int task_run_count() const { return task_run_count_; }

private:
	XTask* GetTask();
	void Run();
	
	std::mutex mux_;
	std::vector<std::thread*> threads_;
	std::list<XTask*> tasks_;
	std::condition_variable cv_;
	/*number of running tasks*/
	std::atomic<int> task_run_count_{};

	int thread_num_{};
	bool is_exit_{};
	
};

#endif
