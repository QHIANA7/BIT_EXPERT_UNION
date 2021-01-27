//dlgmodalserverconfig.cpp

#include "std.h"

HWND hIpAddress, hEditServerConfigPort;

BOOL CALLBACK DlgModalServerConfigProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static SERVERINFO *pData;

	switch (msg)
	{
	case WM_INITDIALOG:	//대화상자가 생성시 수행
	{
		//==================== 서버 설정 ===========================
		hIpAddress = GetDlgItem(hDlg, IDC_IPADDRESS1);
		hEditServerConfigPort = GetDlgItem(hDlg, IDC_EDITSERVERCONFIGPORT);
		//==========================================================
		pData = (PSERVERINFO)lParam; 

		SendMessage(hIpAddress, IPM_SETADDRESS, 0, (LPARAM)pData->s_ip);
		SetDlgItemInt(hDlg, IDC_EDITSERVERCONFIGPORT, pData->s_port,0);

	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:	//등록을 눌렀구나!
		{
			pData->s_port = GetDlgItemInt(hDlg, IDC_EDITSERVERCONFIGPORT, 0, 0);
			SendMessage(hIpAddress, IPM_GETADDRESS, 0, (LPARAM)&pData->s_ip);
			EndDialog(hDlg, IDOK);	//대화상자를 닫고 IDOK를 반환
		}
		return TRUE;

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return TRUE;
		}
	}
	return FALSE;
}