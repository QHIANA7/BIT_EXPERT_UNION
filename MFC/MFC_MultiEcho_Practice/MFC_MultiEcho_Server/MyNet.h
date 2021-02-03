#pragma once

class CMyNet;

typedef struct tagTHREADDATA
{
	CMyNet* pMyNet;
	CView* pView;
	CDocument* pDoc;
	SOCKET  s;
}THREADDATA, *PTHREADDATA;

class CMyNet
{
	SOCKET listen_socket;
	vector<SOCKET> client_list;
	THREADDATA tData;
public:
public:
	CMyNet();
	~CMyNet();
public:
	//시작하는 함수	//
	BOOL mynet_StartServer();
	int recvn(SOCKET s, LPSTR buf, int len, int flags);
	BOOL mynet_SendMessage(SOCKET s, LPTSTR msg, int length);
public:
	SOCKET getListenSocket() { return listen_socket; }
	void ClientSocketAdd(SOCKET s) { client_list.push_back(s); }
	int SocketListSize() { return (int)client_list.size(); }
	SOCKET getClientSocket(int idx) { return client_list[idx]; }
	void DeleteSocket(int idx)
	{
		client_list.erase(client_list.begin() + idx);
	}

private:
	static UINT ListenThread(LPVOID data);	//accept 전용 스레드
	static UINT ComThread(LPVOID data);	//recv-send 전용 스레드 (Echo 스레드)
//private: // WINAPI에서 사용했던 코드도 사용이 가능하다.
//	static DWORD WINAPI ListenThread(LPVOID data);
//	static DWORD WINAPI ComThread(LPVOID data);
public:
	void mynet_OnCloseServer();
	void mynet_OnClientClose(SOCKET s);
};