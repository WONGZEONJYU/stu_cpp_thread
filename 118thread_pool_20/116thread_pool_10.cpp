#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include "xthread_pool.h"
using namespace std;
using namespace this_thread;
using namespace chrono;

class MyTask:public XTask
{
public:
	int Run() override {
		cout << "================================================\n";
		cout << get_id() << " Mytask " << name << '\n';
		cout << "================================================\n";

		for (int i {}; i < 10; i++){
			if (is_exit()) {
				cout << "exit\n";
				break;
			}
			cout << "." << flush;
			sleep_for(milliseconds(500));
		}
		return 0;
	}
	string name {};
};

int main(int argc, char* argv[])
{
	XThreadPool pool;
	pool.Init(16);
	pool.Start();

	MyTask task1;
	task1.name = "test name 001";
	pool.AddTask(&task1);

	MyTask task2;
	task2.name = "test name 002";
	pool.AddTask(&task2);
	sleep_for(milliseconds(300));
	cout << "task run count = " << pool.task_run_count() << "\n";

	sleep_for(seconds(1));
	pool.Stop();

	cout << "task run count = " << pool.task_run_count() << "\n";
	_CRT_UNUSED(getchar());
	return 0;
}

