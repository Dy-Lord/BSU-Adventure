// WinApiBUS.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include<iostream>;
#include "WinApiBUS.h"

#define MAX_LOADSTRING 100
static int OX, OY;

HDC hdcCompatible;
float Shift = 3;
const int BusWidth = 1526;
float Pos;
//float AnimPos;
float AnimShift = 0;
bool On = true;
bool AnimOn = false;
bool AnimFinal = true;

HBRUSH backgr = CreateSolidBrush(RGB(122, 118, 110));
HPEN defoltPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));


void BusPaint(HDC hdc,int Pos,float len)
{
	int Ox = 1378;
	int Oy = 730;
	HPEN ne = CreatePen(PS_NULL, 0, RGB(0, 0, 0));

	//Main
	SelectObject(hdc, defoltPen);
	HPEN wP= CreatePen(PS_SOLID, 8, RGB(255, 221, 0));
	HBRUSH one = CreateSolidBrush(RGB(255, 198, 13));
	SelectObject(hdc, one);
	SelectObject(hdc, wP);
	RoundRect(hdc, Ox / 8 + Pos, Oy / 8, Ox / 2 + Pos, Oy / 3, 20, 20);
	SelectObject(hdc, defoltPen);

	//Windows
	HBRUSH two = CreateSolidBrush(RGB(167, 246, 252));
	SelectObject(hdc, two);
	for (int i = 0; i < 2; i++)
		RoundRect(hdc, Ox / 7 + (i * 120) + Pos, Oy / 7, Ox / 5 + (i * 120) + Pos, Oy / 4, 10, 10);
	HBRUSH twoDown = CreateSolidBrush(RGB(151, 224, 230));
	SelectObject(hdc, twoDown);
	SelectObject(hdc, ne);
	for (int i = 0; i < 2; i++)
		RoundRect(hdc, Ox / 6.2 + (i * 120) + Pos, Oy / 6.2, Ox / 5.3 + (i * 120) + Pos, Oy / 4.3, 10, 10);
	SelectObject(hdc, defoltPen);
	

	//MainWindow
	HBRUSH one1 = CreateSolidBrush(RGB(181, 226, 230));
	SelectObject(hdc, one1);
	RoundRect(hdc, Ox / 2.5 + Pos, Oy / 8, Ox / 2 + Pos, Oy / 4, 20, 20);
	RoundRect(hdc, Ox / 2.3 + Pos, Oy / 8, Ox / 2 + Pos, Oy / 3.5, 20, 20);
	SelectObject(hdc, ne);
	RoundRect(hdc, Ox / 2.4 + Pos, Oy / 7.9, Ox / 2.1 + Pos, Oy / 4, 0, 0);
	DeleteObject(one1);

	HBRUSH one2 = CreateSolidBrush(RGB(161, 200, 204));
	SelectObject(hdc, one2);
	RoundRect(hdc, Ox / 2.4 + Pos, Oy / 7, Ox / 2.05 + Pos, Oy / 4.5, 20, 20);
	RoundRect(hdc, Ox / 2.2 + Pos, Oy / 6, Ox / 2.05 + Pos, Oy / 4.01, 20, 20);
	SelectObject(hdc, ne);
	DeleteObject(one2);
	
	HBRUSH rl = CreateSolidBrush(RGB(235, 145, 12));
	HBRUSH bl = CreateSolidBrush(RGB(66, 27, 3));
	SelectObject(hdc, bl);
	RoundRect(hdc, Ox / 7 + 240 + Pos, Oy / 7, Ox / 5 + 240 + Pos+1.5, Oy / 3, 10, 10);
	if (len == 0)
	{
		//Door
		SelectObject(hdc, defoltPen);
		SelectObject(hdc, rl);
		RoundRect(hdc, Ox / 7 + 240 + Pos, Oy / 7, Ox / 5 + 240 - (Ox / 5 - Ox / 7) / 2 + Pos, Oy / 3, 10, 10);
		RoundRect(hdc, Ox / 5 + 240 - (Ox / 5 - Ox / 7) / 2 + Pos, Oy / 7, Ox / 5 + 240 + Pos, Oy / 3, 10, 10);
		DeleteObject(rl);

		//DoorWndows
		SelectObject(hdc, two);
		RoundRect(hdc, Ox / 7 + 250 + Pos, Oy / 7 + 20, Ox / 5 + 190 + Pos, Oy / 3 - 20, 30, 10);
		RoundRect(hdc, Ox / 7 + 290 + Pos, Oy / 7 + 20, Ox / 5 + 230 + Pos, Oy / 3 - 20, 30, 10);
	}
	
	
	SelectObject(hdc, defoltPen);
	//Wheels
	HBRUSH gr = CreateSolidBrush(RGB(81, 100, 102));
	SelectObject(hdc, gr);
	Ellipse(hdc, Ox / 2.5-350 + Pos, Oy / 3.5, Ox / 2.2-350 + Pos, Oy / 2.6);
	Ellipse(hdc, Ox / 2.5 - 220 + Pos, Oy / 3.5, Ox / 2.2 - 220 + Pos, Oy / 2.6);
	Ellipse(hdc, Ox / 2.5 + Pos, Oy / 3.5, Ox / 2.2 + Pos, Oy / 2.6);


	HBRUSH grDown = CreateSolidBrush(RGB(60, 75, 77));
	SelectObject(hdc, grDown);
	SelectObject(hdc, ne);
	POINT pt1[] = { {Ox / 2.3 + Pos,Oy / 2.7}, {Ox / 2.25 + Pos,Oy / 2.8}, { Ox / 2.32 + Pos,Oy / 3 } };
	Polygon(hdc, pt1, 3);
	POINT pt2[] = { {Ox / 2.3-15 + Pos,Oy / 2.7}, {Ox / 2.25-45 + Pos,Oy / 2.8}, { Ox / 2.32-5 + Pos,Oy / 3 } };
	Polygon(hdc, pt2, 3);
	POINT pt3[] = { {Ox / 2.25 - 50 + Pos,Oy / 2.87}, {Ox / 2.25 - 50 + Pos,Oy / 2.8-40}, { Ox / 2.32 - 5 + Pos,Oy / 3 } };
	Polygon(hdc, pt3, 3);
	POINT pt4[] = { {Ox / 2.25 + 7 + Pos,Oy / 2.87}, {Ox / 2.25 + 8 + Pos,Oy / 2.8 - 40}, { Ox / 2.32 - 5 + Pos,Oy / 3 } };
	Polygon(hdc, pt4, 3);

	POINT pt11[] = { {Ox / 2.3 - 350 + Pos,Oy / 2.7}, {Ox / 2.25 - 350 + Pos,Oy / 2.8}, { Ox / 2.32 - 350 + Pos,Oy / 3 } };
	Polygon(hdc, pt11, 3);
	POINT pt22[] = { {Ox / 2.3 - 15 - 350 + Pos,Oy / 2.7}, {Ox / 2.25 - 45 - 350 + Pos,Oy / 2.8}, { Ox / 2.32 - 5 - 350 + Pos,Oy / 3 } };
	Polygon(hdc, pt22, 3);
	POINT pt33[] = { {Ox / 2.25 - 50 - 350 + Pos,Oy / 2.87}, {Ox / 2.25 - 50 - 350 + Pos,Oy / 2.8 - 40}, { Ox / 2.32 - 5 - 350 + Pos,Oy / 3 } };
	Polygon(hdc, pt33, 3);
	POINT pt44[] = { {Ox / 2.25 + 7 - 350 + Pos,Oy / 2.87}, {Ox / 2.25 + 8 - 350 + Pos,Oy / 2.8 - 40}, { Ox / 2.32 - 5 - 350 + Pos,Oy / 3 } };
	Polygon(hdc, pt44, 3);

	POINT pt111[] = { {Ox / 2.3 - 220 + Pos,Oy / 2.7}, {Ox / 2.25 - 220 + Pos,Oy / 2.8}, { Ox / 2.32 - 220 + Pos,Oy / 3 } };
	Polygon(hdc, pt111, 3);
	POINT pt222[] = { {Ox / 2.3 - 15 - 220 + Pos,Oy / 2.7}, {Ox / 2.25 - 45 - 220 + Pos,Oy / 2.8}, { Ox / 2.32 - 5 - 220 + Pos,Oy / 3 } };
	Polygon(hdc, pt222, 3);
	POINT pt333[] = { {Ox / 2.25 - 50 - 220 + Pos,Oy / 2.87}, {Ox / 2.25 - 50 - 220 + Pos,Oy / 2.8 - 40}, { Ox / 2.32 - 5 - 220 + Pos,Oy / 3 } };
	Polygon(hdc, pt333, 3);
	POINT pt444[] = { {Ox / 2.25 + 7 - 220 + Pos,Oy / 2.87}, {Ox / 2.25 + 8 - 220 + Pos,Oy / 2.8 - 40}, { Ox / 2.32 - 5 - 220 + Pos,Oy / 3 } };
	Polygon(hdc, pt444, 3);
	SelectObject(hdc, defoltPen);


	HBRUSH oneUP = CreateSolidBrush(RGB(255, 200, 50));
	SelectObject(hdc, wP);
	SelectObject(hdc, oneUP);
	Pie(hdc, Ox / 2.5-350 + Pos, Oy / 3.5, Ox / 2.2-350 + Pos, Oy / 2.6, Ox / 2.2-350 + Pos, Oy / 3.05, Ox / 2.5-350 + Pos, Oy / 3.05);
	Pie(hdc, Ox / 2.5 - 220 + Pos, Oy / 3.5, Ox / 2.2 - 220 + Pos, Oy / 2.6, Ox / 2.2 - 220 + Pos, Oy / 3.05, Ox / 2.5 - 220 + Pos, Oy / 3.05);
	Pie(hdc, Ox / 2.5 + Pos, Oy / 3.5, Ox / 2.2 + Pos, Oy / 2.6, Ox / 2.2 + Pos, Oy / 3.05, Ox / 2.5 + Pos, Oy / 3.05);
	DeleteObject(gr);
	DeleteObject(grDown);
	
	//Light
	HBRUSH yLL = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 240, 0));
	SelectObject(hdc, yLL);
	SelectObject(hdc, defoltPen);
	Ellipse(hdc, Ox / 2 - 10 + Pos, Oy / 3.5 - 10, Ox / 2+10 + Pos, Oy / 3.5+10);

	//Strings
	SelectObject(hdc, defoltPen);

	wchar_t V[] = L"  V------НАЧАТЬ ДВИЖЕНИЕ";
	wchar_t N[] = L"  N------ПРЕКРАТИТЬ ДВИЖЕНИЕ";
	wchar_t B[] = L"  B------ОТКРЫТЬ/ЗАКРЫТЬ ДВЕРИ";
	wchar_t L[] = L"  L------ВКЛЮЧИТЬ/ВЫКЛЮЧИТЬ ФАРЫ";

		
	TextOut(hdc, 40, Oy / 2, V, _tcslen(V));
	TextOut(hdc, 40, Oy / 2+20, N, _tcslen(N));
	TextOut(hdc, 40, Oy / 2+40, B, _tcslen(B));
	TextOut(hdc, 40, Oy / 2+60, L, _tcslen(L));

	DeleteObject(yLL);
	DeleteObject(one);
	DeleteObject(oneUP);
	DeleteObject(wP);
	DeleteObject(bl);
	DeleteObject(two);
	DeleteObject(twoDown);
	DeleteObject(ne);
}

void Light(HDC hdc, int Pos,bool on)
{
	int Ox = 1378;
	int Oy = 730;

	//Road
	HBRUSH p = CreateHatchBrush(HS_BDIAGONAL, RGB(122, 118, 110));
	SelectObject(hdc, p);
	Rectangle(hdc, 0, Oy / 2.6 - 100, OX, Oy / 2.6 + 50);
	DeleteObject(p);

	if (on)
	{
		HPEN ne = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
		SelectObject(hdc, ne);
		for (int i = 10; i > 1; i--)
		{
			HBRUSH yL = CreateSolidBrush(RGB(255, 240, i * 15));
			SelectObject(hdc, yL);
			Pie(hdc, Ox / 2 - 250 + Pos, Oy / 3.5 - 120 - i * 20, Ox / 2 + 120 + i * 20 + Pos, Oy / 3.5 + 120, Ox / 2 + 100 + i * 20 + Pos, Oy / 3.5 + 100 + i * 10, Ox / 2 + 100 + i * 20 + Pos, Oy / 3.5 - 100 - i * 10);
			DeleteObject(yL);
		}
		DeleteObject(ne);
		SelectObject(hdc, defoltPen);
	}
}

bool BusAnimation(HDC hdc, int Pos,int AnimPoz,bool rev)
{
	int Ox = 1378;
	int Oy = 730;
	int Check = Ox / 5 + 240 + Pos;
	HBRUSH two = CreateSolidBrush(RGB(167, 246, 252));

	//Door
	SelectObject(hdc, defoltPen);
	HBRUSH rl = CreateSolidBrush(RGB(235, 145, 12));
	SelectObject(hdc, rl);
	
	RoundRect(hdc, Ox / 7 + 240 + Pos - AnimPoz, Oy / 7, Ox / 5 + 240 - (Ox / 5 - Ox / 7) / 2 + Pos - AnimPoz, Oy / 3, 10, 10);
	RoundRect(hdc, Ox / 5 + 240 - (Ox / 5 - Ox / 7) / 2 + Pos + AnimPoz, Oy / 7, Ox / 5 + 240 + Pos + AnimPoz, Oy / 3, 10, 10);

	DeleteObject(rl);

	//DoorWndows
	HBRUSH bl = CreateSolidBrush(RGB(66, 27, 3));
	SelectObject(hdc, bl);
	//RoundRect(hdc, Ox / 7 + 275 + Pos, Oy / 7, Ox / 5 + 205 + Pos, Oy / 3, 1, 1);
	SelectObject(hdc, two);
	RoundRect(hdc, Ox / 7 + 250 + Pos - AnimPoz, Oy / 7 + 20, Ox / 5 + 190 + Pos - AnimPoz, Oy / 3 - 20, 30, 10);
	RoundRect(hdc, Ox / 7 + 290 + Pos + AnimPoz, Oy / 7 + 20, Ox / 5 + 230 + Pos + AnimPoz, Oy / 3 - 20, 30, 10);

	SelectObject(hdc, defoltPen);
	DeleteObject(two);

	if (rev)
	{
		if (Ox / 5 + 240 - (Ox / 5 - Ox / 7) / 2 + Pos + AnimPoz <= Check)
			return true;
		else
			return false;
	}
	else
		if (Ox / 5 + 240 - (Ox / 5 - Ox / 7) / 2 + Pos + AnimPoz >= Check)
			return true;
		else
			return false;
}
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
    LoadStringW(hInstance, IDC_WINAPIBUS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIBUS));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIBUS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNSHADOW +1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIBUS);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
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
	static HDC hdcScreen;
	static HBITMAP hbmScreen;
	RECT rect;

	unsigned int key=0;

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
	case WM_KEYDOWN:
		key = wParam;
	case WM_CHAR:
		switch (key)
		{
		case 86:
			
			Shift = 3;
			break;

		case 78:    

			Shift = 0;
			break;
		case 76:
			if (On)
				On = false;
			else
				On = true;
			break;
		case 66:
			if (!AnimOn)
				AnimOn = true;
			else
				AnimOn = false;
			break;
		}
		break;
	case WM_CREATE: 
	{
		Pos = -BusWidth+500;
		hdcScreen = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		hdcCompatible = CreateCompatibleDC(hdcScreen);
		hbmScreen = CreateCompatibleBitmap(hdcScreen, rect.right, rect.bottom);
		SelectObject(hdcCompatible, hbmScreen);

		SetTimer(hWnd, 1, 15, NULL);
		break;
	}
	case WM_TIMER:
		SelectObject(hdcCompatible, backgr);
		GetClientRect(hWnd, &rect);
		FillRect(hdcCompatible, &rect, backgr);

		Pos += Shift;
		if (Pos >= rect.right)  Pos = -BusWidth;
	

		Light(hdcCompatible, Pos, On);
		BusPaint(hdcCompatible, Pos,AnimShift);

		if (AnimOn)
		{
			if (AnimFinal)
				AnimShift += 1;
				AnimFinal = BusAnimation(hdcCompatible, Pos, AnimShift, true);
		}
		else
			if (AnimShift != 0)
			{
				if (AnimShift >= 0)
					AnimShift -= 1;
				AnimFinal = BusAnimation(hdcCompatible, Pos, AnimShift, false);
			}

		BitBlt(hdcScreen, 0, 0, rect.right, rect.bottom, hdcCompatible, 0, 0, SRCCOPY);

		break;

	case WM_SIZE:
		OX = LOWORD(lParam);
		OY = HIWORD(lParam);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			RECT Rect;
			GetClientRect(hWnd, &Rect);
			DPtoLP(hdc, (LPPOINT)& Rect, 2);
			
			Light(hdc, Pos, On);
			BusPaint(hdc, Pos, AnimShift);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DeleteObject(backgr);
		DeleteObject(defoltPen);
		KillTimer(hWnd, 1);
		ReleaseDC(hWnd, hdcScreen);
		DeleteDC(hdcCompatible);
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
