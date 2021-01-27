#pragma once
//data.h

typedef struct tagDATA
{
	UINT socket;
	TCHAR c_ip[32];
	USHORT c_port;
	TCHAR t_ip[32];
	USHORT t_port;
}DATA;

extern CRITICAL_SECTION cs;
extern CRITICAL_SECTION cs1;
extern HANDLE hEventServerClose;
extern vector<DATA> g_SocketInfo;
extern vector<MEMBER> g_Memberlist;

extern HWND g_hDlg, hListSocket, hEditLog, hStaticSocketCount, hMemberList, hStaticMemberCount;

extern int submenu2;

BOOL data_RemoveSocketInfo(SOCKET sk);

BOOL data_AddMember(PMEMBER pdata);
BOOL data_UserCompareMember(PLOGIN pdata);
BOOL data_DeleteMember(PMEMBER pdata);

BOOL data_Login(PLOGIN pdata);
BOOL data_Logout(PLOGIN pdata);
BOOL data_Message(PMESSAGE pdata);