#define WIN32_LEAN_AND_MEAN	//헤더파일 충돌에대한 처리
#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "MainFrm.h"
#include "MFC_MultiEcho_ServerDoc.h"
#include "MFC_MultiEcho_ServerView.h"
#include "MyNet.h"
#include "Data.h"

CMyNet::CMyNet()
{
	
	
}

CMyNet::~CMyNet()
{
	
}

BOOL CMyNet::mynet_StartServer()
{
	CMyMFC_MultiEcho_ServerDoc* pDoc = (CMyMFC_MultiEcho_ServerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();
	CMyMFC_MultiEcho_ServerView* pView = (CMyMFC_MultiEcho_ServerView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		pView->view_OnLogMessage(TEXT("Can't Initialize Socket !"));
		return FALSE;
	}
	
	
	//--------------------------------------------
	// 1. socket 생성 : TCP : SOCK_STREAM     UDP : SOCK_DGRAM
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	// 2. 생성된 소켓에 주소를 지정
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		 // 주소 종류(AF_INET : IP 주소라는 의미)
	addr.sin_port = htons(pDoc->port); // Port #
	addr.sin_addr.s_addr = INADDR_ANY;	// 자신의 모든 IP 사용 

	if (bind(listen_socket, (PSOCKADDR)&addr, sizeof(addr)) == -1)
	{
		pView->view_OnLogMessage(TEXT("Can't bind")); return FALSE;
	}




	// 3. 소켓을 대기 상태로 전환한다.
	if (listen(listen_socket, 5) == -1)
	{
		pView->view_OnLogMessage(TEXT("Can't Listen")); return FALSE;
	}
	tData.pMyNet = this;
	tData.pDoc = (CDocument*)pDoc;
	tData.pView = (CView*)pView;
	tData.s = listen_socket;

	CWinThread *pThread = AfxBeginThread(ListenThread, (LPVOID)&tData);

	// 기존 API코드 사용가능
	//HANDLE hThread = CreateThread(0, 0, ListenThread,
	//	(LPVOID)this, 0, 0);
	//CloseHandle(hThread);

	return TRUE;
}

UINT CMyNet::ListenThread(LPVOID data)
{
	PTHREADDATA pTData = (PTHREADDATA)data;
	CMyNet* pMyNet = pTData->pMyNet;
	SOCKET s = pMyNet->getListenSocket();
	CMyMFC_MultiEcho_ServerDoc* pDoc = (CMyMFC_MultiEcho_ServerDoc*)pTData->pDoc;
	CMyMFC_MultiEcho_ServerView* pView = (CMyMFC_MultiEcho_ServerView*)pTData->pView;

	//원래 여기에 넘어오는것은 대기소켓입니다.
	pView->view_OnLogMessage(TEXT("클라이언트를 대기합니다"));

	// 4. 이제 Client 에서 부터 전달된 요청을 허용한다.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (PSOCKADDR)&c_addr, &size);

		if (c_s == INVALID_SOCKET)
			break;


		//이거 중요 메시지다 
		TCHAR logbuf[MAX_MESSAGE_LENGHT];
		TCHAR c_ip[MAX_IPADDR_LENGTH];

		InetNtop(AF_INET, &c_addr.sin_addr, c_ip, MAX_IPADDR_LENGTH);

		wsprintf(logbuf, TEXT("클라이언트가 연결되었습니다 IP : %s"),//접속
			c_ip);	//숫자->문자열->호스트 바이트 오더
		pView->view_OnLogMessage(logbuf);

		// linked list 에 socket을 넣는다.
		pMyNet->ClientSocketAdd(c_s);

		//================== DATA 구조체 생성부 ========================
		//이부분은 data처리를 담당하는 data.cpp에서 수행하는것이 좋다.

		Data* temp = new Data();
		TCHAR t_ip[MAX_IPADDR_LENGTH];
		SOCKADDR_IN t_addr;
		int taddr_size = sizeof(t_addr);

		int retavl = getsockname(s, (PSOCKADDR)&t_addr, &taddr_size);

		InetNtop(AF_INET, &t_addr.sin_addr, t_ip, MAX_IPADDR_LENGTH);



		temp->setSocket(c_s);			//통신 소켓
		temp->setCIp(c_ip);	//클라이언트 IP
		temp->setCPort(ntohs(c_addr.sin_port));	//클라이언트 PORT
		temp->setTIp(t_ip);	//현재 IP
		temp->setTPort(ntohs(t_addr.sin_port));	//현재 PORT

		pDoc->m_SocketInfo.push_back(temp);	//vector에 삽입
		pView->view_ListViewPrintAll();
		//OnClientConnect(temp);
		//==============================================================
		pTData->s = c_s;
		// 새로운 스레드를 생성해서 클라이 언트의 요청을 처리한다.
		CWinThread *pThread = AfxBeginThread(ComThread, (LPVOID)data);
	}
	return 0;
}

UINT CMyNet::ComThread(LPVOID data)
{
	PTHREADDATA pTData = (PTHREADDATA)data;
	CMyMFC_MultiEcho_ServerDoc* pDoc = (CMyMFC_MultiEcho_ServerDoc*)pTData->pDoc;
	CMyMFC_MultiEcho_ServerView* pView = (CMyMFC_MultiEcho_ServerView*)pTData->pView;
	SOCKET c_s = pTData->s;

	//==================== 대기 소켓을 이용한 통신 소켓의 정보 ===============
	TCHAR logbuf[MAX_MESSAGE_LENGHT];
	TCHAR c_ip[MAX_IPADDR_LENGTH];
	SOCKADDR_IN c_addr;
	int size = sizeof(c_addr);
	getpeername(c_s, (PSOCKADDR)&c_addr, &size);

	InetNtop(AF_INET, &c_addr.sin_addr, c_ip, MAX_IPADDR_LENGTH);
	//=========================================================================

	TCHAR tbuf[MAX_BUFFER_DECLARE_SIZE] = { 0 };
	TCHAR msg[MAX_MESSAGE_LENGHT] = { 0 };
	int  nRead = 0;


	while (1)
	{

		memset(tbuf, 0, MAX_BUFFER_USE_SIZE);

		//=========================================================
		//nRead = recv(s, (LPSTR)tbuf, MAX_BUFFER_USE_SIZE, 0);
		int recvlen;
		nRead = pTData->pMyNet->recvn(c_s, (LPSTR)&recvlen, sizeof(int), 0);
		if (nRead <= 0) break;

		nRead = pTData->pMyNet->recvn(c_s, (LPSTR)tbuf, recvlen, 0);
		if (nRead <= 0) break;
		//=========================================================


		pDoc->doc_OnRecvData(tbuf);

		//OnClientMessage(msg);


		for (int i = 0; i < pTData->pMyNet->SocketListSize(); ++i)
		{
			pTData->pMyNet->mynet_SendMessage(pTData->pMyNet->getClientSocket(i), tbuf, recvlen);
		}
	}

	// 접속이 끊어 진 경우 list 에서 제거한다.
	for (int i = 0; i < pTData->pMyNet->SocketListSize(); ++i)
	{
		if (pTData->pMyNet->getClientSocket(i) == c_s)
		{
			pTData->pMyNet->DeleteSocket(i);
			break;
		}
	}

	wsprintf(logbuf, TEXT("클라이언트의 연결이 종료되었습니다. IP : %s"),
		c_ip);	//숫자->문자열->호스트 바이트 오더
	pView->view_OnLogMessage(logbuf);
	pTData->pMyNet->mynet_OnClientClose(c_s);
	closesocket(c_s);
	return 0;
}

int CMyNet::recvn(SOCKET s, LPSTR buf, int len, int flags)
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

BOOL CMyNet::mynet_SendMessage(SOCKET s, LPTSTR msg, int sendlen)
{
	send(s, (LPSTR)&sendlen, sizeof(int), 0);
	send(s, (LPSTR)msg, sendlen, 0);
	return 0;
}

void CMyNet::mynet_OnCloseServer()
{
	for (int i = 0; i < (int)((CMyMFC_MultiEcho_ServerDoc*)tData.pDoc)->m_SocketInfo.size(); i++)
	{
		SOCKET cur = ((CMyMFC_MultiEcho_ServerDoc*)tData.pDoc)->m_SocketInfo[i]->getSocket();
		closesocket(cur);
	}
	closesocket(listen_socket);
	//((CMyMFC_MultiEcho_ServerDoc*)tData.pDoc)->m_SocketInfo.clear();
	client_list.clear();
	WSACleanup();
}

void CMyNet::mynet_OnClientClose(SOCKET s)
{
	((CMyMFC_MultiEcho_ServerDoc*)tData.pDoc)->doc_RemoveSocketInfo(s);
	((CMyMFC_MultiEcho_ServerView*)tData.pView)->view_ListViewPrintAll();
}
