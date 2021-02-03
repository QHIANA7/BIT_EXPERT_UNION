
// MFC_MultiEcho_ClientDoc.cpp : CMyMFC_MultiEcho_ClientDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_MultiEcho_Client.h"
#endif

#include "MFC_MultiEcho_ClientDoc.h"
#include "MFC_MultiEcho_ClientView.h"

#include <propkey.h>
#include <WS2tcpip.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyMFC_MultiEcho_ClientDoc

IMPLEMENT_DYNCREATE(CMyMFC_MultiEcho_ClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyMFC_MultiEcho_ClientDoc, CDocument)
END_MESSAGE_MAP()


// CMyMFC_MultiEcho_ClientDoc 생성/소멸

CMyMFC_MultiEcho_ClientDoc::CMyMFC_MultiEcho_ClientDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	ServerConnected = FALSE;
	LoginState = FALSE;
	ConnectProcessing = FALSE;

	InetPton(AF_INET, TEXT("127.0.0.1"), &m_si.s_ip);
	m_si.s_port = 9000;
	m_si.s_ip = ntohl(m_si.s_ip);
	pMyNet = new CMyNet();
}

CMyMFC_MultiEcho_ClientDoc::~CMyMFC_MultiEcho_ClientDoc()
{
}



BOOL CMyMFC_MultiEcho_ClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMyMFC_MultiEcho_ClientDoc serialization

void CMyMFC_MultiEcho_ClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMyMFC_MultiEcho_ClientDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMyMFC_MultiEcho_ClientDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyMFC_MultiEcho_ClientDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyMFC_MultiEcho_ClientDoc 진단

#ifdef _DEBUG
void CMyMFC_MultiEcho_ClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyMFC_MultiEcho_ClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyMFC_MultiEcho_ClientDoc 명령


void CMyMFC_MultiEcho_ClientDoc::doc_OnTryServerConnect()
{
	POSITION pos = GetFirstViewPosition();	//뷰 포지션

	tData.pMyNet = pMyNet;
	tData.pView = ((CMyMFC_MultiEcho_ClientView*)GetNextView(pos));
	tData.pDoc = this;
	tData.s = 0;
	tData.s_ip = m_si.s_ip;
	tData.s_port = m_si.s_port;
	CWinThread *pThread = AfxBeginThread(CMyNet::ServerConnectThread, (LPVOID)&tData);
}


void CMyMFC_MultiEcho_ClientDoc::doc_OnButtonClose()
{
	
}


void CMyMFC_MultiEcho_ClientDoc::doc_OnServerClosed()
{
	doc_OnButtonClose();
}
