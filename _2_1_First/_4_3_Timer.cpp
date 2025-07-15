#if 1 // Total
/*-------------------------------------------------------------

------------------------------------------------------------*/

#if 1 // �ּ�
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
	SYSTEMTIME st; // ���� �ð� API���� �����ؼ� �ٷ� ����
	static TCHAR sTime[128];

	switch (iMessage)
	{
	case WM_CREATE: // �����찡 ó�� ����� �� �߻�
		SetTimer(hWnd, 1, 1000, NULL);
		/* �� SetTimer
		    - (2) : Ÿ�̸� �ĺ� ��ȣ. ���� ���α׷����� 3���� ���α׷��� ����Ѵٸ�, �� SetTimer�� ���� ȣ���ϰ�,
			        (2)�� ���� �ٸ� ��ȣ (Ex. 1, 2, 3) �� �Ҵ��Ͽ� ȣ���Ѵ�.
			- (3) : ���� MS ���� WM_TIMER�� ť�� �ִ´�. (EX. 1'000 �̸� 1�ʸ���, 10'000 �̸� 10�ʸ���)
			- (4) : WM_TIMER ���� ȣ��� �Լ��� ����
		*/

		return 0;
	case WM_TIMER:
		GetLocalTime(&st); // ���� �ð� API���� �����ؼ� �ٷ� ����
		wsprintf(sTime, TEXT("���� �ð��� %d:%d:%d �Դϴ�"),
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
		/* �� KillTimer
		    - (2) : �ı��� Ÿ�̸� �ĺ���ȣ 
		*/

		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

#endif // �ּ�


#if 1// �ڵ常

#endif // �ڵ常


#endif // Total