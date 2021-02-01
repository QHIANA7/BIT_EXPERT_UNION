// AccDeleteDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_AccountManager.h"
#include "MFC_AccountManagerDoc.h"
#include "MainFrm.h"
#include "Account.h"
#include "AccDeleteDlg.h"
#include "afxdialogex.h"


// CAccDeleteDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAccDeleteDlg, CDialogEx)

CAccDeleteDlg::CAccDeleteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACCDELETEDLG, pParent)
	, m_Edit_Delete_AccNum(0)
{
	pAcc = new Account;
}

CAccDeleteDlg::~CAccDeleteDlg()
{
}

void CAccDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELETE_ACCNUM, m_Edit_Delete_AccNum);
}


BEGIN_MESSAGE_MAP(CAccDeleteDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAccDeleteDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAccDeleteDlg 메시지 처리기입니다.


void CAccDeleteDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMyMFC_AccountManagerDoc* pDoc = (CMyMFC_AccountManagerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();
	UpdateData(TRUE);
	pAcc->setAccID(m_Edit_Delete_AccNum);

	for (int i = 0; i < (int)pDoc->m_vecPAccount.size(); i++)
	{
		Account* acc = pDoc->m_vecPAccount[i];

		if (acc->getAccId() == m_Edit_Delete_AccNum)
		{
			pDoc->m_vecPAccount.erase(pDoc->m_vecPAccount.begin() + i);
		}
	}

	CDialogEx::OnOK();
}
