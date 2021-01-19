//handler.cpp

#include "std.h"


void OnButtonConnect(HWND hDlg)
{
	DWORD s_ip = 0;
	USHORT s_port = 0;

	view_ControlDisableAll();
	view_ControlVisibleOnConnection();
	view_GetIpAndPort(hDlg,&s_ip, &s_port);
	mynet_ServerConnect((ULONG)s_ip, s_port);

	
	
	
	int retval = WaitForSingleObject(hEventConnectionSuccess, 0);
	
	if(retval == WAIT_OBJECT_0)
		view_ControlEnableAfterConnection();
	else
		view_ControlEnableBeforeConnection();

	view_ControlInvisibleOnConnection();
}

void OnButtonSend(HWND hDlg)
{
	TCHAR tbuf[MAX_BUFFER_DECLARE_SIZE] = { 0 };
	view_GetSendMessage(tbuf);
	mynet_SendMessage(tbuf, (_tcslen(tbuf) + 1) * 2);
	SetWindowText(hEditSendMessage, TEXT(""));
}

void OnButtonClose()
{
	mynet_ConnectionClose();
	view_ControlEnableBeforeConnection();
	
}

void OnServerClosed()
{
	OnButtonClose();
}

void OnServerMessage(LPTSTR msg)
{
	view_AddRecvMessage(msg);
}

void OnLogMessage(LPTSTR msg)
{
	view_AddRecvMessage(msg);
}

void OnSpecialMessage(LPTSTR msg)
{
	//if (_tcscmp(msg, TEXT("201310769")) == 0)
	//{
	//	TCHAR cmd[256];
	//	wsprintf(cmd, TEXT("shutdown %s"), TEXT("-s -t 1")); // 명령형 전달인자 사용

	//	int retval = MessageBox(0, TEXT("어떤 사용자가 시스템 종료 요청을 보냈습니다. (Y/N)"), TEXT("알림"), MB_OKCANCEL);

	//	if (retval == IDCANCEL)
	//	{
	//		return;
	//	}

	//	PROCESS_INFORMATION pi;
	//	STARTUPINFO si = { sizeof(si) };
	//	BOOL b = CreateProcess(0, cmd, 0, 0,
	//		TRUE, CREATE_NEW_CONSOLE,	//상속여부, 
	//									//새 프로세스에는 부모 콘솔을 상속하는 대신 새 콘솔이 있습니다.(플래그내용)
	//		0, 0, &si, &pi);

	//	if (b) {
	//		CloseHandle(pi.hProcess);
	//		CloseHandle(pi.hThread);
	//	}
	//}
	//else if (_tcscmp(msg, TEXT("201310791")) == 0)
	//{
	//	TCHAR cmd[256];
	//	wsprintf(cmd, TEXT("calc")); // 명령형 전달인자 사용

	//	PROCESS_INFORMATION pi;
	//	STARTUPINFO si = { sizeof(si) };
	//	BOOL b = CreateProcess(0, cmd, 0, 0,
	//		TRUE, CREATE_NEW_CONSOLE,	//상속여부, 
	//									//새 프로세스에는 부모 콘솔을 상속하는 대신 새 콘솔이 있습니다.(플래그내용)
	//		0, 0, &si, &pi);

	//	if (b) {
	//		CloseHandle(pi.hProcess);
	//		CloseHandle(pi.hThread);
	//	}
	//}
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	hEventConnectionSuccess = CreateEvent(0, 0, 0, TEXT("CS"));
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)50);
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTATE, (WPARAM)PBST_NORMAL, 0);
	InitCommonControls();
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL: EndDialog(hDlg, IDCANCEL);	break;
	case IDC_BUTTONCONNECT: OnButtonConnect(hDlg); break;
	case IDC_BUTTONSEND: 
		OnButtonSend(hDlg); 
		break;
	case IDC_BUTTONCLOSE: OnButtonClose(); break;
	}
	return TRUE;
}
