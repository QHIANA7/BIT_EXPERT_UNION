
// MainFrm.cpp : CMainFrame 클래스의 구현
//


#include "stdafx.h"
#include "MFC_Basic_Practice.h"

#include "MainFrm.h"

#include "UI.h"
#include "PaneView.h"
#include "MFC_Basic_PracticeView.h"//정적분할 윈도우




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_MESSAGE(WM_MY_TASKBAR, TrayIconSetting)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_PT,
	ID_INDICATOR_COLOR,
	ID_INDICATOR_TYPE,
	ID_INDICATOR_WIDTH,
	ID_INDICATOR_TIME,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	m_bTray = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	// 상태바 Pane의 Style을 바꾼다. 결국 CStatusBar의 멤버 함수
	// 이용
	//m_wndStatusBar.SetPaneStyle( 5, SBPS_POPOUT);// 볼록
	m_wndStatusBar.SetPaneStyle(5, SBPS_NOBORDERS);// 평면.

												   // Timer 를 설정한다.
	SetTimer(1, 1000, 0); // ID, 주기, 함수.
						  // 처음에 1번 강제로 WM_TIMER를 보낸다.
	SendMessage(WM_TIMER, 1); // wParam = ID


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1)
	{
		CUI::Pane_PrintTime(this);
	}
	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nHitTest == HTMINBUTTON)
	{
		CUI::OnTrayIcon(this);
	}

	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}


LONG CMainFrame::TrayIconSetting(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDOWN) {
		//AfxMessageBox(TEXT("TrayIcon을 선택했습니다."));
		ShowWindow(SW_SHOW);
		CUI::OnTrayDelete(this);
	}
	else if (lParam == WM_RBUTTONDOWN)
	{
		POINT pt;
		::GetCursorPos(&pt);


		CMenu menu;
		menu.LoadMenu(IDR_MYMENU); // 메뉴 아이디

		CMenu *pMenu = menu.GetSubMenu(0); //서브메뉴 몇번째꺼
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTALIGN,
			pt.x, pt.y, AfxGetMainWnd());
	}
	return 0L;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//// 동적 Splitter 만들기.
	//return m_wndSplitter.Create(this, 2, 2, CSize(100, 100), pContext);
	//// 동적 Splitter은 같은 종류의 view( CSampleView)만 가지고
	//// 있기 때문에 사용자가 splitter만 만들면 View는 MFC가 자동으로
	//// 만들어 준다.

	CRect rect;
	GetClientRect(rect);

	// 정적 Splitter 만들기.
	// 1. splitter 를 먼저 만든다.
	m_wndSplitter1.CreateStatic(this, 1, 2);
	//현재 프레임을 1행 2열로 자른다.

	// 2. 정적 splitter은 각View가 다를수 있으므로 직접 view를
	// 정적의 경우 직접 뷰를 할당해 주어야 한다. 없으면 만든다.
	m_wndSplitter1.CreateView(0, 0, //나눈 (0,0)위치에다가
		RUNTIME_CLASS(CMyMFC_Basic_PracticeView), // 분할창의 View 지정
		CSize(rect.right / 2, rect.bottom), pContext);

	//여기까지하고 실행한다면 남은 뷰가 아직 할당되지않아 죽는다. Create에서 오류

	// 0,1 pane에는 splitter을 넣는다.
	m_wndSplitter2.CreateStatic(&m_wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE,m_wndSplitter1.IdFromRowCol(0, 1)); // ID !!!
								//m_wndSplitter1이 자른 곳을 2행 1열로 자르며 부모의 0,1부분에서 수행한다.
																												 
	 // 새로운 splitter위에 View를 넣는다.
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CPaneView), CSize(rect.right / 2, rect.bottom / 2), pContext);
	m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CPaneView), CSize(rect.right / 2, rect.bottom / 2), pContext);
	return TRUE;

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
