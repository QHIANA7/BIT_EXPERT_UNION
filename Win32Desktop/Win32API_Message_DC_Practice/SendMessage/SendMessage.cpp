#include <iostream>
#include <windows.h>
using namespace std;
#define WM_MYMESSAGE WM_USER+100
#define WM_MYMESSAGE1 WM_USER+200

int main()
{
	HWND hwnd = FindWindow(0, TEXT("Hello"));

	cout << "호출 전" << endl;
	int result = SendMessage(hwnd, WM_MYMESSAGE, 10, 20);	//SendMessage(핸들, 메시지, wparam, lparam) 이후 블록
	cout << result << "를 반환받았습니다." << endl;
	int sum = PostMessage(hwnd, WM_MYMESSAGE1, result, result);	//PostMessage(핸들, 메시지, wparam, lparam) 이후 넌블록

	cout << "호출 후" << sum << endl;
	return 0;
}