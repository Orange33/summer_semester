#include <windows.h> // Windows窗口程序编程，需要引用头文件 Windows.h
#include "PacMan.h"

/************** 全局变量 ****************/
// 计时器到时间隔
DWORD dwTimerElapse;

/************** 函数定义 ****************/
// 返回积分
int GetScore() { return score; }

// 游戏控制的一个主要流程。
// 当计时器发生时进行的处理逻辑。
void OnTimer(HWND hwnd)
{
	// 计时器到时以后，吃豆人移动一步。
	// 根据以后的状态，进行后续处理。
	if (Dead_flag == 1)
	{
		Sleep(1000);
		KillTimer(hwnd, TIMER_ID);
		gameState = GS_GAMEOVER;// 然后通知玩家，Game Over了，退出进程。
		GamePaint(hwnd);
		Sleep(2500);//延迟
		ExitProcess(0);
	}
	else
		switch (PacManMove())
		{
		case PACMAN_COMPLETE:
			Sleep(1000);
			KillTimer(hwnd, TIMER_ID);
			// 通知玩家，退出进程，结束游戏。
			gameState = GS_WIN;
			GamePaint(hwnd);
			Sleep(2500);
			ExitProcess(0);
			break;
			// 发生错误，停止计时器，并退出。
		case PACMAN_ERROR:
			KillTimer(hwnd, TIMER_ID);
			MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
			ExitProcess(0);
			break;
			// 没有结束，也没有错误，正常吃到豆子。
		case PACMAN_MOVED:
			break;
		}
	return;
}

// 当用于操作时进行的逻辑处理。
// 本游戏使用到了键盘上下左右键控制
void OnKeyDown(DWORD vk, HWND hwnd)
{
	switch (vk) // virtual key value
	{
	case VK_LEFT:
		if (pause == 0 && gameState == GS_RUNNING)
			SetDirction(PACMAN_LEFT);
		break;
	case VK_RIGHT:
		if (pause == 0 && gameState == GS_RUNNING)
			SetDirction(PACMAN_RIGHT);
		break;
	case VK_UP:
		if (pause == 0 && gameState == GS_RUNNING)
			SetDirction(PACMAN_UP);
		break;
	case VK_DOWN:
		if (pause == 0 && gameState == GS_RUNNING)
			SetDirction(PACMAN_DOWN);
		break;
	}
	return;
}

// 游戏的初始化，
// 创建游戏的内部数据结构和系统对象。
void CreateGame(HWND hwnd, // 主窗口句柄
	DWORD dwInitTimerElapse, //
	int boundary_x, int boundary_y
)
{
	dwTimerElapse = dwInitTimerElapse;

	// 设置游戏的边界
	SetBoundary(boundary_x, boundary_y);

	// 创建一个计时器
	// 每经过 dwTimerElapse 毫秒，hwnd窗口（主窗口）就会收到一个WM_TIMER消息。
	// 计时器是驱动本游戏进行的主要时间线。
	// dwTimerElapse变量影响游戏进行的快慢变化。
	if (pause == 1)
	{
		KillTimer(hwnd, TIMER_ID);
		KillTimer(hwnd, TIMER_ID2);
	}

	else if (pause == 0)
	{
		SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);
		SetTimer(hwnd, TIMER_ID2, 400, NULL);
	}
	/*SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);
	SetTimer(hwnd, TIMER_ID2, 400, NULL);
*/
}
