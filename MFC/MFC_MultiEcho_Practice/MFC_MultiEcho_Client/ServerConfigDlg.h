#pragma once
#include "MFC_MultiEcho_ClientDoc.h"

// CServerConfigDlg 대화 상자입니다.

class CServerConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerConfigDlg)
	SERVERINFO *pSI;

public:
	CServerConfigDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CServerConfigDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERCONFIGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_Edit_ServerConfigPort;
	DWORD m_IpAddr_1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
