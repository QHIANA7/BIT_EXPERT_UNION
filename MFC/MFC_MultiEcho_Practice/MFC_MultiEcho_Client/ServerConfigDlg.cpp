// ServerConfigDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_MultiEcho_Client.h"
#include "ServerConfigDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC_MultiEcho_ClientDoc.h"

// CServerConfigDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CServerConfigDlg, CDialogEx)

CServerConfigDlg::CServerConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVERCONFIGDLG, pParent)
	, m_Edit_ServerConfigPort(0)
	, m_IpAddr_1(0)
{

}

CServerConfigDlg::~CServerConfigDlg()
{
}

void CServerConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSERVERCONFIGPORT, m_Edit_ServerConfigPort);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_IpAddr_1);
}


BEGIN_MESSAGE_MAP(CServerConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CServerConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CServerConfigDlg 메시지 처리기입니다.


BOOL CServerConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMyMFC_MultiEcho_ClientDoc* pDoc = (CMyMFC_MultiEcho_ClientDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();

	pSI = &pDoc->m_si;

	m_Edit_ServerConfigPort = pSI->s_port;
	m_IpAddr_1 = pSI->s_ip;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CServerConfigDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMyMFC_MultiEcho_ClientDoc* pDoc = (CMyMFC_MultiEcho_ClientDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();

	UpdateData(TRUE);

	pSI->s_ip = m_IpAddr_1;
	pSI->s_port = m_Edit_ServerConfigPort;

	CDialogEx::OnOK();
}
