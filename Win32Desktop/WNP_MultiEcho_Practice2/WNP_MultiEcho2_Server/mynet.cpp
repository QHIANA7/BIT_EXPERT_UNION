
//mynet.cpp
#include "std.h"

vector<SOCKET> client_list;	//여기서만 사용할 것이기 때문에 프로젝트 전역으로 쓰지 않음


BOOL mynet_StartServer(USHORT port)
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		OnLogMessage(TEXT("Can't Initialize Socket !"));
		return FALSE;
	}
	//--------------------------------------------
	// 1. socket 생성 : TCP : SOCK_STREAM     UDP : SOCK_DGRAM
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	// 2. 생성된 소켓에 주소를 지정
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		 // 주소 종류(AF_INET : IP 주소라는 의미)
	addr.sin_port = htons(port); // Port #
	addr.sin_addr.s_addr = INADDR_ANY;	// 자신의 모든 IP 사용 

	if (bind(s, (PSOCKADDR)&addr, sizeof(addr)) == -1)
	{
		OnLogMessage(TEXT("Can't bind")); return FALSE;
	}




	// 3. 소켓을 대기 상태로 전환한다.
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
	OnLogMessage(TEXT("클라이언트를 대기합니다"));

	// 4. 이제 Client 에서 부터 전달된 요청을 허용한다.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (PSOCKADDR)&c_addr, &size);


		//========= 서버 종료 작동시 무한루프 탈출 =================
		int retval = WaitForSingleObject(hEventServerClose, 0);
		if (retval == WAIT_OBJECT_0)
		{
			ResetEvent(hEventServerClose);	// 서버종료 시그널 -> 넌 시그널
			break;
		}
		//==========================================================

		//이거 중요 메시지다 
		TCHAR logbuf[MAX_MESSAGE_LENGHT];
		TCHAR c_ip[MAX_IPADDR_LENGTH];
		
		InetNtop(AF_INET, &c_addr.sin_addr,c_ip, MAX_IPADDR_LENGTH);
		//이하 멀티 -> 유니코드 변환 코드는 이제 쓸모 없습니다. 양측이 같다면 그대로 보냅니다.
		//char multiC_addr[32];
		//MultiByteToWideChar(CP_ACP, 0, inet_ntop(AF_INET, &c_addr.sin_addr, multiC_addr, 32), -1, addr, 32);
		//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(c_addr.sin_addr), -1, addr, 32); //경고
		wsprintf(logbuf, TEXT("클라이언트가 접속했습니다. IP : %s"),
			c_ip);	//숫자->문자열->호스트 바이트 오더
		OnLogMessage(logbuf);

		// linked list 에 socket을 넣는다.
		client_list.push_back(c_s);

		//================== DATA 구조체 생성부 ========================
		//이부분은 data처리를 담당하는 data.cpp에서 수행하는것이 좋다.

		DATA temp;
		TCHAR t_ip[MAX_IPADDR_LENGTH];
		SOCKADDR_IN t_addr;
		int taddr_size = sizeof(t_addr);

		int retavl = getsockname(s, (PSOCKADDR)&t_addr, &taddr_size);

		InetNtop(AF_INET, &t_addr.sin_addr, t_ip, MAX_IPADDR_LENGTH);
		//MultiByteToWideChar(CP_ACP, 0, inet_ntop(AF_INET, &c_addr.sin_addr, multiC_addr, 32), -1, addr, 32);
		//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(t_addr.sin_addr), -1, t_ip, 32);
		

		temp.socket = c_s;			//통신 소켓
		_tcscpy_s(temp.c_ip,c_ip);	//클라이언트 IP
		temp.c_port = ntohs(c_addr.sin_port);	//클라이언트 PORT
		_tcscpy_s(temp.t_ip, t_ip);	//현재 IP
		temp.t_port = ntohs(t_addr.sin_port);	//현재 PORT

		//g_SocketInfo.push_back(temp);	//vector에 삽입

		OnClientConnect(temp);

		//==============================================================

		// 새로운 스레드를 생성해서 클라이 언트의 요청을 처리한다.
		HANDLE hThread = CreateThread(0, 0, ComThread, (LPVOID)c_s, 0, 0);
		CloseHandle(hThread);
	}
	return 0;
}

DWORD WINAPI ComThread(LPVOID data)
{
	SOCKET s = (SOCKET)data;

	//==================== 대기 소켓을 이용한 통신 소켓의 정보 ===============
	TCHAR logbuf[MAX_MESSAGE_LENGHT];
	TCHAR c_ip[MAX_IPADDR_LENGTH];
	SOCKADDR_IN c_addr;
	int size = sizeof(c_addr);
	getpeername(s, (PSOCKADDR)&c_addr, &size);

	InetNtop(AF_INET, &c_addr.sin_addr, c_ip, MAX_IPADDR_LENGTH);
	//char multiC_addr[32];
	//MultiByteToWideChar(CP_ACP, 0, inet_ntop(AF_INET, &c_addr.sin_addr, multiC_addr, 32), -1, addr, 32);
	//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(c_addr.sin_addr), -1, addr, 32);	//경고
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

		
		// 받은 data를 list 에 있는 모든 client에게 보낸다.
		
		//MultiByteToWideChar(CP_ACP, 0, buf, -1, tbuf, 1024);

		//wsprintf(msg, TEXT("%10s의 메시지 전송 : %s"), c_ip, tbuf);
		//OnClientMessage(msg);


		for (int i = 0; i < (int)client_list.size(); ++i)
		{
			//if (client_list[i] != s)
				//send(client_list[i], (LPSTR)tbuf, nRead, 0);
				mynet_SendMessage(client_list[i], tbuf, recvlen);
		}
	}

	// 접속이 끊어 진 경우 list 에서 제거한다.
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
	
	wsprintf(logbuf, TEXT("클라이언트가 접속 해제했습니다. IP : %s"),
		c_ip);	//숫자->문자열->호스트 바이트 오더
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
