
// MFC_MultiEcho_ServerView.h : CMyMFC_MultiEcho_ServerView 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CMyMFC_MultiEcho_ServerView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMyMFC_MultiEcho_ServerView();
	DECLARE_DYNCREATE(CMyMFC_MultiEcho_ServerView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MYMFC_MultiEcho_Server_FORM };
#endif

// 특성입니다.
public:
	CMyMFC_MultiEcho_ServerDoc* GetDocument() const;

// 작업입니다.
public:
	CRITICAL_SECTION cs;
	CRITICAL_SECTION cs_ListPrint;

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMyMFC_MultiEcho_ServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnMenuPopUp(CCmdUI* pCmdUI);
	CEdit m_Edit_Log;
	CListCtrl m_Socket_View;
	CListCtrl m_Member_View;
	CStatic m_Static_Member_Cnt;
	CStatic m_Static_Socket_Cnt;
	void view_InitControl();
	afx_msg void OnMenuServerrun();
	afx_msg void OnMenuServerclose();
	void view_OnLogMessage(CString msg);
	void view_AddLogMessage(CString msg);
	void view_ListViewPrintAll();
};

#ifndef _DEBUG  // MFC_MultiEcho_ServerView.cpp의 디버그 버전
inline CMyMFC_MultiEcho_ServerDoc* CMyMFC_MultiEcho_ServerView::GetDocument() const
   { return reinterpret_cast<CMyMFC_MultiEcho_ServerDoc*>(m_pDocument); }
#endif

