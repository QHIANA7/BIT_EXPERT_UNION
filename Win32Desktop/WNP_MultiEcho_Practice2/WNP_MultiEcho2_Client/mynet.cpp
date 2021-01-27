//mynet.cpp

#include "std.h"

static ULONG gs_ip = 0;
static USHORT gs_port = 0;
static SOCKET s; //mynet.cpp ���� ���� ��� ����

BOOL mynet_ServerConnect(ULONG s_ip, USHORT s_port)
{
	//==================== �� �����带 Ż�� ���Ѿ� �ϱ⿡ �������� ���� ======
	gs_ip = s_ip;
	gs_port = s_port;
	//========================================================================


	//================= �ʱ�ȭ �κ� (DLL -> �޸�) ==========================
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		OnLogMessage(TEXT("[SYSTEM] ������ �ʱ�ȭ �� �� �������ϴ�"));
		return FALSE;
	}
	//========================================================================


	//================= Ŭ���̾�Ʈ�� ��� ���� ���� ==========================
	s = socket(AF_INET, SOCK_STREAM, 0);
	//========================================================================

	// 2. �����ּ� ����(bind) -> client �� ���� ���� 
	//    ���� �ϸ� OS�� ������ ��Ʈ�� ������ �ش�

	//============================ ������ �ּ� ���� ==========================
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(gs_port);
	addr.sin_addr.s_addr = htonl(gs_ip);
	//========================================================================


	//================ Connect�� �̿��� �������� ���� ========================
	//connect�� ���ŷ�Լ� �̹Ƿ� ���� ���� ����ϰԵȴ�.
	if (connect(s, (PSOCKADDR)&addr, sizeof(addr)) == -1)
	{
		OnLogMessage(TEXT("[SYSTEM] ������ ������ �� �����ϴ�"));
		return FALSE;
	}
	//========================================================================

	SetEvent(hEventConnectionSuccess);
	OnLogMessage(TEXT("[SYSTEM] ������ ����Ǿ����ϴ�"));


	//=========== �� �����忡�� send�� �ؾ��ϱ⶧���� Ż���ؾ� �Ѵ�===========
	// ���ο� �����带 ���� �������� ���� data�� �����Ѵ�
	HANDLE hThread = CreateThread(0, 0, RecvThread, (LPVOID)s, 0, 0);
	CloseHandle(hThread);
	return TRUE;
	//========================================================================

	//WSACleanup() �� ������ �ݴ� ������ WM_COMMAND�� ���� ��ư�� ���������� �������� �����Ѵ�.
}


//msg : ������ �������� ���� �ּ�
//length : ������ �������� byte ũ��
BOOL mynet_SendMessage(LPTSTR msg, int sendlen)
{
	//================= ���� ������ ���� ���� ======
	send(s, (LPSTR)&sendlen, sizeof(int), 0);
	send(s, (LPSTR)msg, sendlen, 0);
	//==============================================

	//============== send�� �ϱ����� �ʱ�ȭ �� ��Ƽ����Ʈ�� ��ȯ =====================
	//char buf[MAX_BUFFER_SIZE] = { 0 };
	//memset(buf, 0, MAX_BUFFER_SIZE);
	//
	//WideCharToMultiByte(CP_ACP, 0, tbuf, -1, buf, MAX_BUFFER_SIZE, 0, 0);
	//======================================================�̰��� �������� �ڵ尡 �Ǿ����ϴ�. �� �����ּ���.

	//send(s, buf, strlen(buf) + 1, 0);	//�̷� ������ ��������. ������ ���ٸ� �����ڵ������ ��������
	//����� ���������ͱ��̷� �غ��ҽ��ϴ�.
	//�̴� ���ڰ� �ᱹ�� �����ּҿ� ũ���̱� ������ ������ ����

	//send(s, (LPSTR)tbuf, (_tcslen(tbuf) + 1) * 2, 0);	//����!
	return TRUE;
}

void mynet_ConnectionClose()
{
	closesocket(s);
	WSACleanup();
}

int recvn(SOCKET s, LPSTR buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);

}


DWORD WINAPI RecvThread(LPVOID data)
{
	s = (SOCKET)data;	//������ ����, Ŭ���̾�Ʈ�� ��ż���

	//==================== ��� ������ �̿��� ��� ������ ���� ===============
	TCHAR c_ip[MAX_IPADDR_LENGTH];
	SOCKADDR_IN c_addr;
	int size = sizeof(c_addr);
	getpeername(s, (PSOCKADDR)&c_addr, &size);

	InetNtop(AF_INET, &c_addr.sin_addr, c_ip, MAX_IPADDR_LENGTH);

	//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(c_addr.sin_addr), -1, addr, MAX_IPADDR_LENGTH);	//��� �߻�
	//=========================================================================

	// �������� ���� data�� �����Ѵ�.
	TCHAR tbuf[MAX_BUFFER_DECLARE_SIZE];
	TCHAR msg[MAX_MESSAGE_LENGHT];
	//char buf[MAX_BUFFER_SIZE];
	int nRead;
	while (1)
	{
		memset(tbuf, 0, MAX_BUFFER_USE_SIZE);
		//nRead = recv(s, (LPSTR)tbuf, MAX_BUFFER_USE_SIZE, 0);
		//�Ʒ��� ���� ������ ������ ����մϴ�.


		//================= ���� ������ ���� ���ú� ====================
		int recvlen;
		nRead = recvn(s, (LPSTR)&recvlen, sizeof(int), 0);
		if (nRead <= 0) break;

		nRead = recvn(s, (LPSTR)tbuf, recvlen, 0);
		if (nRead <= 0) break;
		//==============================================================

		OnRecvData(tbuf);

		//memset(buf, 0, MAX_BUFFER_SIZE);
		//nRead = recv(s, buf, MAX_BUFFER_SIZE, 0);


		//TCHAR tbuf[MAX_BUFFER_SIZE];
		
		//MultiByteToWideChar(CP_ACP, 0, buf, -1, tbuf, MAX_IPADDR_LENGTH);
		
		
		//wsprintf(msg, TEXT("%10s�� �޽��� ���� : %s"), c_ip, tbuf);
		//OnLogMessage(msg);

	}
	OnLogMessage(TEXT("[SYSTEM] �������� ������ ���� �����ϴ�"));
	gs_ip = 0;
	gs_port = 0;
	closesocket(s);
	OnButtonClose();
	return 0;
}

DWORD WINAPI ServerConnectThread(LPVOID data)
{
	//==================== �� �����带 Ż�� ���Ѿ� �ϱ⿡ �������� ���� ======
	gs_ip = si.s_ip;
	gs_port = si.s_port;
	//========================================================================


	//================= �ʱ�ȭ �κ� (DLL -> �޸�) ==========================
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		OnLogMessage(TEXT("[SYSTEM] ������ �ʱ�ȭ �� �� �������ϴ�"));
		ConnectProcessing = FALSE;
		return FALSE;
	}
	//========================================================================


	//================= Ŭ���̾�Ʈ�� ��� ���� ���� ==========================
	s = socket(AF_INET, SOCK_STREAM, 0);
	//========================================================================

	// 2. �����ּ� ����(bind) -> client �� ���� ���� 
	//    ���� �ϸ� OS�� ������ ��Ʈ�� ������ �ش�

	//============================ ������ �ּ� ���� ==========================
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(gs_port);
	addr.sin_addr.s_addr = htonl(gs_ip);
	//========================================================================


	//================ Connect�� �̿��� �������� ���� ========================
	//connect�� ���ŷ�Լ� �̹Ƿ� ���� ���� ����ϰԵȴ�.
	if (connect(s, (PSOCKADDR)&addr, sizeof(addr)) == -1)
	{
		OnLogMessage(TEXT("[SYSTEM] ������ ������ �� �����ϴ�"));
		ConnectProcessing = FALSE;
		return FALSE;
	}
	//========================================================================

	SetEvent(hEventConnectionSuccess);
	OnLogMessage(TEXT("[SYSTEM] ������ ����Ǿ����ϴ�"));


	//=========== �� �����忡�� send�� �ؾ��ϱ⶧���� Ż���ؾ� �Ѵ�===========
	// ���ο� �����带 ���� �������� ���� data�� �����Ѵ�
	HANDLE hThread = CreateThread(0, 0, RecvThread, (LPVOID)s, 0, 0);
	CloseHandle(hThread);
	ServerConnected = TRUE;
	ConnectProcessing = FALSE;
	view_ControlEnableAfterConnection();
	return TRUE;
	//========================================================================

	//WSACleanup() �� ������ �ݴ� ������ WM_COMMAND�� ���� ��ư�� ���������� �������� �����Ѵ�.
}