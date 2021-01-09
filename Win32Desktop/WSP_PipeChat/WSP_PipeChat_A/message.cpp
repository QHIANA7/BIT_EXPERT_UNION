#include "std.h"
//message.cpp

void msg_CreatePipe(HWND hDlg)
{
			//A		//B		//A			//B
	HANDLE hRead1, hRead2, hWrite1, hWrite2;
	CreatePipe(&hRead1, &hWrite1, 0, 0);
	CreatePipe(&hRead2, &hWrite2, 0, 0);
	//====================================
	hRead = hRead2;	//B
	hWrite = hWrite1;	//A
	//====================================
	HWND B_hwnd = FindWindow(0, TEXT("B"));
	if (B_hwnd == 0)
	{
		MessageBox(hDlg, TEXT("B프로그램을 찾을수 없습니다."), TEXT("알림"), MB_OK);
		return;
	}
	else
	{
		//2. 프로세스 핸들 얻기
		DWORD pid;
		DWORD tid = GetWindowThreadProcessId(B_hwnd, &pid);
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
		//=======================================================

		//3. 핸들 복사
		HANDLE B_read, B_write;
		DuplicateHandle(GetCurrentProcess(), hRead1, hProcess, &B_read, 0, 0, DUPLICATE_SAME_ACCESS);
		DuplicateHandle(GetCurrentProcess(), hWrite2, hProcess, &B_write, 0, 0, DUPLICATE_SAME_ACCESS);
		//=========================================================

		//4. 핸들 전달 및 핸들 테이블 제거
		SendMessage(B_hwnd, WM_USER + 100, (WPARAM)B_read, (LPARAM)B_write);
		CloseHandle(hRead1);
		CloseHandle(hWrite2);	
	}
}

void msg_SendData(TCHAR *msg)
{
	DWORD temp = _tcslen(msg) * 2 + 1;
	WriteFile(hWrite, msg, _tcslen(msg)*2 + 1, 0, 0);
}

DWORD WINAPI msg_RecvThread(void* p)
{
	HWND hDlg = (HWND)p;	//핸들을 가져올수 있다.
	TCHAR buf[4096];
	while (TRUE)
	{
		memset(buf, 0, sizeof(buf));
		DWORD len;
		BOOL b = ReadFile(hRead, buf, sizeof(buf), &len, 0);
		if (!b)break;
		//=====================================
		OnRecvData(hDlg,buf);
		//=====================================

	}
	return 0;
}