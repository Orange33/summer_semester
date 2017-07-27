import pygame
from pygame.locals import *
from Puzzle import *
from sys import exit

#创建一个吃豆人的类
class Pac:
    def __init__(self,x,y,direct):#初始化
        self.direct = direct      #方向
        self.x = x
        self.y = y

    def CreatePacMan(self,screen,i):#创建吃豆人，实现嘴的动态效果
        pygame.draw.circle(screen,(255,255,0),(self.x,self.y),10)
        
        #通过i的值控制吃豆人的动态效果，当i=1时嘴张大，i=0时嘴变小
        if i == 1:
            if self.direct == 1:
                pygame.draw.polygon(screen,(0,0,0),((self.x-10,self.y-5),(self.x-10,self.y+5),(self.x,self.y)))
            elif self.direct == 2:
                pygame.draw.polygon(screen,(0,0,0),((self.x-5,self.y-10),(self.x+5,self.y-10),(self.x,self.y)))
            elif self.direct == 3:
                pygame.draw.polygon(screen,(0,0,0),((self.x+10,self.y-5),(self.x+10,self.y+5),(self.x,self.y)))
            elif self.direct == 4:
                pygame.draw.polygon(screen,(0,0,0),((self.x-5,self.y+10),(self.x+5,self.y+10),(self.x,self.y)))
        else:
            if self.direct == 1:
                pygame.draw.polygon(screen,(0,0,0),((self.x-10,self.y-2),(self.x-10,self.y+2),(self.x,self.y)))
            elif self.direct == 2:
                pygame.draw.polygon(screen,(0,0,0),((self.x-2,self.y-10),(self.x+2,self.y-10),(self.x,self.y)))
            elif self.direct == 3:
                pygame.draw.polygon(screen,(0,0,0),((self.x+10,self.y-2),(self.x+10,self.y+2),(self.x,self.y)))
            elif self.direct == 4:
                pygame.draw.polygon(screen,(0,0,0),((self.x-2,self.y+10),(self.x+2,self.y+10),(self.x,self.y)))

    def Move(self):#吃豆人的移动
        if self.direct == 4:
                if (self.x-10,self.y+10) in Up:
                    self.y += 0
                else: self.y += 10
        elif self.direct == 2:
                if (self.x-10,self.y-30) in Down:
                    self.y -= 0
                else: self.y -= 10
        elif self.direct == 3:
                if (self.x+10,self.y-10) in Left:
                    self.x += 0
                else: self.x += 10
        elif self.direct == 1:
                if (self.x-30,self.y-10) in Right:
                    self.x -= 0
                else: self.x -= 10
        return self.x,self.y

    def GetPosition(self):#得到吃豆人当前的坐标
        return self.x,self.y

    def Turn(self):#键盘按下上下左右键控制移动方向
        pressed_keys = pygame.key.get_pressed()
        if pressed_keys[K_LEFT]:
            self.direct = 1
        elif pressed_keys[K_UP]:
            self.direct = 2
        elif pressed_keys[K_RIGHT]:
            self.direct = 3
        elif pressed_keys[K_DOWN]:
            self.direct = 4
        return self.direct
    
    def CoverPac(self,x0,y0,screen):#覆盖吃豆人走过的地方
            pygame.draw.rect(screen,(0,0,0),Rect((x0,y0-10),(20,20)))
            pygame.draw.rect(screen,(0,0,0),Rect((x0-10,y0),(20,20)))

def PrintPacman(screen,pac,x,y,direct,i):#画吃豆人
    direct = pac.Turn()
    x,y = pac.Move()
    pac = Pac(x,y,direct)
    pac.CreatePacMan(screen,i)

