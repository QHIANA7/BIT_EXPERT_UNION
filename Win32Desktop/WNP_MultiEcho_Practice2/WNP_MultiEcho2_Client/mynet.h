#pragma once
//mynet.h

BOOL mynet_ServerConnect(ULONG s_ip, USHORT s_port);
BOOL mynet_SendMessage(LPTSTR msg, int sendlen);

void mynet_ConnectionClose();
int recvn(SOCKET s, LPSTR buf, int len, int flags);

DWORD WINAPI ServerConnectThread(LPVOID data);
DWORD WINAPI RecvThread(LPVOID data);	//accept 전용 스레드