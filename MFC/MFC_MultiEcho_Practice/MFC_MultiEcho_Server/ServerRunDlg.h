#pragma once


// CServerRunDlg 대화 상자입니다.

class CServerRunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerRunDlg)

public:
	CServerRunDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CServerRunDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERRUNDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_Edit_ServerRun_Port;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
