//message.cpp

#include "std.h"

BOOL msg_ShootMessage(HWND hDlg, TCHAR * nickname, TCHAR * msg, int flag)
{
	DATAMESSAGE dm;
	dm.flag = flag;
	_tcscpy_s(dm.nickname, NORMAL_TCHAR_LENGTH, nickname);
	_tcscpy_s(dm.msg, MSG_LENGHT, msg);

	COPYDATASTRUCT cds;
	cds.cbData = sizeof(DATAMESSAGE);
	cds.dwData = 2;	//1. 회원정보 2. 메시지
	cds.lpData = &dm;

	HWND hwnd = FindWindow(0, TEXT("CLIENT"));
	if (hwnd == 0)	//핸들 못받아 왔단다.
	{
		MessageBox(hDlg, TEXT("CLIENT를 찾을 수 없습니다."), TEXT("알림"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	//SendMessage(hwnd, WM_COPYDATA, (WPARAM)hDlg, (LPARAM)&cds);
	//WM_COPYDATA에 PostMessage를 사용할 수 없습니다.
	//만약 서버에서 클라이언트 쪽 응답을 장기간 기다리는것을 방지하기위해서는
	//SendMessageTimeout을 사용해야합니다.
	DWORD result;
	SendMessageTimeout(hwnd, WM_COPYDATA, (WPARAM)hDlg, (LPARAM)&cds, SMTO_NORMAL, 1000, &result);
		return TRUE;
}

