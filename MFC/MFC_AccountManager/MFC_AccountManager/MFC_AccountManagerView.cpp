
// MFC_AccountManagerView.cpp : CMyMFC_AccountManagerView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_AccountManager.h"
#endif

#include "MFC_AccountManagerDoc.h"
#include "MFC_AccountManagerView.h"
#include "AccInsertDlg.h"
#include "AccDeleteDlg.h"
#include "AccMoneyIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMFC_AccountManagerView

IMPLEMENT_DYNCREATE(CMyMFC_AccountManagerView, CFormView)

BEGIN_MESSAGE_MAP(CMyMFC_AccountManagerView, CFormView)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ACCINSERT, ID_MONEYIO, OnMenuPopUp)
	ON_COMMAND(ID_ACCINSERT, &CMyMFC_AccountManagerView::OnAccinsert)
	ON_COMMAND(ID_ACCDELETE, &CMyMFC_AccountManagerView::OnAccdelete)
	ON_COMMAND(ID_MONEYIO, &CMyMFC_AccountManagerView::OnMoneyio)
	ON_LBN_SELCHANGE(IDC_LIST_ACC, &CMyMFC_AccountManagerView::OnSelchangeListAcc)
	ON_MESSAGE(WM_APPLY, &CMyMFC_AccountManagerView::OnApply)
END_MESSAGE_MAP()

// CMyMFC_AccountManagerView 생성/소멸

CMyMFC_AccountManagerView::CMyMFC_AccountManagerView()
	: CFormView(IDD_MYMFC_AccountManager_FORM)
	, m_Edit_Name(_T(""))
	, m_Edit_Balance(0)
	, m_Edit_AccNum(0)
	, m_Static_Acc_Cnt(_T("계좌 개수 : 00개"))
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pMDlg = NULL;
}

CMyMFC_AccountManagerView::~CMyMFC_AccountManagerView()
{
	
}

void CMyMFC_AccountManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW, m_List_View);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Edit_Name);
	DDX_Text(pDX, IDC_EDIT_BALANCE, m_Edit_Balance);
	DDX_Text(pDX, IDC_EDIT_ACCNUM, m_Edit_AccNum);
	DDX_Text(pDX, IDC_EDIT_ACCDATE, m_Edit_AccDate);
	DDX_Control(pDX, IDC_LIST_ACC, m_List_Acc);
	DDX_Text(pDX, IDC_STATIC_ACC_CNT, m_Static_Acc_Cnt);
}

BOOL CMyMFC_AccountManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMyMFC_AccountManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	view_AccListUpdate();
	view_InitControl();
}


// CMyMFC_AccountManagerView 진단

#ifdef _DEBUG
void CMyMFC_AccountManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyMFC_AccountManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyMFC_AccountManagerDoc* CMyMFC_AccountManagerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFC_AccountManagerDoc)));
	return (CMyMFC_AccountManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFC_AccountManagerView 메시지 처리기


void CMyMFC_AccountManagerView::view_InitControl()
{
	// 마지막 인수 서브아이템의 존재가 궁금합니다.

	m_List_View.InsertColumn(0, TEXT("계좌번호"), HDF_LEFT, 80, 0);
	m_List_View.InsertColumn(1, TEXT("입출금일"), HDF_LEFT, 140, 1);
	m_List_View.InsertColumn(2, TEXT("입금액"), HDF_LEFT, 80, 2);
	m_List_View.InsertColumn(3, TEXT("출금액"), HDF_LEFT, 80, 3);
	m_List_View.InsertColumn(4, TEXT("잔액"), HDF_LEFT, 80, 4);
	//==========================================
	m_List_View.SetExtendedStyle(
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES |
		LVS_EX_HEADERDRAGDROP);

}


void CMyMFC_AccountManagerView::OnAccinsert()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyMFC_AccountManagerDoc* pDoc = GetDocument();

	CAccInsertDlg dlg;	

	if (dlg.DoModal() == IDOK)
	{
		Account* acc = dlg.GetAccount();	//모달로부터 얻는다.
		pDoc->m_vecPAccount.push_back(acc);	//벡터에 푸쉬백
		pDoc->doc_AccListInsert(acc->getAccId(), acc->getBalance(), 0, acc->getBalance()); //벡터에 푸쉬백
		view_AccInfoPrint(dlg.acc->getAccId());
		view_ListViewPrintAll(dlg.acc->getAccId());
		view_AccListUpdate();
		//pDoc->m_bInsert = TRUE;
	}
}


void CMyMFC_AccountManagerView::OnAccdelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyMFC_AccountManagerDoc* pDoc = GetDocument();

	CAccDeleteDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		view_ListViewPrintAll(dlg.pAcc->getAccId());
		view_AccListUpdate();
		pDoc->m_bInsert = FALSE;
	}

	UpdateData(FALSE);	// 멤버 -> UI
}


void CMyMFC_AccountManagerView::OnMenuPopUp(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_ACCINSERT:
		pCmdUI->Enable(!GetDocument()->m_bInsert); break;
	case ID_ACCDELETE:
		pCmdUI->Enable(!GetDocument()->m_bInsert); break;
	case ID_MONEYIO:
		pCmdUI->Enable(!GetDocument()->m_bInsert); break;
	}
}


void CMyMFC_AccountManagerView::OnMoneyio()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	if (m_pMDlg == NULL)
	{
		// 대화상자를 생성하지 않았으므로 메모리 할당하고 모달리스 생성
		m_pMDlg = new CAccMoneyIO;
		m_pMDlg->Create(IDD_ACCMONEYIO);
		// 윈도우가 제대로 생성되었다면 화면에 보인다.
		if (m_pMDlg->GetSafeHwnd())
			m_pMDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		// 대화상자가 이미 생성되었다면 화면에 보여주고 focus이동한다.
		m_pMDlg->ShowWindow(SW_SHOW);
		m_pMDlg->SetFocus();
	}
}


void CMyMFC_AccountManagerView::view_AccInfoPrint(int AccID)
{
	CMyMFC_AccountManagerDoc* pDoc = GetDocument();

	for (int i = 0; i < (int)pDoc->m_vecPAccount.size(); i++)
	{
		Account* acc = pDoc->m_vecPAccount[i];

		if (AccID == acc->getAccId())
		{
			m_Edit_Name = acc->GetName();
			m_Edit_AccNum = acc->getAccId();
			m_Edit_Balance = acc->getBalance();
			//=============================================================
			TCHAR temp[256];
			wsprintf(temp, TEXT("%d/%d/%d (%d:%d:%d)"),
				acc->getDate().GetYear(), acc->getDate().GetMonth(), acc->getDate().GetDay(),
				acc->getDate().GetHour(), acc->getDate().GetMinute(), acc->getDate().GetSecond());
			m_Edit_AccDate = temp;
			UpdateData(FALSE);
		}
	}
}


void CMyMFC_AccountManagerView::view_ListViewPrintAll(int AccID)
{
	CMyMFC_AccountManagerDoc* pDoc = GetDocument();
	
	CString buf;
	//TCHAR buf[50];
	int cur_idx;
	m_List_View.DeleteAllItems();

	for (int i = cur_idx = 0; i< (int)pDoc->m_vecPAccountList.size(); i++)
	{
		AccountList* pAcclist = pDoc->m_vecPAccountList[i];
		//ACCOUNTLIST acc = pDoc->m_vecAcclist[i];

		if (AccID == pAcclist->getAccId())
		{

			buf.Format(TEXT("%d"), pAcclist->getAccId());
			//wsprintf(buf, TEXT("%d"), acc.accid);
			m_List_View.InsertItem(LVIF_TEXT, cur_idx, buf, 0, 0, 0, 0);

			buf.Format(TEXT("%d/%d/%d (%d:%d:%d)"),
			//wsprintf(buf, TEXT("%d/%d/%d (%d:%d:%d)");
				pAcclist->getDate().GetYear(), pAcclist->getDate().GetMonth(), pAcclist->getDate().GetDay(),
				pAcclist->getDate().GetHour(), pAcclist->getDate().GetMinute(), pAcclist->getDate().GetSecond());
			m_List_View.SetItem(cur_idx, 1, LVIF_TEXT, buf, 0, 0, 0, 0);

			buf.Format(TEXT("%d"), pAcclist->getAddMoney());
			//wsprintf(buf, TEXT("%d"), acc.addmoney);
			m_List_View.SetItem(cur_idx, 2, LVIF_TEXT, buf, 0, 0, 0, 0);

			buf.Format(TEXT("%d"), pAcclist->getMinMoney());
			//wsprintf(buf, TEXT("%d"), acc.minmoney);
			m_List_View.SetItem(cur_idx, 3, LVIF_TEXT, buf, 0, 0, 0, 0);

			buf.Format(TEXT("%d"), pAcclist->getBalance());
			//wsprintf(buf, TEXT("%d"), acc.balance);
			m_List_View.SetItem(cur_idx, 4, LVIF_TEXT, buf, 0, 0, 0, 0);

			cur_idx++;
		}
	}
}




void CMyMFC_AccountManagerView::view_AccListUpdate()
{
	CMyMFC_AccountManagerDoc* pDoc = GetDocument();

	m_List_Acc.ResetContent();

	for (int i = 0; i < (int)pDoc->m_vecPAccount.size(); i++)
	{
		Account* pAcc = pDoc->m_vecPAccount[i];
		CString accInfo;
		accInfo.Format(TEXT("%s(%d)"), pAcc->GetName(), pAcc->getAccId());
		m_List_Acc.AddString(accInfo);
	}

	m_Static_Acc_Cnt.Format(TEXT("계좌 개수 : %02d개"), pDoc->m_vecPAccount.size());
	UpdateData(FALSE);
}


void CMyMFC_AccountManagerView::OnSelchangeListAcc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMyMFC_AccountManagerDoc* pDoc = GetDocument();


	int idx = m_List_Acc.GetCurSel();

	if (idx >= 0)
	{
		view_AccInfoPrint(pDoc->m_vecPAccount[idx]->getAccId());
		view_ListViewPrintAll(pDoc->m_vecPAccount[idx]->getAccId());
	}
}


LONG CMyMFC_AccountManagerView::OnApply(WPARAM wParam, LPARAM lParam)
{
	CMyMFC_AccountManagerDoc* pDoc = GetDocument();

	
	pDoc->doc_AccListInsert(m_pMDlg->pAcclist->getAccId(), m_pMDlg->pAcclist->getAddMoney(), m_pMDlg->pAcclist->getMinMoney(),
		m_pMDlg->pAcclist->getBalance());

	for (int i = 0; i < (int)pDoc->m_vecPAccount.size(); i++)
	{
		Account* acc = pDoc->m_vecPAccount[i];

		if (m_pMDlg->m_Edit_MoneyIO_AccNum == acc->getAccId())
		{
			if (m_pMDlg->m_Button_MoneyIO_In.GetCheck() == BST_CHECKED)
				acc->setBalance(acc->getBalance() + m_pMDlg->m_Edit_MoneyIO_InMoney);
			else
				acc->setBalance(acc->getBalance() - m_pMDlg->m_Edit_MoneyIO_InMoney);
		}
	}

	view_ListViewPrintAll(m_pMDlg->pAcclist->getAccId());
	view_AccInfoPrint(m_pMDlg->pAcclist->getAccId());
	return 0L;
}
