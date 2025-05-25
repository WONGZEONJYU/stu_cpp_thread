#include "xabstracttask.h"

namespace xtd {

    void XAbstractTask::swap(XAbstractTask &rhs) {
        std::swap(m_is_exit_,rhs.m_is_exit_);
        std::swap(m_return_,rhs.m_return_);
    }

    XAbstractTask::XAbstractTask(XAbstractTask &&rhs) noexcept:
    m_is_exit_{std::move(rhs.m_is_exit_)},
    m_return_{std::move(rhs.m_return_)} {}

    XAbstractTask &XAbstractTask::operator=(XAbstractTask &&rhs) noexcept {
        XAbstractTask(std::move(rhs)).swap(*this);
        return *this;
    }
}
