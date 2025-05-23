#pragma once
#ifndef X_ABSTRACT_TASK_HPP
#define X_ABSTRACT_TASK_HPP 1

namespace xtd {
    class XAbstractTask {

    protected:
        XAbstractTask() = default;
        virtual ~XAbstractTask() = default;

    public:
        XAbstractTask(const XAbstractTask&) = delete;
        XAbstractTask& operator=(const XAbstractTask&) = delete;

    private:

    };
}

#endif
