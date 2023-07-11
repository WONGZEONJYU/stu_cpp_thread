#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>

//Linux -lpthread
using namespace std;
using namespace chrono;
using namespace this_thread;

/*c++17*/
//static shared_mutex smux;
/*c++14*/
static shared_timed_mutex stmux;

void ThreadRead(const int x)
{
	for (;;) {
		stmux.lock_shared();
		cout << x << "Read\n";
		sleep_for(milliseconds(500));
		stmux.unlock_shared();
		sleep_for(milliseconds(1));
	}
}

void ThreadWrite(const int x)
{
	for (;;) {

		stmux.lock_shared();
		/*��ȡ����*/
		stmux.unlock_shared();
		/*�����ȡ��û���ͷţ����������޷���ȡ������Դ��*/

		stmux.lock();/*������ ��Ҫ���ٽ���Դ����д�룬���̵߳���*/
		stmux.unlock();



	}
}

int main(int argc, char* argv[])
{




	(void)getchar();
	return 0;
}
