#include <iostream>
#include <thread>
#include "xthread_pool.hpp"
#include "xvideo_task.hpp"

using namespace std;
using namespace chrono;
using namespace this_thread;

int main(const int argc,const char* argv[]){

	XThreadPool pool;
	pool.Init(thread::hardware_concurrency());
	pool.Start();
	sleep_for(200ms);

	while (true){
		sleep_for(200ms);
		cout << "\n=======================================================\n";
		cout << "Please enter the command(v , e , l) :\n";
		string cmd;
		cin >> cmd;

		if ("e" == cmd){
			break;
		}else if ("l" == cmd) {
			cout << "task run count = " << pool.task_run_count() << '\n';
			continue;
		}else{}

		const auto task{ make_shared<XVideoTask>() };
		cout << "video source :\n";
		cin >> task->in_path;
		cout << "video target :\n";
		cin >> task->out_path;
		cout << "output width :\n";
		cin >> task->width;
		cout << "output height :\n";
		cin >> task->height;
		pool.add_Task(task);
	}

#if 0
	auto vtask1{ make_shared<XVideoTask>() };
	vtask1->in_path = "test.mp4";
	vtask1->out_path = "640.mp4";
	vtask1->width = 640;
	vtask1->height = 480;
	pool.AddTask(vtask1);
	auto re{ vtask1->GetReturn() };
	std::cout << "vtask1->GetReturn() = " << re << "\n";
	cout << "end\n";
#endif
	getchar();
	return 0;
}

