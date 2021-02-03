
// MFC_MultiEcho_ServerDoc.h : CMyMFC_MultiEcho_ServerDoc 클래스의 인터페이스
//


#pragma once
#include "MyNet.h"
#include "Data.h"


typedef struct tagMEMBER
{
	int flag;
	TCHAR nickname[20];
	TCHAR id[20];
	TCHAR pw[20];
}MEMBER, *PMEMBER;

//로그인/로그아웃(id)
typedef struct tagLOGIN
{
	int flag;
	TCHAR id[20];
	TCHAR pw[20];
}LOGIN, *PLOGIN;

//메시지
typedef struct tagMESSAGE
{
	int flag;
	TCHAR nickname[20];
	TCHAR msg[50];
}MESSAGE, *PMESSAGE;

class CMyMFC_MultiEcho_ServerDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMyMFC_MultiEcho_ServerDoc();
	DECLARE_DYNCREATE(CMyMFC_MultiEcho_ServerDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	UINT port;
	BOOL m_IsServerRun;
	CMyNet* pMyNet;
	vector<Data*> m_SocketInfo;
	vector<MEMBER> m_Memberlist;
	CRITICAL_SECTION cs1;

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMyMFC_MultiEcho_ServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	BOOL doc_RemoveSocketInfo(SOCKET s);
	void doc_OnRecvData(LPTSTR data);
	BOOL doc_AddMember(PMEMBER pdata);
	BOOL doc_DeleteMember(PMEMBER pdata);
	BOOL doc_Login(PLOGIN pdata);
	BOOL doc_Logout(PLOGIN pdata);
};
