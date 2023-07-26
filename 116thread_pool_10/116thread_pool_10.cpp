#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include "xthread_pool.h"

using namespace std;
using namespace this_thread;
using namespace chrono;

int main(int argc, char* argv[])
{
	XThreadPool pool;
	pool.Init(16);
	pool.Start();
	_CRT_UNUSED(getchar());
	return 0;
}

