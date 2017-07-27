#include <windows.h> // Windows窗口程序编程，需要引用头文件 Windows.h
#include <time.h>
#include "PacMan.h"

/*************全局变量****************/
//吃到豆子的分数，到138*1+4*10=178则胜利
score = 0;

//用来标记吃豆人是否死亡，1为死亡
Dead_flag = 0;

//二维数组，用来表示各物初始位置
//0：白色小豆子，共138颗
//8: 黄色能量豆，共4颗，吃豆人吃了后怪兽变为蓝色，此时可吃掉怪兽
//2：墙壁障碍物，不可通路
//3：吃豆人
//4：怪兽，共5只
map[17][17] = {
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,2 },
	{ 2,0,2,2,2,0,2,2,2,2,2,0,2,2,2,0,2 },
	{ 2,0,2,8,0,0,0,0,2,0,0,0,0,8,2,0,2 },
	{ 2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2 },
	{ 2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,2 },
	{ 2,0,2,0,2,0,2,2,0,2,2,0,2,0,2,0,2 },
	{ 2,0,2,0,2,0,2,0,0,0,2,0,2,0,2,0,2 },
	{ 2,0,2,0,0,0,0,0,4,0,2,0,0,3,2,0,2 },
	{ 2,0,2,0,2,0,2,0,0,0,2,0,2,0,2,0,2 },
	{ 2,0,2,0,2,0,2,2,0,2,2,0,2,0,2,0,2 },
	{ 2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,2 },
	{ 2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2 },
	{ 2,0,2,8,0,0,0,0,2,0,0,0,0,8,2,0,2 },
	{ 2,0,2,2,2,0,2,2,2,2,2,0,2,2,2,0,2 },
	{ 2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 } };

GAME_COORD PacMan;//吃豆人
GAME_COORD Monster;//怪兽
GAME_COORD Sbean;//白色小豆子
GAME_COORD Bbean;//黄色能量豆
GAME_COORD Wall;//墙壁障碍物

PGAME_COORD posSbean;//白色小豆子
PGAME_COORD posBbean;//黄色能量豆
PGAME_COORD posWall;//墙壁障碍物
PGAME_COORD posPacMan;//吃豆人
//PGAME_COORD posMonster[5];//怪兽

//初始化
void init()
{
	Monster0 = (GAME_COORD*)malloc(sizeof(GAME_COORD));
	Monster1 = (GAME_COORD*)malloc(sizeof(GAME_COORD));
	Monster2 = (GAME_COORD*)malloc(sizeof(GAME_COORD));
	Monster3 = (GAME_COORD*)malloc(sizeof(GAME_COORD));
	Monster4 = (GAME_COORD*)malloc(sizeof(GAME_COORD));
	int i, j;
	for (i = 0; i < 17; i++)
	{
		for (j = 0; j < 17; j++)
		{
			if (map[i][j] == 0)
			{
				SetSbean(i, j);
				posSbean = GetsSbean();
			}
			if (map[i][j] == 8)
			{
				SetBbean(i, j);
				posBbean = GetsBbean();
			}
			if (map[i][j] == 2)
			{
				SetWall(i, j);
				posWall = GetsWall();
			}
			if (map[i][j] == 3)
			{
				SetPacMan(i, j);
				posPacMan = GetsPacMan();
			}
		}
	}
	Monster0->x = 1; Monster0->y = 1;
	Monster1->x = 1; Monster1->y = 15;
	Monster2->x = 8; Monster2->y = 8;
	Monster3->x = 15; Monster3->y = 1;
	Monster4->x = 15; Monster4->y = 15;
}

// 游戏边界（这是右下，左上为0,0）
GAME_COORD boundary;

// 改变吃豆人移动的方向
void SetDirction(dirction dir)
{
	Pacman_dir = dir;
}

// 获得当前吃豆人的方向
dirction GetDirction()
{
	return Pacman_dir;
}

/*********** 内部函数申明 **************/

// 设置边界坐标
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// 获得边界坐标
PGAME_COORD GetBoundary()
{
	return &boundary;
}

//设置小豆子的坐标
void SetSbean(short x, short y)
{
	Sbean.x = x;
	Sbean.y = y;
}

//获得小豆子的坐标
PGAME_COORD GetsSbean()
{
	return &Sbean;
}

//设置能量豆的坐标
void SetBbean(short x, short y)
{
	Bbean.x = x;
	Bbean.y = y;
}

//获得能量豆的坐标
PGAME_COORD GetsBbean()
{
	return &Bbean;
}

//设置墙壁障碍物的坐标
void SetWall(short x, short y)
{
	Wall.x = x;
	Wall.y = y;
}

//获得墙壁障碍物的坐标
PGAME_COORD GetsWall()
{
	return &Wall;
}

//设置吃豆人的坐标
void SetPacMan(short x, short y)
{
	PacMan.x = x;
	PacMan.y = y;
}

//获得吃豆人的坐标
PGAME_COORD GetsPacMan()
{
	return &PacMan;
}


// 用来移动一步，
// 移动以后，如果吃到了小豆子，则豆子计分数器加一
//如果吃到能量豆，豆子计分器加十
int PacManMove()
{
	// 根据当前方向来设定新的坐标。
	switch (Pacman_dir)
	{
	case PACMAN_UP:
		posPacMan->y = posPacMan->y - 1;
		int m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                             //下一步为小豆子
		{
			posPacMan->y = posPacMan->y + 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->y = posPacMan->y - 1;
			score++;
		}
		else if (m == 1 || m == 3)                //下一步为空地或吃豆人
		{
			posPacMan->y = posPacMan->y + 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->y = posPacMan->y - 1;
		}
		else if (m == 8)                          //下一步为能量豆
		{
			posPacMan->y = posPacMan->y + 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->y = posPacMan->y - 1;
			score += 10;
		}
		else                                    //墙壁
			posPacMan->y = posPacMan->y + 1;
		break;

	case PACMAN_DOWN:
		posPacMan->y = posPacMan->y + 1;
		m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                              //下一步为小豆子
		{
			posPacMan->y = posPacMan->y - 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->y = posPacMan->y + 1;
			score++;
		}
		else if (m == 1 || m == 3)              //下一步为空地或吃豆人
		{
			posPacMan->y = posPacMan->y - 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->y = posPacMan->y + 1;
		}
		
		else if (m == 8)                        //下一步为能量豆
		{
			posPacMan->y = posPacMan->y - 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->y = posPacMan->y + 1;
			score += 10;
		}
		else                                     //墙壁
			posPacMan->y = posPacMan->y - 1;

		break;
	case PACMAN_LEFT:
		posPacMan->x = posPacMan->x - 1;
		m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                              //下一步为小豆子
		{
			posPacMan->x = posPacMan->x + 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->x = posPacMan->x - 1;
			score++;
		}
		else if (m == 1 || m == 3)               //下一步为空地或吃豆人
		{
			posPacMan->x = posPacMan->x + 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->x = posPacMan->x - 1;
		}
		else if (m == 8)                          //下一步为能量豆
		{
			posPacMan->x = posPacMan->x + 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->x = posPacMan->x - 1;
			score += 10;
		}
		else                                      //墙壁
			posPacMan->x = posPacMan->x + 1;

		break;
	case PACMAN_RIGHT:
		posPacMan->x = posPacMan->x + 1;
		m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                             //下一步为小豆子
		{
			posPacMan->x = posPacMan->x - 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->x = posPacMan->x + 1;
			score++;
		}
		else if (m == 1 || m == 3)              //下一步为空地或吃豆人
		{
			posPacMan->x = posPacMan->x - 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->x = posPacMan->x + 1;
		}
		else if (m == 8)                        //下一步为能量豆
		{
			posPacMan->x = posPacMan->x - 1;
			map[posPacMan->x][posPacMan->y] = 1;//走过的地方变为空地
			posPacMan->x = posPacMan->x + 1;
			score += 10;
			//倒计时
		}
		else                                     //墙壁
			posPacMan->x = posPacMan->x - 1;
		break;
	}
	map[posPacMan->x][posPacMan->y] = 3;        //此处变为3，代表吃豆人

	if (GetScore() == 178)
		return PACMAN_COMPLETE;
	return PACMAN_MOVED;
}

//控制怪兽随机移动一步
//若遇到墙壁则改变方向
PGAME_COORD MonsterMove(PGAME_COORD pMonster)
{
	/*map[pMonster->x][pMonster->y] = 1;*/
	//只要吃豆人在身边怪兽就就立即靠上去
	if (posPacMan->x == pMonster->x && (pMonster->y + 1) == posPacMan->y)
	{
		pMonster->y = pMonster->y + 1; Dead_flag = 1;
	}
	else if (posPacMan->x == pMonster->x && (pMonster->y - 1) == posPacMan->y)
	{
		pMonster->y = pMonster->y - 1; Dead_flag = 1;
	}
	else if (posPacMan->y == pMonster->y && (pMonster->x + 1) == posPacMan->x)
	{
		pMonster->x = pMonster->x + 1; Dead_flag = 1;
	}
	else if (posPacMan->y == pMonster->y && (pMonster->x - 1) == posPacMan->x)
	{
		pMonster->x = pMonster->x - 1; Dead_flag = 1;
	}
	else
	{
		int Mon;
	loop:
		/*srand((unsigned)time(NULL)); */ /*设置种子,并生成伪随机序列*/
		Mon = rand() % 4 + 1;//方向采取随机赋值,原则是新的方向不可以和原来的方向相反
		//if (Mon[0] == 1 && Mon[1] == 2 || Mon[0] == 2 && Mon[1] == 1)//左右
		//	goto loop;
		//if (Mon[0] == 3 && Mon[1] == 4 || Mon[0] == 4 && Mon[1] == 3)//上下
		//	goto loop;
		//Mon[1] = Mon[0];
		//四个方向
		if (Mon == 1)//方向向左
		{
			pMonster->x = pMonster->x - 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2 || a == 4)//下一步为墙壁，回到原来的地方等待随机的方向
			{
				pMonster->x = pMonster->x + 1; goto loop;
			}
			else if (a == 1 || a == 0 || a == 8)
			{
				pMonster->x = pMonster->x + 1;
				map[pMonster->x][pMonster->y] = a;
				pMonster->x = pMonster->x - 1;
			}
		}
		else if (Mon == 2)//方向向右
		{
			pMonster->x = pMonster->x + 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2||a==4)//下一步为墙壁，回到原来的地方等待随机的方向
			{
				pMonster->x = pMonster->x - 1; goto loop;
			}
			else if (a == 1 || a == 0 || a == 8 )
			{
				pMonster->x = pMonster->x - 1;
				map[pMonster->x][pMonster->y] = a;
				pMonster->x = pMonster->x + 1;
			}
		}
		else if (Mon == 3)//方向向下
		{
			pMonster->y = pMonster->y + 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2||a == 4)//下一步为墙壁
			{
				pMonster->y = pMonster->y - 1; goto loop;
			}
			else if (a == 1 || a == 0 || a == 8)
			{
				pMonster->y = pMonster->y - 1;
				map[pMonster->x][pMonster->y] = a;
				pMonster->y = pMonster->y + 1;
			}

		}
		else if (Mon == 4)//方向向上
		{
			pMonster->y = pMonster->y - 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2 || a == 4)//下一步为墙壁
			{
				pMonster->y = pMonster->y + 1; goto loop;
			}
			else if (a == 1 || a == 0 || a == 8)
			{
				pMonster->y = pMonster->y + 1;
				map[pMonster->x][pMonster->y] = a;
				pMonster->y = pMonster->y - 1;
			}
		}
	}
	map[pMonster->x][pMonster->y] = 4;

	return pMonster;
}