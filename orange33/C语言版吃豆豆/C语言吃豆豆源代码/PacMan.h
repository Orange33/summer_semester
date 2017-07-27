#pragma once
#include <windows.h> // Windows窗口程序编程，需要引用头文件 Windows.h

//计时器1的ID
#define TIMER_ID 12340
//计时器2的ID
#define TIMER_ID2 12345

//枚举游戏状态
enum {
	GS_READY,     //准备开始
	GS_RUNNING,   //游戏进行中
	GS_GAMEOVER,  //游戏结束
	GS_WIN        //玩家获胜
};


// 吃豆人的状态
#define PACMAN_MOVED		   0//吃豆人移动
#define PACMAN_COMPLETE        1//玩家获胜
#define PACMAN_ERROR		   2//发生错误

// 吃豆人的方向
typedef enum _dirction
{
	PACMAN_UP,
	PACMAN_DOWN,
	PACMAN_LEFT,
	PACMAN_RIGHT,
}dirction;

// 怪兽的方向
typedef enum _dirction2
{
	Monster_UP,
	Monster_DOWN,
	Monster_LEFT,
	Monster_RIGHT,
}dirction2;

// 吃豆人移动方向
dirction Pacman_dir;
// 怪兽移动方向
dirction2 Monster_dir[5];

// 游戏坐标
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;


/*******全局变量*********/

//PGAME_COORD pMonster[5];//怪兽

//五只怪兽
PGAME_COORD Monster0;
PGAME_COORD Monster1;
PGAME_COORD Monster2;
PGAME_COORD Monster3;
PGAME_COORD Monster4;

//游戏状态
int gameState;

//1是暂停，0是继续
int pause;

//吃到豆子的数量，吃完138+4=142颗则胜利
int score;

//表示地图的二维数组
int map[17][17];

//判断吃豆人是否死亡，Dead_flag=1时为死亡
int Dead_flag;


/********函数声明*********/

//PacMan.c中的接口函数

void init();

// 设置边界坐标
void SetBoundary(int x, int y);

// 获得边界坐标
PGAME_COORD GetBoundary();

//设置小豆子的坐标
void SetSbean(short x, short y);

//获得小豆子的坐标
PGAME_COORD GetsSbean();

//设置能量豆的坐标
void SetBbean(short x, short y);

//获得能量豆的坐标
PGAME_COORD GetsBbean();

//设置墙壁障碍物的坐标
void SetWall(short x, short y);

//获得墙壁障碍物的坐标
PGAME_COORD GetsWall();

//设置吃豆人的坐标
void SetPacMan(short x, short y);

//获得吃豆人的坐标
PGAME_COORD GetsPacMan();

// 吃豆人移动一步，
// 移动以后，如果吃到了豆子，则豆子计数器加一
//如果吃到能量豆，怪兽变为蓝色，吃豆人碰到怪兽则吃掉怪兽而不是死亡。
// 如果能量豆未起作用时碰到怪兽，则吃豆人死亡，并返回是否死亡的状态。
int PacManMove();

// 改变吃豆人移动的方向
void SetDirction(dirction dir);

// 获得当前吃豆人的方向
dirction GetDirction();

//怪兽移动一步
PGAME_COORD MonsterMove(PGAME_COORD Monster);

// game_opration.c 中的接口函数

void initState();//初始化游戏状态
int GetScore();
void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	int boundary_x, int boundary_y
);
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk, HWND hwnd);
void GamePaint(HWND hwnd);