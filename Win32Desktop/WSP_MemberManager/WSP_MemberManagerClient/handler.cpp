//handler.cpp

#include "std.h"

void OnAddMember(HWND hDlg)
{
	DATA data;
	view_GetAddMemberData(hDlg, &data);
	msg_DataSend(hDlg, 1, data);	//1. ȸ������
}

void OnButtonInteractive(HWND hDlg)
{
	DATA data;
	TCHAR buf[32];
	GetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, buf, sizeof(buf));
	if (_tcscmp(buf, TEXT("�α���")) == (long)0)
	{
		view_GetAddMemberData(hDlg, &data);
		msg_DataSend(hDlg, 3, data);
	}
	else
	{
		view_GetAddMemberData(hDlg, &data);
		msg_DataSend(hDlg, 4, data);	
	}
}

void OnButtonDeleteAccount(HWND hDlg)
{
	DATA data;
	view_GetAddMemberData(hDlg, &data);
	msg_DataSend(hDlg, 2, data);	//2. ȸ�� Ż��
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	SetTimer(hDlg, 2, 10, 0);
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)50);
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTATE, (WPARAM)PBST_NORMAL, 0);
	//SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE32, 0, 100);
	//SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETPOS, 100, 0);
	//SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETBARCOLOR, 0, (LPARAM)RGB(255, 145, 169));
	
	view_GetControlHandle(hDlg);
	view_SetControlInit(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BUTTONDELETEACCOUNT: OnButtonDeleteAccount(hDlg); break;
	case IDC_BUTTONINTERACTIVE: OnButtonInteractive(hDlg); break;
	case IDOK: OnAddMember(hDlg); break;
	case IDCANCEL: KillTimer(hDlg, 2); EndDialog(hDlg, IDCANCEL);	break;
	}
	return TRUE;
}

BOOL OnCopyData(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	// ������� �Դٸ� lParam���� ���۵� �����������Ͱ� ����ִ�.
	COPYDATASTRUCT *ps = (COPYDATASTRUCT*)lParam;

	if (ps->dwData == 1)	//ȸ�� ���� DATA
	{
		DATA *pdata = (DATA*)ps->lpData;
		//�̷������� ����ȯ�Ͽ� �ָ�ȴ�. ��, �ݵ�� ����ü�� ����,ũ�Ⱑ �����ؾ���

	}
	else if (ps->dwData == 2)	//�޽��� DATAMESSAGE
	{
		DATAMESSAGE *pdatamsg = (DATAMESSAGE*)ps->lpData;
		//if (pdatamsg->flag == 11)	//ȸ�� ���� - ����
		//{
		//	MessageBox(hDlg, pdatamsg->msg, TEXT("�˸�"), MB_OK);
		//	//view_PopUpMessageBox()
		//}
		//else if (pdatamsg->flag == 12)	//ȸ�� ���� - ����
		//{
		//	MessageBox(hDlg, pdatamsg->msg, TEXT("�˸�"), MB_OK);
		//	//view_PopUpMessageBox()
		//}
		MessageBox(hDlg, pdatamsg->msg, TEXT("�˸�"), MB_OK);
		if (pdatamsg->flag == 21)
		{
			view_SetControlInit(hDlg);
			SendMessage(hEditID, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditPW, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditNickName, EM_SETREADONLY, (WPARAM)FALSE, 0);
			Button_Enable(hButtonOk, TRUE);
			SetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, TEXT("�α���"));
			ShowWindow(hButtonDeleteAccount, SW_HIDE);
		}
		else if (pdatamsg->flag == 31)	//�α��� ����
		{
			SendMessage(hEditID, EM_SETREADONLY, (WPARAM)TRUE, 0);
			SendMessage(hEditPW, EM_SETREADONLY, (WPARAM)TRUE, 0);
			SendMessage(hEditNickName, EM_SETREADONLY, (WPARAM)TRUE, 0);
			Button_Enable(hButtonOk, FALSE);
			SetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, TEXT("�α׾ƿ�"));
			ShowWindow(hButtonDeleteAccount, SW_SHOW);
			
		}
		else if (pdatamsg->flag == 41)
		{
			view_SetControlInit(hDlg);
			SendMessage(hEditID, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditPW, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendMessage(hEditNickName, EM_SETREADONLY, (WPARAM)FALSE, 0);
			Button_Enable(hButtonOk, TRUE);
			SetDlgItemText(hDlg, IDC_BUTTONINTERACTIVE, TEXT("�α���"));
			ShowWindow(hButtonDeleteAccount, SW_HIDE);
		}
		//view_PopUpMessageBox()
	}

	return TRUE;
}