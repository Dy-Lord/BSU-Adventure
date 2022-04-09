// WinApi TEMP4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WinApi TEMP4.h"
#include<ctime>
static int Ox, Oy;
HBRUSH hGreenBrush, hBlueBrush, hYellowBrush, hWhiteBrush;

#define MAX_LOADSTRING 100

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
    LoadStringW(hInstance, IDC_WINAPITEMP4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPITEMP4));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPITEMP4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPITEMP4);
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
		hGreenBrush = CreateSolidBrush(RGB(204, 255, 255));
		hBlueBrush = CreateSolidBrush(RGB(255, 204, 204));		hYellowBrush = CreateSolidBrush(RGB(255, 255, 204));
		hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
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

			int g = 0;
			int a, b, c, d;
			

			HBRUSH Colors[3];

			Colors[0] = hGreenBrush;
			Colors[1] = hBlueBrush;
			Colors[2] = hYellowBrush;
			
			
			for (int i = 1; i < 7; i++)
			{
				
				if (i % 2 == 0)
					g = 0;
				else
					if (i % 3 == 0)
						g = 1;
					else
						g = 2;

				SelectObject(hdc, Colors[g]);
				Rectangle(hdc, a = Ox / 20, b = Oy * i / 7, c = Ox / 3, d = Oy * i / 7+Oy/7);

				
				RECT now;
				now.left = a;
				now.top = b;
				now.right = c;
				now.bottom = d;
				
				if (g == 0)
				{
					SetBkColor(hdc, RGB(204, 255, 255));
					DrawText(hdc, L"Практика", 8, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Ауд.608", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				if (g == 1)
				{
					SetBkColor(hdc, RGB(255, 204, 204));
					DrawText(hdc, L"Физкультура", 11, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Физ-зал", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				
				if (g == 2)
				{
					SetBkColor(hdc, RGB(255, 255, 204));
					DrawText(hdc, L"Лекция", 6, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Ауд.501", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			
			for (int i = 1; i < 7; i++)
			{
				
				if (i % 3 == 0)
					g = 0;
				else
					if (i % 2 == 0)
						g = 1;
					else
						g = 2;


				SelectObject(hdc, Colors[g]);
				Rectangle(hdc, a = Ox / 3, b = Oy * i / 7, c = Ox * 2 / 3, d = Oy * i / 7 + Oy / 7);

				RECT now;
				now.left = a;
				now.top = b;
				now.right = c;
				now.bottom = d;

				if (g == 0)
				{
					SetBkColor(hdc, RGB(204, 255, 255));
					DrawText(hdc, L"Практика", 8, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Ауд.608", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				if (g == 1)
				{
					SetBkColor(hdc, RGB(255, 204, 204));
					DrawText(hdc, L"Физкультура", 11, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Физ-зал", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				if (g == 2)
				{
					SetBkColor(hdc, RGB(255, 255, 204));
					DrawText(hdc, L"Лекция", 6, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Ауд.501", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			
			for (int i = 1; i < 7; i++)
			{
				
				if (i % 3 == 0)
					g = 1;
				else
					if (i % 2 == 0)
						g = 2;
					else
						g = 0;


				SelectObject(hdc, Colors[g]);
				Rectangle(hdc, a = Ox * 2 / 3, b = Oy * i / 7, c = Ox, d = Oy * i / 7 + Oy / 7);

				RECT now;
				now.left = a;
				now.top = b;
				now.right = c;
				now.bottom = d;

				if (g == 0)
				{
					SetBkColor(hdc, RGB(204, 255, 255));
					DrawText(hdc, L"Практика", 8, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Ауд.608", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				if (g == 1)
				{
					SetBkColor(hdc, RGB(255, 204, 204));
					DrawText(hdc, L"Физкультура", 11, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Физ-зал", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				if (g == 2)
				{
					SetBkColor(hdc, RGB(255, 255, 204));
					DrawText(hdc, L"Лекция", 6, &now, DT_CENTER | DT_SINGLELINE);
					DrawText(hdc, L"Ауд.501", 7, &now, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}



			SetBkColor(hdc, RGB(255,255,255));

			wchar_t Vert[] = L"Vert";
			HFONT VertFont = CreateFont(15, 5, 900, 10, 100, 100, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, Vert);			SelectObject(hdc, VertFont);

			for (int i = 1; i < 7; i++)
			{
				SelectObject(hdc, hWhiteBrush);
				Rectangle(hdc, a = 0, b = Oy * i / 7, c = Ox / 20, d = Oy * i / 7 + Oy / 7);
				RECT now;
				now.left = a;
				now.top = b;
				now.right = c;
				now.bottom = d;

				if(i==1)
				DrawText(hdc, L"Понед.", 7, &now, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE );
				if (i == 2)
					DrawText(hdc, L"Вторник", 7, &now, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
				if (i == 3)
					DrawText(hdc, L"Среда", 7, &now, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
				if (i == 4)
					DrawText(hdc, L"Четверг", 7, &now, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
				if (i == 5)
					DrawText(hdc, L"Пятница", 7, &now, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
				if (i == 6)
					DrawText(hdc, L"Суббота", 7, &now, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);

			}

			DeleteObject(VertFont);

			wchar_t Arial[] = L"Arial";
			HFONT newFont = CreateFont(30, 30, 0, 100, 100, 100, 100, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, Arial);			SelectObject(hdc, newFont);
			wchar_t Title[] = L"РАСПИСАНИЕ ЗАНЯТИЙ НА НЕДЕЛЮ";
			TextOut(hdc, Ox / 10, Oy / 20, Title, _tcslen(Title));
			DeleteObject(newFont);


		}
		EndPaint(hWnd, &ps);
	}
	break;
    case WM_DESTROY:
		DeleteObject(hBlueBrush);
		DeleteObject(hGreenBrush);
		DeleteObject(hYellowBrush);
		DeleteObject(hWhiteBrush);
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
