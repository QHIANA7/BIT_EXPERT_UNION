//view.cpp
#include "std.h"

TCHAR *Items[] = { TEXT("��ǻ������-��������"),TEXT("����ƮIT"),TEXT("���Ӹ�Ƽ�̵��"),TEXT("��۹̵��"),TEXT("ö������ý���") };

void view_SelectPrint(HWND hwnd, int idx)
{
	MEMBER temp = g_veclist[idx];

	SetWindowText(hEditName, temp.name);	//����Ʈ��Ʈ�ѿ� ������ ��������� ����(������ ������ ĸ�ǹ�)
	SetDlgItemInt(hwnd, IDC_EDITNUMBER, (WPARAM)temp.number, 0);	//SetWindowText�� ����ص� �ȴ�.
	SendMessage(hComboSubject, CB_SETCURSEL, temp.subject, 0);
	if(temp.gender == TRUE)
		CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER1);
	else
		CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER2);
}

void view_ControlListBoxPrint(HWND hwnd)
{
	TCHAR buf[50];
	SendMessage(hListMember, LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING�޽��� ���� �����ϴ� �Ű������� i,0�̸� i�ε����� ����� �޽�����.
	for (int i = 0; i < (int)g_veclist.size(); i++)
	{
		MEMBER temp = g_veclist[i];
		wsprintf(buf, TEXT("%s(%d)"), temp.name, temp.number);
		SendMessage(hListMember, LB_ADDSTRING, 0, (LPARAM)buf);
	}
	//LBN_SELCHANGE : ������ �ٲ������ �߻��ϴ� �޽���
	//LB_GETCURSEL : ����Ʈ�ڽ����� �ε����� ��ȯ�Ѵ�.
}

void view_ControlListBoxPrint1(HWND hwnd)
{
	TCHAR buf[50];
	SendMessage(hListMember, LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING�޽��� ���� �����ϴ� �Ű������� i,0�̸� i�ε����� ����� �޽�����.
	for (int i = 0; i < (int)g_veclist.size(); i++)
	{
		MEMBER temp = g_veclist[i];
		wsprintf(buf, TEXT("%s(%d)"), temp.name, temp.number);
		SendMessage(hListMember, LB_ADDSTRING, 0, (LPARAM)buf);
	}
}

void view_ControlCreate(HWND hwnd)
{
	CreateWindow(TEXT("button"), TEXT("[ �Է�â ]"), WS_CHILD | WS_VISIBLE| BS_GROUPBOX, 5, 5, 300, 300,hwnd,0,0,0);
	CreateWindow(TEXT("static"), TEXT("* �̸�"), WS_CHILD | WS_VISIBLE, 20, 30, 60, 20, hwnd, 0, 0, 0);
	hEditName = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 90, 30, 200, 20, hwnd, (HMENU)IDC_EDITNAME, 0, 0);
	
	CreateWindow(TEXT("static"), TEXT("* ����"), WS_CHILD | WS_VISIBLE, 20, 60, 60, 20, hwnd, 0, 0, 0);
	hRadioGender1 = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 90, 60, 50, 20, hwnd, (HMENU)IDC_RADIOGENDER1, 0, 0);
	hRadioGender2 = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 60, 50, 20, hwnd, (HMENU)IDC_RADIOGENDER2, 0, 0);
	
	CreateWindow(TEXT("static"), TEXT("* �а�"), WS_CHILD | WS_VISIBLE, 20, 90, 60, 20, hwnd, 0, 0, 0);
	hComboSubject = CreateWindow(TEXT("combobox"), TEXT(""),
		WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DROPDOWN
		, 90, 90, 200, 200, hwnd, (HMENU)IDC_COMBOSUBJECT, 0, 0);
	for (int i = 0; i<5; i++) {
		SendMessage(hComboSubject, CB_ADDSTRING, 0, (LPARAM)Items[i]);
	}

	CreateWindow(TEXT("static"), TEXT("* �й�"), WS_CHILD | WS_VISIBLE, 20, 220, 60, 20, hwnd, 0, 0, 0);
	hEditNumber = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 90, 220, 200, 20, hwnd, (HMENU)IDC_EDITNUMBER, 0, 0);

	hButtonJoin = CreateWindow(TEXT("button"), TEXT("���"), WS_CHILD | WS_VISIBLE, 60, 260, 60, 20, hwnd, (HMENU)IDC_BUTTONJOIN, 0, 0);
	hButtonCancle = CreateWindow(TEXT("button"), TEXT("���"), WS_CHILD | WS_VISIBLE, 190, 260, 60, 20, hwnd, (HMENU)IDC_BUTTONCANCLE, 0, 0);

	CreateWindow(TEXT("button"), TEXT("[ �������Ʈ ]"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 320, 5, 220, 300, hwnd, 0, 0, 0);
	hListMember = CreateWindow(TEXT("listbox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 330, 30, 200, 270, hwnd, (HMENU)IDC_LISTMEMBER, 0, 0);
	//listbox ��Ÿ�Ͽ� LBS_NOTIFY�� �߰������ LBN_# �޽����� �߻��Ѵ�. (�߿�)

	hButtonUpdate = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_MULTILINE, 545, 40, 30, 50, hwnd, (HMENU)IDC_BUTTONUPDATE, 0, 0);
	hButtonDelete = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_MULTILINE, 545, 200, 30, 50, hwnd, (HMENU)IDC_BUTTONDELETE, 0, 0);
}

void view_ControlInit(HWND hwnd)
{
	SetFocus(hEditName);	//�Է¹������� �������� �ϴ°��� ��Ŀ����� �Ѵ�.
	//�Ű������� �Ѱ��� �ڵ鿡 ��Ŀ���� �ش�. ���� �ڵ��� �Ѱ���ٸ� ���⿡ ��Ŀ���� ���ִ´�.
	CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER1);	//������ư ����
	SendMessage(hComboSubject, CB_SETCURSEL, 0, 0);	//�޺��ڽ� �ڵ鿡 �޽����� ����
	//CB_SETCURSEL�� �޺��ڽ��� wParam�� �Ѿ �ε����� ����� �����϶�� ��	lParam�� �̻��
	//�ݴ�� CB_GETCURSEL�� �޺��ڽ� �ڵ��� ���� ���õ� �ε����� ���� ���´� w,l Param �Ѵ� 0���� �ؾ��Ѵ�.
}

void view_GetControlData(HWND hwnd, MEMBER * mem)
{
	GetWindowText(hEditName, mem->name, sizeof(mem->name));
	//�ڵ鰪�� ��Ʈ���� �Ѱ��ָ� �ش� �ڵ��� ĸ�ǹٸ��� �����´�-> ��Ʈ���� ��� ��
	//��Ʈ�� �ڵ�,���� ���,���� ��� ũ��

	mem->number = GetDlgItemInt(hwnd, IDC_EDITNUMBER, 0, 0);
	//�ϳ��� �θ��� â�� �ְ� �׾��� ID�������� �������� ������
	//�θ��ڵ�, ��Ʈ��ID,0,0

	mem->subject = SendMessage(hComboSubject, CB_GETCURSEL, 0, 0);

	if (SendMessage(hRadioGender1, BM_GETCHECK, 0, 0) == BST_CHECKED)	//��ư �ڵ��� äũ������ �������� �޽���
		mem->gender = TRUE;
	else
		mem->gender = FALSE;
}

void view_SetControlData(HWND hwnd)
{
	SetWindowText(hEditName, TEXT(""));	//����Ʈ��Ʈ�ѿ� ������ ��������� ����(������ ������ ĸ�ǹ�)
	SetDlgItemInt(hwnd, IDC_EDITNUMBER, 0, 0);	//SetWindowText�� ����ص� �ȴ�.
	SendMessage(hComboSubject, CB_SETCURSEL, 0, 0);
	CheckRadioButton(hwnd, IDC_RADIOGENDER1, IDC_RADIOGENDER2, IDC_RADIOGENDER1);
}

void view_PrintMemberInfoToMessageBox(HWND hwnd,MEMBER * mem)
{
	TCHAR buf[256];
	wsprintf(buf, TEXT("�̸� : %s\n"), mem->name);
	wsprintf(buf + _tcslen(buf), TEXT("�й� : %d\n"), mem->number);
	wsprintf(buf + _tcslen(buf), TEXT("�а��ڵ� : %d\n"), mem->subject);
	wsprintf(buf + _tcslen(buf), TEXT("���� : %s\n"), mem->gender ? TEXT("����") : TEXT("����"));
	MessageBox(hwnd, buf, TEXT("��ϵ� ��� ����"), MB_OK);
}
