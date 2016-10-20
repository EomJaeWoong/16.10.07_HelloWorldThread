#include <Windows.h>
#include <process.h>
#include <stdio.h>

//�ϲ� ������ ���ν����� ����
//DWORD WINAPI WorkerThreadProc(LPVOID lpThreadParameter);
unsigned __stdcall WorkerThreadProc(LPVOID lpThreadParameter);

int main(void)
{
	HANDLE hWorkerThread;
	DWORD dwWorkerThreadId;
	DWORD dwPrimaryThreadId;

	//�� �������� �ĺ��ڸ� �� �����Ѵ�.
	dwPrimaryThreadId = GetCurrentThreadId();

	printf("[%08x] Multithreaded hello application started.\n", dwPrimaryThreadId);

	/*
	//�ϲ� ������ ����
	hWorkerThread = CreateThread(
		NULL,					//����Ʈ ���� �Ӽ�
		0,						//����Ʈ ���� ũ��
		WorkerThreadProc,		//������ ������ ���ν���
		(LPVOID)3,				//���� : 3�� ���� �����϶�
		0,						//�÷��� x
		&dwWorkerThreadId		//�ϲ� ������ ID
		);
	*/

	hWorkerThread = (HANDLE)_beginthreadex(NULL, 0, WorkerThreadProc, (LPVOID)3, 0, (unsigned int *)&dwWorkerThreadId);

	if (hWorkerThread != NULL)
	{
		printf("[%08x] Worker thread ID = 0x%08x. \n", dwPrimaryThreadId, dwWorkerThreadId);

		//�� ������ ���
		Sleep(6000);

		//�ϲ� �������� ���� �ڵ带 �а� �ڵ��� �ݴ´�.
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

//�ϲ� �������� ������ ���� ���ν���
//DWORD WINAPI WorkerThreadProc(LPVOID lpThreadParameter)
unsigned __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
{
	//���ڴ� ������ �ð��� ��Ÿ��
	DWORD dwNumSeconds = (DWORD)lpThreadParameter;
	DWORD dwThreadId = GetCurrentThreadId();

	while (dwNumSeconds-- > 0)
	{
		Sleep(1000);

		printf("[%08x] Hello, multithreaded world!\n", dwThreadId);
	}

	return dwThreadId;
}