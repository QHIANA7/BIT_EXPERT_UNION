// AccInsertDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_AccountManager.h"
#include "Account.h"
#include "MFC_AccountManagerDoc.h"
#include "MFC_AccountManagerView.h"
#include "MainFrm.h"
#include "AccInsertDlg.h"
#include "afxdialogex.h"


// CAccInsertDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAccInsertDlg, CDialogEx)

CAccInsertDlg::CAccInsertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACCINSERTDLG, pParent)
	, m_Edit_Insert_AccNum(0)
	, m_Edit_Insert_InitBalance(0)
	, m_Edit_Insert_Name(_T(""))
{
	acc = new Account;
}

CAccInsertDlg::~CAccInsertDlg()
{
}

void CAccInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INSERT_ACCNUM, m_Edit_Insert_AccNum);
	DDX_Text(pDX, IDC_EDIT_INSERT_INITBALANCE, m_Edit_Insert_InitBalance);
	DDX_Text(pDX, IDC_EDIT_INSERT_NAME, m_Edit_Insert_Name);
}


BEGIN_MESSAGE_MAP(CAccInsertDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAccInsertDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAccInsertDlg 메시지 처리기입니다.

Account* CAccInsertDlg::GetAccount()
{
	//acc->accid = m_Edit_Insert_AccNum;
	//acc.balance = m_Edit_Insert_InitBalance;
	//wsprintf(acc.name, m_Edit_Insert_Name);

	//::GetLocalTime(&acc.date);


	return new Account(m_Edit_Insert_Name, m_Edit_Insert_AccNum, m_Edit_Insert_InitBalance);
}


void CAccInsertDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	acc->setAccID(m_Edit_Insert_AccNum);
	acc->setBalance(m_Edit_Insert_InitBalance);
	acc->setName(m_Edit_Insert_Name);
	acc->setDate(CTime::GetCurrentTime());
	//acc->accid = m_Edit_Insert_AccNum;
	//acc->balance = m_Edit_Insert_InitBalance;
	//wsprintf(acc->name, m_Edit_Insert_Name);
	//GetLocalTime(&acc->date);
	CDialogEx::OnOK();
}


BOOL CAccInsertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMyMFC_AccountManagerDoc* pDoc = (CMyMFC_AccountManagerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();

	//acc = &pDoc->m_account; //구코드

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
