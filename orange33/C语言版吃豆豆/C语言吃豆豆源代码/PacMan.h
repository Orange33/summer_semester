#pragma once
#include <windows.h> // Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h

//��ʱ��1��ID
#define TIMER_ID 12340
//��ʱ��2��ID
#define TIMER_ID2 12345

//ö����Ϸ״̬
enum {
	GS_READY,     //׼����ʼ
	GS_RUNNING,   //��Ϸ������
	GS_GAMEOVER,  //��Ϸ����
	GS_WIN        //��һ�ʤ
};


// �Զ��˵�״̬
#define PACMAN_MOVED		   0//�Զ����ƶ�
#define PACMAN_COMPLETE        1//��һ�ʤ
#define PACMAN_ERROR		   2//��������

// �Զ��˵ķ���
typedef enum _dirction
{
	PACMAN_UP,
	PACMAN_DOWN,
	PACMAN_LEFT,
	PACMAN_RIGHT,
}dirction;

// ���޵ķ���
typedef enum _dirction2
{
	Monster_UP,
	Monster_DOWN,
	Monster_LEFT,
	Monster_RIGHT,
}dirction2;

// �Զ����ƶ�����
dirction Pacman_dir;
// �����ƶ�����
dirction2 Monster_dir[5];

// ��Ϸ����
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;


/*******ȫ�ֱ���*********/

//PGAME_COORD pMonster[5];//����

//��ֻ����
PGAME_COORD Monster0;
PGAME_COORD Monster1;
PGAME_COORD Monster2;
PGAME_COORD Monster3;
PGAME_COORD Monster4;

//��Ϸ״̬
int gameState;

//1����ͣ��0�Ǽ���
int pause;

//�Ե����ӵ�����������138+4=142����ʤ��
int score;

//��ʾ��ͼ�Ķ�ά����
int map[17][17];

//�жϳԶ����Ƿ�������Dead_flag=1ʱΪ����
int Dead_flag;


/********��������*********/

//PacMan.c�еĽӿں���

void init();

// ���ñ߽�����
void SetBoundary(int x, int y);

// ��ñ߽�����
PGAME_COORD GetBoundary();

//����С���ӵ�����
void SetSbean(short x, short y);

//���С���ӵ�����
PGAME_COORD GetsSbean();

//����������������
void SetBbean(short x, short y);

//���������������
PGAME_COORD GetsBbean();

//����ǽ���ϰ��������
void SetWall(short x, short y);

//���ǽ���ϰ��������
PGAME_COORD GetsWall();

//���óԶ��˵�����
void SetPacMan(short x, short y);

//��óԶ��˵�����
PGAME_COORD GetsPacMan();

// �Զ����ƶ�һ����
// �ƶ��Ժ�����Ե��˶��ӣ����Ӽ�������һ
//����Ե������������ޱ�Ϊ��ɫ���Զ�������������Ե����޶�����������
// ���������δ������ʱ�������ޣ���Զ����������������Ƿ�������״̬��
int PacManMove();

// �ı�Զ����ƶ��ķ���
void SetDirction(dirction dir);

// ��õ�ǰ�Զ��˵ķ���
dirction GetDirction();

//�����ƶ�һ��
PGAME_COORD MonsterMove(PGAME_COORD Monster);

// game_opration.c �еĽӿں���

void initState();//��ʼ����Ϸ״̬
int GetScore();
void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	int boundary_x, int boundary_y
);
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk, HWND hwnd);
void GamePaint(HWND hwnd);