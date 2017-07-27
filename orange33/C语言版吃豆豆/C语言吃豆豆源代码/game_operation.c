#include <windows.h> // Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h
#include "PacMan.h"

/************** ȫ�ֱ��� ****************/
// ��ʱ����ʱ���
DWORD dwTimerElapse;

/************** �������� ****************/
// ���ػ���
int GetScore() { return score; }

// ��Ϸ���Ƶ�һ����Ҫ���̡�
// ����ʱ������ʱ���еĴ����߼���
void OnTimer(HWND hwnd)
{
	// ��ʱ����ʱ�Ժ󣬳Զ����ƶ�һ����
	// �����Ժ��״̬�����к�������
	if (Dead_flag == 1)
	{
		Sleep(1000);
		KillTimer(hwnd, TIMER_ID);
		gameState = GS_GAMEOVER;// Ȼ��֪ͨ��ң�Game Over�ˣ��˳����̡�
		GamePaint(hwnd);
		Sleep(2500);//�ӳ�
		ExitProcess(0);
	}
	else
		switch (PacManMove())
		{
		case PACMAN_COMPLETE:
			Sleep(1000);
			KillTimer(hwnd, TIMER_ID);
			// ֪ͨ��ң��˳����̣�������Ϸ��
			gameState = GS_WIN;
			GamePaint(hwnd);
			Sleep(2500);
			ExitProcess(0);
			break;
			// ��������ֹͣ��ʱ�������˳���
		case PACMAN_ERROR:
			KillTimer(hwnd, TIMER_ID);
			MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
			ExitProcess(0);
			break;
			// û�н�����Ҳû�д��������Ե����ӡ�
		case PACMAN_MOVED:
			break;
		}
	return;
}

// �����ڲ���ʱ���е��߼�����
// ����Ϸʹ�õ��˼����������Ҽ�����
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

// ��Ϸ�ĳ�ʼ����
// ������Ϸ���ڲ����ݽṹ��ϵͳ����
void CreateGame(HWND hwnd, // �����ھ��
	DWORD dwInitTimerElapse, //
	int boundary_x, int boundary_y
)
{
	dwTimerElapse = dwInitTimerElapse;

	// ������Ϸ�ı߽�
	SetBoundary(boundary_x, boundary_y);

	// ����һ����ʱ��
	// ÿ���� dwTimerElapse ���룬hwnd���ڣ������ڣ��ͻ��յ�һ��WM_TIMER��Ϣ��
	// ��ʱ������������Ϸ���е���Ҫʱ���ߡ�
	// dwTimerElapse����Ӱ����Ϸ���еĿ����仯��
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
