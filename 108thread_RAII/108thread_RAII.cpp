#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "XMutex.h"

//Linux -lpthread
using namespace std;
using namespace chrono;
using namespace this_thread;

static mutex mux;

void TestMutex(const int status)
{
	XMutex lock(mux);
	
	if (1 == status){
		cout << "==1\n";
	}else {
		cout << "!=1\n";
	}
}

static mutex gmutex;

void TestLockGuard(const int i)
{
	gmutex.lock();

	{
		//lock_guard<mutex> lock(gmutex); /*再次锁，抛出异常*/
		lock_guard<mutex> lock(gmutex,adopt_lock);/*不会抛出异常*/

		/*调用lock_guard class重载版的构造函数，不会再次锁定,原理需查看源码*/
		/*普通锁锁两次会抛出异常，递归锁就不会*/
	}

	{
		lock_guard<mutex> lock(gmutex);
		cout << "begin thread" << i << "\n";
	}

	for (;;) {

		{
			lock_guard<mutex> lock(gmutex);
			cout << "In" << i << "\n";
		}
		sleep_for(milliseconds(500));
	}
}

int main(int argc, char* argv[])
{
	/*3 unique_lock 特性结合源码更好理解*/
	/*根据项目需求去选择哪一种*/
	{
		static mutex mux_1;
		{
			/*临时解锁，一般在容器转移数据的时候会用到*/
			unique_lock<mutex> lock(mux_1);
			/*unique_lock构造时会加锁，退出栈区会解锁（unique_lock析构时会释放锁）*/
			lock.unlock();/*临时释放锁，如果不再加锁，unique_lock析构不需要解锁*/
			lock.lock();
			
		}

		{
			mux_1.lock();
			unique_lock<mutex> lock(mux_1, adopt_lock);
			/*已经拥有锁 不锁定，退出栈区解锁（unique_lock析构时解锁）*/
		}

		{
			unique_lock<mutex> lock(mux_1, defer_lock);
			/*推迟加锁（延后加锁） 构造后不会去获得锁 退出栈区不解锁（unique_lock析构时不解锁）*/
			lock.lock();
			/*加锁，退出栈区解锁（unique_lock析构时会解锁）*/
		}

		{
			//mux_1.lock(); /*此处模拟被其他线程已经获得锁*/
			unique_lock<mutex> lock(mux_1,try_to_lock);
			/*尝试加锁 不阻塞 失败不拥有锁 退出栈区不解锁（unique_lock析构时不解锁）*/
			/*假如加锁成功 退出栈区解锁（unique_lock析构时解锁）*/
			if (lock.owns_lock() /*lock.operator bool()*/  /*lock*/ ) {
				cout << "owns_lock\n";
			}else {
				cout << "not owns_lock\n";
			}
		}
	}
	(void)getchar();

	/*2*/
	for (int i = 0; i < 3; i++){

		thread th(TestLockGuard, i + 1);
		th.detach();
	}
	(void)getchar();

	/*1*/
	TestMutex(1);
	TestMutex(2);
	(void)getchar();
	return 0;
}
