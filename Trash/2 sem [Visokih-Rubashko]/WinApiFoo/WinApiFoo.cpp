// WinApiFoo.cpp : Определяет точку входа для приложения.
//
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_NON_CONFORMING_SWPRINTFS
#include "framework.h"
#include "WinApiFoo.h"
#include<string>
#include"cmath"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int Ox, Oy;
int ClientOx, ClientOy;
int LogOx, LogOy;
int leter_position;

enum FooType { one = 1, two = 2, empty = 0 };
FooType GLFOO = empty;
POINT Points[300];

HPEN RED = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
HPEN GREEN = CreatePen(PS_SOLID, 0.7, RGB(8, 1, 79));
HPEN Cells = CreatePen(PS_DOT, 0.3, RGB(254, 169, 0));
HPEN Black = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

std::wstring numbers[] = { L"-50",L"-45",L"-40",L"-35",L"-30", L"-25", L"-20", L"-15", L"-10", L"-5", L"0",L"5", L"10", L"15", L"20", L"25",L"30", L"35",L"40", L"45",L"50" };



// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DataError(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Foo(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIFOO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIFOO));

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

    return (int) msg.wParam;
}

void FOO1()
{

	for (int i = 0; i < 300; i++) 
	{
			Points[i].x = i * 600 / 100 - 600;
			Points[i].y = 100 * (log(Points[i].x / 100.0 * 2 + 2) + log(sin(Points[i].x / 100.0 * 2 + 2)));
	}
}

void FOO2()
{
	for (int i = 0; i < 300; i++) 
	{
		Points[i].x = i * 600 / 100 - 600;
		Points[i].y = 100 * (Points[i].x / 100.0 * cos(Points[i].x / 100.0));
	}
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIFOO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIFOO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  /* HWND hWnd = CreateWindow(szWindowClass, L"Function", WS_OVERLAPPEDWINDOW | WS_BORDER,
	   (GetSystemMetrics(SM_CXSCREEN) - 800) / 2, (GetSystemMetrics(SM_CYSCREEN) - 600) / 2, 800, 600, nullptr, nullptr, hInstance, nullptr);*/

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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case IDM_FOO:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_FOO), hWnd, Foo);
				InvalidateRect(hWnd, 0, true);
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
	case WM_LBUTTONDOWN:
	{
		WORD xPos, yPos, nSize;
		TCHAR szBuf[80];
		HDC hdc = GetDC(hWnd);
		
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, LogOx, LogOy, NULL);
		SetViewportExtEx(hdc, ClientOx, -ClientOy, NULL);
		SetViewportOrgEx(hdc, ClientOx / 2, ClientOy / 2, NULL);

		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);

		POINT T = { xPos,yPos };
		DPtoLP(hdc, (LPPOINT)& T, 1);

		if (GLFOO == one)
		{
			T.y = 100 * (log(T.x / 100.0 * 2 + 2) + log(sin(T.x / 100.0 * 2 + 2)));
		}
		else
			if (GLFOO == two)
			{
				T.y = 100 * (T.x / 100.0 * cos(T.x / 100.0));
			}

		if (T.y < -9000000)
		{
			T.y = 0;
			nSize = wsprintf(szBuf, TEXT("(-, -)mm"), T.x / 10, T.y / 10);
		}
		else
			nSize = wsprintf(szBuf, TEXT("(%d, %d)mm"), T.x / 10, T.y / 10);

		InvalidateRect(hWnd, 0, true);
		UpdateWindow(hWnd);

		TextOut(hdc, T.x, T.y, szBuf, nSize);
		
		ReleaseDC(hWnd, hdc);

		break;
	}
	case WM_CREATE:
		LogOx = 1200;
		LogOy = 1200;
		break;
	case WM_SIZE:
		ClientOx = LOWORD(lParam);
		ClientOy = HIWORD(lParam);
    case WM_PAINT:
        {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, LogOx, LogOy, NULL);
		SetViewportExtEx(hdc, ClientOx, -ClientOy, NULL);
		SetViewportOrgEx(hdc, ClientOx / 2, ClientOy / 2, NULL);
		
		SelectObject(hdc, Cells);
		for (int i = 0; i < 11; ++i)
		{
			MoveToEx(hdc, -500 + i * 100, 600, NULL);
			LineTo(hdc, -500 + i * 100, -600);

			MoveToEx(hdc, 600, -500 + i * 100, NULL);
			LineTo(hdc, -600 * 100, -500 + i * 100);
		}

		SelectObject(hdc, Black);
			MoveToEx(hdc, 0, -600, NULL);
			LineTo(hdc, 0, 600);
			MoveToEx(hdc, -600, 0, NULL);
			LineTo(hdc, 600, 0);
			MoveToEx(hdc, 600, 0, NULL);
			LineTo(hdc, 590, -3);
			MoveToEx(hdc, 600, 0, NULL);
			LineTo(hdc, 590, 3);
			TextOut(hdc, 576, -5, L"mm", 2);
			MoveToEx(hdc, 0, 600, NULL);
			LineTo(hdc, -3, 590);
			MoveToEx(hdc, 0, 600, NULL);
			LineTo(hdc, 3, 590);

			
			SelectObject(hdc, RED);
			if (GLFOO == one)
				FOO1();
			else
				if (GLFOO == two)
					FOO2();

			Polyline(hdc, Points, 300);
			SelectObject(hdc, GREEN);

			for (int i = 0; i < 22; ++i)
			{

				MoveToEx(hdc, -500 + i * 50, -3, NULL);
				LineTo(hdc, -500 + 50 * i, 3);
				SetTextAlign(hdc, TA_CENTER);
				TextOut(hdc, -500 + i * 50, -5, numbers[i].c_str(), numbers[i].size());

				MoveToEx(hdc, -3, -500 + i * 50, NULL);
				LineTo(hdc, 3, -500 + i * 50);
				SetTextAlign(hdc, TA_LEFT);
				if (i != 10)
					TextOut(hdc, 5, -490 + i * 50, numbers[i].c_str(), numbers[i].size());
			}

		EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DeleteObject(RED);
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

INT_PTR CALLBACK Foo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			GLFOO = empty;

			if (IsDlgButtonChecked(hDlg, IDC_FOO1))
				GLFOO = one;

			if (IsDlgButtonChecked(hDlg, IDC_FOO2))
				GLFOO = two;
			
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DataError(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_ErrorLabel, L"Отсутствуют данные!");
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
}