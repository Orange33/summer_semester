import pygame
from pygame.locals import *
global Up
global Down
global Left
global Right
Up=[]
Down=[]
Left=[]
Right=[]


#创建一个长方形类
class Rectangle:
    def __init__(self,n,m,d,dir):#初始化
        self.n=n
        self.m=m
        self.d=d
        self.dir=dir
    def Print(self,screen):#画图
        if self.dir==1 :
            self.a=self.n*2*self.d
            self.b=self.m*2*self.d
            self.w=2*self.d
            self.h=self.d
            pygame.draw.rect(screen,(255,255,255),Rect(self.a,self.b,self.w,self.h))
            Up.append((self.n*2*self.d,self.m*2*self.d))
            Up.append(((self.n*2+1)*self.d,self.m*2*self.d))
            Up.append(((self.n*2-1)*self.d,self.m*2*self.d))
            return Up
        elif self.dir==2 :
            self.a=self.n*2*self.d
            self.b=(2*self.m+1)*self.d
            self.w=2*self.d
            self.h=self.d
            pygame.draw.rect(screen,(255,255,255),Rect(self.a,self.b,self.w,self.h))
            Down.append((self.n*2*self.d,self.m*2*self.d))
            Down.append(((self.n*2+1)*self.d,self.m*2*self.d))
            Down.append(((self.n*2-1)*self.d,self.m*2*self.d))
            return Down
        elif self.dir==3 :
            self.a=self.n*2*self.d
            self.b=self.m*2*self.d
            self.w=self.d
            self.h=2*self.d
            pygame.draw.rect(screen,(255,255,255),Rect(self.a,self.b,self.w,self.h))
            Left.append((self.n*2*self.d,self.m*2*self.d))
            Left.append((self.n*2*self.d,(self.m*2+1)*self.d))
            Left.append((self.n*2*self.d,(self.m*2-1)*self.d))
            return Left
        elif self.dir==4 :
            self.a=(2*self.n+1)*self.d
            self.b=self.m*2*self.d
            self.w=self.d
            self.h=2*self.d
            pygame.draw.rect(screen,(255,255,255),Rect(self.a,self.b,self.w,self.h))
            Right.append((self.n*2*self.d,self.m*2*self.d))
            Right.append((self.n*2*self.d,(self.m*2+1)*self.d))
            Right.append((self.n*2*self.d,(self.m*2-1)*self.d))
            return Right

#创建一个圆形类
class Circle:
    def __init__(self,n,m,d,dir):#初始化
        self.n=n
        self.m=m
        self.d=d
        self.dir=dir
    def Print(self,screen):#画图
        if self.dir==1 :
            self.center=((self.n+1)*2*self.d,(self.m+1)*2*self.d)
            self.r=self.d
            self.a=(self.n+1)*2*self.d
            self.b=(self.m+1)*2*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a,self.b,self.w,self.h))    
        elif self.dir==2 :
            self.center=(self.n*2*self.d,(self.m+1)*2*self.d)
            self.r=self.d
            self.a=(self.n*2-1)*self.d
            self.b=(self.m+1)*2*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a,self.b,self.w,self.h))   
        elif self.dir==3 :
            self.center=((self.n+1)*2*self.d,self.m*2*self.d)
            self.r=self.d
            self.a=(self.n+1)*2*self.d
            self.b=(self.m*2-1)*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a,self.b,self.w,self.h))
        elif self.dir==4 :
            self.center=(self.n*2*self.d,self.m*2*self.d)
            self.r=self.d
            self.a=(self.n*2-1)*self.d
            self.b=(self.m*2-1)*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a,self.b,self.w,self.h))

#再创建一个圆形类
class Circle1:
    def __init__(self,n,m,d,dir):#初始化
        self.n=n
        self.m=m
        self.d=d
        self.dir=dir
    def Print(self,screen):#画图
        if self.dir==1 :
            self.center=((2*self.n+1)*self.d,(2*self.m+1)*self.d)
            self.r=self.d
            self.a1=(2*self.n+1)*self.d
            self.b1=(2*self.m+1)*self.d
            self.a2=(2*self.n+1)*self.d
            self.b2=self.m*2*self.d
            self.a3=self.n*2*self.d
            self.b3=(2*self.m+1)*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a1,self.b1,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a2,self.b2,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a3,self.b3,self.w,self.h))
            Up.append((self.n*2*self.d,self.m*2*self.d))
            Up.append(((self.n*2+1)*self.d,self.m*2*self.d))
            Up.append(((self.n*2-1)*self.d,self.m*2*self.d))
            Left.append((self.n*2*self.d,self.m*2*self.d))
            Left.append((self.n*2*self.d,(self.m*2+1)*self.d))
            Left.append((self.n*2*self.d,(self.m*2-1)*self.d))
            return Up,Left
        elif self.dir==2 :
            self.center=((2*self.n+1)*self.d,(2*self.m+1)*self.d)
            self.r=self.d
            self.a1=self.n*2*self.d
            self.b1=(2*self.m+1)*self.d
            self.a2=self.n*2*self.d
            self.b2=self.m*2*self.d
            self.a3=(2*self.n+1)*self.d
            self.b3=(2*self.m+1)*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a1,self.b1,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a2,self.b2,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a3,self.b3,self.w,self.h))
            Up.append((self.n*2*self.d,self.m*2*self.d))
            Up.append(((self.n*2+1)*self.d,self.m*2*self.d))
            Up.append(((self.n*2-1)*self.d,self.m*2*self.d))
            Right.append((self.n*2*self.d,self.m*2*self.d))
            Right.append((self.n*2*self.d,(self.m*2+1)*self.d))
            Right.append((self.n*2*self.d,(self.m*2-1)*self.d))
            return Up,Right
        elif self.dir==3 :
            self.center=((2*self.n+1)*self.d,(2*self.m+1)*self.d)
            self.r=self.d
            self.a1=(self.n*2+1)*self.d
            self.b1=self.m*2*self.d
            self.a2=self.n*2*self.d
            self.b2=self.m*2*self.d
            self.a3=(self.n*2+1)*self.d
            self.b3=(self.m*2+1)*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a1,self.b1,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a2,self.b2,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a3,self.b3,self.w,self.h))
            Left.append((self.n*2*self.d,self.m*2*self.d))
            Left.append((self.n*2*self.d,(self.m*2+1)*self.d))
            Left.append((self.n*2*self.d,(self.m*2-1)*self.d))
            Down.append((self.n*2*self.d,self.m*2*self.d))
            Down.append(((self.n*2+1)*self.d,self.m*2*self.d))
            Down.append(((self.n*2-1)*self.d,self.m*2*self.d))
            return Left,Down 
        elif self.dir==4 :
            self.center=((2*self.n+1)*self.d,(2*self.m+1)*self.d)
            self.r=self.d
            self.a1=self.n*2*self.d
            self.b1=self.m*2*self.d
            self.a2=(self.n*2+1)*self.d
            self.b2=self.m*2*self.d
            self.a3=self.n*2*self.d
            self.b3=(self.m*2+1)*self.d
            self.w=self.d
            self.h=self.d
            pygame.draw.circle(screen,(255,255,255),self.center,self.r)
            pygame.draw.rect(screen,(0,0,0),Rect(self.a1,self.b1,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a2,self.b2,self.w,self.h))
            pygame.draw.rect(screen,(255,255,255),Rect(self.a3,self.b3,self.w,self.h))
            Right.append((self.n*2*self.d,self.m*2*self.d))
            Right.append((self.n*2*self.d,(self.m*2+1)*self.d))
            Right.append((self.n*2*self.d,(self.m*2-1)*self.d))
            Down.append((self.n*2*self.d,self.m*2*self.d))
            Down.append(((self.n*2+1)*self.d,self.m*2*self.d))
            Down.append(((self.n*2-1)*self.d,self.m*2*self.d))
            return Right,Down

#将迷宫地图显示在窗口中
def PrintPuzzle(screen):
            part1=Circle(0,0,10,1)
            part1.Print(screen)
            for i in range(1,31):
                part2=Rectangle(i,0,10,2)
                part2.Print(screen)
            part3=Circle(31,0,10,2)
            part3.Print(screen)
            for i in range(1,23):
                part4=Rectangle(31,i,10,3)
                part4.Print(screen)
            part5=Circle(31,23,10,4)
            part5.Print(screen)
            for i in range(1,31):
                part6=Rectangle(i,23,10,1)
                part6.Print(screen)
            part7=Circle(0,23,10,3)
            part7.Print(screen)
            for i in range(1,23):
                part8=Rectangle(0,i,10,4)
                part8.Print(screen)
            for c in [0,8,16,24]:
                for d in [0,17]:
                    part9=Circle1(2+c,2+d,10,1)
                    part9.Print(screen)
                    for i in range(3,5):
                        part10=Rectangle(i+c,2+d,10,1)
                        part10.Print(screen)
                    part11=Circle1(5+c,2+d,10,2)
                    part11.Print(screen)
                    part12=Rectangle(5+c,3+d,10,4)
                    part12.Print(screen)
                    part13=Circle1(5+c,4+d,10,4)
                    part13.Print(screen)
                    for i in range(3,5):
                        part14=Rectangle(i+c,4+d,10,2)
                        part14.Print(screen)
                    part15=Circle1(2+c,4+d,10,3)
                    part15.Print(screen)
                    part16=Rectangle(2+c,3+d,10,3)
                    part16.Print(screen)

            for d in [0,13]:
                    part17=Circle1(15,2+d,10,1)
                    part17.Print(screen)
                    part18=Circle1(16,2+d,10,2)
                    part18.Print(screen)
                    for i in range(3,8):
                        part20=Rectangle(16,i+d,10,4)
                        part20.Print(screen)
                    part20=Circle1(16,8+d,10,4)
                    part20.Print(screen)
                    part21=Circle1(15,8+d,10,3)
                    part21.Print(screen)
                    for i in range(3,8):
                        part22=Rectangle(15,i+d,10,3)
                        part22.Print(screen)

            for c in [0,16]:
                    part23=Circle1(7+c,2,10,1)
                    part23.Print(screen)
                    part24=Circle1(8+c,2,10,2)
                    part24.Print(screen)
                    for i in range(3,6):
                        part25=Rectangle(8+c,i,10,4)
                        part25.Print(screen)
                    part26=Circle(8+c,6,10,3)
                    part26.Print(screen)
                    for i in range(9,13):
                        part27=Rectangle(i+c,6,10,1)
                        part27.Print(screen)
                    part28=Circle1(13+c,6,10,2)
                    part28.Print(screen)
                    part29=Rectangle(13+c,7,10,4)
                    part29.Print(screen)
                    part30=Circle1(13+c,8,10,4)
                    part30.Print(screen)
                    for i in range(3,13):
                        part31=Rectangle(i+c,8,10,2)
                        part31.Print(screen)
                    part32=Circle1(2+c,8,10,3)
                    part32.Print(screen)
                    part33=Rectangle(2+c,7,10,3)
                    part33.Print(screen)
                    part34=Circle1(2+c,6,10,1)
                    part34.Print(screen)
                    for i in range(3,7):
                        part35=Rectangle(i+c,6,10,1)
                        part35.Print(screen)
                    part36=Circle(7+c,6,10,4)
                    part36.Print(screen)
                    for i in range(3,6):
                        part37=Rectangle(7+c,i,10,3)
                        part37.Print(screen)
                        
                    part38=Circle1(14,10,10,1)
                    part38.Print(screen)
                    part39=Circle1(17,10,10,2)
                    part39.Print(screen)
                    for i in range(11,13):
                        part40=Rectangle(17,i,10,4)
                        part40.Print(screen)
                    part41=Circle1(17,13,10,4)
                    part41.Print(screen)
                    for i in range(15,17):
                        part41=Rectangle(i,13,10,2)
                        part41.Print(screen)
                    part42=Circle1(14,13,10,3)
                    part42.Print(screen)
                    for i in range(11,13):
                        part43=Rectangle(14,i,10,3)
                        part43.Print(screen)
                    for i in range(30,34):
                        part68=Rectangle(i,20,5,1)
                        part68.Print(screen)

            for c in [0,16]:
                    part44=Circle1(2+c,15,10,1)
                    part44.Print(screen)
                    for i in range(3,13):
                        part45=Rectangle(i+c,15,10,1)
                        part45.Print(screen)
                    part46=Circle1(13+c,15,10,2)
                    part46.Print(screen)
                    part47=Rectangle(13+c,16,10,4)
                    part47.Print(screen)
                    part48=Circle1(13+c,17,10,4)
                    part48.Print(screen)
                    for i in range(9,13):
                        part49=Rectangle(i+c,17,10,2)
                        part49.Print(screen)
                    part50=Circle(8+c,17,10,1)
                    part50.Print(screen)
                    for i in range(18,21):
                        part51=Rectangle(8+c,i,10,4)
                        part51.Print(screen)
                    part52=Circle1(8+c,21,10,4)
                    part52.Print(screen)
                    part53=Circle1(7+c,21,10,3)
                    part53.Print(screen)
                    for i in range(18,21):
                        part54=Rectangle(7+c,i,10,3)
                        part54.Print(screen)
                    part55=Circle(7+c,17,10,2)
                    part55.Print(screen)
                    for i in range(3,7):
                        part56=Rectangle(i+c,17,10,2)
                        part56.Print(screen)
                    part57=Circle1(2+c,17,10,3)
                    part57.Print(screen)
                    part58=Rectangle(2+c,16,10,3)
                    part58.Print(screen)
                    part59=Circle1(2+c,15,10,1)
                    part59.Print(screen)

            for c in [0,4,8,17,21,25]:
                    part60=Circle1(2+c,10,10,1)
                    part60.Print(screen)
                    part61=Rectangle(3+c,10,10,1)
                    part61.Print(screen)
                    part62=Circle1(4+c,10,10,2)
                    part62.Print(screen)
                    for i in range(11,13):
                        part63=Rectangle(4+c,i,10,4)
                        part63.Print(screen)
                    part64=Circle1(4+c,13,10,4)
                    part64.Print(screen)
                    part65=Rectangle(3+c,13,10,2)
                    part65.Print(screen)
                    part66=Circle1(2+c,13,10,3)
                    part66.Print(screen)
                    for i in range(11,13):
                        part67=Rectangle(2+c,i,10,3)
                        part67.Print(screen)

