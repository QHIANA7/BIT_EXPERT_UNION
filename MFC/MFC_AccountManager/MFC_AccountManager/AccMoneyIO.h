#pragma once
#include "afxwin.h"


// CAccMoneyIO 대화 상자입니다.

class CAccMoneyIO : public CDialogEx
{
	DECLARE_DYNAMIC(CAccMoneyIO)
	AccountList* pAcclist;

public:
	CAccMoneyIO(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAccMoneyIO();
	//작업입니다.
	BOOL m_bSelfDelete;	//모달리스 관련 삭제여부

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACCMONEYIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	int m_Edit_MoneyIO_AccNum;
	int m_Edit_MoneyIO_InMoney;
	afx_msg void OnBnClickedOk();
	CButton m_Button_MoneyIO_In;
	virtual BOOL OnInitDialog();
//	LRESULT OnApply(WPARAM wParam, LPARAM lParam);
};
