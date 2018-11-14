#include "illuminate.h"
#include "Cube.h"
#include <cmath>
#include <iostream>
#include <windows.h>
#include <GdiPlus.h>
#define ID_TIMER1 1
HINSTANCE hInst;
LPCTSTR szWindowClass = (LPCTSTR)"QWERTY";
LPCTSTR szTitle = (LPCTSTR)"OPUS MAGNUM";


ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

double teta = M_PI / 720, phi = M_PI;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG msg;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// ÷икл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// стиль окна
	wcex.lpfnWndProc = (WNDPROC)WndProc; // оконна€ процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;		// указатель приложени€
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);		// опре-деление иконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);    // опре-деление курсора
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);   // установка фона
	wcex.lpszMenuName = NULL;		// определение меню
	wcex.lpszClassName = szWindowClass;	// им€ класса
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); // регистраци€ класса окна
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // сохран€ет указатель приложени€ в переменной hInst

	hWnd = CreateWindow(szWindowClass, // им€ класса окна
		szTitle,   // им€ приложени€
		WS_OVERLAPPEDWINDOW, // стиль окна
		CW_USEDEFAULT,	// положение по ’
		CW_USEDEFAULT, 	// положение по Y
		CW_USEDEFAULT,    // размер по ’
		CW_USEDEFAULT,    // размер по Y
		NULL,	// описатель родительского окна
		NULL,       // описатель меню окна
		hInstance,  // указатель приложени€
		NULL);     // параметры создани€.

	if (!hWnd) // ≈сли окно не создалось, функци€ возвращает FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);		// ѕоказать окно
	UpdateWindow(hWnd);			// ќбновить окно
	return TRUE;				//”спешное завершение функции
}
void dr_cub(HDC hdc, HWND hWnd, Cube cub, double phi, double teta, Illuminate& ill1)
{
	cub.transformation(teta, phi, ill1);
	cub.draw(hdc, hWnd, ill1, teta, phi);

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static Illuminate ill1(255, 255, 255);
	Cube scub(75);
	int index1 = 0, index2 = 0;

	//------------------------------------------------------------------

	switch (message)
	{

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case 'R':
			ill1.setcol(255, 0, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'N':
			ill1.setcol(255, 255, 255);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'L':
			ill1.settype(2);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'X':
			ill1.settype(0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'C':
			ill1.settype(1);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'G':
			ill1.setcol(0, 255, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'B':
			ill1.setcol(0, 25, 255);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'Y':
			ill1.setcol(255, 255, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'W':
			ill1.alphaplus();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'A':
			ill1.betaminus();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'D':
			ill1.betaplus();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'S':
			ill1.alphaminus();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_LEFT:
			index1++;
			teta += 2 * (M_PI / (360));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case  VK_DOWN:
			index2++;
			phi += 2 * (M_PI / (360));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_UP:
			index2--;
			phi -= 2 * (M_PI / (360));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			index1--;
			teta -= 2 * (M_PI / (360));
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;


	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);

		RECT rt;
		GetClientRect(hWnd, &rt);
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmMem = CreateCompatibleBitmap(hdc, (INT)(rt.right - rt.left), (INT)(rt.bottom - rt.top));
		SelectObject(hdcMem, hbmMem);
		Gdiplus::Graphics graphics(hdcMem);
		Gdiplus::SolidBrush brush_fon(Gdiplus::Color(255, 0, 0, 0));
		graphics.FillRectangle(&brush_fon, rt.left, rt.top, rt.right, rt.bottom);

		dr_cub(hdcMem, hWnd, cub, phi, teta, ill1);
		BitBlt(hdc, 0, 0, (INT)(rt.right - rt.left), (INT)(rt.bottom - rt.top), hdcMem, 0, 0, SRCCOPY);

		DeleteObject(hbmMem);
		DeleteDC(hdcMem);
		EndPaint(hWnd, &ps);
	}break;

	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, ID_TIMER1);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
#pragma comment(lib, "GdiPlus.lib")