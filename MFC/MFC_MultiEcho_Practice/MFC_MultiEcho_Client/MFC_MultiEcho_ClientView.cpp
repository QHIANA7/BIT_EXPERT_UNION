
// MFC_MultiEcho_ClientView.cpp : CMyMFC_MultiEcho_ClientView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_MultiEcho_Client.h"
#endif

#include "MFC_MultiEcho_ClientDoc.h"
#include "MFC_MultiEcho_ClientView.h"
#include "ServerConfigDlg.h"
#include "AddMemberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMFC_MultiEcho_ClientView

IMPLEMENT_DYNCREATE(CMyMFC_MultiEcho_ClientView, CFormView)

BEGIN_MESSAGE_MAP(CMyMFC_MultiEcho_ClientView, CFormView)
	ON_COMMAND(ID_MENU_SERVERCONFIG, &CMyMFC_MultiEcho_ClientView::OnMenuServerconfig)
	ON_BN_CLICKED(IDC_BUTTONADDMEMBER, &CMyMFC_MultiEcho_ClientView::OnClickedButtonaddmember)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONLOGIN, &CMyMFC_MultiEcho_ClientView::OnClickedButtonlogin)
	ON_BN_CLICKED(IDC_BUTTONLOGOUT, &CMyMFC_MultiEcho_ClientView::OnClickedButtonlogout)
	ON_BN_CLICKED(IDC_BUTTONDELETEMEMBER, &CMyMFC_MultiEcho_ClientView::OnClickedButtondeletemember)
	ON_BN_CLICKED(IDC_BUTTONSEND, &CMyMFC_MultiEcho_ClientView::OnClickedButtonsend)
//	ON_WM_CLOSE()
	ON_COMMAND(ID_APP_EXIT, &CMyMFC_MultiEcho_ClientView::OnAppExit)
END_MESSAGE_MAP()

// CMyMFC_MultiEcho_ClientView 생성/소멸

CMyMFC_MultiEcho_ClientView::CMyMFC_MultiEcho_ClientView()
	: CFormView(IDD_MYMFC_MultiEcho_Client_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	InitializeCriticalSection(&cs_logmsg);
	
}

CMyMFC_MultiEcho_ClientView::~CMyMFC_MultiEcho_ClientView()
{
	DeleteCriticalSection(&cs_logmsg);
}

void CMyMFC_MultiEcho_ClientView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITSENDMESSAGE, m_Edit_SendMsg);
	DDX_Control(pDX, IDC_EDITRECVMESSAGE, m_Edit_RecvMsg);
	DDX_Control(pDX, IDC_EDITPW, m_Edit_PW);
	DDX_Control(pDX, IDC_EDITID, m_Edit_ID);
	DDX_Control(pDX, IDC_BUTTONADDMEMBER, m_Button_AddMem);
	DDX_Control(pDX, IDC_BUTTONDELETEMEMBER, m_Button_DelMem);
	DDX_Control(pDX, IDC_BUTTONLOGIN, m_Button_Login);
	DDX_Control(pDX, IDC_BUTTONLOGOUT, m_Button_Logout);
	DDX_Control(pDX, IDC_BUTTONSEND, m_Button_Send);
}

BOOL CMyMFC_MultiEcho_ClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMyMFC_MultiEcho_ClientView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	SetTimer(1, 1000, 0);
	view_InitControl();
}


// CMyMFC_MultiEcho_ClientView 진단

#ifdef _DEBUG
void CMyMFC_MultiEcho_ClientView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyMFC_MultiEcho_ClientView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyMFC_MultiEcho_ClientDoc* CMyMFC_MultiEcho_ClientView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFC_MultiEcho_ClientDoc)));
	return (CMyMFC_MultiEcho_ClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFC_MultiEcho_ClientView 메시지 처리기


void CMyMFC_MultiEcho_ClientView::view_InitControl()
{
	view_ControlEnableBeforeConnection();
}

void CMyMFC_MultiEcho_ClientView::view_ControlEnableBeforeLogin()
{
	m_Edit_ID.EnableWindow(TRUE);
	m_Edit_PW.EnableWindow(TRUE);
	m_Edit_RecvMsg.EnableWindow(FALSE);
	m_Edit_SendMsg.EnableWindow(FALSE);

	m_Button_DelMem.EnableWindow(FALSE);
	m_Button_Logout.EnableWindow(FALSE);
	m_Button_AddMem.EnableWindow(TRUE);
	m_Button_Login.EnableWindow(TRUE);
	m_Button_Send.EnableWindow(FALSE);

	m_Button_Login.ShowWindow(SW_SHOW);
	m_Button_AddMem.ShowWindow(SW_SHOW);
	m_Button_Logout.ShowWindow(SW_HIDE);
	m_Button_DelMem.ShowWindow(SW_HIDE);

	m_Edit_ID.SetWindowTextW(TEXT(""));
	m_Edit_PW.SetWindowTextW(TEXT(""));
}

void CMyMFC_MultiEcho_ClientView::view_ControlEnableAfterLogin()
{
	m_Edit_ID.EnableWindow(FALSE);
	m_Edit_PW.EnableWindow(FALSE);
	m_Edit_RecvMsg.EnableWindow(TRUE);
	m_Edit_SendMsg.EnableWindow(TRUE);

	m_Button_DelMem.EnableWindow(TRUE);
	m_Button_Logout.EnableWindow(TRUE);
	m_Button_AddMem.EnableWindow(FALSE);
	m_Button_Login.EnableWindow(FALSE);
	m_Button_Send.EnableWindow(TRUE);

	m_Button_Login.ShowWindow(SW_HIDE);
	m_Button_AddMem.ShowWindow(SW_HIDE);
	m_Button_Logout.ShowWindow(SW_SHOW);
	m_Button_DelMem.ShowWindow(SW_SHOW);
}

void CMyMFC_MultiEcho_ClientView::view_ControlEnableBeforeConnection()
{
	m_Button_DelMem.EnableWindow(FALSE);
	m_Button_Login.EnableWindow(FALSE);
	m_Button_Logout.EnableWindow(FALSE);
	m_Button_AddMem.EnableWindow(FALSE);
	m_Button_Send.EnableWindow(FALSE);

	m_Edit_ID.EnableWindow(FALSE);
	m_Edit_PW.EnableWindow(FALSE);
	m_Edit_RecvMsg.EnableWindow(FALSE);
	m_Edit_SendMsg.EnableWindow(FALSE);

	m_Button_Logout.ShowWindow(SW_HIDE);
	m_Button_Login.ShowWindow(SW_SHOW);
	m_Button_AddMem.ShowWindow(SW_SHOW);
}

void CMyMFC_MultiEcho_ClientView::view_ControlEnableAfterConnection()
{
	m_Button_Login.EnableWindow(TRUE);
	m_Button_AddMem.EnableWindow(TRUE);

	m_Edit_ID.EnableWindow(TRUE);
	m_Edit_PW.EnableWindow(TRUE);
}

void CMyMFC_MultiEcho_ClientView::view_ControlVisibleOnConnection()
{
}

void CMyMFC_MultiEcho_ClientView::view_ControlInvisibleOnConnection()
{
}

void CMyMFC_MultiEcho_ClientView::view_OnLogMessage(CString msg)
{
	view_AddLogMessage(msg);
}


void CMyMFC_MultiEcho_ClientView::OnMenuServerconfig()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyMFC_MultiEcho_ClientDoc* pDoc = GetDocument();

	CServerConfigDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		view_OnServerClosed();
	}

}


void CMyMFC_MultiEcho_ClientView::OnClickedButtonaddmember()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMyMFC_MultiEcho_ClientDoc* pDoc = GetDocument();

	CAddMemberDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		
	}

}


void CMyMFC_MultiEcho_ClientView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMyMFC_MultiEcho_ClientDoc* pDoc = GetDocument();


	if (!pDoc->ConnectProcessing && !pDoc->ServerConnected)
	{
		pDoc->ConnectProcessing = TRUE;
		pDoc->doc_OnTryServerConnect();
	}

	CFormView::OnTimer(nIDEvent);
}


void CMyMFC_MultiEcho_ClientView::view_AddLogMessage(CString msg)
{
	CString buf;
	buf.Format(TEXT("\r\n"));

	EnterCriticalSection(&cs_logmsg);
	m_Edit_RecvMsg.ReplaceSel(msg);
	m_Edit_RecvMsg.ReplaceSel(buf);
	LeaveCriticalSection(&cs_logmsg);
}

void CMyMFC_MultiEcho_ClientView::OnClickedButtonlogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString buf;
	LOGIN log;
	m_Edit_ID.GetWindowTextW(buf);
	wsprintf(log.id, buf);
	m_Edit_PW.GetWindowTextW(buf);
	wsprintf(log.pw, buf);
	log.flag = PACK_LOGIN;
	int sendlen = sizeof(LOGIN);
	GetDocument()->pMyNet->mynet_SendMessage((LPTSTR)&log, sendlen);
}

void CMyMFC_MultiEcho_ClientView::view_OnRecvData(LPTSTR data)
{
	CMyMFC_MultiEcho_ClientDoc* pDoc = GetDocument();
	PINT p = (PINT)data;

	switch (*p)
	{	// 요 아래도 핸들러로 모두 분류하라 너무 길다.
	case ACK_ADDMEMBERS:
	{
		MEMBER mem = *(PMEMBER)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[ADDMEMBER] %s님의 회원가입이 정상적으로 완료되었습니다."), mem.nickname);
		view_OnLogMessage(msg);
	}
	break;

	case ACK_ADDMEMBERF:
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[ADDMEMBER] ID중복/공백 등으로 인해 실패하였습니다."));
		view_OnLogMessage(msg);
	}break;

	case ACK_DELMEMBERS:
	{
		MEMBER mem = *(PMEMBER)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[DELMEMBER] %s님의 회원탈퇴가 정상적으로 완료되었습니다."), mem.nickname);
		view_OnLogMessage(msg);
		if (_tcscmp(pDoc->LoginNick, mem.nickname) == 0)
		{
			pDoc->LoginState = FALSE;
			view_ControlEnableBeforeLogin();
			pDoc->LoginNick.Format(TEXT(""));
		}
	}
	break;

	case ACK_DELMEMBERF:
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[DELMEMBER] 회원탈퇴 처리를 완료하지 못했습니다."));
		view_OnLogMessage(msg);
	}break;
	case ACK_LOGINS:
	{
		LOGIN log = *(PLOGIN)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGIN] %s님 환영합니다."), log.pw);
		view_OnLogMessage(msg);
		LOGIN tlog;
		CString tlog_id;

		//위에 함수 호출은 문제없는데 View쪽 컨트롤의 get함수를 쓰면 에러나는 문제가있다.
		m_Edit_ID.GetWindowTextW(tlog_id);
		wsprintf(tlog.id,tlog_id);
		if (_tcscmp(log.id, tlog_id) == 0)
		{
			pDoc->LoginState = TRUE;
			view_ControlEnableAfterLogin();
			pDoc->LoginNick.Format(TEXT("%s"), log.pw);
		}
	}
	break;
	case ACK_LOGINF:
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGIN] ID 및 PW가 일치하지 않습니다."));
		view_OnLogMessage(msg);
	}
	break;
	case ACK_LOGOUTS:
	{
		LOGIN log = *(PLOGIN)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGOUT] %s님이 로그아웃하였습니다"), log.pw);
		view_OnLogMessage(msg);
		if (_tcscmp(pDoc->LoginNick, log.pw) == 0)
		{
			pDoc->LoginState = FALSE;
			view_ControlEnableBeforeLogin();
			pDoc->LoginNick.Format(TEXT(""));
		}
	}
	break;
	case ACK_LOGOUTF:
	{
		TCHAR msg[MAX_MESSAGE_LENGHT];
		wsprintf(msg, TEXT("[LOGOUT] ID 및 PW가 일치하지 않습니다. (나타날수 없습니다)"));
		view_OnLogMessage(msg);
	}
	break;
	case ACK_MESSAGE:
	{
		MESSAGE log = *(PMESSAGE)data;
		TCHAR msg[MAX_MESSAGE_LENGHT];
		//wsprintf(msg, TEXT("[%s] %s"), GetDocument()->LoginNick, log.msg);
		wsprintf(msg, TEXT("%s"),log.msg);
		if (pDoc->LoginState)
			view_OnLogMessage(msg);

	}
	break;
	}
}

void CMyMFC_MultiEcho_ClientView::OnClickedButtonlogout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LOGIN log;
	CString buf;
	m_Edit_ID.GetWindowTextW(buf);
	wsprintf(log.id, buf);
	m_Edit_PW.GetWindowTextW(buf);
	wsprintf(log.pw, buf);
	log.flag = PACK_LOGOUT;
	int sendlen = sizeof(LOGIN);
	GetDocument()->pMyNet->mynet_SendMessage((LPTSTR)&log, sendlen);
}

void CMyMFC_MultiEcho_ClientView::OnClickedButtondeletemember()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MEMBER mem;
	CString buf;
	m_Edit_ID.GetWindowTextW(buf);
	wsprintf(mem.id, buf);
	m_Edit_PW.GetWindowTextW(buf);
	wsprintf(mem.pw, buf);
	wsprintf(mem.nickname,GetDocument()->LoginNick);
	mem.flag = PACK_DELMEMBER;
	int sendlen = sizeof(MEMBER);
	GetDocument()->pMyNet->mynet_SendMessage((LPTSTR)&mem, sendlen);

}

void CMyMFC_MultiEcho_ClientView::OnClickedButtonsend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MESSAGE msg;
	CString buf;
	m_Edit_SendMsg.GetWindowTextW(buf);


	wsprintf(msg.msg, TEXT("[%s] %s"), GetDocument()->LoginNick, buf);
	//wsprintf(msg.msg, TEXT("%s"), buf);
	msg.flag = PACK_MESSAGE;
	int sendlen = sizeof(MESSAGE);
	GetDocument()->pMyNet->mynet_SendMessage((LPTSTR)&msg, sendlen);

	m_Edit_SendMsg.SetWindowTextW(TEXT(""));
}


//void CMyMFC_MultiEcho_ClientView::OnClose()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	KillTimer(1);
//	CFormView::OnClose();
//}


void CMyMFC_MultiEcho_ClientView::OnAppExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(1);
}


void CMyMFC_MultiEcho_ClientView::view_OnServerClosed()
{
	CMyMFC_MultiEcho_ClientDoc* pDoc = GetDocument();
	if (pDoc->LoginState)
	{
		OnClickedButtonlogout();
	}
	pDoc->pMyNet->mynet_ConnectionClose();
	view_ControlEnableBeforeConnection();
	pDoc->LoginState = FALSE;
	pDoc->ServerConnected = FALSE;
}
