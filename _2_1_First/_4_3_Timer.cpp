#if 1 // Total
/*-------------------------------------------------------------

------------------------------------------------------------*/

#if 1 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Timer");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st; // 추후 시간 API에서 집중해서 다룰 예정
	static TCHAR sTime[128];

	switch (iMessage)
	{
	case WM_CREATE: // 윈도우가 처음 시행될 때 발생
		SetTimer(hWnd, 1, 1000, NULL);
		/* ○ SetTimer
		    - (2) : 타이머 식별 번호. 만약 프로그램에서 3개의 프로그램을 사용한다면, 위 SetTimer를 세번 호출하고,
			        (2)에 각자 다른 번호 (Ex. 1, 2, 3) 을 할당하여 호출한다.
			- (3) : 단위 MS 마다 WM_TIMER를 큐에 넣는다. (EX. 1'000 이면 1초마다, 10'000 이면 10초마다)
			- (4) : WM_TIMER 마다 호출될 함수를 지정
		*/

		return 0;
	case WM_TIMER:
		GetLocalTime(&st); // 추후 시간 API에서 집중해서 다룰 예정
		wsprintf(sTime, TEXT("지금 시간은 %d:%d:%d 입니다"),
			st.wHour, st.wMinute, st.wSecond);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, sTime, lstrlen(sTime));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		/* ○ KillTimer
		    - (2) : 파괴할 타이머 식별번호 
		*/

		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // 주석


#if 1// 코드만

#endif // 코드만


#endif // Total