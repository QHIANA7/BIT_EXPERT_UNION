//handler.cpp

#include "std.h"

void OnLogMessage(LPTSTR msg)
{
	view_AddLogMessage(msg);
}

void OnClientMessage(LPTSTR msg)
{
	view_ClientMessagePrint(msg);
}

void OnClientConnect(DATA dt)
{
	g_SocketInfo.push_back(dt);	//리스트에 삽입
	view_ListViewPrintAll();
	view_StaticMemberCountPrint();
}

void OnClientClose(SOCKET sk)
{
	data_RemoveSocketInfo(sk);
	view_ListViewPrintAll();
	view_StaticMemberCountPrint();
}

void OnServerRun(HWND hDlg)
{
	UINT port = 9000;	//기본 9000 포트

	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOGSERVEREXCUTE),	//모달 대화상자 ID
		hDlg,		// 부모
		DlgModalProc,	// 메세지 처리 프로시저
		(LPARAM)&port);

	if (ret == IDOK)	//등록에 의한 종료였을 경우
	{
		//===========================	서버 실행 부분 ==============
		ResetEvent(hEventServerClose);
		mynet_StartServer(port);
	}
}

void OnServerExit(HWND hDlg)
{
	SetEvent(hEventServerClose);	//서버 닫는 이벤트 발생
}

void OnRecvData(LPTSTR data)
{
	PINT p = (PINT)data;

	switch (*p)
	{
	case PACK_ADDMEMBER:
	{
		//============= 이하부분을 data.cpp 에 구현하라 =========
		PMEMBER mem = (PMEMBER)data;	
		if (data_AddMember(mem))	//성공
		{
			view_StaticMemberCountPrint();
			view_ListViewPrintAll();
			mem->flag = ACK_ADDMEMBERS;
		}
		else
		{
			mem->flag = ACK_ADDMEMBERF;
		}
	}
	break;
	case PACK_DELMEMBER:
	{
		PMEMBER mem = (PMEMBER)data;
		if (data_DeleteMember(mem))	//성공
		{
			view_StaticMemberCountPrint();
			view_ListViewPrintAll();
			mem->flag = ACK_DELMEMBERS;
		}
		else
		{
			mem->flag = ACK_DELMEMBERF;
		}

	}
	break;
	case PACK_LOGIN:
	{
		PLOGIN log = (PLOGIN)data;
		if (data_Login(log))	//성공
		{
			log->flag = ACK_LOGINS;
			view_ListViewPrintAll();
		}
		else
			log->flag = ACK_LOGINF;
	}
	break;
	case PACK_LOGOUT:
	{
		PLOGIN log = (PLOGIN)data;
		if (data_Logout(log))	//성공
		{
			log->flag = ACK_LOGOUTS;
			view_ListViewPrintAll();
		}
		else
			log->flag = ACK_LOGOUTF;
	}
	break;
	case PACK_MESSAGE:
	{
		PMESSAGE msg = (PMESSAGE)data;
		msg->flag = ACK_MESSAGE;
	}
	break;
	}
}

BOOL OnInitMenuPopUp(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = (HMENU)wParam;

	EnableMenuItem(hMenu, ID_40002, submenu2 == ID_40002 ? MF_GRAYED : MF_ENABLED);
	EnableMenuItem(hMenu, ID_40003, submenu2 == ID_40003 ? MF_GRAYED : MF_ENABLED);
	return 0;
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&cs1);
	hEventServerClose = CreateEvent(0, TRUE, 0, TEXT("SC"));
	g_hDlg = GetWindow(hDlg, GW_OWNER);
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case ID_40002: submenu2 = ID_40002; OnServerRun(hDlg); break;
	case ID_40003: submenu2 = ID_40003; OnServerExit(hDlg); break;
	case ID_40001:
	case IDCANCEL:
		DeleteCriticalSection(&cs);
		DeleteCriticalSection(&cs1);
		EndDialog(hDlg, IDCANCEL);	return 0;
	}
	return TRUE;
}

