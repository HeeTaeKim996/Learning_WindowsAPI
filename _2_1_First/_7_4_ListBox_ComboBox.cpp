#if 0 // Total
/*----------------------------------------------------------------------------------------------------
   리스트박스와 콤보박스에 관한 내용입니다.
   리스트 박스는 C#의 리스트와 유사하며,
   콤보박스는 Edit 과 리스트박스를 합친 기능으로,
   웹페이지에서 자주 보는 형태이니 쓰임새가 많을 것 같습니다
----------------------------------------------------------------------------------------------------*/


#if 0 // 주석
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_ListBox_ComoboBox");

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
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
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

/*---------------------------------------------------------------------------------------------------
	□ 리스트박스
	○ 개요
	 - 마찬가지로 윈도우의 일종
	 - C#의 List와 유사
	   ( LB_ADDSTRING 으로 데이터를 추가, LB_DELETESTRING 으로 삭제, LB_GETCURSEL 로 현재 활성화 인덱스,
		 LB_GETTEXT로 할당한 인덱스의 텍스트를 불러오는 등..  )

	○ LBS (ENUM) - 리스트 박스를 생성할 때 사용하는 이넘
	 - LBS_MULTIPLESEL	: 여러 개의 항목을 선택할 수 있음. ( 디펄트로는 하나만 선택 가능함 )
	 - LBS_NOTIFY		: 사용자가 목록 중 하나를 선택했을 때, 부모 윈도우로 통보 메세지 (거의 필수로 사용)
	 - LBS_SORT			: 추가된 항목들을 자동 정렬
	 - LBS_OWNERDRAW	: 문자열이 아닌 비트맵이나 그림을 넣을 수 있다
	 - LBS_STANDARD		: LBS_NOTIFY | LBS_SORT | WS_BORDER

	  => LBS_NOTIFY 는 거의 필수. LOBS_SORT 나 LBS_MULTIPLE 을 간혹 사용

	○ LB (ENUM) - 주로 부모 윈도우 -> 리스트박스 윈도우 로 SendMessage 때 사용하는 ENUM
	 - LB_ADDSTRING		: 리스트 박스에 항목을 추가. LPARAM에 TCHAR [] 를 LPARAM으로 형변환하여 넘겨줌
	 - LB_DELETESTRING	: 항목을 삭제. WPARAM에 삭제할 항목 번호를 넘겨주며, 남은 항목수를 리턴받음
	 - LB_GETCURSEL		: 현재 선택된 항목의 번호 를 리턴받는다
	 - LB_GETTEXT		: 항목번호를 넘겨주면, 해당 인덱스의 항목을 리턴받는다.
						  WPARAM 에는 항목번호. LPARAM에는 항목 데이터를 담기 위한 TCHAR[] 를 LPARAM 형변환하여 넘겨줌
	 - LB_GETCOUNT		: 항목의 개수를 조사
	 - LB_SETCURSEL		: WPARAM 에 인덱스를 넘겨준다. 리스트 박스 윈도우는 해당 인덱스를 '선택' 한다

	○ LBN (ENUM) - 리스트박스 윈도우 -> 부모 윈도우로 보내는 메세지의 식별 이넘. HIWORD(WPARAM) 에서 식별
	 - LBN_DBLCLK		: 리스트 박스를 더블클릭하였음을 통보
	 - LBN_ERRSPACE		: 메모리 부족 통보
	 - LBN_KILLFOCUS	: 키보드 포커스를 잃었다
						 ( 리스트박스를 Tab 키로 선택할 변경할 수 있는 상태를 키보드 포커스 상태라 한다.
						   주로 리스트박스를 마우스 클릭 후 활성화)
	 - LBN_SELCANCEL	: 사용자가 선택을 췩소했다
	 - LBN_SELCHANGE	: 사용자가 선택을 변경했다
	 - LBN_SETFOCUS		: 키보드 포커르르 얻었다


	 □ 콤보박스
	 ○ 개요
	  - 앞선 Edit과, 리스트박스를 합친 형태
	  - Edit처럼, 박스를 클릭하면 문자열 입력 및 Edit 처럼 처리 가능
	  - 박스 옆의 아래 화살표 클릭시, 리스트박스처럼 미리 준비한 요소들이 나열되고, 해당 요소를 선택 가능
	  - ENUM 들 또한, 리스트 박스와 매우 유사. LBS -> CBS, LB -> CB, LBN -> CBN 으로, 이후 내용은
		리스트 박스와 매우 유사함

	 ○ CBS (일부)
	  - CBS_SIMPLE			: 에디트와 리스트 박스를 가지되, 리스트 박스가 항상 펼쳐져 있다
	  - CBS_DROPDOWN		: 에디트와 리스트 박스를 가진다
	  - CBS_DROPDOWNLIST	: 리스트박스만 가지며, 에디트에 항목을 입력할 수 없다 (이럼 리스트박스 쓰지 왜쓸까..)
---------------------------------------------------------------------------------------------------*/

#define ID_LISTBOX 100
HWND hList;

#define ID_COMBOBOX 101
HWND hCombo;

const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_CREATE:
	{ // 리스트박스
		hList = CreateWindow(TEXT("listBox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			10, 10, 100, 200,
			hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
	}

	{ // 콤보 박스
		hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			600, 10, 100, 200,
			hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
		for (int i = 0; i < 5; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
	}


	return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX: // 리스트박스
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{

				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
			break;
			}

		case ID_COMBOBOX: // 콤보 박스
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd, str);

				break;

			case CBN_KILLFOCUS:
				GetWindowText(hCombo, str, 128);

				if (SendMessage(hCombo, CB_FINDSTRINGEXACT, -1, (LPARAM)str) == CB_ERR)
					// ※ (3)항 n + 1 인덱스부터 조회. -1일시, 인덱스 0부터 조회니 전체 조회. 
					// ※ CB_ERR == -1. CB에서 Find등 실패시, -1 반환
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)str);
				}


				break;
			}


			break;
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}





#endif // 주석


#if 1 // 코드만
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Learning_ListBox_ComoboBox");

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
	WndClass.hIcon = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, g_hInst, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


#define ID_LISTBOX 100
HWND hList;

#define ID_COMBOBOX 101
HWND hCombo;

const TCHAR* Items[] = { TEXT("Apple"), TEXT("Orange"), TEXT("Melon"), TEXT("Grape"), TEXT("Strawberry") };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_CREATE:
	{ 
		{ // ListBox
			hList = CreateWindow(TEXT("listBox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY,
				10, 10, 100, 200,
				hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
			for (int i = 0; i < 5; i++)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
			}
		}

		{ // ComboBox
			hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
				600, 10, 100, 200,
				hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
			for (int i = 0; i < 5; i++)
			{
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
			}
		}

		return 0;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX: // ListBox
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}

			}
			break;
		}

		case ID_COMBOBOX: // ComboBox
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);

				break;
			}
				

			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd, str);
				
				break;

			case CBN_KILLFOCUS:
				GetWindowText(hCombo, str, 128);

				if (SendMessage(hCombo, CB_FINDSTRINGEXACT, -1, (LPARAM)str) == CB_ERR)
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)str);
				}

				break;
			}

			break;
		}

		return 0;



	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}



#endif // 코드만


#endif // Total