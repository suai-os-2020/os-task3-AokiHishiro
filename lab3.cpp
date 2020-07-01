#include "lab3.h"
#include <windows.h> 
#include <stdio.h>

using namespace std;

#define THREADCOUNT 3


HANDLE MutexLock;
HANDLE semStart;
HANDLE threads[3];
DWORD thread_id;

HANDLE SemB, SemC;

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

DWORD WINAPI thread_a(LPVOID) {
	WaitForSingleObject(semStart, INFINITE);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'a' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_b(LPVOID) {

	WaitForSingleObject(threads[0], INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'b' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	ReleaseSemaphore(SemB, 1, NULL);

	return TRUE;
}

DWORD WINAPI thread_c(LPVOID) {

	WaitForSingleObject(threads[0], INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'c' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	ReleaseSemaphore(SemC, 1, NULL);

	return TRUE;
}


DWORD WINAPI thread_k(LPVOID) {
	WaitForSingleObject(threads[1], INFINITE);
	WaitForSingleObject(threads[2], INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'k' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

int lab3_init()
{
	DWORD ThreadID;

	MutexLock = CreateMutex(NULL, FALSE, NULL);
	if (MutexLock == NULL)
	{
		cout << "CreateMutex error " << GetLastError() << endl;
		return 1;
	}
	semStart = CreateSemaphore(NULL, 1, 6, NULL);
	if (semStart == NULL) {
		cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}
	SemC = CreateSemaphore(NULL, 0, 6, NULL);
	if (SemC == NULL) {
		cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}
	SemB = CreateSemaphore(NULL, 0, 6, NULL);
	if (SemB == NULL) {
		cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

	threads[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	threads[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	threads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	WaitForSingleObject(threads[1], INFINITE);
	WaitForSingleObject(threads[2], INFINITE);


	CloseHandle(SemB);
	CloseHandle(SemC);
	CloseHandle(MutexLock);

	for (int i = 0; i < 3; i++) {
		CloseHandle(threads[i]);
	}


	return 0;

}
