
// MFC_MultiEcho_ServerView.cpp : CMyMFC_MultiEcho_ServerView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_MultiEcho_Server.h"
#endif

#include "resource.h"
#include "ServerRunDlg.h"
#include "MFC_MultiEcho_ServerDoc.h"
#include "MFC_MultiEcho_ServerView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMFC_MultiEcho_ServerView

IMPLEMENT_DYNCREATE(CMyMFC_MultiEcho_ServerView, CFormView)

BEGIN_MESSAGE_MAP(CMyMFC_MultiEcho_ServerView, CFormView)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MENU_SERVERRUN, ID_MENU_SERVERCLOSE, OnMenuPopUp)
	ON_COMMAND(ID_MENU_SERVERRUN, &CMyMFC_MultiEcho_ServerView::OnMenuServerrun)
	ON_COMMAND(ID_MENU_SERVERCLOSE, &CMyMFC_MultiEcho_ServerView::OnMenuServerclose)
END_MESSAGE_MAP()

// CMyMFC_MultiEcho_ServerView 생성/소멸

CMyMFC_MultiEcho_ServerView::CMyMFC_MultiEcho_ServerView()
	: CFormView(IDD_MYMFC_MultiEcho_Server_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&cs_ListPrint);
}

CMyMFC_MultiEcho_ServerView::~CMyMFC_MultiEcho_ServerView()
{
	DeleteCriticalSection(&cs);
	DeleteCriticalSection(&cs_ListPrint);
}

void CMyMFC_MultiEcho_ServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITLOG, m_Edit_Log);
	DDX_Control(pDX, IDC_LISTSOCKET, m_Socket_View);
	DDX_Control(pDX, IDC_MEMBERLIST, m_Member_View);
	DDX_Control(pDX, IDC_STATICMEMBERCOUNT, m_Static_Member_Cnt);
	DDX_Control(pDX, IDC_STATICSOCKETCOUNT, m_Static_Socket_Cnt);
}

BOOL CMyMFC_MultiEcho_ServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMyMFC_MultiEcho_ServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	view_InitControl();
}


// CMyMFC_MultiEcho_ServerView 진단

#ifdef _DEBUG
void CMyMFC_MultiEcho_ServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyMFC_MultiEcho_ServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyMFC_MultiEcho_ServerDoc* CMyMFC_MultiEcho_ServerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFC_MultiEcho_ServerDoc)));
	return (CMyMFC_MultiEcho_ServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFC_MultiEcho_ServerView 메시지 처리기


void CMyMFC_MultiEcho_ServerView::OnMenuPopUp(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_MENU_SERVERRUN:
		pCmdUI->Enable(!GetDocument()->m_IsServerRun); break;
	case ID_MENU_SERVERCLOSE:
		pCmdUI->Enable(GetDocument()->m_IsServerRun); break;
	}
}


void CMyMFC_MultiEcho_ServerView::view_InitControl()
{
	m_Socket_View.InsertColumn(0, TEXT("소켓"), HDF_LEFT, 50, 0);
	m_Socket_View.InsertColumn(1, TEXT("SOCKET"), HDF_LEFT, 140, 1);
	m_Socket_View.InsertColumn(2, TEXT("PEER"), HDF_LEFT, 140, 2);
	//==========================================
	m_Socket_View.SetExtendedStyle(
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES |
		LVS_EX_HEADERDRAGDROP);


	//=========================================================
	m_Member_View.InsertColumn(0, TEXT("ID"), HDF_LEFT, 80, 0);
	m_Member_View.InsertColumn(1, TEXT("PW"), HDF_LEFT, 80, 1);
	m_Member_View.InsertColumn(2, TEXT("NICKNAME"), HDF_LEFT, 80, 2);
	m_Member_View.InsertColumn(3, TEXT("LoginState"), HDF_LEFT, 80, 3);
	m_Member_View.SetExtendedStyle(
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES |
		LVS_EX_HEADERDRAGDROP);
}


void CMyMFC_MultiEcho_ServerView::OnMenuServerrun()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyMFC_MultiEcho_ServerDoc* pDoc = GetDocument();

	CServerRunDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		if(pDoc->pMyNet->mynet_StartServer())
			pDoc->m_IsServerRun = TRUE;
	}

}

void CMyMFC_MultiEcho_ServerView::OnMenuServerclose()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyMFC_MultiEcho_ServerDoc* pDoc = GetDocument();
	pDoc->pMyNet->mynet_OnCloseServer();
	pDoc->m_IsServerRun = FALSE;
}

void CMyMFC_MultiEcho_ServerView::view_OnLogMessage(CString msg)
{
	view_AddLogMessage(msg);
}


void CMyMFC_MultiEcho_ServerView::view_AddLogMessage(CString msg)
{
	CString buf;
	buf.Format(TEXT("\r\n"));

	EnterCriticalSection(&cs);
	m_Edit_Log.ReplaceSel(msg);
	m_Edit_Log.ReplaceSel(buf);
	LeaveCriticalSection(&cs);
}


void CMyMFC_MultiEcho_ServerView::view_ListViewPrintAll()
{
	CMyMFC_MultiEcho_ServerDoc* pDoc = GetDocument();
	CString buf;

	EnterCriticalSection(&cs_ListPrint);
	m_Socket_View.DeleteAllItems();

	for (int i = 0; i< (int)pDoc->m_SocketInfo.size(); i++)
	{
		Data* dt = pDoc->m_SocketInfo[i];

			buf.Format(TEXT("%d"), dt->getSocket());
			m_Socket_View.InsertItem(LVIF_TEXT, i, buf, 0, 0, 0, 0);

			buf.Format(TEXT("(%05d)%s"), dt->getTPort(), dt->getTIp());
			m_Socket_View.SetItem(i, 1, LVIF_TEXT, buf, 0, 0, 0, 0);

			buf.Format(TEXT("(%05d)%s"), dt->getCPort(), dt->getCIp());
			m_Socket_View.SetItem(i, 2, LVIF_TEXT, buf, 0, 0, 0, 0);
	}

	buf.Format(TEXT("통신소켓 개수 %02d개"), pDoc->m_SocketInfo.size());
	m_Static_Socket_Cnt.SetWindowTextW(buf);

	m_Member_View.DeleteAllItems();
	for (int i = 0; i< (int)pDoc->m_Memberlist.size(); i++)
	{
		MEMBER dt = pDoc->m_Memberlist[i];

		buf.Format(TEXT("%s"), dt.id);
		m_Member_View.InsertItem(LVIF_TEXT, i, buf, 0, 0, 0, 0);

		buf.Format(TEXT("%s"), dt.pw);
		m_Member_View.SetItem(i, 1, LVIF_TEXT, buf, 0, 0, 0, 0);

		buf.Format(TEXT("%s"), dt.nickname);
		m_Member_View.SetItem(i, 2, LVIF_TEXT, buf, 0, 0, 0, 0);

		dt.flag ? buf.Format(TEXT("%s"), TEXT("로그온")) : buf.Format(TEXT("%s"), TEXT("로그오프"));
		m_Member_View.SetItem(i, 3, LVIF_TEXT, buf, 0, 0, 0, 0);

	}

	buf.Format(TEXT("회원 가입자수 %02d명"), pDoc->m_Memberlist.size());
	m_Static_Member_Cnt.SetWindowTextW(buf);
	LeaveCriticalSection(&cs_ListPrint);
}
