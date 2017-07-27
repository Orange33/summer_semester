#include <windows.h> // Windows窗口程序编程，需要引用头文件 Windows.h
#include "PacMan.h"
#pragma comment( lib, "msimg32.lib" )//TransparentBlt函数（设置背景透明）用到的库

// 画图时使用的表示的圆形的直径像素点个数
#define CELL_PIXEL	    30    

// 用来绘图的颜色
#define COLOR_PACMAN		RGB(0, 191, 255)
#define COLOR_SMALLBEAN		RGB(248, 248 ,255)
#define COLOR_BIGBEAN		RGB(255, 255, 0)
#define COLOR_WALL		    RGB(105, 105, 105)
#define COLOR_TEXT			RGB(0,0,0)

// 游戏的参数的设置 
#define INIT_TIMER_ELAPSE   300	// 确定游戏中吃豆人的移动速度
#define MAX_X		16	// 游戏界面大小
#define MAX_Y		19	// 游戏界面大小
#define INIT_X		13	// 吃豆人的初始位置
#define INIT_Y		8	// 吃豆人的初始位置

// 全局变量
HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
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

// 函数声明
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

//游戏状态初始化
void initState()
{
	gameState = GS_READY;
	pause = 1;
}

//DC初始化
void initDC()
{
	/******初始化DC*********/
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
* ##########   入口函数WinMain    ##########
*******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hinstance, // 程序实例句柄，在程序运行，进程创建后，由操作系统向应用程序传入
	HINSTANCE hPrevInstance, // 父进程的程序实例句柄
	LPSTR lpCmdLine,  // 命令行参数，地位和作用类似C语言main函数参数argc和argv,但是没有按空格进行切分
	int nCmdShow)   // 用于指明窗口是否需要显示的参数。
{
	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	HWND hwnd;

	MSG msg;
	int fGotMessage;

	hinst = hinstance;

	// 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.lpfnWndProc = MainWndProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// 窗口的菜单的资源名。
	wc.lpszMenuName = "MainMenu";
	// 给窗口类起一个名字，在创建窗口时需要这个名字。
	wc.lpszClassName = "MainWClass";

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	// 窗口注册成功，继续运行。

	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",			// 窗口类名，必须是已经注册了的窗口类
		"PacMan Game!!",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	// 窗口创建成功，继续运行。

	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwnd, nCmdShow);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);

	// 以下进入消息循环。获取消息--翻译消息--分配消息（由窗口的消息处理函数来处理消息）
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

	// 创建需要用到的PEN和BRUSH
	hbrushSbean = CreateSolidBrush(COLOR_SMALLBEAN); // RGB颜色，实心BRUSH
	hbrushBbean = CreateSolidBrush(COLOR_BIGBEAN);
	hpen = CreatePen(PS_DOT, 2, RGB(0, 0, 0));  // PEN
	hBrushPaMan = CreateSolidBrush(COLOR_PACMAN);
	hBrushWall = CreateSolidBrush(COLOR_WALL);
	hPenBoundary = CreatePen(10, 10, COLOR_WALL);

	if (gameState == GS_READY)//停留在开始画面中
	{
		pause = 1;//游戏暂停中
		BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hLoadingDC, 0, 0, SRCCOPY);
		loadingCount = rand(loadingCount) % 50;//产生随机数，得到动态效果
		if (loadingCount < 25)
			TransparentBlt(hdc, 170, 320, 198, 28, hPressDC, 0, 0, 197, 27
				, RGB(0, 0, 0));
	}
	if (gameState == GS_WIN)//玩家胜利
		BitBlt(hdc, 15, 5, rect.right - rect.left, rect.bottom - rect.top, hWinDC, 0, 0, SRCCOPY);
	if (gameState == GS_GAMEOVER)//玩家失败，游戏结束
		BitBlt(hdc, 15, 5, rect.right - rect.left, rect.bottom - rect.top, hGameOverDC, 0, 0, SRCCOPY);
	if (gameState == GS_RUNNING)//游戏进行中
	{
		if (pause == 1)//暂停
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
		* #############  画背景  ################
		*******************************************************************************/
		FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		int i, j;
		for (i = 0; i < 17; i++)
			for (j = 0; j < 17; j++)
				if (map[i][j] == 0)/*代表小豆子*/
				{
					/*******************************************************************************
					* #############  画小豆子  ################
					*******************************************************************************/

					// 将画图需要用的PEN和BRUSH选择到DC中
					hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushSbean);
					hOldPen = (HPEN)SelectObject(hdcmem, hpen);

					SetSbean(i, j);
					lpSbean = GetsSbean();//得到小豆子的坐标

				   // （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
					Ellipse(hdcmem,
						lpSbean->x * CELL_PIXEL + 10 + rectBoundary.left,
						lpSbean->y * CELL_PIXEL + 10 + rectBoundary.top,
						(lpSbean->x)*CELL_PIXEL + 20 + rectBoundary.left,
						(lpSbean->y)*CELL_PIXEL + 20 + rectBoundary.top);
				}
				else if (map[i][j] == 8)/*代表能量豆*/
				{
					/*******************************************************************************
					* #############  画能量豆  ################
					*******************************************************************************/
					// 将画图需要用的PEN和BRUSH选择到DC中
					hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushBbean);
					hOldPen = (HPEN)SelectObject(hdcmem, hpen);

					SetBbean(i, j);
					lpBbean = GetsBbean();//得到能量豆的坐标

					// （椭）圆形，使用上面选择的PEN勾勒边框，BRUSH填充
					Ellipse(hdcmem,
						lpBbean->x * CELL_PIXEL + 5 + rectBoundary.left,
						lpBbean->y * CELL_PIXEL + 5 + rectBoundary.top,
						(lpBbean->x)*CELL_PIXEL + 25 + rectBoundary.left,
						(lpBbean->y)*CELL_PIXEL + 25 + rectBoundary.top);
				}
				else if (map[i][j] == 3)/*代表吃豆人*/
				{
					/*******************************************************************************
					* #############  画吃豆人  ################
					*******************************************************************************/

					SelectObject(hdcmem, hBrushPaMan);
					SetPacMan(i, j);
					pPaMan = GetsPacMan();//得到吃豆人的坐标
					switch (Pacman_dir)
					{
						//方向向上
					case PACMAN_UP:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 10 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 20 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top);//向上的嘴

						SelectObject(hdc, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 5 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 15 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 8 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 18 + rectBoundary.top);//眼睛

						break;

						//方向向下
					case PACMAN_DOWN:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 20 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 25 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 10 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 25 + rectBoundary.top);//向下的嘴

						SelectObject(hdc, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 22 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 15 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 25 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 18 + rectBoundary.top);//眼睛

						break;

						//方向向左
					case PACMAN_LEFT:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 5 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 20 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 5 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 10 + rectBoundary.top);//向左的嘴

						SelectObject(hdc, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 15 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 18 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 8 + rectBoundary.top);//眼睛

						break;

						//方向向右
					case PACMAN_RIGHT:
						Pie(hdcmem,
							pPaMan->x *CELL_PIXEL + rectBoundary.left,
							pPaMan->y * CELL_PIXEL + rectBoundary.top,
							(pPaMan->x + 1)*CELL_PIXEL + rectBoundary.left,
							(pPaMan->y + 1)*CELL_PIXEL + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 25 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 10 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 25 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 20 + rectBoundary.top);//向右的嘴

						SelectObject(hdcmem, hpen);

						Ellipse(hdcmem,
							pPaMan->x *CELL_PIXEL + 15 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 5 + rectBoundary.top,
							pPaMan->x *CELL_PIXEL + 18 + rectBoundary.left,
							pPaMan->y *CELL_PIXEL + 8 + rectBoundary.top);//眼睛
						break;
					}
				}
				else if (map[i][j] == 2)/*代表墙壁*/
				{
					/*******************************************************************************
					* #############  画墙壁  ################
					*******************************************************************************/
					SelectObject(hdcmem, hBrushWall);

					SetWall(i, j);
					pWall = GetsWall();//得到墙壁的坐标
					//画方形
					Rectangle(hdcmem,
						pWall->x *CELL_PIXEL + rectBoundary.left,
						pWall->y * CELL_PIXEL + rectBoundary.top,
						(pWall->x + 1)*CELL_PIXEL + rectBoundary.left,
						(pWall->y + 1)*CELL_PIXEL + rectBoundary.top);
				}
				else if (map[i][j] == 4)/*代表怪兽*/
				{
					/*******************************************************************************
					* #############  画怪兽  ################
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
		* #############  画边界  ################
		*******************************************************************************/

		SelectObject(hdcmem, hPenBoundary);

		// 将PEN移动到需要绘制的方框的左上角
		MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);
		// 画了一个方框。演示LineTo函数
		LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
		LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
		LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
		LineTo(hdcmem, rectBoundary.left, rectBoundary.top);

		/*******************************************************************************
		* #############  写一行字  ################
		*******************************************************************************/

		// 创建了一个字体对象
		hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

		// 将这个FONT对象放入DC中
		if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
		{
			CHAR szSourceInfo[1024];
			wsprintf(szSourceInfo, "      Score   %d     ", GetScore());
			// 设置输出颜色
			SetTextColor(hdcmem, COLOR_TEXT);
			// 输出字符串。
			TextOut(hdcmem, rectBoundary.left + 5, rectBoundary.bottom - 89,
				szSourceInfo, lstrlen(szSourceInfo));
			// 输出完成，将原来的字体对象放回DC中
			SelectObject(hdcmem, hOldFont);
		}

		// 在内存DC中画完，一次输出的窗口DC上。
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
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;
	PGAME_COORD pCoordBoundary = GetBoundary();

	// 设置游戏边界
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x + 1);
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y + 1);

	// 计算上下左右角的位置
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left, // 保存边界和左右两边边框相等。
		rectBoundary.bottom,
		TRUE);
}

/*******************************************************************************
* ##########   消息处理回调函数    ##########*/
LONG CALLBACK MainWndProc(
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam) // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
{
	// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
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
			//当按下ESC按键时候发出关闭窗口的消息
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
				MessageBox(GetActiveWindow(), "《说明》\n1.↑→↓←移动蓝色吃豆人\n2.碰到怪兽则游戏结束\n3.按空格键暂停或继续\n", "HELP", MB_OK);
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
