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
	g_SocketInfo.push_back(dt);	//����Ʈ�� ����
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
	UINT port = 9000;	//�⺻ 9000 ��Ʈ

	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOGSERVEREXCUTE),	//��� ��ȭ���� ID
		hDlg,		// �θ�
		DlgModalProc,	// �޼��� ó�� ���ν���
		(LPARAM)&port);

	if (ret == IDOK)	//��Ͽ� ���� ���ῴ�� ���
	{
		//===========================	���� ���� �κ� ==============
		ResetEvent(hEventServerClose);
		mynet_StartServer(port);
	}
}

void OnServerExit(HWND hDlg)
{
	SetEvent(hEventServerClose);	//���� �ݴ� �̺�Ʈ �߻�
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

