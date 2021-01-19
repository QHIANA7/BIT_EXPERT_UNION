//handler.cpp

#include "std.h"

void OnLogMessage(LPTSTR msg)
{
	view_AddLogMessage(msg);
}

void OnClientMessage(LPTSTR msg)
{
	view_ClientMessagePrint(msg);
}

void OnClientConnect(DATA dt)
{
	g_SocketInfo.push_back(dt);	//리스트에 삽입
	view_ListViewPrintAll();
	view_StaticMemberCountPrint();
}

void OnClientClose(SOCKET sk)
{
	data_RemoveSocketInfo(sk);
	view_ListViewPrintAll();
	view_StaticMemberCountPrint();
}

void OnServerRun(HWND hDlg)
{
	UINT port = 9000;	//기본 9000 포트

	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOGSERVEREXCUTE),	//모달 대화상자 ID
		hDlg,		// 부모
		DlgModalProc,	// 메세지 처리 프로시저
		(LPARAM)&port);

	if (ret == IDOK)	//등록에 의한 종료였을 경우
	{
		//===========================	서버 실행 부분 ==============
		ResetEvent(hEventServerClose);
		mynet_StartServer(port);
	}
}

void OnServerExit(HWND hDlg)
{
	SetEvent(hEventServerClose);	//서버 닫는 이벤트 발생
}

void OnRecvData(LPTSTR data)
{

}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&cs1);
	hEventServerClose = CreateEvent(0, TRUE, 0, TEXT("SC"));
	InitCommonControls();
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL: 
		DeleteCriticalSection(&cs);
		DeleteCriticalSection(&cs1);
		EndDialog(hDlg, IDCANCEL);	return 0;
	case ID_40001: EndDialog(hDlg, IDCANCEL); return 0;
	case ID_40002: OnServerRun(hDlg); break;
	case ID_40003: OnServerExit(hDlg); break;
	}
	return TRUE;
}

