#pragma once


// CAccDeleteDlg 대화 상자입니다.

class CAccDeleteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccDeleteDlg)
	Account* pAcc;

public:
	CAccDeleteDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAccDeleteDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACCDELETEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_Edit_Delete_AccNum;
	afx_msg void OnBnClickedOk();
};
