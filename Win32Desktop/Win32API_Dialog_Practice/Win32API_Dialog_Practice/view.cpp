//view.cpp
#include "std.h"

void view_ListViewPrintAll(HWND hDlg)
{
	ListView_DeleteAllItems(hListView);	//����Ʈ�� ��� ��� ����


	LVITEM Ll;
	Ll.mask = LVIF_TEXT;
	for(int i = 0;i < (int)g_veclist.size() ; i++)
	{
		MEMBER mem = g_veclist[i];
		TCHAR buf[50];

		Ll.iSubItem = 0;
		Ll.iItem = 0;
		Ll.pszText = mem.name;
		SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&Ll);

		Ll.iSubItem = 1;
		wsprintf(buf, TEXT("%d"), mem.number);
		Ll.pszText = buf;
		SendMessage(hListView, LVM_SETITEM, 1, (LPARAM)&Ll);

		Ll.iSubItem = 2;
		if (mem.gender == TRUE)
			_tcscpy_s(buf, TEXT("����"));
		else
			_tcscpy_s(buf, TEXT("����"));
		Ll.pszText = buf;
		SendMessage(hListView, LVM_SETITEM, 2, (LPARAM)&Ll);

		Ll.iSubItem = 3;
		Ll.pszText = mem.subject;
		SendMessage(hListView, LVM_SETITEM, 3, (LPARAM)&Ll);

	}
	

}

void view_GetControlHandle(HWND hDlg)
{
	hListView = GetDlgItem(hDlg, IDC_LISTVIEW);
	hEditName = GetDlgItem(hDlg, IDC_EDITNAME);
	hEditNum = GetDlgItem(hDlg, IDC_EDITNUM);
	hRadioM = GetDlgItem(hDlg, IDC_RADIOM);
	hRadioF = GetDlgItem(hDlg, IDC_RADIOF);
	hComboSubject = GetDlgItem(hDlg, IDC_COMBOSUBJECT);
}

void view_InitControl(HWND hDlg)
{
	old = (WNDPROC)SetWindowLong(hEditNum, GWL_WNDPROC, (LONG)EditProc);

	SetFocus(hEditName);

	CheckRadioButton(hDlg, IDC_RADIOM, IDC_RADIOF,		IDC_RADIOM);
	SendMessage(hComboSubject, CB_ADDSTRING, 0, (LPARAM)TEXT("��ǻ��"));
	SendMessage(hComboSubject, CB_ADDSTRING, 0, (LPARAM)TEXT("IT"));
	SendMessage(hComboSubject, CB_ADDSTRING, 0, (LPARAM)TEXT("����"));
	SendMessage(hComboSubject, CB_ADDSTRING, 0, (LPARAM)TEXT("��Ÿ"));
	SendMessage(hComboSubject, CB_SETCURSEL, (WPARAM)0, 0);	//�̰� �� IT�� ������? -> Sort�� �⺻ TRUE

	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 70;
	COL.pszText = TEXT("�̸�");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("�й�");				
	COL.iSubItem = 1;
	SendMessage(hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = TEXT("����");
	COL.cx = 40;
	COL.iSubItem = 2;
	SendMessage(hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.pszText = TEXT("�а�");
	COL.cx = 70;
	COL.iSubItem = 3;
	SendMessage(hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	ListView_SetExtendedListViewStyle(hListView,
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES |
		LVS_EX_HEADERDRAGDROP);
}

void view_GetControlData(HWND hDlg, MEMBER * mem)
{
	GetWindowText(hEditName, mem->name, sizeof(mem->name));
	
	if (SendMessage(hRadioM, BM_GETCHECK, 0, 0) == BST_CHECKED)
		mem->gender = TRUE;
	else
		mem->gender = FALSE;

	mem->number = GetDlgItemInt(hDlg, IDC_EDITNUM, 0, 0);

	int idx = SendMessage(hComboSubject, CB_GETCURSEL, 0, 0);
	SendMessage(hComboSubject, CB_GETLBTEXT, (WPARAM)idx, (LPARAM)mem->subject);
}
