#include <iostream>
#include <thread>
#include "xthread_pool.h"
#include "xvideo_task.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

/*��������Ƶת�빤��*/
/*ffmpeg����*/
/*�û����� ��ƵԴ �����Ƶ�ߴ�*/
/*���̳߳���ִ��ת������*/
/*ת���������ffmpeg*/
/*	ffmpeg -y -i test.mp4 -s 400x300 400.mp4 >log.txt 2>&1	*/

int main(int argc, char* argv[])
{
	XThreadPool pool;
	pool.Init(16);
	pool.Start();

	auto vtask1{ make_shared<XVideoTask>() };
	vtask1->in_path = "test.mp4";
	vtask1->out_path = "640.mp4";
	vtask1->width = 640;
	vtask1->height = 480;
	pool.AddTask(vtask1);
	auto re{ vtask1->GetReturn() };
	std::cout << "vtask1->GetReturn() = " << re << "\n";
	
	//_CRT_UNUSED(getchar());
	return 0;
}

