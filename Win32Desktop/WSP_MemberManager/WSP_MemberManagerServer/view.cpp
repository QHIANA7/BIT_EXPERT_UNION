//view.cpp

#include "std.h"

void view_GetControlHandle(HWND hDlg)
{
	hListView = GetDlgItem(hDlg, IDC_LISTVIEW);
	hEditLog = GetDlgItem(hDlg, IDC_EDITLOG);
	hStaticMemberCount = GetDlgItem(hDlg, IDC_STATICMEMBERCOUNT);
	//static text ��Ʈ���� ��� ID�� ������ ��� ���⶧���� ID������ ����϶�.
}

void view_InitControl(HWND hDlg)
{
	//����Ʈ�信 ��� �߰�
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 80;
	COL.pszText = TEXT("ID");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 80;
	COL.pszText = TEXT("PW");
	COL.iSubItem = 1;
	SendMessage(hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 80;
	COL.pszText = TEXT("NICKNAME");
	COL.iSubItem = 2;
	SendMessage(hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	ListView_SetExtendedListViewStyle(hListView,
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES |
		LVS_EX_HEADERDRAGDROP);
}

void view_ListViewPrintAll(HWND hDlg)
{
	ListView_DeleteAllItems(hListView);	//����Ʈ�� ��� ��� ����

	LVITEM LI;
	LI.mask = LVIF_TEXT;
	for (int i = 0; i < (int)g_datalist.size(); i++)
	{
		DATA dt = g_datalist[i];
		//TCHAR buf[256];

		LI.iSubItem = 0;
		LI.iItem = 0;
		LI.pszText = dt.id;
		SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 1;
		LI.pszText = dt.pw;
		SendMessage(hListView, LVM_SETITEM, 1, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = dt.nickname;
		SendMessage(hListView, LVM_SETITEM, 2, (LPARAM)&LI);
	}
}

void view_StaticMemberCountPrint(HWND hDlg)
{
	int cnt = g_datalist.size();
	TCHAR buf[64];
	wsprintf(buf, TEXT("ȸ�������ڼ� %d ��"), cnt);
	SetDlgItemText(hDlg, IDC_STATICMEMBERCOUNT, buf);
}

void view_AddLogMessage(HWND hDlg, TCHAR * msg)
{
	SendMessage(hEditLog, EM_REPLACESEL, 0, (LPARAM)msg);
}
