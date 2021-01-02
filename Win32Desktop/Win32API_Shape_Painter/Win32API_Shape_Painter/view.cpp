//view.cpp
#include "std.h"

void view_ControlCreate(HWND hwnd)	//��Ʈ�� ����
{
	CreateWindow(TEXT("button"), TEXT("[ ���� ���� ]"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 220, 300, hwnd, 0, 0, 0);
	CreateWindow(TEXT("static"), TEXT("- Ÿ��"), WS_CHILD | WS_VISIBLE, 20, 40, 50, 20, hwnd, 0, 0, 0);
	hRadioRectangle = CreateWindow(TEXT("button"), TEXT("�簢��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
		80, 40, 70, 20, hwnd, (HMENU)IDC_RADIORECTANGLE, 0, 0);
	hRadioEllipse = CreateWindow(TEXT("button"), TEXT("Ÿ��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		160, 40, 60, 20, hwnd, (HMENU)IDC_RADIOELLIPSE, 0, 0);
	CreateWindow(TEXT("static"), TEXT("- ��ǥ"), WS_CHILD | WS_VISIBLE, 20, 70, 50, 20, hwnd, 0, 0, 0);

	CreateWindow(TEXT("static"), TEXT("X"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 70, 20, 20, hwnd, 0, 0, 0);
	hEditPosX = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 70, 40, 20, hwnd, (HMENU)IDC_EDITPOSX, 0, 0);
	CreateWindow(TEXT("static"), TEXT("Y"), WS_CHILD | WS_VISIBLE | SS_CENTER, 150, 70, 20, 20, hwnd, 0, 0, 0);
	hEditPosY = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 170, 70, 40, 20, hwnd, (HMENU)IDC_EDITPOSY, 0, 0);

	CreateWindow(TEXT("static"), TEXT("- ����"), WS_CHILD | WS_VISIBLE, 20, 100, 50, 20, hwnd, 0, 0, 0);
	CreateWindow(TEXT("static"), TEXT("R"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 100, 20, 20, hwnd, 0, 0, 0);
	hEditColorR = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 100, 40, 20, hwnd, (HMENU)IDC_EDITCOLORR, 0, 0);
	CreateWindow(TEXT("static"), TEXT("G"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 130, 20, 20, hwnd, 0, 0, 0);
	hEditColorG = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 130, 40, 20, hwnd, (HMENU)IDC_EDITCOLORG, 0, 0);
	CreateWindow(TEXT("static"), TEXT("B"), WS_CHILD | WS_VISIBLE | SS_CENTER, 80, 160, 20, 20, hwnd, 0, 0, 0);
	hEditColorB = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 100, 160, 40, 20, hwnd, (HMENU)IDC_EDITCOLORB, 0, 0);

	CreateWindow(TEXT("static"), TEXT("- �β�"), WS_CHILD | WS_VISIBLE, 20, 190, 50, 20, hwnd, 0, 0, 0);
	hComboPenWidth = CreateWindow(TEXT("combobox"), TEXT(""),
		WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DROPDOWN
		, 80, 190, 60, 80, hwnd, (HMENU)IDC_COMBOPENWIDTH, 0, 0);
	SendMessage(hComboPenWidth, CB_ADDSTRING, 0, (LPARAM)TEXT("1"));
	SendMessage(hComboPenWidth, CB_ADDSTRING, 0, (LPARAM)TEXT("3"));
	SendMessage(hComboPenWidth, CB_ADDSTRING, 0, (LPARAM)TEXT("5"));

	CreateWindow(TEXT("static"), TEXT("- ���"), WS_CHILD | WS_VISIBLE, 20, 270, 50, 20, hwnd, 0, 0, 0);
	hEditMode = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 80, 270, 40, 20, hwnd, (HMENU)IDC_EDITMODE, 0, 0);

	CreateWindow(TEXT("static"), TEXT("- ����"), WS_CHILD | WS_VISIBLE, 130, 270, 50, 20, hwnd, 0, 0, 0);
	hEditTransparentMode = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 180, 270, 40, 20, hwnd, (HMENU)IDC_EDITTRANSPARENTMODE, 0, 0);

	CreateWindow(TEXT("button"), TEXT("[ ���� ���� ]"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 240, 10, 170, 600, hwnd, 0, 0, 0);
	CreateWindow(TEXT("static"), TEXT("- ���� ����"), WS_CHILD | WS_VISIBLE, 250, 40, 80, 20, hwnd, 0, 0, 0);

	hEditSaveCount = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT, 340, 40, 40, 20, hwnd, (HMENU)IDC_EDITSAVECOUNT, 0, 0);
	CreateWindow(TEXT("static"), TEXT("��"), WS_CHILD | WS_VISIBLE | SS_CENTER, 380, 40, 20, 20, hwnd, 0, 0, 0);

	hListSave = CreateWindow(TEXT("listbox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 250, 70, 150, 540, hwnd, (HMENU)IDC_LISTSAVE, 0, 0);
}

void view_ControlInit(HWND hwnd)	//cur_data -> Control
{
	if (cur_data.type == 1)
		CheckRadioButton(hwnd, IDC_RADIORECTANGLE, IDC_RADIOELLIPSE, IDC_RADIORECTANGLE);
	else
		CheckRadioButton(hwnd, IDC_RADIORECTANGLE, IDC_RADIOELLIPSE, IDC_RADIOELLIPSE);
	SetDlgItemInt(hwnd, IDC_EDITPOSX, cur_data.pt.x, 0);
	SetDlgItemInt(hwnd, IDC_EDITPOSY, cur_data.pt.y, 0);
	SetDlgItemInt(hwnd, IDC_EDITCOLORR, GetRValue(cur_data.color), 0);
	SetDlgItemInt(hwnd, IDC_EDITCOLORG, GetGValue(cur_data.color), 0);
	SetDlgItemInt(hwnd, IDC_EDITCOLORB, GetBValue(cur_data.color), 0);
	SendMessage(hComboPenWidth, CB_SETCURSEL, cur_data.penwidth/2, 0);
	SetDlgItemInt(hwnd, IDC_EDITSAVECOUNT, g_veclist.size(), 0);

	if (cur_data.transparentFlag)
		SetWindowText(hEditTransparentMode, TEXT("TRUE"));
	else
		SetWindowText(hEditTransparentMode, TEXT("FALSE"));

	InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);
}

void view_ControlListBoxPrint(HWND hwnd) //����Ʈ�ڽ� ���� ���� -> g_veclist�� �ִ� ��� ���� �߰�
{
	TCHAR buf[50];	//�ӽ� ���� ���ڿ� ����
	SendMessage(hListSave, LB_RESETCONTENT, 0, 0);
	//LB_DELETESTRING�޽��� ���� �����ϴ� �Ű������� i,0�̸� i�ε����� ����� �޽�����. (�ݺ��� �ʿ�)
	for (int i = 0; i < (int)g_veclist.size(); i++)	//vector�� ����� ����ŭ �ݺ�
	{
		DRAWTYPE temp = g_veclist[i];	
		wsprintf(buf, TEXT("%02d|%s(%3d,%3d)"),i+1 , temp.type == 1 ? TEXT("�簢��") : TEXT("Ÿ����"), temp.pt.x, temp.pt.y);
		SendMessage(hListSave, LB_ADDSTRING, 0, (LPARAM)buf);	//ListBox�� ���ڿ��� �߰�
		//���� : �� �������� ���ڿ��� �߰����� �ʴ´�. ����޽��� ó���� LB_ADDSTRING ó���� �߰��ȴ�.
	}
	//LB_ADDSTRING : ListBox�� ���ڿ��� �߰��϶�� �޽��� - lParam�� ���ڿ��� �Ѱ������
	//LBN_SELCHANGE : ������ �ٲ������ �߻��ϴ� �޽���
	//LB_GETCURSEL : ����Ʈ�ڽ����� �ε����� ��ȯ�Ѵ�.
}

void view_GetControlData(HWND hwnd)	//Control -> cur_data
{
	if (SendMessage(hRadioRectangle, BM_GETCHECK, 0, 0) == BST_CHECKED)	//��ư ��Ʈ���� äũ������ �������� �޽���
		cur_data.type = 1;
	else
		cur_data.type = 2;

	cur_data.pt.x =	GetDlgItemInt(hwnd, IDC_EDITPOSX, 0, 0);	//EDIT ��Ʈ�� �ؽ�Ʈ�� �������� ������
	cur_data.pt.y = GetDlgItemInt(hwnd, IDC_EDITPOSY, 0, 0);	//Pos �κ�

	cur_data.color = RGB(
		(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORR, 0, 0),	//EDIT ��Ʈ�� �ؽ�Ʈ�� �������� ������
		(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORG, 0, 0),	//RGB�κ�
		(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORB, 0, 0));

	//GetDlgItemInt : �ϳ��� �θ��� â�� �ְ� �׾��� ID�������� �������� ������
	//�θ��ڵ�, ��Ʈ��ID,NULL,NULL

	cur_data.penwidth = SendMessage(hComboPenWidth, CB_GETCURSEL, 0, 0) * 2 + 1;
	//ComboBox ��Ʈ���� ���õ� �ε����� �޶�� �޽���

	TCHAR buf[50];
	GetWindowText(hEditTransparentMode, buf, sizeof(buf));
	if (!_tcscmp(buf, TEXT("TRUE")))
		cur_data.transparentFlag = TRUE;
	else
		cur_data.transparentFlag = FALSE;

	InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);	//PrivewColor�κ� ��ȿȭ������ ����� WM_Paint�߻�
}

void view_SetControlData(HWND hwnd)
{
	view_ControlInit(hwnd);
}

void view_DrawShape(HWND hwnd, DRAWTYPE * dt, WPARAM wParam, LPARAM lParam)
{
	cur_data.pt.x = LOWORD(lParam);	//LOWORD�� lParam�� ���� 16��Ʈ ���� �������°�.
	cur_data.pt.y = HIWORD(lParam);	//HIWORD�� ����16��Ʈ�� ������

	TCHAR buf[50];
	GetWindowText(hEditTransparentMode, buf, sizeof(buf));
	//(submenu3 == ID_40008 && cur_data.color == RGB(255,255,255)) ?
	_tcscmp(buf,TEXT("TURE")) ?
		cur_data.transparentFlag = TRUE : cur_data.transparentFlag = FALSE;
		//�޴��� ������ ���õ��ְ� cur_data�� RGB�� ����ΰ�� cur_data�� ������ Ȱ��ȭ

	
	view_GetControlData(hwnd);		//Control -> cur_data
	

	if (wParam & MK_CONTROL)	//��Ʈ���� �������� ���
	{
		if ((int)g_veclist.size() > 0)	//vector�� �ϳ��� ����Ǿ����� ���
			g_veclist.pop_back();		//�������� ���Ե� ��� ����
	}
	else
	{
		g_veclist.push_back(cur_data);	//cur_data�� vector�� ����
	}

	InvalidateRect(hwnd, &InvalidArea, TRUE);	//�׸��� ������ ��ȿȭ -> WM_PAINT �߻�
	//���� : �� �Լ� ������ OnPaint�Լ��� ����Ǵ°� �±��ϳ� ���� �޽����� �����Ŀ� ����Ǿ�
	//�� �������� �׷����� �ʴ´�.

	OnCommandInvalid = TRUE;
	view_ControlInit(hwnd);			//cur_data -> Control
	OnCommandInvalid = FALSE;
}

void view_SetTimer(HWND hwnd)	//OnCreate���� ���� : Ÿ�̸� ����
{
	SetTimer(hwnd, 1, 1000, NULL);	//ID�� 1�� 1000ms������ Ÿ�̸Ӹ� �����ϰ� �ֱ⸶�� WM_TIMER ȣ��
	SendMessage(hwnd, WM_TIMER, 1, NULL);
	//�� �޽����� �����ϴ� ������ ���� WM_CREATE�޽��� ó�����̹Ƿ� WM_TIMER �޽����� �� ���߿� ó���Ѵ�.
	//ShowWindow�Լ� ���� ���� GetMessage - DispatchMessage�� ���� �޽����� ó���ϴ� �������� ó���ȴ�.
	//WM_TIMER�� OnCreate ��ÿ� ť�� �����Ͽ� ������ �߻����� �����Ѵ�.
}

void view_SetTimeToWindowText(HWND hwnd)
{
	SYSTEMTIME st;	//
	TCHAR buf[256];
	GetLocalTime(&st);
	wsprintf(buf, TEXT("���� �ð� - %04d�� %02d�� %02d��"), st.wYear, st.wMonth, st.wDay);
	wsprintf(buf + _tcslen(buf), TEXT("  %02d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond);
	SetWindowText(hwnd, buf);
}

void view_ShapePrint(HDC hdc, vector<DRAWTYPE> *g_veclist) //OnPaint���� ���� : ���Ϳ� ����� ��� �׸��� �׸�
{
	for (int i = 0; i < (int)g_veclist->size(); i++)	//vector�� ����� ����ŭ �ݺ�
	{
		DRAWTYPE dt = (*g_veclist)[i];	//���������ؾ� ���ʿ� �迭�� �����Ѵ�. ���� g_veclist�� �������� ���� �ε����� ã�´�.

		HBRUSH br;	//�ӽ� �귯�� �ڵ� ����
		if (dt.transparentFlag)		//���� ����� ������
			br = (HBRUSH)GetStockObject(NULL_BRUSH);	//�̸����ǵ� ����귯���� ������ br������
		else
			br = CreateSolidBrush(dt.color);			//���� ����� RGB�� �귯���� �����Ͽ� br�� ����

		HBRUSH oldbr = (HBRUSH)SelectObject(hdc, br);	//������ ������ �귯���� ������ ���������� oldbr�� ����

		HPEN pn = CreatePen(PS_SOLID, dt.penwidth, RGB(255,145,169));	//�������� �������� �Ǽ��� ����
		HPEN oldpn = (HPEN)SelectObject(hdc, pn);		//������ ������ ������ ������ ���������� oldpn�� ����

		if (dt.type == 1)	//�������� type�� 1�� ���
			Rectangle(hdc, dt.pt.x-25, dt.pt.y-25, dt.pt.x + 25, dt.pt.y + 25);	//�簢���� �׸�
		else if (dt.type == 2)
			Ellipse(hdc, dt.pt.x-25, dt.pt.y-25, dt.pt.x + 25, dt.pt.y + 25);	//Ÿ���� �׸�

		DeleteObject(SelectObject(hdc, oldbr));	//������ ����ߴ� �귯��, ���� ���������� ������ �Ҹ�
		DeleteObject(SelectObject(hdc, oldpn));
	}
}

void view_PreviewColorPrint(HDC hdc)	//OnPaint���� ���� : RGB EDIT��Ʈ�� ���� ���� ���� �簢���� �׸�
{
	HBRUSH br;	//�ӽ� �귯�� �ڵ� ����
	//if ((submenu3 == ID_40008 || cur_data.transparentFlag == TRUE) && cur_data.color == RGB(255, 255, 255))
	if(cur_data.transparentFlag)
			//�޴��� ������ ���õ��ְų� cur_data�� ������ Ȱ��ȭ ���ְ� RGB�� ����ΰ��
		br = (HBRUSH)GetStockObject(NULL_BRUSH);	//�̸����ǵ� ����귯���� ������ br������
	else
		br = CreateSolidBrush(cur_data.color);	//cur_data�� RGB���� �귯���� �����Ͽ� br�� ����

	HBRUSH oldbr = (HBRUSH)SelectObject(hdc, br);	//������ ������ �귯���� ������ ���������� oldbr�� ����

	MoveToEx(hdc, 150, 100, NULL);	//���� �׸�
	LineTo(hdc, 210, 180);
	MoveToEx(hdc, 150, 180, NULL);
	LineTo(hdc, 210, 100);

	Rectangle(hdc, 150, 100, 210, 180);	//�簢���� �׸�

	DeleteObject(SelectObject(hdc, oldbr));	//������ ����ߴ� �귯�ø� �����ɷ� ������ ����ߴ� �귯���� �Ҹ�
}

void view_NewFile(HWND hwnd)
{
	OnCommandInvalid = TRUE;	//���� �����ϴµ��� OnCommand ��ȿȭ
	DrawInit(&cur_data);		//cur_data�� �ʱ���·� ����
	g_veclist.clear();			//vector����Ʈ�� �ʱ�ȭ
	view_ControlInit(hwnd);		//Control�� �ʱ�ȭ�Ѵ�.(cur_data�� ���� �д´�.)
	InvalidateRect(hwnd, &InvalidArea, TRUE);	//InvalidArea������ ��ȿȭ��Ű�� �����.
	view_ControlListBoxPrint(hwnd);			//ListBox��Ʈ���� ����Ѵ�
	OnCommandInvalid = FALSE;	//�� �ʱ�ȭ�� �Ϸ�Ǿ� OnCommand ��ȿȭ
}

void view_RefreshSetting(HWND hwnd)
{
	OnCommandInvalid = TRUE;	//���� �����ϴµ��� OnCommand ��ȿȭ
	if (ShapeUpdateMode)
	{
		view_ControlInit(hwnd);						//cur_data -> Control
		view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
	}
	else
	{
		view_ControlInit(hwnd);		//cur_data -> Control
		view_GetControlData(hwnd);	//Control -> cur_data
	}
	OnCommandInvalid = FALSE;	//�� ������ �Ϸ�Ǿ� OnCommand ��ȿȭ
}

void view_UpdateShapeByLBControl(HWND hwnd)	//g_veclist[idx] -> cur_data -> Control
{
	OnCommandInvalid = TRUE;	//�� �Լ��� �����ϴµ��� OnCommand �޽����� ó������ ����

	int idx = SendMessage(hListSave, LB_GETCURSEL, 0, 0);	//����Ʈ�ڽ��� Ŀ���� �޶�� �޽��� ����

	cur_data = g_veclist[idx];	//vector�� idx �ε��� ��Ҹ� cur_data�� ����

	view_ControlInit(hwnd);		//cur_data -> Control

	//if (dt.type == 1)	//��ư �ڵ��� äũ������ �������� �޽���
	//{
	//	SendMessage(hRadioRectangle, BM_SETCHECK, BST_CHECKED, 0);
	//	SendMessage(hRadioEllipse, BM_SETCHECK, BST_UNCHECKED, 0);
	//}
	//else
	//{
	//	SendMessage(hRadioRectangle, BM_SETCHECK,BST_UNCHECKED, 0);
	//	SendMessage(hRadioEllipse, BM_SETCHECK, BST_CHECKED, 0);
	//}

	//SetDlgItemInt(hwnd, IDC_EDITPOSX, dt.pt.x, 0);
	//SetDlgItemInt(hwnd, IDC_EDITPOSY, dt.pt.y, 0);

	//SetDlgItemInt(hwnd, IDC_EDITCOLORR, GetRValue(dt.color), 0);
	//SetDlgItemInt(hwnd, IDC_EDITCOLORG, GetGValue(dt.color), 0);
	//SetDlgItemInt(hwnd, IDC_EDITCOLORB, GetBValue(dt.color), 0);

	//SendMessage(hComboPenWidth, CB_SETCURSEL, dt.penwidth / 2, 0);
	//InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);

	OnCommandInvalid = FALSE; //���ݺ��� OnCommand �޽����� ó��
}

void view_UpdateShapeByEditControl(HWND hwnd)	//Control -> cur_data -> c_veclist[idx]
{
	int i = SendMessage(hListSave, LB_GETCURSEL, 0, 0);	//����Ʈ�ڽ��� Ŀ���� �޶�� �޽��� ����

	if (i == LB_ERR)	//�� �޽����� ��ȯ���� �������� ���
		return;
	else
	{

		view_GetControlData(hwnd);	//Control -> cur_data
		g_veclist[i] = cur_data;	//vector�� i��° ��Ҵ� cur_data�� ��ü
		
		
		//if (SendMessage(hRadioRectangle, BM_GETCHECK, 0, 0) == BST_CHECKED)	//��ư �ڵ��� äũ������ �������� �޽���
		//	g_veclist[i].type = 1;
		//else
		//	g_veclist[i].type = 2;

		//g_veclist[i].pt.x = GetDlgItemInt(hwnd, IDC_EDITPOSX, 0, 0);
		//g_veclist[i].pt.y = GetDlgItemInt(hwnd, IDC_EDITPOSY, 0, 0);

		//g_veclist[i].color = RGB(
		//	(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORR, 0, 0),
		//	(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORG, 0, 0),
		//	(BYTE)GetDlgItemInt(hwnd, IDC_EDITCOLORB, 0, 0));

		//(submenu3 == ID_40008 && cur_data.color == RGB(255, 255, 255)) ?
		//	g_veclist[i].transparentFlag = TRUE : g_veclist[i].transparentFlag = FALSE;

		//g_veclist[i].penwidth = SendMessage(hComboPenWidth, CB_GETCURSEL, 0, 0) * 2 + 1;

		view_ControlListBoxPrint(hwnd);	//vector�� ����� ��ҵ��� ������ ����Ʈ�ڽ��� ���

		SendMessage(hListSave, LB_SETCURSEL, i, 0);	//����Ʈ�ڽ��� ���ŵǾ����Ƿ� ���� ���õ��ִ� �ε����� �ٽ� ����

		InvalidateRect(hwnd, &InvalidArea, TRUE);	//�׸��� ���� ��ȿȭ
		InvalidateRect(hwnd, &ExtraInvalidArea, TRUE);

		return;
	}
}

