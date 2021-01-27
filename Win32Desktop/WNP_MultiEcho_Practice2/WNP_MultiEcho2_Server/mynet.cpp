
//mynet.cpp
#include "std.h"

vector<SOCKET> client_list;	//���⼭�� ����� ���̱� ������ ������Ʈ �������� ���� ����


BOOL mynet_StartServer(USHORT port)
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		OnLogMessage(TEXT("Can't Initialize Socket !"));
		return FALSE;
	}
	//--------------------------------------------
	// 1. socket ���� : TCP : SOCK_STREAM     UDP : SOCK_DGRAM
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	// 2. ������ ���Ͽ� �ּҸ� ����
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		 // �ּ� ����(AF_INET : IP �ּҶ�� �ǹ�)
	addr.sin_port = htons(port); // Port #
	addr.sin_addr.s_addr = INADDR_ANY;	// �ڽ��� ��� IP ��� 

	if (bind(s, (PSOCKADDR)&addr, sizeof(addr)) == -1)
	{
		OnLogMessage(TEXT("Can't bind")); return FALSE;
	}




	// 3. ������ ��� ���·� ��ȯ�Ѵ�.
	if (listen(s, 5) == -1)
	{
		OnLogMessage(TEXT("Can't Listen")); return FALSE;
	}

	HANDLE hThread = CreateThread(0, 0, ListenThread, (LPVOID)s, 0, 0);
	CloseHandle(hThread);

	HANDLE hThread2 = CreateThread(0, 0, WaitServerClose,(LPVOID)s ,0, 0);
	CloseHandle(hThread2);

	return TRUE;
}

DWORD WINAPI WaitServerClose(LPVOID data)
{
	SOCKET s = (SOCKET)data;
	WaitForSingleObject(hEventServerClose, INFINITE);
	for (int i = 0; i < (int)g_SocketInfo.size(); i++)
	{
		SOCKET cur = g_SocketInfo[i].socket;
		closesocket(cur);
	}
	closesocket(s);
	g_SocketInfo.clear();
	client_list.clear();
	WSACleanup();
	return 0;
}

DWORD WINAPI ListenThread(LPVOID data)
{
	SOCKET s = (SOCKET)data;
	OnLogMessage(TEXT("Ŭ���̾�Ʈ�� ����մϴ�"));

	// 4. ���� Client ���� ���� ���޵� ��û�� ����Ѵ�.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (PSOCKADDR)&c_addr, &size);


		//========= ���� ���� �۵��� ���ѷ��� Ż�� =================
		int retval = WaitForSingleObject(hEventServerClose, 0);
		if (retval == WAIT_OBJECT_0)
		{
			ResetEvent(hEventServerClose);	// �������� �ñ׳� -> �� �ñ׳�
			break;
		}
		//==========================================================

		//�̰� �߿� �޽����� 
		TCHAR logbuf[MAX_MESSAGE_LENGHT];
		TCHAR c_ip[MAX_IPADDR_LENGTH];
		
		InetNtop(AF_INET, &c_addr.sin_addr,c_ip, MAX_IPADDR_LENGTH);
		//���� ��Ƽ -> �����ڵ� ��ȯ �ڵ�� ���� ���� �����ϴ�. ������ ���ٸ� �״�� �����ϴ�.
		//char multiC_addr[32];
		//MultiByteToWideChar(CP_ACP, 0, inet_ntop(AF_INET, &c_addr.sin_addr, multiC_addr, 32), -1, addr, 32);
		//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(c_addr.sin_addr), -1, addr, 32); //���
		wsprintf(logbuf, TEXT("Ŭ���̾�Ʈ�� �����߽��ϴ�. IP : %s"),
			c_ip);	//����->���ڿ�->ȣ��Ʈ ����Ʈ ����
		OnLogMessage(logbuf);

		// linked list �� socket�� �ִ´�.
		client_list.push_back(c_s);

		//================== DATA ����ü ������ ========================
		//�̺κ��� dataó���� ����ϴ� data.cpp���� �����ϴ°��� ����.

		DATA temp;
		TCHAR t_ip[MAX_IPADDR_LENGTH];
		SOCKADDR_IN t_addr;
		int taddr_size = sizeof(t_addr);

		int retavl = getsockname(s, (PSOCKADDR)&t_addr, &taddr_size);

		InetNtop(AF_INET, &t_addr.sin_addr, t_ip, MAX_IPADDR_LENGTH);
		//MultiByteToWideChar(CP_ACP, 0, inet_ntop(AF_INET, &c_addr.sin_addr, multiC_addr, 32), -1, addr, 32);
		//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(t_addr.sin_addr), -1, t_ip, 32);
		

		temp.socket = c_s;			//��� ����
		_tcscpy_s(temp.c_ip,c_ip);	//Ŭ���̾�Ʈ IP
		temp.c_port = ntohs(c_addr.sin_port);	//Ŭ���̾�Ʈ PORT
		_tcscpy_s(temp.t_ip, t_ip);	//���� IP
		temp.t_port = ntohs(t_addr.sin_port);	//���� PORT

		//g_SocketInfo.push_back(temp);	//vector�� ����

		OnClientConnect(temp);

		//==============================================================

		// ���ο� �����带 �����ؼ� Ŭ���� ��Ʈ�� ��û�� ó���Ѵ�.
		HANDLE hThread = CreateThread(0, 0, ComThread, (LPVOID)c_s, 0, 0);
		CloseHandle(hThread);
	}
	return 0;
}

DWORD WINAPI ComThread(LPVOID data)
{
	SOCKET s = (SOCKET)data;

	//==================== ��� ������ �̿��� ��� ������ ���� ===============
	TCHAR logbuf[MAX_MESSAGE_LENGHT];
	TCHAR c_ip[MAX_IPADDR_LENGTH];
	SOCKADDR_IN c_addr;
	int size = sizeof(c_addr);
	getpeername(s, (PSOCKADDR)&c_addr, &size);

	InetNtop(AF_INET, &c_addr.sin_addr, c_ip, MAX_IPADDR_LENGTH);
	//char multiC_addr[32];
	//MultiByteToWideChar(CP_ACP, 0, inet_ntop(AF_INET, &c_addr.sin_addr, multiC_addr, 32), -1, addr, 32);
	//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(c_addr.sin_addr), -1, addr, 32);	//���
	//=========================================================================

	TCHAR tbuf[MAX_BUFFER_DECLARE_SIZE] = { 0 };
	TCHAR msg[MAX_MESSAGE_LENGHT] = { 0 };
	int  nRead = 0;

	//char buf[1024] = { 0 };
	//int  nRead = 0;

	while (1)
	{

		memset(tbuf, 0, MAX_BUFFER_USE_SIZE);

		//=========================================================
		//nRead = recv(s, (LPSTR)tbuf, MAX_BUFFER_USE_SIZE, 0);
		int recvlen;
		nRead = recvn(s, (LPSTR)&recvlen, sizeof(int), 0);
		if (nRead <= 0) break;

		nRead = recvn(s, (LPSTR)tbuf, recvlen, 0);
		if (nRead <= 0) break;
		//=========================================================

		//memset(buf, 0, 1024);
		//nRead = recv(s, buf, 1024, 0);
		
		OnRecvData(tbuf);

		
		// ���� data�� list �� �ִ� ��� client���� ������.
		
		//MultiByteToWideChar(CP_ACP, 0, buf, -1, tbuf, 1024);

		//wsprintf(msg, TEXT("%10s�� �޽��� ���� : %s"), c_ip, tbuf);
		//OnClientMessage(msg);


		for (int i = 0; i < (int)client_list.size(); ++i)
		{
			//if (client_list[i] != s)
				//send(client_list[i], (LPSTR)tbuf, nRead, 0);
				mynet_SendMessage(client_list[i], tbuf, recvlen);
		}
	}

	// ������ ���� �� ��� list ���� �����Ѵ�.
	for (int i = 0; i < (int)client_list.size(); ++i)
	{
		if (client_list[i] == s)
		{
			vector<SOCKET>::iterator p = client_list.begin();
			p = p + i;
			client_list.erase(p);
			break;
		}
	}
	
	wsprintf(logbuf, TEXT("Ŭ���̾�Ʈ�� ���� �����߽��ϴ�. IP : %s"),
		c_ip);	//����->���ڿ�->ȣ��Ʈ ����Ʈ ����
	OnLogMessage(logbuf);
	OnClientClose(s);
	closesocket(s);
	return 0;
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

	return 0;
}

BOOL mynet_SendMessage(SOCKET s, LPTSTR msg, int sendlen)
{
	send(s, (LPSTR)&sendlen, sizeof(int), 0);
	send(s, (LPSTR)msg, sendlen, 0);
	return 0;
}
