#ifndef _XTHREAD_POOL_HPP
#define _XTHREAD_POOL_HPP

#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <atomic>
#include <memory>

class XTask;

class XThreadPool {
	std::shared_ptr<XTask> get_Task();
	void Run();
public:
	XThreadPool(const XThreadPool&) = delete;
	XThreadPool& operator=(const XThreadPool&) = delete;

	explicit XThreadPool() = default;

	/*
	 * 线程池数量
	 */
	void Init(const uint64_t &num = std::thread::hardware_concurrency());

	void Start();

	void Stop();

	void add_Task(const std::shared_ptr<XTask> &);

	inline auto is_exit() const{ return m_is_exit_.load(); }

	inline auto task_run_count() const{ return task_run_count_.load(); }

	virtual ~XThreadPool() { Stop(); }

private:
	std::mutex m_mux_{};
	std::vector<std::shared_ptr<std::thread>> m_threads_{};
	std::list< std::shared_ptr<XTask> > m_tasks_{};
	std::condition_variable m_cv_{};
	std::atomic_uint64_t m_thread_num_{},task_run_count_ {};
	std::atomic_bool m_is_exit_{};
};

#endif
