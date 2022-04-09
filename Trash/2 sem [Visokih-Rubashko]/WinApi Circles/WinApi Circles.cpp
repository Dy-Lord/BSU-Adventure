// WinApi Circles.cpp : Определяет точку входа для приложения.
//
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_NON_CONFORMING_SWPRINTFS
#include "framework.h"
#include <cstring>
#include <windowsx.h>
#include "WinApi Circles.h"

#define MAX_LOADSTRING 100
#define IDM_INPUT                283
#define IDM_CALC                284
#define IDM_DRAW                285

static int OX, OY;
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HMENU hMenu, hMenuPopup;

enum Method { LEN = 1, SQR = 2, EMP = 0 };
Method MTH1 = EMP;
Method MTH2 = EMP;

int Radius = 0;
bool drawfoo = false;
float Size;

wchar_t input[] = L"Input";
wchar_t calc[] = L"Claculation";
wchar_t draw[] = L"Draw";
wchar_t exitt[] = L"Exit";
wchar_t file[] = L"File";
wchar_t ab[] = L"About";

wchar_t Square[] = L"Square ";
wchar_t Length[] = L"Length ";

wchar_t title[] = L"Vozovikov Nikita Aleksandrovich 10 Group Variant 4";

wchar_t str[10];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutError(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    _Input(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    _Calc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	hMenu = CreateMenu();
	hMenuPopup = CreateMenu();

	AppendMenu(hMenu, MF_POPUP, (UINT)hMenuPopup, file);
	AppendMenu(hMenu, MF_STRING, IDM_ABOUT, ab);

	AppendMenu(hMenuPopup, MF_STRING, IDM_INPUT, input);
	AppendMenu(hMenuPopup, MF_STRING, IDM_CALC, calc);
	AppendMenu(hMenuPopup, MF_STRING, IDM_DRAW, draw);

	AppendMenu(hMenuPopup, MF_SEPARATOR, 0, NULL);
	AppendMenu(hMenuPopup, MF_STRING, IDM_EXIT, exitt);

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPICIRCLES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPICIRCLES));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPICIRCLES));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, 800, 800, nullptr, hMenu, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		CreateDialog(hInst, input, hWnd, _Input);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_INPUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_INPUT), hWnd, _Input);
			break;

		case IDM_CALC:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_CALCUL), hWnd, _Calc);
			break;

		case IDM_DRAW:
			if (Radius * 2 < 740 && Radius > 0)
			{
				drawfoo = true;
				InvalidateRect(hWnd, 0, true);
			}
			else
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_Erorr), hWnd, AboutError);
			}
			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
		OX = LOWORD(lParam);
		OY = HIWORD(lParam);
	case WM_PAINT:
	{
		
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			if (drawfoo)
				Ellipse(hdc, OX / 2 - Radius, OY / 2 - Radius, OX / 2 + Radius, OY / 2 + Radius);
			EndPaint(hWnd, &ps);
		
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AboutError(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:

		if (Radius <= 0)
			SetDlgItemText(hDlg, IDC_STATIC, L"Null radius!");
		else
			SetDlgItemText(hDlg, IDC_STATIC, L"Maximum radius exceeded!");

		return (INT_PTR)TRUE;

	case WM_COMMAND:


		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK _Input(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{


	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;


	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), str, 10);
			Radius = _wtoi(str);
			
			if(IsDlgButtonChecked(hDlg, IDC_Square))
				MTH1 = SQR;
			else
				MTH1 = EMP;
			
			if (IsDlgButtonChecked(hDlg, IDC_Length))
				MTH2 = LEN;
			else
				MTH2 = EMP;

			
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK _Calc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;


	case WM_COMMAND:
			
			if (MTH1 == SQR)
			{
				
				Size = 3.14 * Radius * Radius;
				
				wchar_t buf[30];			
				swprintf(buf, L"%8.2f\0", Size);
				SetDlgItemText(hDlg, IDC_MethodLabel, Square);
				SetDlgItemText(hDlg, IDC_LABEL, buf);				
			}
			else
				SetDlgItemText(hDlg, IDC_MethodLabel, L"No Square");
			
			if (MTH2 == LEN)
			{
				Size = 2 * 3.14 * Radius;

				wchar_t buf[30];
				swprintf(buf, L"%8.2f\0", Size);

				SetDlgItemText(hDlg, IDC_MethodLabel2, Length);
				SetDlgItemText(hDlg, IDC_LABEL2, buf);
			}
			else
				SetDlgItemText(hDlg, IDC_MethodLabel2, L"No Length");

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}

	return (INT_PTR)FALSE;
}

