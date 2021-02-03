
// MFC_MultiEcho_ClientDoc.h : CMyMFC_MultiEcho_ClientDoc 클래스의 인터페이스
//
#include "MyNet.h"

#pragma once
typedef struct tagSERVERINFO
{
	DWORD s_ip = 0;
	USHORT s_port = 0;
}SERVERINFO, *PSERVERINFO;

class CMyMFC_MultiEcho_ClientDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMyMFC_MultiEcho_ClientDoc();
	DECLARE_DYNCREATE(CMyMFC_MultiEcho_ClientDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	BOOL ServerConnected;
	BOOL LoginState;
	BOOL ConnectProcessing;
	CString LoginNick;
	CMyNet* pMyNet;
	SERVERINFO m_si;
	THREADDATA tData;


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
	virtual ~CMyMFC_MultiEcho_ClientDoc();
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
	void doc_OnTryServerConnect();
	void doc_OnButtonClose();
	void doc_OnServerClosed();
};
