//handler.cpp
#include"std.h"

extern vector<MEMBER> g_veclist;
extern MEMBER curmember;

void OnButtonJoin(HWND hwnd)
{
	MEMBER temp;
	view_GetControlData(hwnd, &temp);
	curmember = temp;
	g_veclist.push_back(temp);
	//MessageBox(hwnd, TEXT("회원등록 완료"), TEXT("알림"), MB_OK);
	view_SetControlData(hwnd);
	view_ControlListBoxPrint(hwnd);
}

void OnButtonCancle(HWND hwnd)
{
	//MessageBox(hwnd, TEXT("취소버튼 눌림"), TEXT("알림"), MB_OK);
	SendMessage(hwnd, WM_CLOSE, 0, 0);
}

void OnButtonUpdate(HWND hwnd)
{
	int number = GetDlgItemInt(hwnd, IDC_EDITNUMBER, 0, 0);
	for (int i = 0; i < (int)g_veclist.size(); i++)
	{
		MEMBER temp = g_veclist[i];
		if (temp.number == number)
		{
			g_veclist[i].subject = SendMessage(hComboSubject, CB_GETCURSEL, 0, 0);
			view_ControlListBoxPrint(hwnd);
			return;
		}
	}
}

void OnButtonDelete(HWND hwnd)
{
	int number = GetDlgItemInt(hwnd, IDC_EDITNUMBER, 0, 0);
	//int i = SendMessage(hListMember, LB_GETCURSEL, 0, 0);
	for (int i = 0; i < (int)g_veclist.size(); i++)
	{
		MEMBER temp = g_veclist[i];
		if (temp.number == number)
		{
			g_veclist.erase(g_veclist.begin() + i);
			view_ControlListBoxPrint(hwnd);
			return;
		}
	}
}

void OnListBox(HWND hwnd, WPARAM wParam)
{
	int i;
	switch (HIWORD(wParam))
	{
		case LBN_SELCHANGE:
		i = SendMessage(hListMember, LB_GETCURSEL, 0, 0);
		view_SelectPrint(hwnd, i);
		break;
	}
}

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	view_ControlCreate(hwnd);	//컨트롤 생성부분
	view_ControlInit(hwnd);
	return 0;	//핸들러 함수는 성공시 0을 리턴한다고 했었다.
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))	//WM_COMMAND 발생시 wParam중 하위 16비트에 ID가 담겨온다.
	{
	case IDC_LISTMEMBER:	//리스트박스로부터 온 메시지
		OnListBox(hwnd,wParam);
		break;
	case IDC_BUTTONJOIN:	//등록버튼
		OnButtonJoin(hwnd);
		break;
	case IDC_BUTTONCANCLE:	//취소버튼
		OnButtonCancle(hwnd);
		break;
	case IDC_BUTTONUPDATE:	//갱신버튼
		OnButtonUpdate(hwnd);
		break;
	case IDC_BUTTONDELETE:	//삭제버튼
		OnButtonDelete(hwnd);
		break;
	}
	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	view_PrintMemberInfoToMessageBox(hwnd, &curmember);
	return 0;
}

