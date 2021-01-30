
// MFC_Basic_PracticeView.h : CMyMFC_Basic_PracticeView 클래스의 인터페이스
//

#pragma once


class CMyMFC_Basic_PracticeView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMyMFC_Basic_PracticeView();
	DECLARE_DYNCREATE(CMyMFC_Basic_PracticeView)

// 특성입니다.
public:
	CMyMFC_Basic_PracticeDoc* GetDocument() const;

// 작업입니다.
public:
	CPoint m_ptFrom;
	CPoint m_ptOld;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMyMFC_Basic_PracticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnColor(UINT nID);
	void OnShape(UINT nID);
	void OnWidth(UINT nID);
	void OnAppInfo();
	// 브러쉬 색상 메뉴 UI처리
	void OnColorUpdate(CCmdUI* pCmdUI);
	// 모양 메뉴 UI처리
	void OnShapeUpdate(CCmdUI* pCmdUI);
	// 두께 메뉴 UI처리
	void OnWidthUpdate(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void OnCmdlgColor();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // MFC_Basic_PracticeView.cpp의 디버그 버전
inline CMyMFC_Basic_PracticeDoc* CMyMFC_Basic_PracticeView::GetDocument() const
   { return reinterpret_cast<CMyMFC_Basic_PracticeDoc*>(m_pDocument); }
#endif

