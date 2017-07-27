import pygame
from pygame.locals import *

#from time import sleep
#from sys import stdout

from sys import exit
from Puzzle import *
from Beans import *
from Ghost import *
from Pac import *

pac = Pac(290,290,3)
direct = 3
x,y = 290,290
x0,y0=0,0
#怪兽1
a1,b1 = 16,11
directghost1 = 2
ghost1 = Ghost(a1,b1,[(0+a1*20+10,3.75+b1*20+10),
                   (3.57+a1*20+10,9.38+b1*20+10),
                   (7.14+a1*20+10,3.75+b1*20+10),
                   (9.71+a1*20+10,9.38+b1*20+10),
                   (9.71+a1*20+10,-6.25+b1*20+10),
                   (7.14+a1*20+10,-9.38+b1*20+10),
                   (-7.14+a1*20+10,-9.38+b1*20+10),
                   (-9.71+a1*20+10,-6.25+b1*20+10),
                   (-9.71+a1*20+10,9.38+b1*20+10),
                   (-7.14+a1*20+10,3.75+b1*20+10),
                   (-3.57+a1*20+10,9.38+b1*20+10)],GhostColor[0],2)
#怪兽2
a2,b2 = 16,12
directghost2 = 2
ghost2 = Ghost(a2,b2,[(0+a2*20+10,3.75+b2*20+10),
                   (3.57+a2*20+10,9.38+b2*20+10),
                   (7.14+a2*20+10,3.75+b2*20+10),
                   (9.71+a2*20+10,9.38+b2*20+10),
                   (9.71+a2*20+10,-6.25+b2*20+10),
                   (7.14+a2*20+10,-9.38+b2*20+10),
                   (-7.14+a2*20+10,-9.38+b2*20+10),
                   (-9.71+a2*20+10,-6.25+b2*20+10),
                   (-9.71+a2*20+10,9.38+b2*20+10),
                   (-7.14+a2*20+10,3.75+b2*20+10),
                   (-3.57+a2*20+10,9.38+b2*20+10)],GhostColor[1],2)
#怪兽3
a3,b3 = 15,11
directghost3 = 2
ghost3 = Ghost(a3,b3,[(0+a3*20+10,3.75+b3*20+10),
                   (3.57+a3*20+10,9.38+b3*20+10),
                   (7.14+a3*20+10,3.75+b3*20+10),
                   (9.71+a3*20+10,9.38+b3*20+10),
                   (9.71+a3*20+10,-6.25+b3*20+10),
                   (7.14+a3*20+10,-9.38+b3*20+10),
                   (-7.14+a3*20+10,-9.38+b3*20+10),
                   (-9.71+a3*20+10,-6.25+b3*20+10),
                   (-9.71+a3*20+10,9.38+b3*20+10),
                   (-7.14+a3*20+10,3.75+b3*20+10),
                   (-3.57+a3*20+10,9.38+b3*20+10)],GhostColor[2],2)
#怪兽4
a4,b4 = 15,12
directghost4 = 2
ghost4 = Ghost(a4,b4,[(0+a4*20+10,3.75+b4*20+10),
                   (3.57+a4*20+10,9.38+b4*20+10),
                   (7.14+a4*20+10,3.75+b4*20+10),
                   (9.71+a4*20+10,9.38+b4*20+10),
                   (9.71+a4*20+10,-6.25+b4*20+10),
                   (7.14+a4*20+10,-9.38+b4*20+10),
                   (-7.14+a4*20+10,-9.38+b4*20+10),
                   (-9.71+a4*20+10,-6.25+b4*20+10),
                   (-9.71+a4*20+10,9.38+b4*20+10),
                   (-7.14+a4*20+10,3.75+b4*20+10),
                   (-3.57+a4*20+10,9.38+b4*20+10)],GhostColor[3],2)


m = 0
n = 0
o = 0
p = 0
q = 0
i = 1



#游戏初始化
pygame.init()
screen = pygame.display.set_mode((640,480),0,32)#设置窗口大小
while True:
    for event in pygame.event.get():
        if event.type == QUIT:#终止游戏
            pygame.quit()
            exit()
        elif event.type == KEYDOWN:#按下键盘
                direct = pac.Turn()
    m += 1
    n += 1
    o += 1
    p += 1
    q += 1

    #2
    #四只怪兽的方向
    a01,b01 = ghost1.GetPosition()
    a02,b02 = ghost2.GetPosition()
    a03,b03 = ghost3.GetPosition()
    a04,b04 = ghost4.GetPosition()

    #吃豆人的方向
    x,y = pac.GetPosition()

    #实现怪兽的追踪
    if m > 25000:
        m = 0
        if n > 75000:
            n = 0

            #怪兽1
            PossibleTurnList1 = ghost1.PossibleTurn(a01,b01)
            if ((a1 < x/20) and (3 in PossibleTurnList1)) == 1:  #吃豆人在怪兽左边
                directghost1 = 3                   #方向向左
            elif ((b1 < y/20) and (4 in PossibleTurnList1)) == 1:#吃豆人在怪兽上方
                directghost1 = 4                    #方向向上
            elif ((a1 > x/20) and (1 in PossibleTurnList1)) == 1:#吃豆人在怪兽右边
                directghost1 = 1                    #方向向右
            elif ((b1 > y/20) and (2 in PossibleTurnList1)) == 1:#吃豆人在怪兽下方
                directghost1 = 2                    #方向向下
            a1,b1 = ghost1.Move(directghost1)                    #怪兽移动
            ghost1 = Ghost(a1,b1,[(0+a1*20+10,3.75+b1*20+10),#怪兽每移动一步就要调用一次怪兽的类中的相应函数
                   (3.57+a1*20+10,9.38+b1*20+10),
                   (7.14+a1*20+10,3.75+b1*20+10),
                   (9.71+a1*20+10,9.38+b1*20+10),
                   (9.71+a1*20+10,-6.25+b1*20+10),
                   (7.14+a1*20+10,-9.38+b1*20+10),
                   (-7.14+a1*20+10,-9.38+b1*20+10),
                   (-9.71+a1*20+10,-6.25+b1*20+10),
                   (-9.71+a1*20+10,9.38+b1*20+10),
                   (-7.14+a1*20+10,3.75+b1*20+10),
                   (-3.57+a1*20+10,9.38+b1*20+10)],GhostColor[0],directghost1)
            ghost1.CoverGhost(a01,b01,screen)

            #怪兽2
            PossibleTurnList2 = ghost2.PossibleTurn(a02,b02)
            if ((a2 < x/20) and (3 in PossibleTurnList2)) == 1:
                directghost2 = 3
            elif ((b2 < y/20) and (4 in PossibleTurnList2)) == 1:
                directghost2 = 4
            elif ((a2 > x/20) and (1 in PossibleTurnList2)) == 1:
                directghost2 = 1
            elif ((b2 > y/20) and (2 in PossibleTurnList2)) == 1:
                directghost2 = 2
            if o > 1000000:
                a2,b2 = ghost2.Move(directghost2)
                if (a2,b2) == (a1,b1):#若怪兽1与怪兽2相遇，怪兽2坐标变为（1,1）
                    a2,b2 = 1,1
            ghost2 = Ghost(a2,b2,[(0+a2*20+10,3.75+b2*20+10),
                   (3.57+a2*20+10,9.38+b2*20+10),
                   (7.14+a2*20+10,3.75+b2*20+10),
                   (9.71+a2*20+10,9.38+b2*20+10),
                   (9.71+a2*20+10,-6.25+b2*20+10),
                   (7.14+a2*20+10,-9.38+b2*20+10),
                   (-7.14+a2*20+10,-9.38+b2*20+10),
                   (-9.71+a2*20+10,-6.25+b2*20+10),
                   (-9.71+a2*20+10,9.38+b2*20+10),
                   (-7.14+a2*20+10,3.75+b2*20+10),
                   (-3.57+a2*20+10,9.38+b2*20+10)],GhostColor[1],directghost2)
            ghost2.CoverGhost(a02,b02,screen)
            
            #怪兽3
            PossibleTurnList3 = ghost3.PossibleTurn(a03,b03)
            if ((a3 < x/20) and (3 in PossibleTurnList3)) == 1:
                directghost3 = 3
            elif ((b3 < y/20) and (4 in PossibleTurnList3)) == 1:
                directghost3 = 4
            elif ((a3 > x/20) and (1 in PossibleTurnList3)) == 1:
                directghost3 = 1
            elif ((b3 > y/20) and (2 in PossibleTurnList3)) == 1:
                directghost3 = 2
            if p > 2000000:
                a3,b3 = ghost3.Move(directghost3)
                if (a3,b3) == (a1,b1):#若怪兽1与怪兽3相遇，怪兽3坐标变为（1,1）
                    a3,b3 = 1,1
                elif (a3,b3) == (a2,b2):#若怪兽2与怪兽3相遇，怪兽3坐标变为（1,1）
                    a3,b3 = 1,1
            ghost3 = Ghost(a3,b3,[(0+a3*20+10,3.75+b3*20+10),
                   (3.57+a3*20+10,9.38+b3*20+10),
                   (7.14+a3*20+10,3.75+b3*20+10),
                   (9.71+a3*20+10,9.38+b3*20+10),
                   (9.71+a3*20+10,-6.25+b3*20+10),
                   (7.14+a3*20+10,-9.38+b3*20+10),
                   (-7.14+a3*20+10,-9.38+b3*20+10),
                   (-9.71+a3*20+10,-6.25+b3*20+10),
                   (-9.71+a3*20+10,9.38+b3*20+10),
                   (-7.14+a3*20+10,3.75+b3*20+10),
                   (-3.57+a3*20+10,9.38+b3*20+10)],GhostColor[2],directghost3)
            ghost3.CoverGhost(a03,b03,screen)

            #怪兽4
            PossibleTurnList4 = ghost4.PossibleTurn(a04,b04)
            if ((a4 < x/20) and (3 in PossibleTurnList4)) == 1:
                directghost4 = 3
            elif ((b4 < y/20) and (4 in PossibleTurnList4)) == 1:
                directghost4 = 4
            elif ((a4 > x/20) and (1 in PossibleTurnList4)) == 1:
                directghost4 = 1
            elif ((b4 > y/20) and (2 in PossibleTurnList4)) == 1:
                directghost4 = 2
            if q > 3000000:
                a4,b4 = ghost4.Move(directghost4)
                if (a4,b4) == (a1,b1):#若怪兽1与怪兽4相遇，怪兽4坐标变为（1,1）
                    a4,b4 = 1,1
                elif (a4,b4) == (a2,b2):#若怪兽2与怪兽3相遇，怪兽4坐标变为（1,1）
                    a4,b4 = 1,1
                elif (a4,b4) == (a3,b3):#若怪兽3与怪兽4相遇，怪兽4坐标变为（1,1）
                    a4,b4 = 1,1
            ghost4 = Ghost(a4,b4,[(0+a4*20+10,3.75+b4*20+10),
                   (3.57+a4*20+10,9.38+b4*20+10),
                   (7.14+a4*20+10,3.75+b4*20+10),
                   (9.71+a4*20+10,9.38+b4*20+10),
                   (9.71+a4*20+10,-6.25+b4*20+10),
                   (7.14+a4*20+10,-9.38+b4*20+10),
                   (-7.14+a4*20+10,-9.38+b4*20+10),
                   (-9.71+a4*20+10,-6.25+b4*20+10),
                   (-9.71+a4*20+10,9.38+b4*20+10),
                   (-7.14+a4*20+10,3.75+b4*20+10),
                   (-3.57+a4*20+10,9.38+b4*20+10)],GhostColor[3],directghost4)
            ghost4.CoverGhost(a04,b04,screen)
        
        
        pac.CoverPac(x0,y0,screen)#覆盖吃豆人走过的位置
        PrintBeans(screen,x0,y0)  #画豆子
        PrintPuzzle(screen)       #画地图

        #吃豆人嘴的动态效果
        if  i <= 1:           #嘴张大
            PrintPacman(screen,pac,x,y,direct,i)
        else:
            i = 0             #嘴变小
            PrintPacman(screen,pac,x,y,direct,i)
        i += 1         #关键语句
        x0,y0=pac.GetPosition()
        
        #4
        #画怪兽
        ghost1.DrawGhost(screen)
        ghost2.DrawGhost(screen)
        ghost3.DrawGhost(screen)
        ghost4.DrawGhost(screen)

        #5
        #判断吃豆人与怪兽是否相遇，相遇则游戏失败，终止游戏
        if (((a1*20-x+10)*(a1*20-x+10)) <1) and (((b1*20-y+10)*(b1*20-y+10)) <1) == 1:
            pygame.quit()
            exit()
        if (((a2*20-x+10)*(a2*20-x+10)) <1) and (((b2*20-y+10)*(b2*20-y+10)) <1) == 1:
            pygame.quit()
            exit()
        if (((a3*20-x+10)*(a3*20-x+10)) <1) and (((b3*20-y+10)*(b3*20-y+10)) <1) == 1:
            pygame.quit()
            exit()
        if (((a4*20-x+10)*(a4*20-x+10)) <1) and (((b4*20-y+10)*(b4*20-y+10)) <1) == 1:
            pygame.quit()
            exit()

        #更新画面
        pygame.display.update()
