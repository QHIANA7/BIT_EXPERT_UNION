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
	g_SocketInfo.push_back(dt);	//����Ʈ�� ����
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
	UINT port = 9000;	//�⺻ 9000 ��Ʈ

	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOGSERVEREXCUTE),	//��� ��ȭ���� ID
		hDlg,		// �θ�
		DlgModalProc,	// �޼��� ó�� ���ν���
		(LPARAM)&port);

	if (ret == IDOK)	//��Ͽ� ���� ���ῴ�� ���
	{
		//===========================	���� ���� �κ� ==============
		ResetEvent(hEventServerClose);
		mynet_StartServer(port);
	}
}

void OnServerExit(HWND hDlg)
{
	SetEvent(hEventServerClose);	//���� �ݴ� �̺�Ʈ �߻�
}

void OnRecvData(LPTSTR data)
{
	PINT p = (PINT)data;

	switch (*p)
	{
	case PACK_ADDMEMBER:
	{
		//============= ���Ϻκ��� data.cpp �� �����϶� =========
		PMEMBER mem = (PMEMBER)data;	
		if (data_AddMember(mem))	//����
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
		if (data_DeleteMember(mem))	//����
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
		if (data_Login(log))	//����
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
		if (data_Logout(log))	//����
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

