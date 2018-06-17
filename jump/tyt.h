#pragma once //һ���Ƚϳ��õ�c/c++ ��ע  ��ͷ�ļ��ͷ���ϾͿ��Ա�֤ͷ�ļ�ֻ������һ��


#include <stdio.h>
#include <stdlib.h>
#include <graphics.h> //��ͼ��
#include <time.h>
#include <conio.h>//conio��Console Input/Output������̨����������ļ�д�����ж�����ͨ������̨���������������������ĺ�������Ҫ��һЩ�û�ͨ�������̲����Ķ�Ӧ����������getch()�����ȵȡ�
#include <math.h>
#include <mmsystem.h>//windows��Ͷ�ý������й�
#include <windows.h>

//���ļ�
#pragma comment(lib,"winmm.lib")

//ȫ�ֺ���
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

//�ṹ��
typedef struct Man
{
	int grade;
	int x, y;
	bool survival;//bool�ͱ�����ֻ��yes��no
	IMAGE fm;//class IMAGE �Զ���ͼ�ζ���ϵͳ����Ľṹ��
};

typedef struct Brick
{
	int x;
	int width;
};


#define PI 3.1415926
#define KEY_DOWN(VK_NONAME) ((GetAsayncKeyState(VK_NONAME) & 0x8000) ? 1:0) //����������