// AddMemberDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_MultiEcho_Client.h"
#include "AddMemberDlg.h"
#include "afxdialogex.h"
#include "MFC_MultiEcho_ClientDoc.h"
#include "MainFrm.h"


// CAddMemberDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddMemberDlg, CDialogEx)

CAddMemberDlg::CAddMemberDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDMEMBERDLG, pParent)
	, m_Edit_AddMem_ID(_T(""))
	, m_Edit_AddMem_NICK(_T(""))
	, m_Edit_AddMem_PW(_T(""))
{

}

CAddMemberDlg::~CAddMemberDlg()
{
}

void CAddMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADDMEMBEREDITID, m_Edit_AddMem_ID);
	DDX_Text(pDX, IDC_ADDMEMBEREDITNICK, m_Edit_AddMem_NICK);
	DDX_Text(pDX, IDC_ADDMEMBEREDITPW, m_Edit_AddMem_PW);
}


BEGIN_MESSAGE_MAP(CAddMemberDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddMemberDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddMemberDlg 메시지 처리기입니다.


void CAddMemberDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CMyMFC_MultiEcho_ClientDoc* pDoc = (CMyMFC_MultiEcho_ClientDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();

	UpdateData(TRUE);

	MEMBER mem;
	wsprintf(mem.id, m_Edit_AddMem_ID);
	wsprintf(mem.pw, m_Edit_AddMem_PW);
	wsprintf(mem.nickname, m_Edit_AddMem_NICK);
	mem.flag = PACK_ADDMEMBER;
	int sendlen = sizeof(MEMBER);


	pDoc->pMyNet->mynet_SendMessage((LPTSTR)&mem, sendlen);

	CDialogEx::OnOK();
}
