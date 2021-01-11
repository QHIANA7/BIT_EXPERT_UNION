//process.cpp

#include "std.h"

HANDLE pro_CreateProcess(TCHAR * proName)
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	
	if (CreateProcess(0, proName, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		WaitForInputIdle(pi.hProcess, INFINITE);
		//pi�� �ڵ��� �����ǰų�, ���� ms�ð���ŭ �������� ���°� ��ȯ��

		//CloseHandle(pi.hProcess);	//���� ���⼭ ��Ʈ�� ���� �����Ƿ� �ݾ�����
		//CloseHandle(pi.hThread);	//���� ���μ������� ���� �ڵ������� ��������
		return pi.hProcess;
	}
	return 0;
	
	//MessageBox(0, TEXT(""), TEXT(""), MB_OK);

	//�۾������ڿ����ϴ� ���μ��� �����Ⱑ �ٷ� TerminateProcess���� ��!
	//TerminateProcess(pi.hProcess,0);
	//������ 10������ calc ����� �ٷ� �װ� Calculator��°� ����ǹǷ� Ž�� �Ұ���
}

void pro_InsertProcessInfo(TCHAR * proName, HANDLE hProcess)
{
	PROCESSINFO info;
	_tcscpy_s(info.name, proName);
	info.hProcess = hProcess;
	GetLocalTime(&info.st);

	g_veclist.push_back(info);
}

DWORD pro_GetProcessState(HANDLE hProcess)
{
	DWORD code;
		GetExitCodeProcess(hProcess, &code);
		if (code != STILL_ACTIVE)
			CloseHandle(hProcess);
	return code;
}

void pro_ExitProcess(HANDLE hProcess)
{
	TerminateProcess(hProcess, 0);
}

void pro_GetTotalCurrentProcessList(HWND hDlg)
{
	// process list ��������(id��)
	DWORD aProcess[1024], cbNeeded, cProcesses;
	UINT i;
	
	if (!EnumProcesses(aProcess, sizeof(aProcess), &cbNeeded))
		// �迭 ��, ���ϵǴ� ����Ʈ �� 
		// �迭�� id������ ����.
		return;
	
	// �󸶳� ���� ���μ������� ���ϵǾ��� ���
	cProcesses = cbNeeded / sizeof(DWORD);
	
	// process �̸� ���
	for (i = 0; i < cbNeeded; i++)
		pro_PrintProcessNameAndID(aProcess[i]);
}

void pro_PrintProcessNameAndID(DWORD processID) 
{
	TCHAR szProcessName[MAX_PATH] = TEXT("unknown");
	
	// ���μ����� �ڵ� ���
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ, FALSE, processID);

	// process �̸� ��������
	if (NULL != hProcess) 
	{
		HMODULE hMod;
		DWORD	cbNeeded;
		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
		}
		else
			return;
	}
	else 
		return;
	
	//print
	//_tprintf_s(TEXT("%s ( PROCESS ID : %u )\n"), szProcessName, processID);

	PROCESSINFO info;
	_tcscpy_s(info.name, szProcessName);
	info.hProcess = (HANDLE)processID;
	g_allveclist.push_back(info);
	CloseHandle(hProcess);
}
