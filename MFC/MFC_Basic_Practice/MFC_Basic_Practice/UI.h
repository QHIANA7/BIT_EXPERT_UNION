#pragma once

//클래스 선언(전방참조) 
//class CMainFrame;

class CUI
{
public:
	CUI();
	~CUI();
public:
	//==================== 상태바 관련 기능 ========================
	static void Pane_PrintTime(CMainFrame* p);
	static void Pane_PrintPT(CMainFrame* p, CPoint point);
	static void Pane_PrintColor(CMainFrame* p,COLORREF color);
	static void Pane_PrintType(CMainFrame* p,int type);
	static void Pane_PrintWidth(CMainFrame* p, int width);
	//===============================================================

	//===================== 트레이 아이콘 ===========================
	static void OnTrayIcon(CMainFrame* p);
	static void OnTrayDelete(CMainFrame* p);
	//===============================================================
	
};

