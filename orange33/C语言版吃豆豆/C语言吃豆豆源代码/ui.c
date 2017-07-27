#include <windows.h> // Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h
#include "PacMan.h"
#pragma comment( lib, "msimg32.lib" )//TransparentBlt���������ñ���͸�����õ��Ŀ�

// ��ͼʱʹ�õı�ʾ��Բ�ε�ֱ�����ص����
#define CELL_PIXEL	    30    

// ������ͼ����ɫ
#define COLOR_PACMAN		RGB(0, 191, 255)
#define COLOR_SMALLBEAN		RGB(248, 248 ,255)
#define COLOR_BIGBEAN		RGB(255, 255, 0)
#define COLOR_WALL		    RGB(105, 105, 105)
#define COLOR_TEXT			RGB(0,0,0)

// ��Ϸ�Ĳ��������� 
#define INIT_TIMER_ELAPSE   300	// ȷ����Ϸ�гԶ��˵��ƶ��ٶ�
#define MAX_X		16	// ��Ϸ�����С
#define MAX_Y		19	// ��Ϸ�����С
#define INIT_X		13	// �Զ��˵ĳ�ʼλ��
#define INIT_Y		8	// �Զ��˵ĳ�ʼλ��

// ȫ�ֱ���
HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;

HDC hdc, hdcmem, hdcBitmapSrc;
HDC		hWinDC;
HBITMAP	hWinBmp;
HDC		hLoadingDC;
HBITMAP	hLoadingBmp;
HDC		hPressDC;
HBITMAP	hPressBmp;
HDC		hGameOverDC;
HBITMAP	hGameOverBmp;
HBITMAP hbmpMonster;

// ��������
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

//��Ϸ״̬��ʼ��
void initState()
{
	gameState = GS_READY;
	pause = 1;
}

//DC��ʼ��
void initDC()
{
	/******��ʼ��DC*********/
	hGameOverDC = CreateCompatibleDC(NULL);
	hGameOverBmp = (HBITMAP)LoadImage(NULL, "gameover.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hGameOverDC, hGameOverBmp);

	hLoadingDC = CreateCompatibleDC(NULL);
	hLoadingBmp = (HBITMAP)LoadImage(NULL, "loading.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hLoadingDC, hLoadingBmp);

	hPressDC = CreateCompatibleDC(NULL);
	hPressBmp = (HBITMAP)LoadImage(NULL, "enter.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hPressDC, hPressBmp);

	hWinDC = CreateCompatibleDC(NULL);
	hWinBmp = (HBITMAP)LoadImage(NULL, "win.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hWinDC, hWinBmp);

	hdcBitmapSrc = CreateCompatibleDC(hdcmem);
	hbmpMonster = LoadImage(NULL, "monster.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

/*******************************************************************************
* ##########   ��ں���WinMain    ##########
*******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hinstance, // ����ʵ��������ڳ������У����̴������ɲ���ϵͳ��Ӧ�ó�����
	HINSTANCE hPrevInstance, // �����̵ĳ���ʵ�����
	LPSTR lpCmdLine,  // �����в�������λ����������C����main��������argc��argv,����û�а��ո�����з�
	int nCmdShow)   // ����ָ�������Ƿ���Ҫ��ʾ�Ĳ�����
{
	WNDCLASS wc;
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// ���ڵĲ˵�����Դ����
	wc.lpszMenuName = "MainMenu";
	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
	wc.lpszClassName = "MainWClass";

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�

	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",			// �����������������Ѿ�ע���˵Ĵ�����
		"PacMan Game!!",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}

	// ���ڴ����ɹ����������С�

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);

	// ���½�����Ϣѭ������ȡ��Ϣ--������Ϣ--������Ϣ���ɴ��ڵ���Ϣ��������������Ϣ��
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void GamePaint(HWND hwnd)
{
	HPEN hpen;

	HBITMAP hbmMem;
	BITMAP bmp;

	HDC		tempDC;
	HBITMAP	tempBMP;

	HPEN hPenBoundary;
	HPEN hOldPen;

	HBRUSH hbrushSbean;
	HBRUSH hbrushBbean;
	HBRUSH hBrushPaMan;
	HBRUSH hBrushWall;
	HBRUSH hOldBrush;

	HFONT hFont, hOldFont;

	RECT rect;

	PGAME_COORD pPaMan;
	PGAME_COORD lpSbean;
	PGAME_COORD lpBbean;
	PGAME_COORD pWall;

	int loadingCount = 0;

	GetClientRect(hwnd, &rect);

	hdc = GetDC(hwnd);

	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,
		rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hdcmem, hbmMem);

	tempDC = CreateCompatibleDC(NULL);
	tempBMP = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(tempDC, tempBMP);

	// ������Ҫ�õ���PEN��BRUSH
	hbrushSbean = CreateSolidBrush(COLOR_SMALLBEAN); // RGB��ɫ��ʵ��BRUSH
	hbrushBbean = CreateSolidBrush(COLOR_BIGBEAN);
	hpen = CreatePen(PS_DOT, 2, RGB(0, 0, 0));  // PEN
	hBrushPaMan = CreateSolidBrush(COLOR_PACMAN);
	hBrushWall = CreateSolidBrush(COLOR_WALL);
	hPenBoundary = CreatePen(10, 10, COLOR_WALL);

	if (gameState == GS_READY)//ͣ���ڿ�ʼ������
	{
		pause = 1;//��Ϸ��ͣ��
		BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hLoadingDC, 0, 0, SRCCOPY);
		loadingCount = rand(loadingCount) % 50;//������������õ���̬Ч��
		if (loadingCount < 25)
			TransparentBlt(hdc, 170, 320, 198, 28, hPressDC, 0, 0, 197, 27
				, RGB(0, 0, 0));
	}
	if (gameState == GS_WIN)//���ʤ��
		BitBlt(hdc, 15, 5, rect.right - rect.left, rect.bottom - rect.top, hWinDC, 0, 0, SRCCOPY);
	if (gameState == GS_GAMEOVER)//���ʧ�ܣ���Ϸ����
		BitBlt(hdc, 15, 5, rect.right - rect.left, rect.bottom - rect.top, hGameOverDC, 0, 0, SRCCOPY);
	if (gameState == GS_RUNNING)//��Ϸ������
	{
		if (pause == 1)//��ͣ
		{
			if (gameState == GS_RUNNING)
			{
				TextOut(tempDC, 0, 2, "PAUSE", sizeof("PAUSE") - 1);
				BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, tempDC, 0, 0, SRCCOPY);
				Sleep(20);
				return;
			}
		}
		/*******************************************************************************
		* #############  ������  ################
		*******************************************************************************/
		FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		int i, j;
		for (i = 0; i < 17; i++)
			for (j = 0; j < 17; j++)
				if (map[i][j] == 0)/*����С����*/
				{
					/*******************************************************************************
					* #############  ��С����  ################
					*******************************************************************************/

					// ����ͼ��Ҫ�õ�PEN��BRUSHѡ��DC��
					hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushSbean);
					hOldPen = (HPEN)SelectObject(hdcmem, hpen);

					SetSbean(i, j);
					lpSbean = GetsSbean();//�õ�С���ӵ�����

				   // ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
					Ellipse(hdcmem,
						lpSbean->x * CELL_PIXEL + 10 + rectBoundary.left,
						lpSbean->y * CELL_PIXEL + 10 + rectBoundary.top,
						(lpSbean->x)*CELL_PIXEL + 20 + rectBoundary.left,
						(lpSbean->y)*CELL_PIXEL + 20 + rectBoundary.top);
				}
				else if (map[i][j] == 8)/*����������*/
				{
					/*******************************************************************************
					* #############  ��������  ################
					*******************************************************************************/
					// ����ͼ��Ҫ�õ�PEN��BRUSHѡ��DC��
					hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushBbean);
					hOldPen = (HPEN)SelectObject(hdcmem, hpen);

					SetBbean(i, j);
					lpBbean = GetsBbean();//�õ�������������

					// ���֣�Բ�Σ�ʹ������ѡ���PEN���ձ߿�BRUSH���
					Ellipse(hdcmem,
						lpBbean->x * CELL_PIXEL + 5 + rectBoundary.left,
						lpBbean->y * CELL_PIXEL + 5 + rectBoundary.top,
						(lpBbean->x)*CELL_PIXEL + 25 + rectBoundary.left,
						(lpBbean->y)*CELL_PIXEL + 25 + rectBoundary.top);
				}
				else if (map[i][j] == 3)/*����Զ���*/
				{
					/*******************************************************************************
					* #############  ���Զ���  ################
					*******************************************************************************/

					SelectObject(hdcmem, hBrushPaMan);
					SetPacMan(i, j);
					pPaMan = GetsPacMan();//�õ��Զ��˵�����
					switch (Pacman_dir)
					{
						//��������
					case PACMAN_UP:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 10 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 20 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top);//���ϵ���

						SelectObject(hdc, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 5 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 15 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 8 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 18 + rectBoundary.top);//�۾�

						break;

						//��������
					case PACMAN_DOWN:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 20 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 25 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 10 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 25 + rectBoundary.top);//���µ���

						SelectObject(hdc, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 22 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 15 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 25 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 18 + rectBoundary.top);//�۾�

						break;

						//��������
					case PACMAN_LEFT:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 5 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 20 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 5 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 10 + rectBoundary.top);//�������

						SelectObject(hdc, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 15 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 18 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 8 + rectBoundary.top);//�۾�

						break;

						//��������
					case PACMAN_RIGHT:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 25 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 10 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 25 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 20 + rectBoundary.top);//���ҵ���

						SelectObject(hdcmem, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 15 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 18 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 8 + rectBoundary.top);//�۾�
						break;
					}
				}
				else if (map[i][j] == 2)/*����ǽ��*/
				{
					/*******************************************************************************
					* #############  ��ǽ��  ################
					*******************************************************************************/
					SelectObject(hdcmem, hBrushWall);

					SetWall(i, j);
					pWall = GetsWall();//�õ�ǽ�ڵ�����
					//������
					Rectangle(hdcmem,
						pWall->x *CELL_PIXEL + rectBoundary.left,
						pWall->y * CELL_PIXEL + rectBoundary.top,
						(pWall->x + 1)*CELL_PIXEL + rectBoundary.left,
						(pWall->y + 1)*CELL_PIXEL + rectBoundary.top);
				}
				else if (map[i][j] == 4)/*�������*/
				{
					/*******************************************************************************
					* #############  ������  ################
					*******************************************************************************/

					GetObject(hbmpMonster, sizeof(BITMAP), &bmp);
					SelectObject(hdcBitmapSrc, hbmpMonster);

					StretchBlt(hdcmem,
						i* CELL_PIXEL + rectBoundary.left,
						j* CELL_PIXEL + rectBoundary.top,
						CELL_PIXEL, CELL_PIXEL,
						hdcBitmapSrc,
						0, 0, bmp.bmWidth, bmp.bmHeight,
						SRCCOPY);
				}

		/*******************************************************************************
		* #############  ���߽�  ################
		*******************************************************************************/

		SelectObject(hdcmem, hPenBoundary);

		// ��PEN�ƶ�����Ҫ���Ƶķ�������Ͻ�
		MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
		// ����һ��������ʾLineTo����
		LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
		LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
		LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
		LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

		/*******************************************************************************
		* #############  дһ����  ################
		*******************************************************************************/

		// ������һ���������
		hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

		// �����FONT�������DC��
		if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
		{
			CHAR szSourceInfo[1024];
			wsprintf(szSourceInfo, "      Score   %d     ", GetScore());
			// ���������ɫ
			SetTextColor(hdcmem, COLOR_TEXT);
			// ����ַ�����
			TextOut(hdcmem, rectBoundary.left + 5, rectBoundary.bottom - 89,
				szSourceInfo, lstrlen(szSourceInfo));
			// �����ɣ���ԭ�����������Ż�DC��
			SelectObject(hdcmem, hOldFont);
		}

		// ���ڴ�DC�л��꣬һ������Ĵ���DC�ϡ�
		BitBlt(hdc,
			0, 0, rect.right - rect.left, rect.bottom - rect.top,
			hdcmem, 0, 0, SRCCOPY);
	}

	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	DeleteObject(hbrushSbean);
	DeleteObject(hbrushBbean);
	DeleteObject(hBrushPaMan);
	DeleteObject(hBrushWall);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	ReleaseDC(hwnd, hdc);
}

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	PGAME_COORD pCoordBoundary = GetBoundary();

	// ������Ϸ�߽�
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y + 1);

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // ����߽���������߱߿���ȡ�
		rectBoundary.bottom,
		TRUE);
}

/*******************************************************************************
* ##########   ��Ϣ����ص�����    ##########*/
LONG CALLBACK MainWndProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		CreateGame(hwnd,
			INIT_TIMER_ELAPSE,
			MAX_X, MAX_Y);
		ReSizeGameWnd(hwnd);
		init();
		initState();
		initDC();
		break;
	case WM_PAINT:
		GamePaint(hwnd);
		break;

	case WM_KEYDOWN:
		GamePaint(hwnd);
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			//������ESC����ʱ�򷢳��رմ��ڵ���Ϣ
			if (gameState != GS_RUNNING)
			{
				PostMessage(hwnd, WM_CLOSE, 0, 0);
			}
			else
			{
				gameState = GS_READY;
			}
		}
		break;
		case VK_SPACE:
		{
			if (pause == 0 && gameState == GS_RUNNING)
				pause = 1;

			else if (pause == 1 && gameState == GS_RUNNING)
				pause = 0;
		}
		break;
		case VK_RETURN:
		{
			if (gameState == GS_READY)
			{
				MessageBox(GetActiveWindow(), "��˵����\n1.���������ƶ���ɫ�Զ���\n2.������������Ϸ����\n3.���ո����ͣ�����\n", "HELP", MB_OK);
				gameState = GS_RUNNING;
				pause = 0;
			}
		}
		break;
		default:
		{
			if (gameState == GS_RUNNING)
			{
				OnKeyDown(wParam, hwnd);
			}
		}
		break;
		}

	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_ID:
			OnTimer(hwnd);
			GamePaint(hwnd);
			break;

		case TIMER_ID2:
			GamePaint(hwnd);
			Monster0 = MonsterMove(Monster0);
			Monster1 = MonsterMove(Monster1);
			Monster2 = MonsterMove(Monster2);
			Monster3 = MonsterMove(Monster3);
			Monster4 = MonsterMove(Monster4);
			break;
		}
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}
