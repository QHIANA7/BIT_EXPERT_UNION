#define WIN32_LEAN_AND_MEAN	//헤더파일 충돌에대한 처리
#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "MainFrm.h"
#include "MFC_MultiEcho_ClientDoc.h"
#include "MFC_MultiEcho_ClientView.h"
#include "MyNet.h"



CMyNet::CMyNet()
{
	
}


CMyNet::~CMyNet()
{
	
}



BOOL CMyNet::mynet_ServerConnect(ULONG s_ip, USHORT s_port)
{

	CMyMFC_MultiEcho_ClientDoc* pDoc = (CMyMFC_MultiEcho_ClientDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();
	CMyMFC_MultiEcho_ClientView* pView = (CMyMFC_MultiEcho_ClientView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	//==================== 주 스레드를 탈출 시켜야 하기에 전역으로 빼자 ======
	gs_ip = s_ip;
	gs_port = s_port;
	//=====================================================================

	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		pView->view_OnLogMessage(TEXT("Can't Initialize Socket !"));
		return FALSE;
	}

	//================= 클라이언트용 통신 소켓 생성 ==========================
	s = socket(AF_INET, SOCK_STREAM, 0);
	//========================================================================

	// 2. 소켓주소 지정(bind) -> client 는 생략 가능 
	//    생략 하면 OS가 임의의 포트를 지정해 준다

	//============================ 서버측 주소 설정 ==========================
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(gs_port);
	addr.sin_addr.s_addr = htonl(gs_ip);
	//========================================================================


	//================ Connect를 이용해 서버측에 연결 ========================
	//connect는 블록킹함수 이므로 몇초 정도 대기하게된다.
	if (connect(s, (PSOCKADDR)&addr, sizeof(addr)) == -1)
	{
		pView->view_OnLogMessage(TEXT("[SYSTEM] 서버와 연결할 수 없습니다"));
		return FALSE;
	}
	//========================================================================

	//SetEvent(hEventConnectionSuccess);
	pView->view_OnLogMessage(TEXT("[SYSTEM] 서버에 연결되었습니다"));


	//=========== 주 스레드에서 send를 해야하기때문에 탈출해야 한다===========
	// 새로운 스레드를 만들어서 서버에서 오는 data를 수신한다

	tData.pMyNet = this;
	tData.pDoc = (CDocument*)pDoc;
	tData.pView = (CView*)pView;
	tData.s = 0;
	CWinThread *pThread = AfxBeginThread(RecvThread, (LPVOID)&tData);
	//pThread->Delete();
	return TRUE;
	//========================================================================

	//WSACleanup() 과 소켓을 닫는 동작은 WM_COMMAND의 해제 버튼을 눌렀을때의 동작으로 수행한다.
}


//msg : 전송할 데이터의 시작 주소
//length : 전송할 데이터의 byte 크기
BOOL CMyNet::mynet_SendMessage(LPTSTR msg, int sendlen)
{
	//================= 가변 데이터 길이 전송 ======
	send(s, (LPSTR)&sendlen, sizeof(int), 0);
	send(s, (LPSTR)msg, sendlen, 0);
	//==============================================

	//============== send를 하기위해 초기화 및 멀티바이트로 변환 =====================
	//char buf[MAX_BUFFER_SIZE] = { 0 };
	//memset(buf, 0, MAX_BUFFER_SIZE);
	//
	//WideCharToMultiByte(CP_ACP, 0, tbuf, -1, buf, MAX_BUFFER_SIZE, 0, 0);
	//======================================================이것은 쓸데없는 코드가 되었습니다. 글 내려주세요.

	//send(s, buf, strlen(buf) + 1, 0);	//이럴 이유가 전혀없다. 양측이 같다면 유니코드상으로 보내도됨
	//상단의 가변데이터길이로 해보았습니다.
	//이는 인자가 결국에 시작주소와 크기이기 때문에 가능한 것임

	//send(s, (LPSTR)tbuf, (_tcslen(tbuf) + 1) * 2, 0);	//전송!
	return TRUE;
}

void CMyNet::mynet_ConnectionClose()
{
	closesocket(s);
	WSACleanup();
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

}


UINT CMyNet::RecvThread(LPVOID data)
{
	PTHREADDATA pTData = (PTHREADDATA)data;
	CMyMFC_MultiEcho_ClientDoc* pDoc = (CMyMFC_MultiEcho_ClientDoc*)pTData->pDoc;
	CMyMFC_MultiEcho_ClientView* pView = (CMyMFC_MultiEcho_ClientView*)pTData->pView;
	CMyNet* pMyNet = pTData->pMyNet;
	SOCKET sock = pMyNet->getSocket();//서버측 소켓, 클라이언트의 통신소켓

						//==================== 대기 소켓을 이용한 통신 소켓의 정보 ===============
	TCHAR c_ip[MAX_IPADDR_LENGTH];
	SOCKADDR_IN c_addr;
	int size = sizeof(c_addr);
	getpeername(sock, (PSOCKADDR)&c_addr, &size);

	InetNtop(AF_INET, &c_addr.sin_addr, c_ip, MAX_IPADDR_LENGTH);

	//MultiByteToWideChar(CP_ACP, 0, inet_ntoa(c_addr.sin_addr), -1, addr, MAX_IPADDR_LENGTH);	//경고 발생
	//=========================================================================

	// 서버에서 오는 data를 수신한다.
	TCHAR tbuf[MAX_BUFFER_DECLARE_SIZE];
	//TCHAR msg[MAX_MESSAGE_LENGHT];
	//char buf[MAX_BUFFER_SIZE];
	int nRead;
	while (1)
	{
		memset(tbuf, 0, MAX_BUFFER_USE_SIZE);
		//nRead = recv(s, (LPSTR)tbuf, MAX_BUFFER_USE_SIZE, 0);
		//아래의 가변 데이터 길이을 사용합니다.


		//================= 가변 데이터 길이 리시브 ====================
		int recvlen;
		nRead = pMyNet->recvn(sock, (LPSTR)&recvlen, sizeof(int), 0);
		if (nRead <= 0) break;

		nRead = pMyNet->recvn(sock, (LPSTR)tbuf, recvlen, 0);
		if (nRead <= 0) break;
		//==============================================================

		pView->view_OnRecvData(tbuf);

	}
	pView->view_OnLogMessage(TEXT("[SYSTEM] 서버와의 접속이 끊어 졌습니다"));
	pMyNet->gs_ip = 0;
	pMyNet->gs_port = 0;
	closesocket(sock);
	pView->view_OnServerClosed();
	return 0;
}

UINT CMyNet::ServerConnectThread(LPVOID data)
{
	PTHREADDATA pTData = (PTHREADDATA)data;
	CMyMFC_MultiEcho_ClientDoc* pDoc = (CMyMFC_MultiEcho_ClientDoc*)pTData->pDoc;
	CMyMFC_MultiEcho_ClientView* pView = (CMyMFC_MultiEcho_ClientView*)pTData->pView;
	CMyNet* pMyNet = pTData->pMyNet;
	//==================== 주 스레드를 탈출 시켜야 하기에 전역으로 빼자 ======
	pMyNet->gs_ip = pTData->s_ip;
	pMyNet->gs_port = pTData->s_port;
	//========================================================================

	//================= 초기화 부분 (DLL -> 메모리) ==========================
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		pView->view_OnLogMessage(TEXT("[SYSTEM] 소켓을 초기화 할 수 없었습니다"));
		pDoc->ConnectProcessing = FALSE;
		return 0;
	}
	//========================================================================

	//================= 클라이언트용 통신 소켓 생성 ==========================
	pMyNet->s = socket(AF_INET, SOCK_STREAM, 0);
	//========================================================================

	// 2. 소켓주소 지정(bind) -> client 는 생략 가능 
	//    생략 하면 OS가 임의의 포트를 지정해 준다

	//============================ 서버측 주소 설정 ==========================
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(pMyNet->gs_port);
	addr.sin_addr.s_addr = htonl(pMyNet->gs_ip);
	//========================================================================


	//================ Connect를 이용해 서버측에 연결 ========================
	//connect는 블록킹함수 이므로 몇초 정도 대기하게된다.
	if (connect(pMyNet->s, (PSOCKADDR)&addr, sizeof(addr)) == -1)
	{
		pView->view_OnLogMessage(TEXT("[SYSTEM] 서버와 연결할 수 없습니다"));
		pDoc->ConnectProcessing = FALSE;
		return FALSE;
	}
	//========================================================================

	//SetEvent(hEventConnectionSuccess);
	pView->view_OnLogMessage(TEXT("[SYSTEM] 서버에 연결되었습니다"));


	//=========== 주 스레드에서 send를 해야하기때문에 탈출해야 한다===========
	// 새로운 스레드를 만들어서 서버에서 오는 data를 수신한다
	pMyNet->tData.pMyNet = pMyNet;
	pMyNet->tData.pDoc = (CDocument*)pDoc;
	pMyNet->tData.pView = (CView*)pView;
	pMyNet->tData.s = 0;

	CWinThread *pThread = AfxBeginThread(RecvThread, (LPVOID)&pMyNet->tData);
	pDoc->ServerConnected = TRUE;
	pDoc->ConnectProcessing = FALSE;
	pView->view_ControlEnableAfterConnection();
	return TRUE;
	//========================================================================

	//WSACleanup() 과 소켓을 닫는 동작은 WM_COMMAND의 해제 버튼을 눌렀을때의 동작으로 수행한다.
}