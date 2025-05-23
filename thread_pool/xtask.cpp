#include "xtask.hpp"

namespace xtd {
    void XTask::swap_(XTask &obj) {
        std::swap(m_is_exit_,obj.m_is_exit_);
        std::swap(m_promise_,obj.m_promise_);
    }

    XTask::XTask(XTask&& obj) noexcept:
        m_is_exit_{ std::move(obj.m_is_exit_) },
        m_promise_{ std::move(obj.m_promise_) } {}

    XTask & XTask::operator=(XTask &&obj) noexcept {
        XTask(std::move(obj)).swap_(*this);
        return *this;
    }
}
