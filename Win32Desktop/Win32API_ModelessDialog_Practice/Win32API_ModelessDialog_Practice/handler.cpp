//handler.cpp
#include "std.h"

void OnACInputSelect(HWND hDlg)
{
	ACCOUNT data;
	//=========================================================
	//DialogBoxParam : 모달 대화상자를 띄움
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_MODALACCOUNTINPUT),	//모달 대화상자 ID
		hDlg,		// 부모
		DlgModalAccInputProc,	// 메세지 처리 프로시저
		(LPARAM)&data);			//대화상자에 넘길 데이터 주소 LPARAM타입
	//모달의 경우 대화상자가 닫히기 전까진 이 이후로 진행되지 않음
	//대화상자가 닫혔을 때 UINT ret에 종료 ID 값이 들어감
	//=========================================================

	if (ret == IDOK)	//등록에 의한 종료였을 경우
	{
		cur_data = data;
		account_exist = TRUE;
	}
}

void OnACDeleteSelect(HWND hDlg)
{
	ACCOUNT data = cur_data;
	//=========================================================
	//DialogBoxParam : 모달 대화상자를 띄움
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_MODALACCOUNTDELETE),	//모달 대화상자 ID
		hDlg,		// 부모
		DlgModalAccDeleteProc,	// 메세지 처리 프로시저
		(LPARAM)&data);		// 모달 대화상자에 넘길 데이터 주소 LPARAM타입
	//모달의 경우 대화상자가 닫히기 전까진 이 이후로 진행되지 않음
	//대화상자가 닫혔을 때 UINT ret에 종료 ID 값이 들어감
	//=========================================================
	
	if (ret == IDOK)	//삭제버튼에 의한 종료 였을 경우
	{
		account_exist = FALSE;
		AccountInit(&cur_data);			//계좌 초기화
		g_veclist.clear();				//입출금내역을 담은 벡터 초기화
		view_ListViewPrintAll(hDlg);	//리스트뷰 재출력
	}
}

void OnBankingButtonSelect(HWND hDlg)
{
	if (g_hDlg == 0)
	{
		//=========================================================
		//static의 역할은 현재 파일에서만 사용할것
		//모달리스 대화상자에서는 지역변수를 사용하는것이 바람직하지 않음
		//-> 모달리스의 경우 바로 함수가 종료되기 때문에 지역변수가 소멸된다.
		//대책 : 전역변수로 만들어라.
		//=========================================================
		g_hDlg = CreateDialogParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_MODALESSBANKING),	//모달 대화상자 ID
			hDlg,		// 부모
			DlgModalessProc, // 메세지 처리 프로시저
			(LPARAM)&cur_data);
		ShowWindow(g_hDlg, SW_SHOW);
	}
	else
		SetFocus(g_hDlg);	//이미 만들어진경우 포커스만 
}

BOOL OnNotify(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	return TRUE;
}

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCommonControls();
	view_GetControlHandle(hDlg);
	view_InitControl(hDlg);
	AccountInit(&cur_data);
	return 0;
}

BOOL OnInitDialogAtModaless(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	return 0;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
		//입/출금 버튼
	case IDC_BUTTONBANKING: OnBankingButtonSelect(hDlg); return 0;	
	case ID_ACCOUNTDELETE: OnACDeleteSelect(hDlg); return 0;
	case ID_ACCOUNTINPUT: OnACInputSelect(hDlg); return 0;
	case IDCANCEL:	EndDialog(hDlg, IDCANCEL);return 0;
		//메뉴-프로그램종료
	case ID_PROGEXIT: EndDialog(hDlg, IDCANCEL); return 0;
	}
	return TRUE;
}

BOOL OnMouseMove(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	if (account_exist)
		Button_Enable(hButtonBanking, TRUE);
	else
		Button_Enable(hButtonBanking, FALSE);



	return TRUE;
}

LRESULT OnInitMenuPopUp(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = (HMENU)wParam;	//임시 메뉴핸들 변수에 드롭다운 메뉴 핸들 대입

	if (account_exist)	//계좌가 생성되어 있는 경우
	{
		EnableMenuItem(hMenu, ID_ACCOUNTINPUT, MF_GRAYED);
		EnableMenuItem(hMenu, ID_ACCOUNTDELETE, MF_ENABLED);
	}
	else
	{
		EnableMenuItem(hMenu, ID_ACCOUNTDELETE, MF_GRAYED);
		EnableMenuItem(hMenu, ID_ACCOUNTINPUT, MF_ENABLED);
	}
	return TRUE;
}
