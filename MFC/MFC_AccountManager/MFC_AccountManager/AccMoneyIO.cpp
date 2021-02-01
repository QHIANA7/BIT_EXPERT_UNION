// AccMoneyIO.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC_AccountManager.h"
#include "AccountList.h"
#include "MFC_AccountManagerDoc.h"
#include "MFC_AccountManagerView.h"
#include "MainFrm.h"
#include "AccMoneyIO.h"
#include "afxdialogex.h"


// CAccMoneyIO 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAccMoneyIO, CDialogEx)

CAccMoneyIO::CAccMoneyIO(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACCMONEYIO, pParent)
	, m_Edit_MoneyIO_AccNum(0)
	, m_Edit_MoneyIO_InMoney(0)
{
	pAcclist = new AccountList;
	m_bSelfDelete = FALSE;
}

CAccMoneyIO::~CAccMoneyIO()
{
}

void CAccMoneyIO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MONEYIO_ACCNUM, m_Edit_MoneyIO_AccNum);
	DDX_Text(pDX, IDC_EDIT_MONEYIO_INMONEY, m_Edit_MoneyIO_InMoney);
	DDX_Control(pDX, IDC_RADIO_MONEYIO_IN, m_Button_MoneyIO_In);
}


BEGIN_MESSAGE_MAP(CAccMoneyIO, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAccMoneyIO::OnBnClickedOk)
//	ON_MESSAGE(WM_APPLY, OnApply)
END_MESSAGE_MAP()


// CAccMoneyIO 메시지 처리기입니다.


void CAccMoneyIO::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_bSelfDelete)
	{
		delete this;
	}
	else
	{
		CDialog::PostNcDestroy();
	}

	CDialogEx::PostNcDestroy();
}


void CAccMoneyIO::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMyMFC_AccountManagerDoc* pDoc = (CMyMFC_AccountManagerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();

	UpdateData(TRUE);	//UI -> 멤버
	int money = m_Edit_MoneyIO_InMoney;
	
	if (m_Button_MoneyIO_In.GetCheck() == BST_CHECKED)
	{
		pAcclist->setAddMoney(money);
		pAcclist->setMinMoney(0);
		pAcclist->setBalance(pAcclist->getBalance() + money);

		//pDoc->m_accountlist.addmoney = money;
		//pDoc->m_accountlist.minmoney = 0;
		//pDoc->m_accountlist.balance += money;
	}
	else
	{
		pAcclist->setAddMoney(0);
		pAcclist->setMinMoney(money);
		pAcclist->setBalance(pAcclist->getBalance() - money);

		//pDoc->m_acclist.addmoney = 0;
		//pDoc->m_acclist.minmoney = money;
		//pDoc->m_acclist.balance -= money;
	}
	pAcclist->setDate(CTime::GetCurrentTime());
	//GetLocalTime(&pDoc->m_acclist.date);

	//pDoc->m_account.setBalance(pAcclist->getBalance());
	//pDoc->m_account.setBalance(pDoc->m_acclist.balance);

	((CMyMFC_AccountManagerView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView())->SendMessage(WM_APPLY, 0, 0);

	CDialogEx::OnOK();
}


BOOL CAccMoneyIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMyMFC_AccountManagerDoc* pDoc = (CMyMFC_AccountManagerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();
	CMyMFC_AccountManagerView* pView = (CMyMFC_AccountManagerView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	//pDoc->m_accountlist.setAccID(pDoc->m_account.getAccId());
	//pAcclist->setAccID(pDoc->m_account.getAccId());

	//pDoc->m_accountlist.setBalance(pDoc->m_account.getBalance());
	//pAcclist->setBalance(pDoc->m_account.getBalance());

	pAcclist->setBalance(pDoc->m_vecPAccount[pView->m_List_Acc.GetCurSel()]->getBalance());
	pAcclist->setAccID(pDoc->m_vecPAccount[pView->m_List_Acc.GetCurSel()]->getAccId());
	m_Edit_MoneyIO_AccNum = pAcclist->getAccId();
	m_Edit_MoneyIO_InMoney = 0;

	UpdateData(FALSE);	//멤버 -> UI
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//LRESULT CAccMoneyIO::OnApply(WPARAM wParam, LPARAM lParam)
//{
//	CMyMFC_AccountManagerDoc* pDoc = (CMyMFC_AccountManagerDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveView()->GetDocument();
//	CMyMFC_AccountManagerView* pView = (CMyMFC_AccountManagerView*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
//
//	pDoc->doc_AccListInsert(pAcclist->getAccId(), pAcclist->getAddMoney(), pAcclist->getMinMoney(),
//		pAcclist->getBalance());
//
//	for (int i = 0; i < (int)pDoc->m_vecPAccount.size(); i++)
//	{
//		Account acc = *pDoc->m_vecPAccount[i];
//
//		//if(acc.getAccId() = )
//	}
//
//	//pDoc->doc_AccListInsert(pDoc->m_acclist.accid, pDoc->m_acclist.addmoney,
//	//	pDoc->m_acclist.minmoney, pDoc->m_acclist.balance);
//	pView->view_ListViewPrintAll();
//	pView->view_AccInfoPrint();
//	return 0L;
//}
