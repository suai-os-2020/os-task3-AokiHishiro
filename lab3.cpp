﻿#include "lab3.h"
#include <windows.h> 
#include <stdio.h>
using namespace std;
#define THREADCOUNT 5
HANDLE Thread[THREADCOUNT];
HANDLE Mutex;
HANDLE SemG, SemH, SemI;
unsigned int lab3_thread_graph_id()
{
	return 12;
}
const char* lab3_unsynchronized_threads()
{
	return "defg";
}
const char* lab3_sequential_threads()
{
	return "ghi";
}
DWORD WINAPI threads_unsynchronized(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}
DWORD WINAPI thread_g(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemG, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemH, 1, NULL);
	}
	return 0;
}
DWORD WINAPI thread_h(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemH, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemI, 1, NULL);
	}
	return 0;
}
DWORD WINAPI thread_i(LPVOID text)
{
	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(SemI, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemG, 1, NULL);
	}
	return 0;
}
int lab3_init()
{
	DWORD ThreadID;
	Mutex = CreateMutex(NULL, FALSE, NULL);
	if (Mutex == NULL)
	{
		cout << "CreateMutex error " << GetLastError() << endl;
		return 1;
	}
	SemG = CreateSemaphore(NULL, 1, 1, NULL);
	if (SemG == NULL)
	{
		cout << "CreateSemaphore error: SemE" << GetLastError() << endl;
		return 1;
	}
	SemH = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemG == NULL)
	{
		cout << "CreateSemaphore error: SemH " << GetLastError() << endl;
		return 1;
	}
	SemI = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemG == NULL)
	{
		cout << "CreateSemaphore error: SemI" << GetLastError() << endl;
		return 1;
	}
	char const* textsA = "a";
	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsA, 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error: " << textsA << GetLastError() << endl;
		return 1;
	}
	WaitForSingleObject(Thread[0], INFINITE);
	int count = 0;
	char const* textsBC[] = { "b","c" };
	for (int i = 0; i < 2; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsBC[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsBC[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}
	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}
	count = 0;
	char const* textsDEFG[] = { "d", "e", "f","g" };
	for (int i = 0; i < 4; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsDEFG[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsDEFG[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}
	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}
	count = 0;
	char const* textsGHI[] = { "g", "h", "i" };
	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_g, (void*)textsGHI[0], 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error:  " << textsDEFG[0] << GetLastError() << endl;
		return 1;
	}
	Thread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_h, (void*)textsGHI[1], 0, &ThreadID);
	if (Thread[1] == NULL)
	{
		cout << "CreateThread error:  " << textsDEFG[1] << GetLastError() << endl;
		return 1;
	}
	Thread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_i, (void*)textsGHI[2], 0, &ThreadID);
	if (Thread[2] == NULL)
	{
		cout << "CreateThread error:  " << textsDEFG[2] << GetLastError() << endl;
		return 1;
	}
	for (int i = 0; i < 3; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}
	char const* textsK = "k";
	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsK, 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error: " << textsK << GetLastError() << endl;
		return 1;
	}
	WaitForSingleObject(Thread[0], INFINITE);
	for (int i = 0; i < THREADCOUNT; ++i) {
		CloseHandle(Thread[i]);
	}

	CloseHandle(SemG);
	CloseHandle(SemH);
	CloseHandle(SemI);
	CloseHandle(Mutex);
	cout << endl;

	return 0;

}