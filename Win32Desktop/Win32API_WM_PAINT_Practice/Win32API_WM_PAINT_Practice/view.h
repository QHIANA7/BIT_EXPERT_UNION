//view.h
// ��������� ����� h���Ͽ� ��Ŭ����ϸ� �ߺ������� �ٹ��Ѵ�. cpp�� ��Ŭ����ص� ��������.
#include <vector>
#include <Windows.h>
using namespace std;

void view_ShapePrint(HDC hdc, vector<DRAWTYPE> *g_veclist);
void view_WindowTextPrint(HWND hwnd, int size,int x, int y);