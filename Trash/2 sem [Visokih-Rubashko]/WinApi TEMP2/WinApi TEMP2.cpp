// WinApi TEMP2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WinApi TEMP2.h"

#define MAX_LOADSTRING 100

HPEN hRedPen, hGreenPen, hBluePen, hYellowPen;
HBRUSH hRedBrush, hGreenBrush, hBlueBrush, hYellowBrush;
static int Ox, Oy;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_WINAPITEMP2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPITEMP2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPITEMP2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_CAPTIONTEXT +20);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPITEMP2);
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
	case WM_CREATE:
		hRedPen = CreatePen(PS_DOT, 4, RGB(150, 0, 0));
		hGreenPen = CreatePen(PS_DOT, 1, RGB(0, 150, 0));
		hBluePen = CreatePen(PS_DASHDOT, 1, RGB(0, 0, 150));
		hYellowPen = CreatePen(PS_SOLID, 15, RGB(255, 255, 0));
		
		hRedBrush = CreateSolidBrush(RGB(255, 120, 120));
		hGreenBrush = CreateHatchBrush(HS_CROSS, RGB(120, 255, 120));
		hBlueBrush = CreateSolidBrush(RGB(120, 120, 255));		hYellowBrush = CreateHatchBrush(HS_HORIZONTAL, RGB(255, 255, 0));
	case WM_SIZE:
		Ox = LOWORD(lParam);
		Oy = HIWORD(lParam);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			if (hdc != NULL)
			{
				RECT Rect;
				GetClientRect(hWnd, &Rect);
				DPtoLP(hdc, (LPPOINT)& Rect, 2);

				MoveToEx(hdc, Ox / 2, 0, nullptr);
				LineTo(hdc, Ox / 2, Oy);

				MoveToEx(hdc, 0, Oy / 2, nullptr);
				LineTo(hdc, Ox, Oy / 2);

				
				SetTextColor(hdc, RGB(0, 0, 200));
				wchar_t Elips[] = L"Эллипс";
				wchar_t Recct[] = L"Прямоугольник";
				wchar_t Sector[] = L"Сектор";
				wchar_t Romb[] = L"Ромб";

				TextOut(hdc, Ox/4-25, Oy/2-25, Elips, _tcslen(Elips));
				TextOut(hdc, Ox / 2 + Ox / 3, Oy / 2 - 20, Romb, _tcslen(Romb));
				TextOut(hdc, Ox / 4 - Ox / 16, Oy - 25, Sector, _tcslen(Sector));
				TextOut(hdc, Ox - 380, Oy - 20 , Recct, _tcslen(Recct));

				SelectObject(hdc, hBluePen);
				SelectObject(hdc, hRedBrush);
				Ellipse(hdc, Ox / 10, Oy / 10, Ox / 2 - 30, Oy / 2 - Ox / 8);

				SelectObject(hdc, hYellowPen);
				SelectObject(hdc, hGreenBrush);
				Rectangle(hdc, Ox/2+20, Oy/2+20, Ox-30 , Oy-30 );

				SelectObject(hdc, hGreenPen);
				SelectObject(hdc, hBlueBrush);
				POINT pt[] = { {Ox / 2 + Ox / 4,10}, {Ox - Ox / 8,Oy / 4}, { Ox / 2 + Ox / 4,Oy / 2 - 20 },{Ox / 2 + Ox / 8,Oy / 4} };
				Polygon(hdc, pt, 4);

				SelectObject(hdc, hRedPen);
				SelectObject(hdc, hYellowBrush);
				Pie(hdc, Ox / 8 , Oy / 2 + 20, Ox/2 - 30, Oy - 30, Ox/8, Oy / 2 + Oy / 8, Ox/2-Ox/4, Oy-Oy/4);
			}
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
		DeleteObject(hRedBrush);
		DeleteObject(hRedPen);

		DeleteObject(hBlueBrush);
		DeleteObject(hBluePen);

		DeleteObject(hGreenBrush);
		DeleteObject(hGreenPen);

		DeleteObject(hYellowBrush);
		DeleteObject(hYellowPen);
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
