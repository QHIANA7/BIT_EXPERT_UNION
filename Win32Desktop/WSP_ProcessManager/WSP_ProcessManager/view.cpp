//view.cpp
#include "std.h"

void view_GetProcessName(HWND hDlg, TCHAR *temp)
{
	GetDlgItemText(hDlg, IDC_EDITPROCESSNAME, temp, TCHAR_LENGTH);
	//넘겨온 포인터변수 temp에 sizeof연산을 하게되면 고정 4바이트밖에 나오질 않는다.
	//방법1 : 이 함수에 크기도 같이 전달한다.
	//방법2 : _tcslen함수를 이용하면 글자수가 오지만 불안정
	//방법3 : 크기에 직접 값을 준다.
	SetDlgItemText(hDlg, IDC_EDITPROCESSNAME,TEXT(""));
}

void view_PrintAllProcessInfo(HWND hDlg)
{
	TCHAR buf[256];	//임시 범용 문자열 변수
	
	SendMessage(GetDlgItem(hDlg, IDC_LISTPROCESSINFO), LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING메시지 또한 가능하다 매개변수는 i,0이며 i인덱스를 지우는 메시지다. (반복문 필요)
	for (int i = 0; i < (int)g_veclist.size(); i++)	//vector에 저장된 수만큼 반복
	{
		PROCESSINFO temp = g_veclist[i];
		wsprintf(buf, TEXT("%15s　%010d　"),temp.name,temp.hProcess);
		wsprintf(buf + _tcslen(buf), TEXT("%04d년 %02d월 %02d일"), temp.st.wYear, temp.st.wMonth, temp.st.wDay);
		wsprintf(buf + _tcslen(buf), TEXT("  %02d:%02d:%02d"), temp.st.wHour, temp.st.wMinute, temp.st.wSecond);
		SendMessage(GetDlgItem(hDlg, IDC_LISTPROCESSINFO), LB_ADDSTRING, 0, (LPARAM)buf);	//ListBox에 문자열을 추가
																//주의 : 이 시점에서 문자열이 추가되진 않는다. 현재메시지 처리후 LB_ADDSTRING 처리시 추가된다.
	}
}

void view_ListProcessInfoSelectChange(HWND hDlg)
{
	TCHAR buf[256];
	int idx = SendMessage(GetDlgItem(hDlg, IDC_LISTPROCESSINFO), LB_GETCURSEL, 0, 0);	//리스트박스의 커서를 달라는 메시지 보냄
	cur_data = g_veclist[idx];	//vector의 idx 인덱스 요소를 cur_data에 대입

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
		SetDlgItemText(hDlg, IDC_EDITPROCESSSTATUS, TEXT("살았음"));
	}
	else
	{
		TCHAR buf[256];
		wsprintf(buf, TEXT("죽었음 : (%d)"), code);
		SetDlgItemText(hDlg, IDC_EDITPROCESSSTATUS, buf);
	}
}

void view_DeleteProcessListByHandle(HANDLE hProcess)
{
	for (int i = 0; i < (int)g_veclist.size(); i++)	//vector에 저장된 수만큼 반복
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
	//리스트뷰에 헤더 추가
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 270;
	COL.pszText = TEXT("이름");				// 첫 번째 헤더
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
	ListView_DeleteAllItems(hListView);	//리스트의 모든 요소 지움

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