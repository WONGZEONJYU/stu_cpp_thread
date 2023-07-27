#ifndef XTASK_H
#define XTASK_H
#include <functional>

class XTask
{
public:
	virtual int Run() = 0;
	std::function<bool()> is_exit{};
};

#endif

