
// MFC_MultiEcho_ClientView.h : CMyMFC_MultiEcho_ClientView 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"


class CMyMFC_MultiEcho_ClientView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMyMFC_MultiEcho_ClientView();
	DECLARE_DYNCREATE(CMyMFC_MultiEcho_ClientView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MYMFC_MultiEcho_Client_FORM };
#endif

// 특성입니다.
public:
	CMyMFC_MultiEcho_ClientDoc* GetDocument() const;

// 작업입니다.
public:
	CRITICAL_SECTION cs_logmsg;

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMyMFC_MultiEcho_ClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit_SendMsg;
	CEdit m_Edit_RecvMsg;
	CEdit m_Edit_PW;
	CEdit m_Edit_ID;
	CButton m_Button_AddMem;
	CButton m_Button_DelMem;
	CButton m_Button_Login;
	CButton m_Button_Logout;
	CButton m_Button_Send;
	void view_InitControl();
	void view_ControlEnableBeforeLogin();
	void view_ControlEnableAfterLogin();
	void view_ControlEnableBeforeConnection();
	void view_ControlEnableAfterConnection();
	void view_ControlVisibleOnConnection();
	void view_ControlInvisibleOnConnection();
	void view_OnLogMessage(CString msg);
	afx_msg void OnMenuServerconfig();
	afx_msg void OnClickedButtonaddmember();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void view_AddLogMessage(CString msg);
	afx_msg void OnClickedButtonlogin();
	void view_OnRecvData(LPTSTR data);
	afx_msg void OnClickedButtonlogout();
	afx_msg void OnClickedButtondeletemember();
	afx_msg void OnClickedButtonsend();
//	afx_msg void OnClose();
	afx_msg void OnAppExit();
	void view_OnServerClosed();
};

#ifndef _DEBUG  // MFC_MultiEcho_ClientView.cpp의 디버그 버전
inline CMyMFC_MultiEcho_ClientDoc* CMyMFC_MultiEcho_ClientView::GetDocument() const
   { return reinterpret_cast<CMyMFC_MultiEcho_ClientDoc*>(m_pDocument); }
#endif

