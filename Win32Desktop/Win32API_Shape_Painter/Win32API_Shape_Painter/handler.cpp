//handler.cpp
#include "std.h"

BOOL IsContainPos(POINT pt, RECT rt)	// pt��ǥ�� rt���� ���ο� �ֽ��ϱ�?
{
	if (pt.x > rt.left && pt.x < rt.right)
		if (pt.y > rt.top && pt.y < rt.bottom)
			return TRUE;

	return FALSE;
}

void OnEditPos(HWND hwnd, WPARAM wParam)	//��ǥ�� ǥ���ϴ� EDIT ��Ʈ���� �޽���
{
	switch (HIWORD(wParam))	//���� �޽����ΰ�?
	{
	case EN_CHANGE:	//����Ʈ �˸� : ���� ����Ǿ���.
		if (ShapeUpdateMode)	//������尡 Ȱ��ȭ �Ǿ��ִ°�?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
			view_GetControlData(hwnd);				//Control -> cur_data
		break;
	}
}

void OnEditColor(HWND hwnd, WPARAM wParam)
{
	switch (HIWORD(wParam))	//���� �޽����ΰ�?
	{
	case EN_CHANGE:	//����Ʈ �˸� : ���� ����Ǿ���.
		cur_data.transparentFlag = FALSE;
		SetWindowText(hEditTransparentMode, TEXT("FALSE"));
		if (ShapeUpdateMode)	//������尡 Ȱ��ȭ �Ǿ��ִ°�?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
		{
			view_GetControlData(hwnd);				//Control -> cur_data		
		}
		break;
	}	
}

void OnRadioDrawType(HWND hwnd, WPARAM wParam)
{
	switch (HIWORD(wParam))	//���� �޽����ΰ�?
	{
	case BN_CLICKED:	//��ư �˸� : ��ư�� Ŭ���Ǿ���.
		if (ShapeUpdateMode)	//������尡 Ȱ��ȭ �Ǿ��ִ°�?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
			view_GetControlData(hwnd);				//Control -> cur_data
		break;
	}
}

void OnComboPenWidth(HWND hwnd, WPARAM wParam)
{
	switch (HIWORD(wParam))	//���� �޽����ΰ�?
	{
	case CBN_SELCHANGE:	//�޺��ڽ� �˸� : �޺��ڽ� ���� ��ϻ��ڿ��� ������ ����Ǿ���.
		if (ShapeUpdateMode)	//������尡 Ȱ��ȭ �Ǿ��ִ°�?
			view_UpdateShapeByEditControl(hwnd);	//Control -> cur_data -> c_veclist[idx]
		else
			view_GetControlData(hwnd);				//Control -> cur_data
		break;
	}
}

void OnListSave(HWND hwnd, WPARAM wParam)
{

	switch (HIWORD(wParam))
	{
	case LBN_SELCHANGE:	//����Ʈ�ڽ� �˸� : ����Ʈ �ڽ� ���� ������ ����� ���
		view_UpdateShapeByLBControl(hwnd);		//g_veclist[idx] -> cur_data -> Control
		ShapeUpdateMode = TRUE;					//�׸� ������� Ȱ��ȭ
		SetWindowText(hEditMode, TEXT("����"));	//Edit��Ʈ�� �ؽ�Ʈ ����
		break;
		//	case LBN_SETFOCUS:
		//	case LBN_KILLFOCUS:
		//	ShapeUpdateMode = FALSE;
		//	SetWindowText(hEditMode, TEXT("�Է�"));
		//	break;
	}
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT  pt = { LOWORD(lParam),HIWORD(lParam) };	//���� ���콺 ��ǥ�� pt�� ����
	if (PtInRect(&InvalidArea,pt))		//pt��ǥ�� ��ȿȭ���������ϰ�츸 ���� 
	{
		view_DrawShape(hwnd, &cur_data, wParam, lParam);	//Control ���� ���� �׸��� vector�� ������ WM_PAINT �߻�
		view_ControlListBoxPrint(hwnd);					//vector�� ����� ��ҵ��� ������ ����Ʈ�ڽ��� ���
	}
	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;	//Ŭ�� ������ �׸��µ� �ʿ��� ������ ����
	HDC hdc = BeginPaint(hwnd, &ps);	//DC�ڵ��� ȹ���� �׷����� ���������� PAINTSTRUCTŸ�Կ� ������

	//==============================
	view_PreviewColorPrint(hdc);		//RGB EDIT��Ʈ�� ���� ���� ���� �簢���� �׸�
	view_ShapePrint(hdc, &g_veclist);	//view�ҽ��� vector�� ����� ���׸� ���
	//==============================

	EndPaint(hwnd, &ps);				//DC�ڵ� �Ҹ�
	return 0;
}

LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT  pt = { LOWORD(lParam),HIWORD(lParam) };	//���� ���콺 ��ǥ�� pt�� ����
	if (IsContainPos(pt, InvalidArea))	//pt��ǥ�� ��ȿȭ���������ϰ�츸 ���� 
	{
		ShapeUpdateMode = FALSE;	//�׸� ������带 ��
		SetDlgItemInt(hwnd, IDC_EDITPOSX, pt.x, NULL);	//EDIT ��Ʈ�ѿ� ���� ���콺�� X,Y ��ǥ�� ����
		SetDlgItemInt(hwnd, IDC_EDITPOSY, pt.y, NULL);
	}

	if (ShapeUpdateMode)	//���� �׸� ������尡 �������� ���
	{
		SetWindowText(hEditMode, TEXT("����"));	//EDIT ��Ʈ�ѿ� ���� ���
	}
	else
		SetWindowText(hEditMode, TEXT("�Է�"));
	return 0;
}

LRESULT OnInitMenuPopUp(HWND hwnd, WPARAM wParam, LPARAM lParam)	//�޴��� ������ ��
{
	HMENU hMenu = (HMENU)wParam;	//�ӽ� �޴��ڵ� ������ ��Ӵٿ� �޴� �ڵ� ����

	if (cur_data.type == 1)	//cur_data�� 1�� ���
		submenu2 = ID_40003;
	else
		submenu2 = ID_40004;

	CheckMenuItem(hMenu, ID_40003, submenu2 == ID_40003 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40004, submenu2 == ID_40004 ? MF_CHECKED : MF_UNCHECKED);
	//������ �޴� �׸��� üũ���¸� ���� �Ǵ� ������ �����մϴ�.
	//�޴��ڵ�, �޴�ID, ���¼���


	TCHAR buf[50];
	GetWindowText(hEditTransparentMode, buf, sizeof(buf));
	//cur_data�� color�� ������ ���� ��� submenu3�� �⺻���ð��� ����
	if (GetRValue(cur_data.color) == 255 && GetGValue(cur_data.color) == 0 && GetBValue(cur_data.color) == 0)
		submenu3 = ID_40005;
	else if (GetRValue(cur_data.color) == 0 && GetGValue(cur_data.color) == 255 && GetBValue(cur_data.color) == 0)
		submenu3 = ID_40006;
	else if (GetRValue(cur_data.color) == 0 && GetGValue(cur_data.color) == 0 && GetBValue(cur_data.color) == 255)
		submenu3 = ID_40007;
	else if (!_tcscmp(buf, TEXT("TRUE")))
		submenu3 = ID_40008;
	else
		submenu3 = NULL;


	CheckMenuItem(hMenu, ID_40005, submenu3 == ID_40005 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40006, submenu3 == ID_40006 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40007, submenu3 == ID_40007 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40008, submenu3 == ID_40008 ? MF_CHECKED : MF_UNCHECKED);


	//cur_data�� penwidth�� ������ ���� ��� submenu4�� �⺻���ð��� ����
	if (cur_data.penwidth == 1)
		submenu4 = ID_40009;
	else if (cur_data.penwidth == 3)
		submenu4 = ID_40010;
	else if (cur_data.penwidth == 5)
		submenu4 = ID_40011;
	else
		submenu4 = NULL;

	CheckMenuItem(hMenu, ID_40009, submenu4 == ID_40009 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40010, submenu4 == ID_40010 ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_40011, submenu4 == ID_40011 ? MF_CHECKED : MF_UNCHECKED);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)	//��Ʈ�ѿ��� �޽��� �߻� ��
{
	switch (LOWORD(wParam))	//WM_COMMAND �߻��� wParam�� ���� 16��Ʈ�� ID�� ��ܿ´�.
	{
	case IDC_EDITPOSX:
	case IDC_EDITPOSY:
		OnEditPos(hwnd, wParam);
		break;
	case IDC_EDITCOLORR:
	case IDC_EDITCOLORG:
	case IDC_EDITCOLORB:
		OnEditColor(hwnd, wParam);
		break;
	case IDC_RADIORECTANGLE:
	case IDC_RADIOELLIPSE:
		OnRadioDrawType(hwnd, wParam);
		break;
	case IDC_COMBOPENWIDTH:
		OnComboPenWidth(hwnd, wParam);
		break;
	case IDC_LISTSAVE:
		OnListSave(hwnd, wParam);
		break;
	case ID_40001:	view_NewFile(hwnd);		break;
	case ID_40002:	SendMessage(hwnd, WM_CLOSE, 0, 0);		break;
	case ID_40003:	submenu2 = ID_40003; cur_data.type = 1; view_RefreshSetting(hwnd); break;
	case ID_40004:	submenu2 = ID_40004; cur_data.type = 2; view_RefreshSetting(hwnd); break;
	case ID_40005:	submenu3 = ID_40005; cur_data.color = RGB(255, 0, 0);
		cur_data.transparentFlag = FALSE; SetWindowText(hEditTransparentMode, TEXT("FALSE")); view_RefreshSetting(hwnd); break;
	case ID_40006:	submenu3 = ID_40006; cur_data.color = RGB(0, 255, 0);
		cur_data.transparentFlag = FALSE; SetWindowText(hEditTransparentMode, TEXT("FALSE")); view_RefreshSetting(hwnd); break;
	case ID_40007:	submenu3 = ID_40007; cur_data.color = RGB(0, 0, 255);
		cur_data.transparentFlag = FALSE; SetWindowText(hEditTransparentMode, TEXT("FALSE")); view_RefreshSetting(hwnd); break;
	case ID_40008:	submenu3 = ID_40008; cur_data.color = RGB(255, 255, 255);
		cur_data.transparentFlag = TRUE;
		SetWindowText(hEditTransparentMode, TEXT("TRUE"));
		view_RefreshSetting(hwnd); break;
	case ID_40009:	submenu4 = ID_40009; cur_data.penwidth = 1; view_RefreshSetting(hwnd); break;
	case ID_40010:	submenu4 = ID_40010; cur_data.penwidth = 3; view_RefreshSetting(hwnd); break;
	case ID_40011:	submenu4 = ID_40011; cur_data.penwidth = 5; view_RefreshSetting(hwnd); break;
	}

	return 0;
}

LRESULT OnTimer(HWND hwnd, WPARAM wParam, LPARAM lParam)
{

	view_SetTimeToWindowText(hwnd);	//ĸ�ǹٿ� ���� �ð� ���
	return 0;
}

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	view_SetTimer(hwnd);		//Ÿ�̸� ����
	view_ControlCreate(hwnd);	//��Ʈ�� ����
	DrawInit(&cur_data);		//cur_data �ʱ�ȭ
	view_ControlInit(hwnd);		//cur_data -> Control
	return 0;
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	KillTimer(hwnd, 1);	//ID�� 1�� Ÿ�̸� ����
	PostQuitMessage(0);	//WM_QUIT �޽���
	return 0;
}
