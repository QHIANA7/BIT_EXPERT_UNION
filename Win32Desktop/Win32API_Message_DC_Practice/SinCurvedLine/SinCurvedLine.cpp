#include <windows.h> 
#include <tchar.h>
#include <math.h>
#define NUM 1000
#define TWOPI (2 * 3.14159)
#define PI 3.14159

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	POINT apt[NUM];

	switch (msg)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		InvalidateRect(hwnd, 0, TRUE);
		return 0;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);
		MoveToEx(hdc, cxClient/2, 0, NULL);
		LineTo(hdc, cxClient/2, cyClient);
		for (i = 0; i < NUM; i++)
		{
			int n = 0;

			//양끝은 -π(-3.14), π(3.14)를 가리킨다.
			//NUM이 1000이고 창이 1280x720 크기 일 때
			//i가 0일 때 좌표는 (0, 360)
			//i가 250일 때 좌표는 (320, 720)
			//i가 500일 때 좌표는 (640, 360)
			//i가 750일 때 좌표는 (960, 0)
			//i가 1000일 때 좌표는 (1280, 360)

			//sin(x)의 결과는 항상 (-1 ~ 1)을 가진다 우리는 이를 (720 ~ 0)으로 매핑해야한다.
			//(sin(x) - 1)을 하면 (-2 ~ 0)을 가지고 여기에 -360을 곱해주면 (720 ~ 0)범위가된다.
			//(sin(x) - 1)* (-cyClient / 2)가 최종 y좌표가 된다.

			//이제 x에 들어갈 값을 구해야한다.

			//sin(x) x는 (-π ~ π) 의 범위를 갖는다. 이 스코프에서 i는 (0 ~ 1000)의 범위로 동작한다.
			//i/NUM을 하면 (0 ~ 1)이 된다. 이거 2배는 해주는게 편하겠다.
			//i/NUM*2를 하면 (0 ~ 2)범위가 된다. 이제 -1 하면되나?
			//(i/NUM*2-1)가되면 범위는 (-1 ~ 1)이 되고 π곱하면 되겠다.
			//(i/NUM*2-1) * π가 최종 x좌표 되시겠다.

			apt[i].x = i * cxClient / NUM; // 0 ~ 1000
			apt[i].y = (int)((sin(((double)i / NUM * 2 - 1) * PI) - 1) * (-cyClient / 2));
			//apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
			n = apt[i].x;
		}
		Polyline(hdc, apt, NUM);
	}
		return 0;
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	// 1. 윈도우 클래스 만들기 
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0; wc.style = 0;

	// 2. 등록(레지스트리에) 
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0, // WS_EX_TOPMOST 
		TEXT("first"), // 클래스 명 
		TEXT("Hello"), // 캡션바 내용 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// 초기 위치 
		0, 0, // 부모 윈도우 핸들, 메뉴 핸들 
		hInst, // WinMain의 1번째 파라미터 (exe 주소) 
		0); // 생성 인자 

	// 4. 윈도우 보여주기 
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} return 0;
}