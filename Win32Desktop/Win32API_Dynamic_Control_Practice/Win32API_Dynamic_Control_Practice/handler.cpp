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
	//MessageBox(hwnd, TEXT("ȸ����� �Ϸ�"), TEXT("�˸�"), MB_OK);
	view_SetControlData(hwnd);
	view_ControlListBoxPrint(hwnd);
}

void OnButtonCancle(HWND hwnd)
{
	//MessageBox(hwnd, TEXT("��ҹ�ư ����"), TEXT("�˸�"), MB_OK);
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
	view_ControlCreate(hwnd);	//��Ʈ�� �����κ�
	view_ControlInit(hwnd);
	return 0;	//�ڵ鷯 �Լ��� ������ 0�� �����Ѵٰ� �߾���.
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))	//WM_COMMAND �߻��� wParam�� ���� 16��Ʈ�� ID�� ��ܿ´�.
	{
	case IDC_LISTMEMBER:	//����Ʈ�ڽ��κ��� �� �޽���
		OnListBox(hwnd,wParam);
		break;
	case IDC_BUTTONJOIN:	//��Ϲ�ư
		OnButtonJoin(hwnd);
		break;
	case IDC_BUTTONCANCLE:	//��ҹ�ư
		OnButtonCancle(hwnd);
		break;
	case IDC_BUTTONUPDATE:	//���Ź�ư
		OnButtonUpdate(hwnd);
		break;
	case IDC_BUTTONDELETE:	//������ư
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

