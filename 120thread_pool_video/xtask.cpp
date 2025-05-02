#include "xtask.hpp"

XTask::XTask(XTask&& obj) noexcept:
    is_exit{ std::move(obj.is_exit) },
    m_promise_{ std::move(obj.m_promise_) } {}

XTask & XTask::operator=(XTask &&obj) noexcept {

    if (std::addressof(obj) != this) {
        is_exit = std::move(obj.is_exit);
        m_promise_ = std::move(obj.m_promise_);
    }

    return *this;
}
