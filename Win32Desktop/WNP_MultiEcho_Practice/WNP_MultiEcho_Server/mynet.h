#pragma once
//mynet.h

BOOL mynet_StartServer(USHORT port);

DWORD WINAPI WaitServerClose(LPVOID data);
DWORD WINAPI ListenThread(LPVOID data);	//accept ���� ������
DWORD WINAPI ComThread(LPVOID data);	//recv-send ���� ������ (Echo ������)

int recvn(SOCKET s, LPSTR buf, int len, int flags);
BOOL mynet_SendMessage(SOCKET s, LPTSTR msg, int length);