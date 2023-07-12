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
	/*3 unique_lock ���Խ��Դ��������*/
	/*������Ŀ����ȥѡ����һ��*/
	{
		static mutex mux_1;
		{
			/*��ʱ������һ��������ת�����ݵ�ʱ����õ�*/
			unique_lock<mutex> lock(mux_1);
			/*unique_lock����ʱ��������˳�ջ���������unique_lock����ʱ���ͷ�����*/
			lock.unlock();/*��ʱ�ͷ�����������ټ�����unique_lock��������Ҫ����*/
			lock.lock();
			
		}

		{
			mux_1.lock();
			unique_lock<mutex> lock(mux_1, adopt_lock);
			/*�Ѿ�ӵ���� ���������˳�ջ��������unique_lock����ʱ������*/
		}

		{
			unique_lock<mutex> lock(mux_1, defer_lock);
			/*�Ƴټ������Ӻ������ ����󲻻�ȥ����� �˳�ջ����������unique_lock����ʱ��������*/
			lock.lock();
			/*�������˳�ջ��������unique_lock����ʱ�������*/
		}

		{
			//mux_1.lock(); /*�˴�ģ�ⱻ�����߳��Ѿ������*/
			unique_lock<mutex> lock(mux_1,try_to_lock);
			/*���Լ��� ������ ʧ�ܲ�ӵ���� �˳�ջ����������unique_lock����ʱ��������*/
			/*��������ɹ� �˳�ջ��������unique_lock����ʱ������*/
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
