# -*- coding: cp936 -*-
import pygame
from pygame.locals import *
from sys import exit

#�����˳�ʼ��Path
Path=[]
for i in range(0,32):
    Path.append([])
    Path[i]=24*[0]
for j in [14,15,16,17]:
    Path[j][14]=1

#����һ�����ӵ���
class SmallBeans:
    def __init__(self,radius,beancolor,covercolor):  
        self.radius=radius
        self.beancolor=beancolor
        self.covercolor=covercolor
    #��ԭ����color��Ϊ��beancolor
    def DrawSmallBeans(self,screen):#������
        for i in range(1,31):
            for j in range(1,23):
                pygame.draw.circle(screen,self.beancolor,(10+i*20,10+j*20),self.radius)
    #����һ��Ϳ������Ķ��ӵĺ���
    def Cover(self,screen,x,y,width,hight):
        pygame.draw.rect(screen,self.covercolor,Rect((x-width/2.0,y-hight/2.0),(width,hight)))
    #���ǳԶ����߹��Ķ���
    def Coverbeans(self,screen,x0,y0,eatenbeans):  #eatenbeans������¼���Ե��Ķ�����
        Path[int((x0-10)/20)][int((y0-10)/20)]=1
        for i in range(1,32):
            for j in range(1,24):
                if Path[i][j]==1:
                    pygame.draw.rect(screen,self.covercolor,Rect((i*20,j*20),(20,20)))
                    eatenbeans=eatenbeans+1
        return eatenbeans
    
    #��������Ϸ�����ĺ���
def PrintBeans(screen,x0,y0):
    smallbeans=SmallBeans(2,(255,255,255),(0,0,0))
    smallbeans.DrawSmallBeans(screen)
    smallbeans.Cover(screen,80,70,80,60)
    smallbeans.Cover(screen,240,70,80,60)
    smallbeans.Cover(screen,400,70,80,60)
    smallbeans.Cover(screen,560,70,80,60)
    smallbeans.Cover(screen,80,410,80,60)
    smallbeans.Cover(screen,240,410,80,60)
    smallbeans.Cover(screen,400,410,80,60)
    smallbeans.Cover(screen,560,410,80,60)
    smallbeans.Cover(screen,160,110,40,140)
    smallbeans.Cover(screen,320,110,40,140)
    smallbeans.Cover(screen,480,110,40,140)
    smallbeans.Cover(screen,160,370,40,140)
    smallbeans.Cover(screen,320,370,40,140)
    smallbeans.Cover(screen,480,370,40,140)
    smallbeans.Cover(screen,70,240,60,80)
    smallbeans.Cover(screen,150,240,60,80)
    smallbeans.Cover(screen,230,240,60,80)
    smallbeans.Cover(screen,570,240,60,80)
    smallbeans.Cover(screen,490,240,60,80)
    smallbeans.Cover(screen,410,240,60,80)
    smallbeans.Cover(screen,320,250,80,90)
    smallbeans.Cover(screen,160,150,240,60)
    smallbeans.Cover(screen,480,150,240,60)
    smallbeans.Cover(screen,160,330,240,60)
    smallbeans.Cover(screen,480,330,240,60)
    numeatenbeans=smallbeans.Coverbeans(screen,x0,y0,0)
    if numeatenbeans==272:
        pygame.quit()
        exit()
        
    
    


        
    

