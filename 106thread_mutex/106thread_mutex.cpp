#include <thread>
#include <iostream>
#include <string>
#include <mutex>

//Linux -lpthread
using namespace std;
using namespace chrono;
using namespace this_thread;

static mutex mux;

void TestThread()
{
	for (;;) {

		//mux.lock();	/*获取锁资源，如果获取不成功则阻塞等待*/

		if (!mux.try_lock()){	/*
									尝试获得锁，假如获取成功返回true,否则返回false，
									并不会阻塞线程,但仍然需释放
								*/
			cout << "." << flush;
			sleep_for(chrono::milliseconds(100));
			continue;
		}
		cout << "===============================================" << endl;
		cout << "test 001" << endl;
		cout << "test 002" << endl;
		cout << "test 003" << endl;
		cout << "===============================================" << endl;
		mux.unlock();
		sleep_for(chrono::milliseconds(1000));
	}
}

void ThreadMainMux(int x)
{
	for (;;) {
		mux.lock();
		cout << x << "[in]\n";
		sleep_for(chrono::milliseconds(1000));
		mux.unlock();/*操作系统不会马上释放这个锁*/
		sleep_for(chrono::milliseconds(1));

		/*
			分析：
				如果按照期望，1号线程获取锁资源，2号3号线程在等待，
				当1号线程释放锁资源，按道理2号3号线程随便一个线程获得锁资源，lock()马上返回，
				开始“做事”。可是操作系统并不是马上释放掉这个锁资源，
				操作系统还会认定你获取了这个锁资源，有一个时间差
				然而unlock()与lock()调用之间相差的时间很短很短，它就会再次进来
		*/

		/*
			解决办法：
				在unlock()之后，加一点点延时去让操作系统有这个时间去释放这个锁资源，
				如果unlock()之后，往下还有业务逻辑需要操作，有可能就不需要这个延时，
				需要和不需要看有没有出现问题。
		*/
	}
}

int main(int argc, char* argv[])
{
	for (int i{}; i < 3; i++) {

		thread th(ThreadMainMux, i + 1 );
		th.detach();
	}
	(void)getchar();

	for (int i{}; i < 10; i++){
		thread th(TestThread);
		th.detach();
	}
	(void)getchar();

	return 0;
}

