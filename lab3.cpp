#include "lab3.h"
#include <windows.h> 
#include <stdio.h>

using namespace std;

#define THREADCOUNT 7


HANDLE MutexLock;
HANDLE semStart;
HANDLE threads[7];
DWORD thread_id;

HANDLE;

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

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'a' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_b(LPVOID) {

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'b' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_c(LPVOID) {

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'c' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}


DWORD WINAPI thread_d(LPVOID) {

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'd' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_e(LPVOID) {

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'e' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_f(LPVOID) {

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'f' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}


	return TRUE;
}


DWORD WINAPI thread_g(LPVOID) {

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'g' << flush;
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

	WaitForSingleObject(semStart, INFINITE);

	threads[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	WaitForSingleObject(threads[0], INFINITE);
	threads[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &thread_id);
	if (threads[1] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	threads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &thread_id);
	if (threads[2] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	WaitForSingleObject(threads[1], INFINITE);
	WaitForSingleObject(threads[2], INFINITE);
	threads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &thread_id);
	if (threads[3] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	threads[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &thread_id);
	if (threads[4] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	threads[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &thread_id);
	if (threads[5] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	threads[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &thread_id);
	if (threads[6] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

	WaitForMultipleObjects(7, threads, TRUE, INFINITE);
	CloseHandle(semStart);

	CloseHandle(MutexLock);

	for (int i = 0; i < 7; i++) {
		CloseHandle(threads[i]);
	}


	return 0;

}
