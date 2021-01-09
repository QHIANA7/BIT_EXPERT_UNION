//view.cpp

#include "std.h"

//컨트롤 핸들 얻기
void view_GetControlHandle(HWND hDlg)
{
	hButton1 = GetDlgItem(hDlg, IDC_BUTTON1);
	hButton2 = GetDlgItem(hDlg, IDC_BUTTON2);
	hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
	hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
	hEdit3 = GetDlgItem(hDlg, IDC_EDIT3);
}
//버튼 상태값 변경
void view_ButtonState(BOOL b1, BOOL b2)
{
	EnableWindow(hButton1, b1);		
	EnableWindow(hButton2, b2);
}

//전송 에디트 컨트롤 초기화 및 포커스주기
void view_SendEditInitFocus(HWND hDlg)
{
	SetWindowText(hEdit2, TEXT(""));
	SetFocus(hEdit2);
}

//전송 데이터 획득
void view_GetSendData(HWND hDlg, TCHAR* msg)
{
	//ex) [홍길동] hi~~(11:10:15)
	TCHAR name[20], message[50];
	SYSTEMTIME st;
	GetWindowText(hEdit3, name, sizeof(name));
	GetWindowText(hEdit2, message, sizeof(char)* 50);
	GetLocalTime(&st);
	//============================================================

	wsprintf(msg, TEXT("[%s] %s (%d:%d:%d)"), name, message, st.wHour, st.wMinute, st.wSecond);
	
}

//대화창에 출력
void view_ChatMessagePrint(HWND hDlg,TCHAR* msg)
{
	if (hDlg == (HWND)GetModuleHandle(0))
	{
		SendMessage(hEdit1, EM_REPLACESEL, 0, (LPARAM)msg);
		SendMessage(hEdit1, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	}
	else
	{
		SendMessage(hEdit1, EM_REPLACESEL, 0, (LPARAM)msg);
		SendMessage(hEdit1, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	}
}