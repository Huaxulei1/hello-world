// Expand.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "windows.h"
using namespace std;

typedef void (*PINIT)(const unsigned long long a, const unsigned long long b);
typedef bool (*PNEXT)();
typedef unsigned long long (*PCURRENT)();
typedef unsigned (*PINDEX)();


int main()
{
	HMODULE hDLL = LoadLibrary(L"MathLibrary1.dll");
	if (hDLL == NULL) {
		cout << "获取动态链接库失败!";
		return 0;
	}
	PINIT fibonacci_init = (PINIT)GetProcAddress(hDLL, "fibonacci_init");
	PNEXT fibonacci_next = (PNEXT)GetProcAddress(hDLL, "fibonacci_next");
	PCURRENT fibonacci_current = (PCURRENT)GetProcAddress(hDLL, "fibonacci_current");
	PINDEX fibonacci_index = (PINDEX)GetProcAddress(hDLL, "fibonacci_index");

	//Initialize a Fibonacci relation sequence.
	fibonacci_init(1, 1);
	//Write out the sequence values until overflow.
	do {
		std::cout << fibonacci_index() << ": "
			<< fibonacci_current() << std::endl;
	} while (fibonacci_next());
	//Report count of values written before overflow.
	std::cout << fibonacci_index() + 1 <<
		" Fibonacci sequence values fit in an " <<
		"unsigned 64-bit integer." << std::endl;
	/*if (fibonacci_init != null)
	{
		printf("");
		fibonacci_init(20,10);
	}*/

	FreeLibrary(hDLL);
	return 0;
}
