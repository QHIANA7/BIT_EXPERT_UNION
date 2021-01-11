//process.cpp

#include "std.h"

HANDLE pro_CreateProcess(TCHAR * proName)
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	
	if (CreateProcess(0, proName, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		WaitForInputIdle(pi.hProcess, INFINITE);
		//pi의 핸들이 생성되거나, 정한 ms시간만큼 지났을때 상태가 반환됨

		//CloseHandle(pi.hProcess);	//계산기 여기서 컨트롤 하지 않으므로 닫아주자
		//CloseHandle(pi.hThread);	//현재 프로세스에서 계산기 핸들정보를 지워주자
		return pi.hProcess;
	}
	return 0;
	
	//MessageBox(0, TEXT(""), TEXT(""), MB_OK);

	//작업관리자에서하는 프로세스 끝내기가 바로 TerminateProcess였던 것!
	//TerminateProcess(pi.hProcess,0);
	//윈도우 10에서는 calc 실행시 바로 죽고 Calculator라는게 실행되므로 탐지 불가능
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
	// process list 가져오기(id값)
	DWORD aProcess[1024], cbNeeded, cProcesses;
	UINT i;
	
	if (!EnumProcesses(aProcess, sizeof(aProcess), &cbNeeded))
		// 배열 수, 리턴되는 바이트 수 
		// 배열에 id값들이 들어간다.
		return;
	
	// 얼마나 많은 프로세스들이 리턴되었나 계산
	cProcesses = cbNeeded / sizeof(DWORD);
	
	// process 이름 출력
	for (i = 0; i < cbNeeded; i++)
		pro_PrintProcessNameAndID(aProcess[i]);
}

void pro_PrintProcessNameAndID(DWORD processID) 
{
	TCHAR szProcessName[MAX_PATH] = TEXT("unknown");
	
	// 프로세스의 핸들 얻기
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ, FALSE, processID);

	// process 이름 가져오기
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
