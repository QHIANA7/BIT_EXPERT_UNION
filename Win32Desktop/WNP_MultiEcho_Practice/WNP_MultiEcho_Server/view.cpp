//view.cpp

#include "std.h"

void view_GetControlHandle(HWND hDlg)
{
	hListSocket = GetDlgItem(hDlg, IDC_LISTSOCKET);
	hEditLog = GetDlgItem(hDlg, IDC_EDITLOG);
	hStaticSocketCount = GetDlgItem(hDlg, IDC_STATICSOCKETCOUNT);
	//static text ��Ʈ���� ��� ID�� ������ ��� ���⶧���� ID������ ����϶�.
}

void view_InitControl(HWND hDlg)
{
	//����Ʈ�信 ��� �߰�
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = TEXT("����");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(hListSocket, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 140;
	COL.pszText = TEXT("SOCKET");
	COL.iSubItem = 1;
	SendMessage(hListSocket, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 140;
	COL.pszText = TEXT("PEER");
	COL.iSubItem = 2;
	SendMessage(hListSocket, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	ListView_SetExtendedListViewStyle(hListSocket,
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES |
		LVS_EX_HEADERDRAGDROP);
}

void view_AddLogMessage(LPTSTR msg)
{
	EnterCriticalSection(&cs1);
	SendMessage(hEditLog, EM_REPLACESEL, 0, (LPARAM)msg);
	SendMessage(hEditLog, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	LeaveCriticalSection(&cs1);
}

void view_ListViewPrintAll()
{
	ListView_DeleteAllItems(hListSocket);	//����Ʈ�� ��� ��� ����

	LVITEM LI;
	LI.mask = LVIF_TEXT;
	for (int i = 0; i < (int)g_SocketInfo.size(); i++)
	{
		DATA dt = g_SocketInfo[i];
		TCHAR buf[256];

		LI.iSubItem = 0;
		LI.iItem = 0;
		wsprintf(buf, TEXT("%d"), dt.socket);
		LI.pszText = buf;
		SendMessage(hListSocket, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 1;
		wsprintf(buf, TEXT("(%05d)%s"), dt.t_port,dt.t_ip);
		LI.pszText = buf;
		SendMessage(hListSocket, LVM_SETITEM, 1, (LPARAM)&LI);

		LI.iSubItem = 2;
		wsprintf(buf, TEXT("(%05d)%s"), dt.c_port, dt.c_ip);
		LI.pszText = buf;
		SendMessage(hListSocket, LVM_SETITEM, 2, (LPARAM)&LI);
	}
}

void view_StaticMemberCountPrint()
{
	int cnt = g_SocketInfo.size();
	TCHAR buf[64];
	wsprintf(buf, TEXT("��ż��� ���� %02d��"), cnt);
	SetWindowText(hStaticSocketCount,buf);
}

void view_ClientMessagePrint(LPTSTR msg)
{
	view_AddLogMessage(msg);
	//SendMessage(hEditLog, EM_REPLACESEL, 0, (LPARAM)msg);
	//SendMessage(hEditLog, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
}