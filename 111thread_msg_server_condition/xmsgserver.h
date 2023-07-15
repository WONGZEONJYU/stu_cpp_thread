#ifndef XMSGSERVER_H
#define XMSGSERVER_H

#include "xthread.h"
#include <string>
#include <list>
#include <mutex>

class XMsgServer:public XThread
{
public:
	/*给当前线程发消息*/
	void SendMsg(const std::string& msg);
	virtual void Stop() override;
private:
	/*处理消息的线程入口函数*/
	virtual void Main() override;
	/*消息队列缓冲区*/
	std::list<std::string> msgs_;
	/*互斥访问消息队列*/
	std::mutex mux_;
	/*条件变量*/
	std::condition_variable cv_;
};

#endif // XMSGSERVER_H
