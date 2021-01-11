//handler.cpp

#include "std.h"

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return 0;
	}
	return TRUE;
}

BOOL OnCopyData(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	// ������� �Դٸ� lParam���� ���۵� �����������Ͱ� ����ִ�.
	COPYDATASTRUCT *ps = (COPYDATASTRUCT*)lParam;

	if(ps->dwData == 1)	//ȸ�� ���� DATA
	{
		
		DATA *pdata = (DATA*)ps->lpData;
		//�̷������� ����ȯ�Ͽ� �ָ�ȴ�. ��, �ݵ�� ����ü�� ����,ũ�Ⱑ �����ؾ���
		if (pdata->flag == 1)	//ȸ�� ���� �κ�
		{
			view_AddLogMessage(hDlg, TEXT("Receive  WM_COPYDATA F:1   Add_Member\r\n"));
			if (data_AddMember(pdata))	//�ߺ� ����
			{		
				view_StaticMemberCountPrint(hDlg);
				view_ListViewPrintAll(hDlg);
				TCHAR msg[MSG_LENGHT];
				_tcscpy_s(msg, MSG_LENGHT, pdata->nickname);
				wsprintf(msg + _tcslen(msg), TEXT("�� "),MSG_LENGHT);
				wsprintf(msg + _tcslen(msg), TEXT("ȸ�������� ���������� �Ϸ�Ǿ����ϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 11);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:11 Add_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("ID�ߺ�/���� ������ ���� �����Ͽ����ϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg,12);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:12 Add_Fail\r\n"));
				//msg_SendAddFail(hDlg, 12, pdata);
			}
		}
		else if (pdata->flag == 2)	//ȸ�� Ż�� �κ�
		{
			view_AddLogMessage(hDlg, TEXT("Receive  WM_COPYDATA F:2   Delete_Member\r\n"));
			if (data_DeleteMember(pdata))
			{
				view_StaticMemberCountPrint(hDlg);
				view_ListViewPrintAll(hDlg);
				TCHAR msg[MSG_LENGHT];
				_tcscpy_s(msg, MSG_LENGHT, pdata->nickname);
				wsprintf(msg + _tcslen(msg), TEXT("�� "), MSG_LENGHT);
				wsprintf(msg + _tcslen(msg), TEXT("ȸ��Ż�� ���������� �Ϸ�Ǿ����ϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 21);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:21 Delete_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("�� �޽����� ��Ÿ�� �� ���� �޽��� �Դϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 22);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:22 Delete_Fail\r\n"));
			}
		}
		else if (pdata->flag == 3)	//�α��� �κ�
		{
			view_AddLogMessage(hDlg, TEXT("Receive  WM_COPYDATA F:3   Try_Login\r\n"));
			if (data_CompareMember(pdata))
			{
				TCHAR msg[MSG_LENGHT];
				_tcscpy_s(msg, MSG_LENGHT, pdata->nickname);
				wsprintf(msg + _tcslen(msg), TEXT("�� "), MSG_LENGHT);
				wsprintf(msg + _tcslen(msg), TEXT("ȯ���մϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 31);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:31 Login_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("ID �� PW�� ��ġ���� �ʽ��ϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 32);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:32 Login_Fail\r\n"));
			}
		}
		else if (pdata->flag == 4)
		{
			view_AddLogMessage(hDlg, TEXT("Receive  WM_COPYDATA F:4   Try_Logout\r\n"));
			if (data_CompareMember(pdata))
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("���������� �α׾ƿ� �Ǿ����ϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 41);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:41 Logout_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("�� �޽����� ��Ÿ�� �� ���� �޽��� �Դϴ�."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 42);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:42 Logout_Fail\r\n"));
			}
		}

	}
	else if (ps->dwData == 2)	//�޽��� DATAMESSAGE
	{
		//DATAMESSAGE *pdatamsg = (DATAMESSAGE*)ps->lpData;
	}

	return TRUE;
}
