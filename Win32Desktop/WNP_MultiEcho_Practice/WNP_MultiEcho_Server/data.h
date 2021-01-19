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

BOOL data_RemoveSocketInfo(SOCKET sk);

extern CRITICAL_SECTION cs;
extern CRITICAL_SECTION cs1;
extern HANDLE hEventServerClose;
extern vector<DATA> g_SocketInfo;

extern HWND hListSocket, hEditLog, hStaticSocketCount;