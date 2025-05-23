#pragma once
#ifndef X_TASK_HPP
#define X_TASK_HPP

#include <functional>
#include <future>

namespace xtd {
	class XTask {

		void set_exit_func(auto && f) {
			m_is_exit_ = f;
		}

		void set_return(const int64_t &v){
			m_promise_.set_value(v);
		}

		virtual int64_t Run() {return 0;}
		[[nodiscard]] virtual int64_t Run() const {return 0;}

		void swap_(XTask &);

	public:
		auto get_return() {
			return m_promise_.get_future().get();
		}

	protected:
		std::function<bool()> m_is_exit_{};
	private:
		std::promise<int64_t> m_promise_{};
	protected:
		explicit XTask() = default;
	public:
		XTask(const XTask&) = delete;
		XTask& operator=(const XTask&) = delete;

		XTask(XTask &&) noexcept;
		XTask &operator=(XTask &&) noexcept;

		virtual ~XTask() = default;
		friend class XThreadPool;
	};

}

#endif
