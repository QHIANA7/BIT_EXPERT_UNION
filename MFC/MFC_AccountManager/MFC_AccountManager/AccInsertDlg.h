#pragma once


// CAccInsertDlg 대화 상자입니다.

class CAccInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccInsertDlg)
	Account* acc;

public:
	CAccInsertDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAccInsertDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACCINSERTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_Edit_Insert_AccNum;
	int m_Edit_Insert_InitBalance;
	CString m_Edit_Insert_Name;
	Account* GetAccount();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
