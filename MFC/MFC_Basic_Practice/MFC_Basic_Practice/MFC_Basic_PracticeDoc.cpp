
// MFC_Basic_PracticeDoc.cpp : CMyMFC_Basic_PracticeDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_Basic_Practice.h"
#endif

#include "MFC_Basic_PracticeDoc.h"
//#include <vector>
//using namespace std;

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyMFC_Basic_PracticeDoc

IMPLEMENT_DYNCREATE(CMyMFC_Basic_PracticeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyMFC_Basic_PracticeDoc, CDocument)
END_MESSAGE_MAP()


// CMyMFC_Basic_PracticeDoc 생성/소멸

CMyMFC_Basic_PracticeDoc::CMyMFC_Basic_PracticeDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_curData = new ShapeData(CPoint(0, 0), RGB(255, 0, 0), ID_SHAPE_RECT, ID_WIDTH_1);


}

CMyMFC_Basic_PracticeDoc::~CMyMFC_Basic_PracticeDoc()
{
}

BOOL CMyMFC_Basic_PracticeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	POSITION pos = m_lineList.GetHeadPosition();
	while (pos)
	{
		LINE* p = m_lineList.GetNext(pos);
		delete p;
	}
	m_lineList.RemoveAll();
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMyMFC_Basic_PracticeDoc serialization

void CMyMFC_Basic_PracticeDoc::Serialize(CArchive& ar)
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
void CMyMFC_Basic_PracticeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMyMFC_Basic_PracticeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyMFC_Basic_PracticeDoc::SetSearchContent(const CString& value)
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

// CMyMFC_Basic_PracticeDoc 진단

#ifdef _DEBUG
void CMyMFC_Basic_PracticeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyMFC_Basic_PracticeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyMFC_Basic_PracticeDoc 명령
