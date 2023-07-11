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

		//mux.lock();	/*��ȡ����Դ�������ȡ���ɹ��������ȴ�*/

		if (!mux.try_lock()){	/*
									���Ի�����������ȡ�ɹ�����true,���򷵻�false��
									�����������߳�,����Ȼ���ͷ�
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
		mux.unlock();/*����ϵͳ���������ͷ������*/
		sleep_for(chrono::milliseconds(1));

		/*
			������
				�������������1���̻߳�ȡ����Դ��2��3���߳��ڵȴ���
				��1���߳��ͷ�����Դ��������2��3���߳����һ���̻߳������Դ��lock()���Ϸ��أ�
				��ʼ�����¡������ǲ���ϵͳ�����������ͷŵ��������Դ��
				����ϵͳ�����϶����ȡ���������Դ����һ��ʱ���
				Ȼ��unlock()��lock()����֮������ʱ��̺̣ܶܶ����ͻ��ٴν���
		*/

		/*
			����취��
				��unlock()֮�󣬼�һ�����ʱȥ�ò���ϵͳ�����ʱ��ȥ�ͷ��������Դ��
				���unlock()֮�����»���ҵ���߼���Ҫ�������п��ܾͲ���Ҫ�����ʱ��
				��Ҫ�Ͳ���Ҫ����û�г������⡣
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

