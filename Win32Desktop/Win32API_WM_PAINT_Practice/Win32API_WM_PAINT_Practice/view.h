//view.h
// 사용자정의 헤더를 h파일에 인클루드하면 중복문제가 다발한다. cpp에 인클루드해도 문제없다.
#include <vector>
#include <Windows.h>
using namespace std;

void view_ShapePrint(HDC hdc, vector<DRAWTYPE> *g_veclist);
void view_WindowTextPrint(HWND hwnd, int size,int x, int y);