#pragma once


// CAddMemberDlg 대화 상자입니다.

class CAddMemberDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddMemberDlg)

public:
	CAddMemberDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddMemberDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDMEMBERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_Edit_AddMem_ID;
	CString m_Edit_AddMem_NICK;
	CString m_Edit_AddMem_PW;
	afx_msg void OnBnClickedOk();
};
