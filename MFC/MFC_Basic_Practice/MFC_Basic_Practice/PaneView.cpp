#include "stdafx.h"
#include "MFC_Basic_Practice.h"
#include "PaneView.h"

// 런타임에 동적으로 생성
IMPLEMENT_DYNCREATE(CPaneView, CView)

CPaneView::CPaneView()
{
}


CPaneView::~CPaneView()
{
}

CMyMFC_Basic_PracticeDoc* CPaneView::GetDocument()
{
	return (CMyMFC_Basic_PracticeDoc*)m_pDocument;
}


void CPaneView::OnDraw(CDC * pDC)
{
	CMyMFC_Basic_PracticeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// View를 새롭게 만들경우 GetDocument()를 다시 만들어 주는게 
	// 좋다.
	// Doc의 list내용을 2배 확대해서 그린다.
	POSITION pos = pDoc->m_lineList.GetHeadPosition();
	CPen* pen = new CPen(PS_SOLID, 25, RGB(255, 0, 0));
	CPen* old = pDC->SelectObject(pen); // 수정.
	while (pos)
	{
		LINE * pLine = pDoc->m_lineList.GetNext(pos);
		pDC->MoveTo(pLine->ptFrom.x * 2, pLine->ptFrom.y * 2);
		pDC->LineTo(pLine->ptTo.x * 2, pLine->ptTo.y * 2);
	}
	delete pDC->SelectObject(old);

}
