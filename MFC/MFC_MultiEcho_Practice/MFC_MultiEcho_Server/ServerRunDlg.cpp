// ServerRunDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_MultiEcho_Server.h"
#include "ServerRunDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC_MultiEcho_ServerDoc.h"

// CServerRunDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CServerRunDlg, CDialogEx)

CServerRunDlg::CServerRunDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVERRUNDLG, pParent)
	, m_Edit_ServerRun_Port(0)
{

}

CServerRunDlg::~CServerRunDlg()
{
}

void CServerRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITPORT, m_Edit_ServerRun_Port);
}


BEGIN_MESSAGE_MAP(CServerRunDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CServerRunDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CServerRunDlg 메시지 처리기입니다.


BOOL CServerRunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMyMFC_MultiEcho_ServerDoc* pDoc = (CMyMFC_MultiEcho_ServerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();

	m_Edit_ServerRun_Port = pDoc->port;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CServerRunDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CMyMFC_MultiEcho_ServerDoc* pDoc = (CMyMFC_MultiEcho_ServerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();

	pDoc->port = m_Edit_ServerRun_Port;

	CDialogEx::OnOK();
}
