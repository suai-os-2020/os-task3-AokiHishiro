#include "lab3.h"
#include <windows.h> 
#include <stdio.h>

using namespace std;

#define THREADCOUNT 5

HANDLE Thread[THREADCOUNT];
HANDLE Mutex;
HANDLE SemE, SemH, SemI;

unsigned int lab3_thread_graph_id()
{
	return 16;
}

const char* lab3_unsynchronized_threads()
{
	return "bcef";
}

const char* lab3_sequential_threads()
{
	return "ehi";
}

DWORD WINAPI threads_unsynchronized(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI thread_e(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemE, INFINITE);
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
	for (int i = 0; i < 3; ++i)
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
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemI, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemE, 1, NULL);
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

	SemE = CreateSemaphore(NULL, 1, 1, NULL);
	if (SemE == NULL)
	{
		cout << "CreateSemaphore error: SemE" << GetLastError() << endl;
		return 1;
	}

	SemH = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemE == NULL)
	{
		cout << "CreateSemaphore error: SemH " << GetLastError() << endl;
		return 1;
	}

	SemI = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemE == NULL)
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
	char const* textsBCEF[] = { "b","c","e","f" };

	for (int i = 0; i < 4; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsBCEF[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsBCEF[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsBDEFG[] = { "b", "d", "e", "f","g" };

	for (int i = 0; i < 4; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsBDEFG[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsBDEFG[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}


	count = 0;

	char const* textsEHI[] = { "e", "h", "i" };

	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_e, (void*)textsEHI[0], 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error:  " << textsBDEFG[0] << GetLastError() << endl;
		return 1;
	}
	Thread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_h, (void*)textsEHI[1], 0, &ThreadID);
	if (Thread[1] == NULL)
	{
		cout << "CreateThread error:  " << textsBDEFG[1] << GetLastError() << endl;
		return 1;
	}
	Thread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_i, (void*)textsEHI[2], 0, &ThreadID);
	if (Thread[2] == NULL)
	{
		cout << "CreateThread error:  " << textsBDEFG[2] << GetLastError() << endl;
		return 1;
	}

	for (int i = 0; i < 3; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;

	char const* textsIK[] = { "i", "k" };

	for (int i = 0; i < 2; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsIK[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsIK[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}

	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	


	CloseHandle(SemE);
	CloseHandle(SemH);
	CloseHandle(SemI);
	CloseHandle(Mutex);

	cout << endl;

	return 0;
}