#include <iostream>
#include <windows.h>
using namespace std;
#define WM_MYMESSAGE WM_USER+100
#define WM_MYMESSAGE1 WM_USER+200

int main()
{
	HWND hwnd = FindWindow(0, TEXT("Hello"));

	cout << "ȣ�� ��" << endl;
	int result = SendMessage(hwnd, WM_MYMESSAGE, 10, 20);	//SendMessage(�ڵ�, �޽���, wparam, lparam) ���� ���
	cout << result << "�� ��ȯ�޾ҽ��ϴ�." << endl;
	int sum = PostMessage(hwnd, WM_MYMESSAGE1, result, result);	//PostMessage(�ڵ�, �޽���, wparam, lparam) ���� �ͺ��

	cout << "ȣ�� ��" << sum << endl;
	return 0;
}