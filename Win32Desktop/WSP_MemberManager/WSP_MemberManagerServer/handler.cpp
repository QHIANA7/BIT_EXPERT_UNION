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
	// 여기까지 왔다면 lParam에는 전송된 데이터포인터가 들어있다.
	COPYDATASTRUCT *ps = (COPYDATASTRUCT*)lParam;

	if(ps->dwData == 1)	//회원 정보 DATA
	{
		
		DATA *pdata = (DATA*)ps->lpData;
		//이런식으로 형변환하여 주면된다. 단, 반드시 구조체의 순서,크기가 동일해야함
		if (pdata->flag == 1)	//회원 가입 부분
		{
			view_AddLogMessage(hDlg, TEXT("Receive  WM_COPYDATA F:1   Add_Member\r\n"));
			if (data_AddMember(pdata))	//중복 없음
			{		
				view_StaticMemberCountPrint(hDlg);
				view_ListViewPrintAll(hDlg);
				TCHAR msg[MSG_LENGHT];
				_tcscpy_s(msg, MSG_LENGHT, pdata->nickname);
				wsprintf(msg + _tcslen(msg), TEXT("님 "),MSG_LENGHT);
				wsprintf(msg + _tcslen(msg), TEXT("회원가입이 성공적으로 완료되었습니다."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 11);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:11 Add_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("ID중복/공백 등으로 인해 실패하였습니다."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg,12);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:12 Add_Fail\r\n"));
				//msg_SendAddFail(hDlg, 12, pdata);
			}
		}
		else if (pdata->flag == 2)	//회원 탈퇴 부분
		{
			view_AddLogMessage(hDlg, TEXT("Receive  WM_COPYDATA F:2   Delete_Member\r\n"));
			if (data_DeleteMember(pdata))
			{
				view_StaticMemberCountPrint(hDlg);
				view_ListViewPrintAll(hDlg);
				TCHAR msg[MSG_LENGHT];
				_tcscpy_s(msg, MSG_LENGHT, pdata->nickname);
				wsprintf(msg + _tcslen(msg), TEXT("님 "), MSG_LENGHT);
				wsprintf(msg + _tcslen(msg), TEXT("회원탈퇴 성공적으로 완료되었습니다."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 21);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:21 Delete_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("이 메시지는 나타날 수 없는 메시지 입니다."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 22);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:22 Delete_Fail\r\n"));
			}
		}
		else if (pdata->flag == 3)	//로그인 부분
		{
			view_AddLogMessage(hDlg, TEXT("Receive  WM_COPYDATA F:3   Try_Login\r\n"));
			if (data_CompareMember(pdata))
			{
				TCHAR msg[MSG_LENGHT];
				_tcscpy_s(msg, MSG_LENGHT, pdata->nickname);
				wsprintf(msg + _tcslen(msg), TEXT("님 "), MSG_LENGHT);
				wsprintf(msg + _tcslen(msg), TEXT("환영합니다."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 31);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:31 Login_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("ID 및 PW가 일치하지 않습니다."), MSG_LENGHT);
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
				wsprintf(msg, TEXT("정상적으로 로그아웃 되었습니다."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 41);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:41 Logout_Success\r\n"));
			}
			else
			{
				TCHAR msg[MSG_LENGHT];
				wsprintf(msg, TEXT("이 메시지는 나타날 수 없는 메시지 입니다."), MSG_LENGHT);
				msg_ShootMessage(hDlg, pdata->nickname, msg, 42);
				view_AddLogMessage(hDlg, TEXT("Dispatch WM_COPYDATA F:42 Logout_Fail\r\n"));
			}
		}

	}
	else if (ps->dwData == 2)	//메시지 DATAMESSAGE
	{
		//DATAMESSAGE *pdatamsg = (DATAMESSAGE*)ps->lpData;
	}

	return TRUE;
}
