#include <windows.h>
#include <TCHAR.H>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;
	//����Ű
	HACCEL   hAcc;
	hAcc = LoadAccelerators(hInstance,
		MAKEINTRESOURCE(IDR_ACCELERATOR5_1));

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	/*WndClass.lpszMenuName = NULL;*/
	WndClass.lpszClassName = _T("Window Class Name");
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),

		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL

		);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		//�̺κи� ����(���� ����Ű�� ���� �ؼ�)
		if (!TranslateAccelerator(hwnd, hAcc, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,

	WPARAM wParam, LPARAM lParam)

{

	HDC hdc;
	PAINTSTRUCT	ps;
	static int radius2 = 100;
	static int	dx, dy;
	static int	ux, uy;
	static bool isClick = false;
	static int iColor = 1;
	static int select = 1;

	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	/*HBRUSH hBrush, OldBrush;*/
	int i;

	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		//�� ���� �ֱ�
		(HPEN)SelectObject(hdc, CreatePen(PS_DOT, 10, color));
		//���� �� �ֱ�
		//(HBRUSH)SelectObject(hdc, CreateSolid(color));

		if (select == 1)
		{
			// �� �׸���
			MoveToEx(hdc, dx, dy, NULL);
			LineTo(hdc, ux, uy);
		}
		else if (select == 2)
		{
			// Ÿ�� �׸���
			Ellipse(hdc, dx, dy, ux, uy);
		}

		else
		{
			// �簢�� �׸���
			Rectangle(hdc, dx, dy, ux, uy);
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:

		dx = LOWORD(lParam);
		dy = HIWORD(lParam);

		//isClick = true;
		//InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_LBUTTONUP:
		ux = LOWORD(lParam);
		uy = HIWORD(lParam);

		//isClick = true;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {
		case ID_Line:
			select = 1;
			break;

		case ID_Eclipse:
			select = 2;
			break;

		case ID_Rectangle:
			select = 3;
			break;

		case ID_Color:
			for (i = 0; i<16; i++)
				tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);	//������ 16�� ����
			memset(&COLOR, 0, sizeof(CHOOSECOLOR));
			COLOR.lStructSize = sizeof(CHOOSECOLOR);
			COLOR.hwndOwner = hwnd;
			COLOR.lpCustColors = tmp;	//������ ������ ����������� �ֱ�
			COLOR.Flags = CC_FULLOPEN;
			if (ChooseColor(&COLOR) != 0) //���� ���� �� 'Ȯ��' ������ ��
			{
				color = COLOR.rgbResult;
				InvalidateRgn(hwnd, NULL, TRUE);	//Paint �Լ� ȣ��
			}
			break;
		}
		break;

	case WM_DESTROY:

		PostQuitMessage(0);

		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

