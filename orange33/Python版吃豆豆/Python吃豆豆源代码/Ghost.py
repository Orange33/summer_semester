import pygame
from pygame.locals import *

#定义怪兽的颜色
GhostColor = {0:(229,0,0), 1:(0,76,229), 2:(255,153,0), 3:(25,191,178), 4:(250,105,18), 5:(102,33,232)}
#怪兽的路径
GhostPath=[]
for i in range(0,32):
    GhostPath.append([])
    GhostPath[i] = 24 * [0]
for i in range(12):
    GhostPath[0][i] = 1
for i in range(16):
    GhostPath[i][0] = 1
for i in [2,3,4,5,7,8,10,11,12,13,15]:
    GhostPath[i][0] = 1
    GhostPath[i][2] = 1
    GhostPath[i][3] = 1
    GhostPath[i][4] = 1
for i in [7,8,15]:
    GhostPath[i][5] = 1
for i in [2,3,4,5,6,7,8,9,10,11,12,13,15]:
    GhostPath[i][6] = 1
    GhostPath[i][7] = 1
    GhostPath[i][8] = 1
for i in [2,3,4,5,6,7,8,10,11,12,14,15]:
    GhostPath[i][10] = 1
    GhostPath[i][11] = 1
for i in range(12):
    for j in range(16):
        GhostPath[j][23-i] = GhostPath[j][i]
for i in range(16):
    for j in range(24):
        GhostPath[31-i][j] = GhostPath[i][j]

#定义一个怪兽类 
class Ghost:
    def __init__(self,i,j,pointlist,color,directghost):#初始化
        self.x = i
        self.y = j
        self.pointlist = pointlist
        self.color = color
        self.directghost = directghost

    def DrawGhost(self,screen):#画怪兽
        pygame.draw.polygon(screen,self.color,self.pointlist)
        if self.directghost == 3:
            pygame.draw.circle(screen,(255,255,255),(-4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(255,255,255),(4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(0,0,0),(-4+self.x*20+10+1,-2+self.y*20+10),2)
            pygame.draw.circle(screen,(0,0,0),(4+self.x*20+10+1,-2+self.y*20+10),2)
        elif self.directghost == 1:
            pygame.draw.circle(screen,(255,255,255),(-4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(255,255,255),(4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(0,0,0),(-4+self.x*20+10-1,-2+self.y*20+10),2)
            pygame.draw.circle(screen,(0,0,0),(4+self.x*20+10-1,-2+self.y*20+10),2)
        elif self.directghost == 2:
            pygame.draw.circle(screen,(255,255,255),(-4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(255,255,255),(4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(0,0,0),(-4+self.x*20+10,-2+self.y*20+10-1),2)
            pygame.draw.circle(screen,(0,0,0),(4+self.x*20+10,-2+self.y*20+10-1),2)
        elif self.directghost == 4:
            pygame.draw.circle(screen,(255,255,255),(-4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(255,255,255),(4+self.x*20+10,-2+self.y*20+10),3)
            pygame.draw.circle(screen,(0,0,0),(-4+self.x*20+10,-2+self.y*20+10+1),2)
            pygame.draw.circle(screen,(0,0,0),(4+self.x*20+10,-2+self.y*20+10+1),2)

    def GetPosition(self):#得到怪兽坐标
        return self.x,self.y

    def CoverGhost(self,a0,b0,screen):#覆盖怪兽已经走过的地方
        pygame.draw.rect(screen,(0,0,0),Rect((a0*20,b0*20),(20,20)))

    def PossibleTurn(self,c,d):#怪兽下一步可走的方向
        PossibleTurnList = []
        if GhostPath[c+1][d] == 0:
            PossibleTurnList.append(3)
        if GhostPath[c-1][d] == 0:
            PossibleTurnList.append(1)
        if GhostPath[c][d-1] == 0:
            PossibleTurnList.append(2)
        if GhostPath[c][d+1] == 0:
            PossibleTurnList.append(4)
        return PossibleTurnList

    def Move(self,directghost):#怪兽移动
        if directghost == 4:
            self.y += 1
        elif directghost == 2:
            self.y -= 1
        elif directghost == 3:
            self.x += 1
        elif directghost == 1:
            self.x -= 1
        return self.x,self.y
