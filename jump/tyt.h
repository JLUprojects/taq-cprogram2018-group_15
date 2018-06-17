#pragma once //一个比较常用的c/c++ 杂注  在头文件最开头加上就可以保证头文件只被编译一次


#include <stdio.h>
#include <stdlib.h>
#include <graphics.h> //绘图库
#include <time.h>
#include <conio.h>//conio是Console Input/Output（控制台输入输出）的简写，其中定义了通过控制台进行数据输入和数据输出的函数，主要是一些用户通过按键盘产生的对应操作，比如getch()函数等等。
#include <math.h>
#include <mmsystem.h>//windows里和多媒体接入有关
#include <windows.h>

//库文件
#pragma comment(lib,"winmm.lib")

//全局函数
class Man;
class Brick;
void welcome();
void drawbrick(int x, int width, int& red, int& green, int& blue, int& width0, Brick& brick);
void init(Man& man, int& red, int& green, int& blue, int& width0, Brick& brick);
void jump(int j, int& judge2, int& width0, int& red, int& green, int& blue, Man& man, Brick& brick);
void end(Man& man);
void game(int& judge2, int& width0, int& red, int& green, int& blue, Man& man, Brick& brick);
void save(Man& man);
void move(Man& man, Brick& brick, int& red, int& green, int& blue, int& width0);
bool gameover();
void star(int a);
int judge();
void sort(int a[], int n);
void read();
void createOneDimensionalVector();
void outfile();

//结构体
typedef struct Man
{
	int grade;
	int x, y;
	bool survival;//bool型变量，只有yes和no
	IMAGE fm;//class IMAGE 自定义图形对象，系统定义的结构体
};

typedef struct Brick
{
	int x;
	int width;
};


#define PI 3.1415926
#define KEY_DOWN(VK_NONAME) ((GetAsayncKeyState(VK_NONAME) & 0x8000) ? 1:0) //用来检测鼠标