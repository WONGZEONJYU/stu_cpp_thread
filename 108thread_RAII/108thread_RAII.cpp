#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>

//Linux -lpthread
using namespace std;
using namespace chrono;
using namespace this_thread;

/*RAII*/
class XMutex
{
	XMutex(const XMutex&) = delete;
	XMutex& operator =(const XMutex&) = delete;

public:
	explicit XMutex(mutex& mux) :mux_{ mux } {
		cout << "Lock\n";
		mux.lock();
	}

	~XMutex()noexcept {
		cout << "Unlock\n";
		mux_.unlock();
	}

private:
	mutex& mux_;
};

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
		//lock_guard<mutex> lock(gmutex); /*�ٴ������׳��쳣*/
		lock_guard<mutex> lock(gmutex,adopt_lock);/*�����׳��쳣*/

		/*����lock_guard class���ذ�Ĺ��캯���������ٴ�����,ԭ����鿴Դ��*/
		/*��ͨ�������λ��׳��쳣���ݹ����Ͳ���*/
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
