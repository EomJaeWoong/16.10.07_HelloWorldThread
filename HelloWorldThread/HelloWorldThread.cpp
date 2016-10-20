#include <Windows.h>
#include <process.h>
#include <stdio.h>

//일꾼 스레드 프로시저의 원형
//DWORD WINAPI WorkerThreadProc(LPVOID lpThreadParameter);
unsigned __stdcall WorkerThreadProc(LPVOID lpThreadParameter);

int main(void)
{
	HANDLE hWorkerThread;
	DWORD dwWorkerThreadId;
	DWORD dwPrimaryThreadId;

	//주 스레드의 식별자를 얻어서 저장한다.
	dwPrimaryThreadId = GetCurrentThreadId();

	printf("[%08x] Multithreaded hello application started.\n", dwPrimaryThreadId);

	/*
	//일꾼 스레드 생성
	hWorkerThread = CreateThread(
		NULL,					//디폴트 보안 속성
		0,						//디폴트 스택 크기
		WorkerThreadProc,		//시작할 스레드 프로시저
		(LPVOID)3,				//인자 : 3초 동안 수행하라
		0,						//플래그 x
		&dwWorkerThreadId		//일꾼 스레드 ID
		);
	*/

	hWorkerThread = (HANDLE)_beginthreadex(NULL, 0, WorkerThreadProc, (LPVOID)3, 0, (unsigned int *)&dwWorkerThreadId);

	if (hWorkerThread != NULL)
	{
		printf("[%08x] Worker thread ID = 0x%08x. \n", dwPrimaryThreadId, dwWorkerThreadId);

		//주 스레드 대기
		Sleep(6000);

		//일꾼 스레드의 종료 코드를 읽고 핸들을 닫는다.
		DWORD dwThreadExitCode;
		GetExitCodeThread(hWorkerThread, &dwThreadExitCode);

		printf("[%08x] Worker thread exit code = 0x%08x. \n", dwPrimaryThreadId, dwThreadExitCode);

		CloseHandle(hWorkerThread);
	}

	else
	{
		printf("[%08x] Failed to create worker thread: error 0x%x. \n", dwPrimaryThreadId, GetLastError());
	}

	printf("[%08x] Multithreaded hello application exiting.\n", dwPrimaryThreadId);

	return 0;
}

//일꾼 스레드의 스레드 시작 프로시저
//DWORD WINAPI WorkerThreadProc(LPVOID lpThreadParameter)
unsigned __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
{
	//인자는 수행할 시간을 나타냄
	DWORD dwNumSeconds = (DWORD)lpThreadParameter;
	DWORD dwThreadId = GetCurrentThreadId();

	while (dwNumSeconds-- > 0)
	{
		Sleep(1000);

		printf("[%08x] Hello, multithreaded world!\n", dwThreadId);
	}

	return dwThreadId;
}