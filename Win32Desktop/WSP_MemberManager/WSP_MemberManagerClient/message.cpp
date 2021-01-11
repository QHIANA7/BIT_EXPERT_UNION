//message.cpp

#include "std.h"

BOOL msg_DataSend(HWND hDlg, int flag, DATA data)
{
	data.flag = flag;

	COPYDATASTRUCT cds;
	cds.cbData = sizeof(DATA);
	cds.dwData = 1;	//1. 회원정보 2. 메시지
	cds.lpData = &data;

	HWND hwnd = FindWindow(0, TEXT("SERVER"));
	if (hwnd == 0)	//핸들 못받아 왔단다.
	{
		MessageBox(hDlg, TEXT("SERVER를 찾을 수 없습니다."), TEXT("알림"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	SendMessage(hwnd, WM_COPYDATA, (WPARAM)hDlg, (LPARAM)&cds);

	return TRUE;
}

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

	HWND hwnd = FindWindow(0, TEXT("SERVER"));
	if (hwnd == 0)	//핸들 못받아 왔단다.
	{
		MessageBox(hDlg, TEXT("SERVER를 찾을 수 없습니다."), TEXT("알림"), MB_OK | MB_ICONWARNING);
		return FALSE;
	}
	SendMessage(hwnd, WM_COPYDATA, (WPARAM)hDlg, (LPARAM)&cds);

	return TRUE;
}
