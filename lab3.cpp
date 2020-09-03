#include "lab3.h"
#include <windows.h> 
#include <stdio.h>

using namespace std;

#define THREADCOUNT 10


HANDLE MutexLock;

HANDLE threads[10];
DWORD thread_id;

HANDLE  semGH, semHI, semIG;

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

DWORD WINAPI thread_a(LPVOID param) {

	UNREFERENCED_PARAMETER(param);//j правилу мы должны передавать какой-то параметр в поток,но пользоваться этим не будем ,так что отвязываем 
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'a' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_b(LPVOID param) {

	UNREFERENCED_PARAMETER(param);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'b' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_c(LPVOID param) {
	UNREFERENCED_PARAMETER(param);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'c' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}


DWORD WINAPI thread_d(LPVOID param) {
	UNREFERENCED_PARAMETER(param);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'd' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_e(LPVOID param) {
	UNREFERENCED_PARAMETER(param);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'e' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	return TRUE;
}

DWORD WINAPI thread_f(LPVOID param) {
	UNREFERENCED_PARAMETER(param);
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'f' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}


	return TRUE;
}


DWORD WINAPI thread_g(LPVOID param) {
	UNREFERENCED_PARAMETER(param);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'g' << flush;
		ReleaseMutex(MutexLock);
		computation();
	}

	
	WaitForSingleObject(threads[3], INFINITE);
	WaitForSingleObject(threads[4], INFINITE);
	WaitForSingleObject(threads[5], INFINITE);
	
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(semIG, INFINITE);
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'g' << flush;
		ReleaseMutex(MutexLock);
		computation();
		ReleaseSemaphore(semGH, 1, NULL);
	}
	return TRUE;
}
DWORD WINAPI thread_h(LPVOID param) {
	UNREFERENCED_PARAMETER(param);


	for (int i = 0; i <3; i++) {
		WaitForSingleObject(semGH, INFINITE);
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'h' << flush;
		ReleaseMutex(MutexLock);
		computation();
		ReleaseSemaphore(semHI, 1, NULL);
	}

	return TRUE;
}
DWORD WINAPI thread_i(LPVOID param) {
	UNREFERENCED_PARAMETER(param);
	
	 
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(semHI, INFINITE);
		WaitForSingleObject(MutexLock, INFINITE);
		cout << 'i' << flush;
		ReleaseMutex(MutexLock);
		computation();
		ReleaseSemaphore(semIG, 1, NULL);
	}

	return TRUE;
}





DWORD WINAPI thread_k(LPVOID param) {
	UNREFERENCED_PARAMETER(param);
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
	
	semIG = CreateSemaphore(NULL, 1, 6, NULL);
	if (semIG == NULL) {
		cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}
	semHI = CreateSemaphore(NULL, 0, 6, NULL);
	if (semHI == NULL) {
		cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}
	semGH = CreateSemaphore(NULL, 0, 6, NULL);
	if (semGH == NULL) {
		cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}


	

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
	WaitForSingleObject(threads[3], INFINITE);
	WaitForSingleObject(threads[4], INFINITE);
	WaitForSingleObject(threads[5], INFINITE);
	threads[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &thread_id);
	if (threads[7] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	threads[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &thread_id);
	if (threads[8] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	WaitForSingleObject(threads[7], INFINITE);
	WaitForSingleObject(threads[8], INFINITE);
	WaitForSingleObject(threads[9], INFINITE);

	threads[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &thread_id);
	if (threads[9] == NULL) {
		cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
	WaitForMultipleObjects(10, threads, TRUE, INFINITE);
	
	CloseHandle(semIG);
	CloseHandle(semHI);
	CloseHandle(semGH);
	
	CloseHandle(MutexLock);


	
	for (int i = 0; i < 10; i++) {
		CloseHandle(threads[i]);
	}

	cout << endl;

	return 0;
	

}

