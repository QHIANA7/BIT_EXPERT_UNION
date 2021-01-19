#pragma once
//mynet.h

BOOL mynet_StartServer(USHORT port);

DWORD WINAPI WaitServerClose(LPVOID data);
DWORD WINAPI ListenThread(LPVOID data);	//accept 전용 스레드
DWORD WINAPI ComThread(LPVOID data);	//recv-send 전용 스레드 (Echo 스레드)

int recvn(SOCKET s, LPSTR buf, int len, int flags);
BOOL mynet_SendMessage(SOCKET s, LPTSTR msg, int length);