#pragma once
#ifndef XVIDEO_TASK_H
#define XVIDEO_TASK_H

#include "xtask.hpp"

class XVideoTask final :public XTask
{
public:
	std::string in_path{}, out_path{};
	int width{}, height{};
private:
	[[nodiscard]] int64_t Run() const override;
};

#endif
