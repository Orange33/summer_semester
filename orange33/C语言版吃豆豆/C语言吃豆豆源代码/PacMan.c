#include <windows.h> // Windows���ڳ����̣���Ҫ����ͷ�ļ� Windows.h
#include <time.h>
#include "PacMan.h"

/*************ȫ�ֱ���****************/
//�Ե����ӵķ�������138*1+4*10=178��ʤ��
score = 0;

//������ǳԶ����Ƿ�������1Ϊ����
Dead_flag = 0;

//��ά���飬������ʾ�����ʼλ��
//0����ɫС���ӣ���138��
//8: ��ɫ����������4�ţ��Զ��˳��˺���ޱ�Ϊ��ɫ����ʱ�ɳԵ�����
//2��ǽ���ϰ������ͨ·
//3���Զ���
//4�����ޣ���5ֻ
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

GAME_COORD PacMan;//�Զ���
GAME_COORD Monster;//����
GAME_COORD Sbean;//��ɫС����
GAME_COORD Bbean;//��ɫ������
GAME_COORD Wall;//ǽ���ϰ���

PGAME_COORD posSbean;//��ɫС����
PGAME_COORD posBbean;//��ɫ������
PGAME_COORD posWall;//ǽ���ϰ���
PGAME_COORD posPacMan;//�Զ���
//PGAME_COORD posMonster[5];//����

//��ʼ��
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

// ��Ϸ�߽磨�������£�����Ϊ0,0��
GAME_COORD boundary;

// �ı�Զ����ƶ��ķ���
void SetDirction(dirction dir)
{
	Pacman_dir = dir;
}

// ��õ�ǰ�Զ��˵ķ���
dirction GetDirction()
{
	return Pacman_dir;
}

/*********** �ڲ��������� **************/

// ���ñ߽�����
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// ��ñ߽�����
PGAME_COORD GetBoundary()
{
	return &boundary;
}

//����С���ӵ�����
void SetSbean(short x, short y)
{
	Sbean.x = x;
	Sbean.y = y;
}

//���С���ӵ�����
PGAME_COORD GetsSbean()
{
	return &Sbean;
}

//����������������
void SetBbean(short x, short y)
{
	Bbean.x = x;
	Bbean.y = y;
}

//���������������
PGAME_COORD GetsBbean()
{
	return &Bbean;
}

//����ǽ���ϰ��������
void SetWall(short x, short y)
{
	Wall.x = x;
	Wall.y = y;
}

//���ǽ���ϰ��������
PGAME_COORD GetsWall()
{
	return &Wall;
}

//���óԶ��˵�����
void SetPacMan(short x, short y)
{
	PacMan.x = x;
	PacMan.y = y;
}

//��óԶ��˵�����
PGAME_COORD GetsPacMan()
{
	return &PacMan;
}


// �����ƶ�һ����
// �ƶ��Ժ�����Ե���С���ӣ����ӼƷ�������һ
//����Ե������������ӼƷ�����ʮ
int PacManMove()
{
	// ���ݵ�ǰ�������趨�µ����ꡣ
	switch (Pacman_dir)
	{
	case PACMAN_UP:
		posPacMan->y = posPacMan->y - 1;
		int m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                             //��һ��ΪС����
		{
			posPacMan->y = posPacMan->y + 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->y = posPacMan->y - 1;
			score++;
		}
		else if (m == 1 || m == 3)                //��һ��Ϊ�յػ�Զ���
		{
			posPacMan->y = posPacMan->y + 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->y = posPacMan->y - 1;
		}
		else if (m == 8)                          //��һ��Ϊ������
		{
			posPacMan->y = posPacMan->y + 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->y = posPacMan->y - 1;
			score += 10;
		}
		else                                    //ǽ��
			posPacMan->y = posPacMan->y + 1;
		break;

	case PACMAN_DOWN:
		posPacMan->y = posPacMan->y + 1;
		m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                              //��һ��ΪС����
		{
			posPacMan->y = posPacMan->y - 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->y = posPacMan->y + 1;
			score++;
		}
		else if (m == 1 || m == 3)              //��һ��Ϊ�յػ�Զ���
		{
			posPacMan->y = posPacMan->y - 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->y = posPacMan->y + 1;
		}
		
		else if (m == 8)                        //��һ��Ϊ������
		{
			posPacMan->y = posPacMan->y - 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->y = posPacMan->y + 1;
			score += 10;
		}
		else                                     //ǽ��
			posPacMan->y = posPacMan->y - 1;

		break;
	case PACMAN_LEFT:
		posPacMan->x = posPacMan->x - 1;
		m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                              //��һ��ΪС����
		{
			posPacMan->x = posPacMan->x + 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->x = posPacMan->x - 1;
			score++;
		}
		else if (m == 1 || m == 3)               //��һ��Ϊ�յػ�Զ���
		{
			posPacMan->x = posPacMan->x + 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->x = posPacMan->x - 1;
		}
		else if (m == 8)                          //��һ��Ϊ������
		{
			posPacMan->x = posPacMan->x + 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->x = posPacMan->x - 1;
			score += 10;
		}
		else                                      //ǽ��
			posPacMan->x = posPacMan->x + 1;

		break;
	case PACMAN_RIGHT:
		posPacMan->x = posPacMan->x + 1;
		m = map[posPacMan->x][posPacMan->y];
		if (m == 0)                             //��һ��ΪС����
		{
			posPacMan->x = posPacMan->x - 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->x = posPacMan->x + 1;
			score++;
		}
		else if (m == 1 || m == 3)              //��һ��Ϊ�յػ�Զ���
		{
			posPacMan->x = posPacMan->x - 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->x = posPacMan->x + 1;
		}
		else if (m == 8)                        //��һ��Ϊ������
		{
			posPacMan->x = posPacMan->x - 1;
			map[posPacMan->x][posPacMan->y] = 1;//�߹��ĵط���Ϊ�յ�
			posPacMan->x = posPacMan->x + 1;
			score += 10;
			//����ʱ
		}
		else                                     //ǽ��
			posPacMan->x = posPacMan->x - 1;
		break;
	}
	map[posPacMan->x][posPacMan->y] = 3;        //�˴���Ϊ3������Զ���

	if (GetScore() == 178)
		return PACMAN_COMPLETE;
	return PACMAN_MOVED;
}

//���ƹ�������ƶ�һ��
//������ǽ����ı䷽��
PGAME_COORD MonsterMove(PGAME_COORD pMonster)
{
	/*map[pMonster->x][pMonster->y] = 1;*/
	//ֻҪ�Զ�������߹��޾;���������ȥ
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
		/*srand((unsigned)time(NULL)); */ /*��������,������α�������*/
		Mon = rand() % 4 + 1;//�����ȡ�����ֵ,ԭ�����µķ��򲻿��Ժ�ԭ���ķ����෴
		//if (Mon[0] == 1 && Mon[1] == 2 || Mon[0] == 2 && Mon[1] == 1)//����
		//	goto loop;
		//if (Mon[0] == 3 && Mon[1] == 4 || Mon[0] == 4 && Mon[1] == 3)//����
		//	goto loop;
		//Mon[1] = Mon[0];
		//�ĸ�����
		if (Mon == 1)//��������
		{
			pMonster->x = pMonster->x - 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2 || a == 4)//��һ��Ϊǽ�ڣ��ص�ԭ���ĵط��ȴ�����ķ���
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
		else if (Mon == 2)//��������
		{
			pMonster->x = pMonster->x + 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2||a==4)//��һ��Ϊǽ�ڣ��ص�ԭ���ĵط��ȴ�����ķ���
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
		else if (Mon == 3)//��������
		{
			pMonster->y = pMonster->y + 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2||a == 4)//��һ��Ϊǽ��
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
		else if (Mon == 4)//��������
		{
			pMonster->y = pMonster->y - 1;
			int a = map[pMonster->x][pMonster->y];
			if (a == 2 || a == 4)//��һ��Ϊǽ��
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