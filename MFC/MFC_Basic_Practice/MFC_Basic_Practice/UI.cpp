#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "UI.h"


CUI::CUI()
{
}


CUI::~CUI()
{
}

void CUI::Pane_PrintTime(CMainFrame* p)
{
	// 사용자 클래스 => Frame
	CTime t = CTime::GetCurrentTime(); // 현재 시간 얻기
	CString buf;
	buf.Format(TEXT("%02d:%02d:%02d"),
		t.GetHour(), t.GetMinute(), t.GetSecond());
	p->m_wndStatusBar.SetPaneText(5, buf);
}


void CUI::Pane_PrintPT(CMainFrame* p, CPoint point)
{
	CString buf;
	buf.Format(TEXT("(%04d:%04d)"),	point.x,point.y);
	p->m_wndStatusBar.SetPaneText(1, buf);
}


void CUI::Pane_PrintColor(CMainFrame* p, COLORREF color)
{
	CString buf;
	buf.Format(TEXT("(%03d,%03d,%03d)"),
		GetRValue(color), GetGValue(color), GetBValue(color));
	p->m_wndStatusBar.SetPaneText(2, buf);
}


void CUI::Pane_PrintType(CMainFrame* p, int type)
{
	CString buf;

	buf.Format(TEXT("%s"),
		type == ID_SHAPE_RECT ? TEXT("사각형") : TEXT("타　원"));
	p->m_wndStatusBar.SetPaneText(3, buf);
}


void CUI::Pane_PrintWidth(CMainFrame* p, int width)
{
	CString buf;
	
	switch (width)
	{
	case ID_WIDTH_1:buf.Format(TEXT("%03d"), 1); break;
	case ID_WIDTH_3:buf.Format(TEXT("%03d"), 3); break;
	case ID_WIDTH_5:buf.Format(TEXT("%03d"), 5); break;
	}
	p->m_wndStatusBar.SetPaneText(4, buf);
}


void CUI::OnTrayIcon(CMainFrame* p)
{
	p->ShowWindow(SW_HIDE);

	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = p->m_hWnd;
	nid.uID = IDI_ICON1;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	//메시지를 발생시켰을때 처리 | 아이콘 사용 | 툴팁을 출력
	nid.uCallbackMessage = WM_MY_TASKBAR;
	nid.hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);

	TCHAR strTitle[256];
	//p->GetWindowText(strTitle, sizeof(strTitle));
	wsprintf(strTitle, TEXT("MFC_Basic_Practice"));
	lstrcpy(nid.szTip, strTitle);

	Shell_NotifyIcon(NIM_ADD, &nid);
	//실제 트레이아이콘이 등록되는 부분

	p->SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	p->m_bTray = TRUE;
}


void CUI::OnTrayDelete(CMainFrame* p)
{
	if (p->m_bTray) {
		NOTIFYICONDATA nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = p->m_hWnd;
		nid.uID = IDI_ICON1;
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}
