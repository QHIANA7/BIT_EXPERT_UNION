//view.cpp
#include "std.h"

void view_GetProcessName(HWND hDlg, TCHAR *temp)
{
	GetDlgItemText(hDlg, IDC_EDITPROCESSNAME, temp, TCHAR_LENGTH);
	//�Ѱܿ� �����ͺ��� temp�� sizeof������ �ϰԵǸ� ���� 4����Ʈ�ۿ� ������ �ʴ´�.
	//���1 : �� �Լ��� ũ�⵵ ���� �����Ѵ�.
	//���2 : _tcslen�Լ��� �̿��ϸ� ���ڼ��� ������ �Ҿ���
	//���3 : ũ�⿡ ���� ���� �ش�.
	SetDlgItemText(hDlg, IDC_EDITPROCESSNAME,TEXT(""));
}

void view_PrintAllProcessInfo(HWND hDlg)
{
	TCHAR buf[256];	//�ӽ� ���� ���ڿ� ����
	
	SendMessage(GetDlgItem(hDlg, IDC_LISTPROCESSINFO), LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING�޽��� ���� �����ϴ� �Ű������� i,0�̸� i�ε����� ����� �޽�����. (�ݺ��� �ʿ�)
	for (int i = 0; i < (int)g_veclist.size(); i++)	//vector�� ����� ����ŭ �ݺ�
	{
		PROCESSINFO temp = g_veclist[i];
		wsprintf(buf, TEXT("%15s��%010d��"),temp.name,temp.hProcess);
		wsprintf(buf + _tcslen(buf), TEXT("%04d�� %02d�� %02d��"), temp.st.wYear, temp.st.wMonth, temp.st.wDay);
		wsprintf(buf + _tcslen(buf), TEXT("  %02d:%02d:%02d"), temp.st.wHour, temp.st.wMinute, temp.st.wSecond);
		SendMessage(GetDlgItem(hDlg, IDC_LISTPROCESSINFO), LB_ADDSTRING, 0, (LPARAM)buf);	//ListBox�� ���ڿ��� �߰�
																//���� : �� �������� ���ڿ��� �߰����� �ʴ´�. ����޽��� ó���� LB_ADDSTRING ó���� �߰��ȴ�.
	}
}

void view_ListProcessInfoSelectChange(HWND hDlg)
{
	TCHAR buf[256];
	int idx = SendMessage(GetDlgItem(hDlg, IDC_LISTPROCESSINFO), LB_GETCURSEL, 0, 0);	//����Ʈ�ڽ��� Ŀ���� �޶�� �޽��� ����
	cur_data = g_veclist[idx];	//vector�� idx �ε��� ��Ҹ� cur_data�� ����

	wsprintf(buf, TEXT("%02d-%02d-%02d"), cur_data.st.wYear, cur_data.st.wMonth, cur_data.st.wDay);
	wsprintf(buf + _tcslen(buf), TEXT("  %02d:%02d:%02d"), cur_data.st.wHour, cur_data.st.wMinute, cur_data.st.wSecond);

	SetDlgItemText(hDlg, IDC_EDITPROCESSNAME2, cur_data.name);
	SetDlgItemInt(hDlg, IDC_EDITPROCESSHANDLE, (int)cur_data.hProcess, 0);
	SetDlgItemText(hDlg, IDC_EDITPROCESSEXCUTETIME, buf);

}

void view_SetProcessState(HWND hDlg, DWORD code)
{
	if (code == STILL_ACTIVE)
	{
		SetDlgItemText(hDlg, IDC_EDITPROCESSSTATUS, TEXT("�����"));
	}
	else
	{
		TCHAR buf[256];
		wsprintf(buf, TEXT("�׾��� : (%d)"), code);
		SetDlgItemText(hDlg, IDC_EDITPROCESSSTATUS, buf);
	}
}

void view_DeleteProcessListByHandle(HANDLE hProcess)
{
	for (int i = 0; i < (int)g_veclist.size(); i++)	//vector�� ����� ����ŭ �ݺ�
	{
		PROCESSINFO temp = g_veclist[i];
		if (temp.hProcess == hProcess)
		{
			g_veclist.erase(g_veclist.begin() + i);
		}
	}
}

void view_SetProcessInfoInit(HWND hDlg)
{
	SetDlgItemText(hDlg, IDC_EDITPROCESSNAME2, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDITPROCESSHANDLE, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDITPROCESSEXCUTETIME, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDITPROCESSSTATUS, TEXT(""));
}

void view_GetControlHandle(HWND hDlg)
{
	hListView = GetDlgItem(hDlg, IDC_LISTVIEW);
}

void view_InitControl(HWND hDlg)
{
	//����Ʈ�信 ��� �߰�
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 270;
	COL.pszText = TEXT("�̸�");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("PID");
	COL.iSubItem = 1;
	SendMessage(hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

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
	for (int i = 0; i < (int)g_allveclist.size(); i++)
	{
		PROCESSINFO pi = g_allveclist[i];
		TCHAR buf[256];

		LI.iSubItem = 0;
		LI.iItem = 0;
		LI.pszText = pi.name;
		SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 1;
		wsprintf(buf, TEXT("%d"), pi.hProcess);
		LI.pszText = buf;
		SendMessage(hListView, LVM_SETITEM, 1, (LPARAM)&LI);
	}


}