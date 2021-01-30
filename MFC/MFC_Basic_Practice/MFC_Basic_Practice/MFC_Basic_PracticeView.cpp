
// MFC_Basic_PracticeView.cpp : CMyMFC_Basic_PracticeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_Basic_Practice.h"
#endif

#include "MFC_Basic_PracticeDoc.h"
#include "MFC_Basic_PracticeView.h"
#include "MainFrm.h"
#include "UI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMFC_Basic_PracticeView

IMPLEMENT_DYNCREATE(CMyMFC_Basic_PracticeView, CView)

BEGIN_MESSAGE_MAP(CMyMFC_Basic_PracticeView, CView)
	ON_COMMAND_RANGE(ID_COLOR_RED, ID_COLOR_BLUE, OnColor)
	ON_COMMAND_RANGE(ID_SHAPE_RECT, ID_SHAPE_ELLIPSE, OnShape)
	ON_COMMAND_RANGE(ID_WIDTH_1, ID_WIDTH_5, OnWidth)
	ON_COMMAND(ID_HELP_EXIT,OnAppInfo)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLOR_RED,ID_COLOR_BLUE,OnColorUpdate)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SHAPE_RECT, ID_SHAPE_ELLIPSE, OnShapeUpdate)
	ON_UPDATE_COMMAND_UI_RANGE(ID_WIDTH_1, ID_WIDTH_5, OnWidthUpdate)
	//ON_UPDATE_COMMAND_UI(ID_HELP_EXIT, OnAppInfo)
	ON_COMMAND(ID_COLOR_SELECT,OnCmdlgColor)	//색상선택 다이얼로그
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMyMFC_Basic_PracticeView 생성/소멸

CMyMFC_Basic_PracticeView::CMyMFC_Basic_PracticeView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMyMFC_Basic_PracticeView::~CMyMFC_Basic_PracticeView()
{
}

BOOL CMyMFC_Basic_PracticeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMyMFC_Basic_PracticeView 그리기

void CMyMFC_Basic_PracticeView::OnDraw(CDC* pDC)
{
	CMyMFC_Basic_PracticeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (int i = 0; i < (int)pDoc->m_vecList.size(); i++)
	{
		ShapeData* pData = pDoc->m_vecList[i];
		CPoint pt = pData->GetPt();

		CBrush *br = new CBrush(pData->GetColor());
		CBrush *oldBr = nullptr;
		pDC->SelectObject(br);

		CPen *pen = nullptr;
		switch (pData->GetWidth())
		{
		case ID_WIDTH_1:pen = new CPen(PS_SOLID, 1, RGB(0, 0, 0)); break;
		case ID_WIDTH_3:pen = new CPen(PS_SOLID, 3, RGB(0, 0, 0)); break;
		case ID_WIDTH_5:pen = new CPen(PS_SOLID, 5, RGB(0, 0, 0)); break;
		}
		
		CBrush *oldPen = nullptr;
		pDC->SelectObject(pen);



		if (pData->GetType() == ID_SHAPE_RECT)
		{
			pDC->Rectangle(pt.x, pt.y, pt.x + 100, pt.y + 100);
		}
		else
		{
			pDC->Ellipse(pt.x, pt.y, pt.x + 100, pt.y + 100);
		}
		delete pDC->SelectObject(oldPen);
		delete pDC->SelectObject(oldBr);
	}


	CPen* Lpen = new CPen(PS_SOLID, 5, RGB(0, 0, 255));
	CPen* Lold = pDC->SelectObject(Lpen);
	POSITION pos = pDoc->m_lineList.GetHeadPosition();
	while (pos)
	{
		LINE* p = pDoc->m_lineList.GetNext(pos);
		pDC->MoveTo(p->ptFrom);
		pDC->LineTo(p->ptTo);
	}
	delete pDC->SelectObject(Lold);


}


// CMyMFC_Basic_PracticeView 진단

#ifdef _DEBUG
void CMyMFC_Basic_PracticeView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMFC_Basic_PracticeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMFC_Basic_PracticeDoc* CMyMFC_Basic_PracticeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFC_Basic_PracticeDoc)));
	return (CMyMFC_Basic_PracticeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFC_Basic_PracticeView 메시지 처리기


void CMyMFC_Basic_PracticeView::OnColor(UINT nID)
{
	switch (nID) // 메뉴 ID
	{
	case ID_COLOR_RED:
		GetDocument()->m_curData->SetColor(RGB(255, 0, 0));		break;
	case ID_COLOR_GREEN:
		GetDocument()->m_curData->SetColor(RGB(0, 255, 0));		break;
	case ID_COLOR_BLUE:
		GetDocument()->m_curData->SetColor(RGB(0, 0, 255));		break;
	}

	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	CUI::Pane_PrintColor(p,GetDocument()->m_curData->GetColor());
}


void CMyMFC_Basic_PracticeView::OnShape(UINT nID)
{
	switch (nID) // 메뉴 ID
	{
	case ID_SHAPE_RECT:
		GetDocument()->m_curData->SetType(ID_SHAPE_RECT);		break;
	case ID_SHAPE_ELLIPSE:
		GetDocument()->m_curData->SetType(ID_SHAPE_ELLIPSE);	break;
	}
	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	CUI::Pane_PrintType(p, GetDocument()->m_curData->GetType());
}


void CMyMFC_Basic_PracticeView::OnWidth(UINT nID)
{
	switch (nID) // 메뉴 ID
	{
	case ID_WIDTH_1:
		GetDocument()->m_curData->SetWidth(ID_WIDTH_1);		break;
	case ID_WIDTH_3:
		GetDocument()->m_curData->SetWidth(ID_WIDTH_3);		break;
	case ID_WIDTH_5:
		GetDocument()->m_curData->SetWidth(ID_WIDTH_5);		break;
	}
	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	CUI::Pane_PrintWidth(p, GetDocument()->m_curData->GetWidth());
}


void CMyMFC_Basic_PracticeView::OnAppInfo()
{
}


// 브러쉬 색상 메뉴 UI처리
void CMyMFC_Basic_PracticeView::OnColorUpdate(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_COLOR_RED:
		pCmdUI->SetCheck(GetDocument()->m_curData->GetColor() == RGB(255, 0, 0)); 	break;
	case ID_COLOR_GREEN:
		pCmdUI->SetCheck(GetDocument()->m_curData->GetColor() == RGB(0, 255, 0)); 	break;
	case ID_COLOR_BLUE:
		pCmdUI->SetCheck(GetDocument()->m_curData->GetColor() == RGB(0, 0, 255)); 	break;
	}
}


// 모양 메뉴 UI처리

void CMyMFC_Basic_PracticeView::OnShapeUpdate(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_SHAPE_RECT:
		pCmdUI->Enable(GetDocument()->m_curData->GetType() != ID_SHAPE_RECT); break;
	case ID_SHAPE_ELLIPSE:
		pCmdUI->Enable(GetDocument()->m_curData->GetType() != ID_SHAPE_ELLIPSE); break;
	}
}


// 두께 메뉴 UI처리
void CMyMFC_Basic_PracticeView::OnWidthUpdate(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_WIDTH_1:
		pCmdUI->SetCheck(GetDocument()->m_curData->GetWidth() == ID_WIDTH_1); 	break;
	case ID_WIDTH_3:
		pCmdUI->SetCheck(GetDocument()->m_curData->GetWidth() == ID_WIDTH_3); 	break;
	case ID_WIDTH_5:
		pCmdUI->SetCheck(GetDocument()->m_curData->GetWidth() == ID_WIDTH_5); 	break;
	}
}


int CMyMFC_Basic_PracticeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.



	return 0;
}


void CMyMFC_Basic_PracticeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//GetDocument()->m_curData->SetPt(point);
	//CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	//CUI::Pane_PrintPT(p, GetDocument()->m_curData->GetPt());
	if (GetCapture() == this)
	{
		CClientDC dc(this);
		CPen* pen = new CPen(PS_SOLID, 5, RGB(0, 0, 255));
		CPen* old = dc.SelectObject(pen);

		dc.SetROP2(R2_NOTXORPEN);
		dc.MoveTo(m_ptFrom);
		dc.LineTo(m_ptOld);

		dc.MoveTo(m_ptFrom);
		dc.LineTo(point);

		m_ptOld = point;

		delete dc.SelectObject(old);
	}

	CView::OnMouseMove(nFlags, point);
}


void CMyMFC_Basic_PracticeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ShapeData *pData = GetDocument()->m_curData;

	//======================= 상태바 변경 ==========
	pData->SetPt(point);
	CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
	CUI::Pane_PrintPT(p, pData->GetPt());
	//==============================================

	//==================== 저장 및 무효화영역 ======
	ShapeData* temp_Shape = new ShapeData(point, pData->GetColor(), pData->GetType(), pData->GetWidth());

	GetDocument()->m_vecList.push_back(temp_Shape);

	//========================= 정적 분할 선그리기 =====
	m_ptFrom = m_ptOld = point;
	SetCapture();
	//==================================================
	
	Invalidate(FALSE);
	GetDocument()->UpdateAllViews(this, 0, 0);

	CView::OnLButtonDown(nFlags, point);
}


void CMyMFC_Basic_PracticeView::OnCmdlgColor()
{
	ShapeData *pData = GetDocument()->m_curData;

	//COLORREF color = RGB(0, 0, 0);
	CColorDialog dlg(pData->GetColor());
	//위에 들어가는 인자는 다이얼로그를 열었을때의 초기값이다.
	if (dlg.DoModal() == IDOK) {	// dlg.DoModal()이 다이얼로그를 여는 함수다.
		CString str;
		//color = dlg.GetColor();
		pData->SetColor(dlg.GetColor());
		str.Format(TEXT("색상 : (%d, %d, %d)"), GetRValue(pData->GetColor()),
			GetGValue(pData->GetColor()),
			GetBValue(pData->GetColor()));
		AfxMessageBox(str);

		CMainFrame* p = (CMainFrame*)AfxGetMainWnd();
		CUI::Pane_PrintColor(p, pData->GetColor());
	}
}


void CMyMFC_Basic_PracticeView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu menu;
	menu.LoadMenu(IDR_MYMENU); // 메뉴 아이디

	CMenu *pMenu = menu.GetSubMenu(1); //서브메뉴 몇번째꺼
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTALIGN,
		point.x, point.y, AfxGetMainWnd());
}


void CMyMFC_Basic_PracticeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//정적 분할 윈도우 선 그리기
	if (GetCapture() == this)
	{
		ReleaseCapture();
		CClientDC dc(this);
		CPen* pen = new CPen(PS_SOLID, 5, RGB(0, 0, 255));
		CPen* old = dc.SelectObject(pen);

		dc.MoveTo(m_ptFrom);
		dc.LineTo(point);

		delete dc.SelectObject(old);
		// Document에 저장한다.
		CMyMFC_Basic_PracticeDoc* pDoc = GetDocument();
		LINE* pLine = new LINE(m_ptFrom, point);

		pDoc->m_lineList.AddTail(pLine);
		// 모든 View를 다시 그리게 한다.
		
		pDoc->UpdateAllViews(this);
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMyMFC_Basic_PracticeView::OnUpdate(CView* pSender,	LPARAM lHint,	CObject* pHint)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (lHint == 1) // 선은 1개만 추가된 경우이다. 전체를 무효화
	{				// 할 필요는 없다.
		LINE* pLine = (LINE*)pHint;

		// 화면을 무효화 하는 대신 1개선을 여기서 그려주자..
		CClientDC dc(this);
		CPen pen(PS_SOLID, 5, RGB(0, 0, 255));
		CPen* old = dc.SelectObject(&pen);

		dc.MoveTo(pLine->ptFrom);
		dc.LineTo(pLine->ptTo);

		dc.SelectObject(old);
		return;
	}
	// 그외에는 화면 전체 무효화
	InvalidateRect(0);
}
