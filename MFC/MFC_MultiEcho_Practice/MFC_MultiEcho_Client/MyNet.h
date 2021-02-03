#pragma once

class CMyNet;

typedef struct tagTHREADDATA
{
	CMyNet* pMyNet;
	CView* pView;
	CDocument* pDoc;
	SOCKET  s;
	DWORD s_ip;
	USHORT s_port;
}THREADDATA, *PTHREADDATA;

class CMyNet
{
	ULONG gs_ip = 0;
	USHORT gs_port = 0;
	SOCKET s; //mynet.cpp 한정 전역 통신 소켓
	THREADDATA tData;
public:
	CMyNet();
	~CMyNet();
public:
	BOOL mynet_ServerConnect(ULONG s_ip, USHORT s_port);
	BOOL mynet_SendMessage(LPTSTR msg, int sendlen);

	void mynet_ConnectionClose();
	int recvn(SOCKET s, LPSTR buf, int len, int flags);

	SOCKET getSocket() { return s; }

public:
	static UINT ServerConnectThread(LPVOID data);
	static UINT RecvThread(LPVOID data);	//accept 전용 스레드
};

