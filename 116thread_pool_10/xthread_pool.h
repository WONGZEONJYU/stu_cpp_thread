#ifndef _XTHREAD_POOL_H
#define _XTHREAD_POOL_H
#include <thread>
#include <mutex>
#include <vector>

class XThreadPool
{
	XThreadPool(const XThreadPool&) = delete;
	XThreadPool& operator=(const XThreadPool&) = delete;

public:
	explicit XThreadPool() = default;
	/*@parm num thread_num*/
	void Init(int num);
	/*Start thread*/
	void Start();
private:
	void Run();
	int thread_num_{};
	std::mutex mux_;
	std::vector<std::thread*> threads_;
};

#endif
