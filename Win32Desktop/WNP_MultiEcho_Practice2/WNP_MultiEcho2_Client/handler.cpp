//handler.cpp

#include "std.h"


void OnButtonConnect(HWND hDlg)
{
	DWORD s_ip = 0;
	USHORT s_port = 0;


	view_ControlVisibleOnConnection();
	//view_GetIpAndPort(hDlg,&s_ip, &s_port);
	//mynet_ServerConnect((ULONG)s_ip, s_port);
	mynet_ServerConnect((ULONG)si.s_ip, si.s_port);
	
	int retval = WaitForSingleObject(hEventConnectionSuccess, 0);
	
	if(retval == WAIT_OBJECT_0)
		view_ControlEnableAfterConnection();
	else
		view_ControlEnableBeforeConnection();

	view_ControlInvisibleOnConnection();
}

void OnButtonSend(HWND hDlg)
{
	MESSAGE msg;
	view_GetMessageData(hDlg, &msg);
	msg.flag = PACK_MESSAGE;
	int sendlen = sizeof(MESSAGE);
	mynet_SendMessage((LPTSTR)&msg, sendlen);

	SetWindowText(hEditSendMessage, TEXT(""));
	//TCHAR tbuf[MAX_BUFFER_DECLARE_SIZE] = { 0 };
	//view_GetSendMessage(tbuf);
	//mynet_SendMessage(tbuf, (_tcslen(tbuf) + 1) * 2);
	//SetWindowText(hEditSendMessage, TEXT(""));
}

void OnButtonAddMember(HWND hDlg)
{
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_ADDMEMBER),	//모달 대화상자 ID
		hDlg,		// 부모
		DlgModalAddMemberProc,	// 메세지 처리 프로시저
		0);

	if (ret == IDOK)	//등록에 의한 종료였을 경우
	{
		
	}
}

void OnButtonDeleteMember(HWND hDlg)
{
	MEMBER mem;
	view_GetAddMemberData(hDlg, &mem);
	mem.flag = PACK_DELMEMBER;
	int sendlen = sizeof(MEMBER);
	mynet_SendMessage((LPTSTR)&mem, sendlen);
}

void OnButtonLogin(HWND hDlg)
{
	LOGIN log;
	view_GetLoginData(hDlg, &log);
	log.flag = PACK_LOGIN;
	int sendlen = sizeof(LOGIN);
	mynet_SendMessage((LPTSTR)&log, sendlen);
}

void OnButtonLogout(HWND hDlg)
{
	LOGIN log;
	view_GetLoginData(hDlg, &log);
	log.flag = PACK_LOGOUT;
	int sendlen = sizeof(LOGIN);
	mynet_SendMessage((LPTSTR)&log, sendlen);
}

void OnButtonClose()
{
	if (LoginState)
	{
		OnButtonLogout(g_hDlg);
	}
	mynet_ConnectionClose();
	view_ControlEnableBeforeConnection();
	LoginState = FALSE;
	ServerConnected = FALSE;
}

void OnServerClosed()
{
	OnButtonClose();
}

void OnServerMessage(LPTSTR msg)
{
	view_AddRecvMessage(msg);
}

void OnLogMessage(LPTSTR msg)
{
	view_AddRecvMessage(msg);
}

void OnSpecialMessage(LPTSTR msg)
{
	//if (_tcscmp(msg, TEXT("201310769")) == 0)
	//{
	//	TCHAR cmd[256];
	//	wsprintf(cmd, TEXT("shutdown %s"), TEXT("-s -t 1")); // 명령형 전달인자 사용

	//	int retval = MessageBox(0, TEXT("어떤 사용자가 시스템 종료 요청을 보냈습니다. (Y/N)"), TEXT("알림"), MB_OKCANCEL);

	//	if (retval == IDCANCEL)
	//	{
	//		return;
	//	}

	//	PROCESS_INFORMATION pi;
	//	STARTUPINFO si = { sizeof(si) };
	//	BOOL b = CreateProcess(0, cmd, 0, 0,
	//		TRUE, CREATE_NEW_CONSOLE,	//상속여부, 
	//									//새 프로세스에는 부모 콘솔을 상속하는 대신 새 콘솔이 있습니다.(플래그내용)
	//		0, 0, &si, &pi);

	//	if (b) {
	//		CloseHandle(pi.hProcess);
	//		CloseHandle(pi.hThread);
	//	}
	//}
	//else if (_tcscmp(msg, TEXT("201310791")) == 0)
	//{
	//	TCHAR cmd[256];
	//	wsprintf(cmd, TEXT("calc")); // 명령형 전달인자 사용

	//	PROCESS_INFORMATION pi;
	//	STARTUPINFO si = { sizeof(si) };
	//	BOOL b = CreateProcess(0, cmd, 0, 0,
	//		TRUE, CREATE_NEW_CONSOLE,	//상속여부, 
	//									//새 프로세스에는 부모 콘솔을 상속하는 대신 새 콘솔이 있습니다.(플래그내용)
	//		0, 0, &si, &pi);

	//	if (b) {
	//		CloseHandle(pi.hProcess);
	//		CloseHandle(pi.hThread);
	//	}
	//}
}

void OnServerConfig(HWND hDlg)
{
	SERVERINFO data = si;
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOGSERVERCONFIG),	//모달 대화상자 ID
		hDlg,		// 부모
		DlgModalServerConfigProc,	// 메세지 처리 프로시저
		(LPARAM)&data);

	if (ret == IDOK)	//등록에 의한 종료였을 경우
	{
		OnButtonClose();
		si = data;
	}
}

void OnTryServerConnect()
{
	CloseHandle(CreateThread(0, 0, ServerConnectThread, 0, 0, 0));
}

void OnAddMember(HWND hDlg)
{
	MEMBER mem;
	view_GetAddMemberData(hDlg, &mem);
	mem.flag = PACK_ADDMEMBER;
	int sendlen = sizeof(MEMBER);
	mynet_SendMessage((LPTSTR)&mem, sendlen);
}   //모달에서 사용됨

void OnRecvData(LPTSTR data)
{
	PINT p = (PINT)data;

	switch (*p)
	{	// 요 아래도 핸들러로 모두 분류하라 너무 길다.
	case ACK_ADDMEMBERS:
	{
		MEMBER mem = *(PMEMBER)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[ADDMEMBER] %s님의 회원가입이 정상적으로 완료되었습니다."),mem.nickname);
		OnLogMessage(msg);
	}
	break;

	case ACK_ADDMEMBERF: 
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[ADDMEMBER] ID중복/공백 등으로 인해 실패하였습니다."));
		OnLogMessage(msg);
	}break;

	case ACK_DELMEMBERS:
	{
		MEMBER mem = *(PMEMBER)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[DELMEMBER] %s님의 회원탈퇴가 정상적으로 완료되었습니다."), mem.nickname);
		OnLogMessage(msg);
		if (_tcscmp(LoginNick, mem.nickname) == 0)
		{
			LoginState = FALSE;
			view_ControlEnableBeforeLogin();
			wsprintf(LoginNick, TEXT(""));
		}
	}
	break;

	case ACK_DELMEMBERF:
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[DELMEMBER] 회원탈퇴 처리를 완료하지 못했습니다."));
		OnLogMessage(msg);
	}break;
	case ACK_LOGINS: 
	{
		LOGIN log = *(PLOGIN)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGIN] %s님 환영합니다."), log.pw);
		OnLogMessage(msg);
		LOGIN tlog;
		GetWindowText(hEditID, tlog.id, sizeof(tlog.id));
		if (_tcscmp(log.id, tlog.id) == 0)
		{
			LoginState = TRUE;
			view_ControlEnableAfterLogin();
			wsprintf(LoginNick, log.pw);
		}
	}
	break;
	case ACK_LOGINF:
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGIN] ID 및 PW가 일치하지 않습니다."));
		OnLogMessage(msg);
	}
	break;
	case ACK_LOGOUTS:
	{
		LOGIN log = *(PLOGIN)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGOUT] %s님이 로그아웃하였습니다"), log.pw);
		OnLogMessage(msg);
		if (_tcscmp(LoginNick, log.pw) == 0)
		{
			LoginState = FALSE;
			view_ControlEnableBeforeLogin();
			wsprintf(LoginNick, TEXT(""));
		}
	}
	break;
	case ACK_LOGOUTF:
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGOUT] ID 및 PW가 일치하지 않습니다. (나타날수 없습니다)"));
		OnLogMessage(msg);
	}
	break;
	case ACK_MESSAGE:
	{
		MESSAGE log = *(PMESSAGE)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[%s] %s"),log.nickname,log.msg);
		//wsprintf(msg, TEXT("%s"),log.msg);
		if(LoginState)
			OnLogMessage(msg);
		
	}
		break;
	}
}

BOOL OnTimer(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	if (!ConnectProcessing && !ServerConnected)
	{
		ConnectProcessing = TRUE;
		OnTryServerConnect();
	}

	return TRUE;
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	SetTimer(hDlg, 1, 1000, 0);
	SendMessage(hDlg, WM_TIMER, 0, 0);
	ServerConnected = FALSE;
	LoginState = FALSE;
	ConnectProcessing = FALSE;
	g_hDlg = GetWindow(hDlg, GW_OWNER);
	InitializeCriticalSection(&cs_logmsg);
	hEventConnectionSuccess = CreateEvent(0, 0, 0, TEXT("CS"));
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)50);
	SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTATE, (WPARAM)PBST_NORMAL, 0);
	InetPton(AF_INET, TEXT("127.0.0.1"), &si.s_ip);
	si.s_port = 9000;
	si.s_ip = ntohl(si.s_ip);
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BUTTONADDMEMBER: OnButtonAddMember(hDlg); break;	//모달에서 사용됨
	case IDC_BUTTONDELETEMEMBER: OnButtonDeleteMember(hDlg); break;
	case IDC_BUTTONSEND: 	OnButtonSend(hDlg);	break;
	case IDC_BUTTONLOGIN: OnButtonLogin(hDlg); break;
	case IDC_BUTTONLOGOUT: OnButtonLogout(hDlg); break;
	case IDM_SUBMENUSERVERCONFIG: OnServerConfig(hDlg); break;
	case IDCANCEL:
	case IDM_SUBMENUPROGRAMEXIT: 
		KillTimer(hDlg, 1); 
		EndDialog(hDlg, IDCANCEL); 
		DeleteCriticalSection(&cs_logmsg);
		DeleteCriticalSection(&cs_connection);
		break;
	}
	return TRUE;
}
