//view.cpp
#include "std.h"

void view_ListViewPrintAll(HWND hDlg)
{
	ListView_DeleteAllItems(hListView);	//����Ʈ�� ��� ��� ����

	LVITEM LI;
	LI.mask = LVIF_TEXT;
	for(int i = 0;i < (int)g_veclist.size() ; i++)
	{
		ACCOUNTINFO aci = g_veclist[i];
		TCHAR buf[256];

		LI.iSubItem = 0;
		LI.iItem = 0;
		wsprintf(buf, TEXT("%d"), cur_data.accountnumber);
		LI.pszText = buf;
		SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 1;
		wsprintf(buf, TEXT("%d"), aci.deposit);
		LI.pszText = buf;
		SendMessage(hListView, LVM_SETITEM, 1, (LPARAM)&LI);

		LI.iSubItem = 2;
		wsprintf(buf, TEXT("%d"), aci.withdraw);
		LI.pszText = buf;
		SendMessage(hListView, LVM_SETITEM, 2, (LPARAM)&LI);

		LI.iSubItem = 3;
		wsprintf(buf, TEXT("%d"), aci.balance);
		LI.pszText = buf;
		SendMessage(hListView, LVM_SETITEM, 3, (LPARAM)&LI);


		LI.iSubItem = 4;
		wsprintf(buf, TEXT("%04d�� %02d�� %02d��"), aci.st.wYear, aci.st.wMonth, aci.st.wDay);
		wsprintf(buf + _tcslen(buf), TEXT("  %02d:%02d:%02d"), aci.st.wHour, aci.st.wMinute, aci.st.wSecond);
		LI.pszText = buf;
		SendMessage(hListView, LVM_SETITEM, 4, (LPARAM)&LI);
	}
	

}

void view_GetControlHandle(HWND hDlg)
{
	hListView = GetDlgItem(hDlg, IDC_LISTVIEW);
	hButtonBanking = GetDlgItem(hDlg, IDC_BUTTONBANKING);
	hEditName = GetDlgItem(hDlg, IDC_EDITNAME);
}

void view_InitControl(HWND hDlg)
{
	//����Ʈ�信 ��� �߰�
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 70;
	COL.pszText = TEXT("���¹�ȣ");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("�Աݾ�");				
	COL.iSubItem = 1;
	SendMessage(hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = TEXT("��ݾ�");
	COL.cx = 70;
	COL.iSubItem = 2;
	SendMessage(hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.pszText = TEXT("�ܾ�");
	COL.cx = 70;
	COL.iSubItem = 3;
	SendMessage(hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.pszText = TEXT("�ŷ��Ͻ�");
	COL.cx = 220;
	COL.iSubItem = 4;
	SendMessage(hListView, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	ListView_SetExtendedListViewStyle(hListView,
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES |
		LVS_EX_HEADERDRAGDROP);

	account_exist = FALSE;
}

void view_GetControlData(HWND hDlg, ACCOUNT * mem)
{
	
}
