
// MFC_AccountManagerView.h : CMyMFC_AccountManagerView 클래스의 인터페이스
//

#pragma once
#include "afxcmn.h"
#include "AccMoneyIO.h"
#include "afxwin.h"


class CMyMFC_AccountManagerView : public CFormView
{
	CAccMoneyIO* m_pMDlg;
protected: // serialization에서만 만들어집니다.
	CMyMFC_AccountManagerView();
	DECLARE_DYNCREATE(CMyMFC_AccountManagerView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MYMFC_AccountManager_FORM };
#endif

// 특성입니다.
public:
	CMyMFC_AccountManagerDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMyMFC_AccountManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List_View;
	CString m_Edit_Name;
	int m_Edit_Balance;
	int m_Edit_AccNum;
	CString m_Edit_AccDate;
	void view_InitControl();
	afx_msg void OnAccinsert();
	afx_msg void OnAccdelete();
	void OnMenuPopUp(CCmdUI* pCmdUI);
	afx_msg void OnMoneyio();
	void view_AccInfoPrint(int AccID);
	void view_ListViewPrintAll(int AccID);
	CListBox m_List_Acc;
	void view_AccListUpdate();
	CString m_Static_Acc_Cnt;
	afx_msg void OnSelchangeListAcc();
	LONG OnApply(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // MFC_AccountManagerView.cpp의 디버그 버전
inline CMyMFC_AccountManagerDoc* CMyMFC_AccountManagerView::GetDocument() const
   { return reinterpret_cast<CMyMFC_AccountManagerDoc*>(m_pDocument); }
#endif

