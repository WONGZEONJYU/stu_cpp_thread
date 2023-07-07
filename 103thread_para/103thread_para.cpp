#include <thread>
#include <iostream>
#include <string>

using namespace std;
using namespace this_thread;
using namespace chrono;

void ThreadMain(int p1, float p2, string str)
{
	cout << "id: " << get_id() << "\n";
	cout << "ThreadMain parameter:" << p1 << " " << p2 << " " << str << "\n";
}

int main(int argc,char* argv[])
{
	thread th;
	{
		float f1{ 12.1f };
		/*所有的参数做复制*/
		th = thread(ThreadMain, 101, f1, "test string para");
	}
	th.join();
	return 0;
}
