#include "tyt.h"

int main()
{
	int red, green, blue;
	int width0;
	int judge2;
	Man man;
	Brick brick;

	welcome();
	RESTART://停止所有程序段的执行、关闭所有窗口、提交事务、断开与数据库的连接，然后重新启动应用程序。
	init(man,red,green,blue,width0,brick);

	while (1)
	{
		game(judge2,width0,red,green,blue,man,brick);

		if (man.survival)
		{	
			if (judge2 == 1)
			{
				move(man,brick,red,green,blue,width0);
			}

		}
		else
		{
			save(man);

			end(man);

			outfile();

			if (gameover())
			{
				return 0;
			}
			else
			{
				goto RESTART;
			}
		}
	}

	return 0;
}

int judge()
{
	int judge0 = 1;
	MOUSEMSG mouse;

	if (MouseHit())      //开始游戏的链接，判断鼠标是否在这里按下
	{
		mouse = GetMouseMsg();
		if (mouse.x > 363 && mouse.x < 443 && mouse.y > 415 && mouse.y < 495 && mouse.uMsg == WM_LBUTTONDOWN)
		{
			judge0 = 0;
		}
	}

	return judge0;
}

void star(int a)           //画唐敖庆班的标志星星
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 10);
	POINT pts1[] = { { a+50, 200 },{ a+140, 180 },{ a+180, 90 },{ a+220,180 },{ a+310,200 },{ a+235,250 },{ a+270,340 },{ a+180,295 },{ a+90,340 },{ a+125,250 } };
	polygon(pts1, 10);
	POINT pts2[] = { { a+120, 160 },{ a+240, 160 },{ a+260, 255 },{ a+180,320 },{ a+100,255 } };
	polygon(pts2, 5);

	setlinecolor(getpixel(100, 100));//获取坐标（100,100）点的颜色作为线的颜色
	line(a+136, 165, a+155, 125);//a存在的意义是方便移动
	line(a+228, 172, a+270, 181);
	line(a+249, 260, a+284, 350);
	line(a+113, 253, a+88, 238);

	settextstyle(62, 0, TEXT("黑体"));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(360, 197, TEXT("TAQ"));
}

void welcome()
{
	int a=0;
	IMAGE img2;

	initgraph(800, 600);//初始化一个绘图窗口
	setbkcolor(RGB(245, 253, 251));
	srand((unsigned int)time(NULL));//随机数种子
	mciSendString(TEXT("open ./res/猫叫.mp3 alias music0"), 0, 0, 0);//打开音乐文件 并将音乐文件命名为music
	mciSendString("play music0", 0, 0, 0);
	//cleardevice();//用当前背景色清空屏幕，并将当前点移至 (0, 0)
	
	loadimage(NULL, "res\\哈哈.jpg",800,600);
	star(227);

	loadimage(&img2, "res\\222.jpg",300,300);
	setfillstyle(BS_DIBPATTERN, NULL, &img2);//BS_DIBPATTERN,自定义图像填充
	solidcircle(403, 455, 40);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(20, 120, 90));
	settextstyle(20, 0, TEXT("黑体"));
	outtextxy(380, 450, TEXT("START"));
	settextstyle(50, 0, TEXT("幼圆"));
	outtextxy(330, 360, TEXT("跳一跳"));
	
	while (judge())//让程序不继续往下运行，直到有鼠标左键按下,没有实际意义
	{
		a += 1;
	}
	
	cleardevice();

	for (int i = 0;i < 20;i++)
	{
		settextstyle(40, 0, TEXT("幼圆"));
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		outtextxy(160,250, TEXT("据说优秀的泥萌 能永生不死"));
		Sleep(100);
		cleardevice();
	}
	
	setfillstyle(NULL);//把之前设置过的style改成初始或期望状态
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 1);
	setlinecolor(BLACK);
	mciSendString("close music0", 0, 0, 0);
	FlushMouseMsgBuffer();
}

void drawbrick(int x, int width, int& red, int& green, int& blue,int& width0,Brick& brick)
{
	//画砖，随机颜色
	if (rand() % 7 == 0)
	{
		red = 255;
		green = 0;
		blue = 0;
	}
	else
	{
		red = rand() % 256;
		green = rand() % 255 + 1;
		blue = rand() % 255 + 1;
	}

	width0 = brick.width;
	setfillcolor(RGB(red, green, blue));
	solidrectangle(x, 350, x + width, 399);
	brick.x = x;
	brick.width = width;
}

void init(Man& man,int& red,int& green,int& blue,int& width0,Brick& brick)
{
	loadimage(NULL, "res\\w.jpg", 800, 600); 
	mciSendString(TEXT("open ./res/夜曲.mp3 alias music"), 0, 0, 0);       //BGM
	mciSendString("play music repeat", NULL, 0, NULL);
	man.grade = 0;
	man.x = 50;
	man.y = 300;
	man.survival = true;
	loadimage(&man.fm , TEXT("./res/熊.jpg"), 50, 50);
	putimage(50, 300, &man.fm);//输出后小人占据（50~100，300~350）

	line(0, 400, 799, 400);
	drawbrick(50, 50,red,green,blue,width0,brick);
	drawbrick(400, 50, red, green, blue, width0, brick);

	settextcolor(BLACK);
	settextstyle(20, 0, TEXT("幼圆"));
	outtextxy(450, 470, TEXT("Grades:"));
	char s[5];//把整型转化为字符型数组输出
	sprintf(s, "%d", man.grade);
	outtextxy(550, 470, s);
}

void jump(int j,int& judge2,int& width0,int& red,int& green,int& blue,Man& man,Brick& brick)
{
	int p = man.x  + j / 2;//p是抛物线跳跃过程的重点横坐标
	int m = j / 3;//m为最高点的值，决定抛物线的高度
	int x, y;
	loadimage(&man.fm, TEXT("./res/熊.jpg"), 50, 50);

	for (int i = 0; i < 50; i++)//实现抛物线跳跃
	{
		x = p + (-(j/2) * cos(PI * 2 * i / 98));
		y = 300 + (-m * sin(PI * 2 * i / 98));

		setfillcolor(getpixel(100, 100));
		solidrectangle(man.x, man.y, man.x + 50, man.y + 49);//在人的位置画一个填充矩形，注意49
		man.x = x;//把瞬时跳跃结束的位置看做小人新的位置
		man.y = y;//把瞬时跳跃结束的位置看做小人新的位置
		putimage(x, y, &man.fm);
		Sleep(25);
	}
	
	judge2 = 1;

	if (man.x > brick.x - 50 && man.x < brick.x + brick.width)            //bonus部分，跳在方块正中间，正中间偏一点，方块边缘有不同加分，红色方块有额外加分
	{
		if (man.x + 25 > brick.x + brick.width / 2 - 15 && man.x +25< brick.x + brick.width / 2 + 15)
		{
			if (man.x + 25 > brick.x + brick.width / 2 - 10 && man.x+25 < brick.x + brick.width / 2 + 10)
			{
				if (red == 255 && green == 0 && blue == 0)
				{
					man.grade += 20;
				}
				else
				{
					man.grade += 5;
				}
			}
			else
			{
				if (red == 255 && green == 0 && blue == 0)
				{
					man.grade += 15;
				}
				else
				{
					man.grade += 3;
				}
			}
		}
		else
		{
			if (red == 255 && green == 0 && blue == 0)
			{
				man.grade += 10;
			}
			else
			{
				man.grade += 1;
			}
		}
		
	}
	else
	{
		if (man.x < 50 + width0)
		{
			judge2 = 0;
		}
		else
		{
			for (int i = 0; i < 50; i++)
			{
				setfillcolor(getpixel(100, 100));
				solidrectangle(man.x, man.y, man.x + 50, man.y + 50);
				man.y += 1;
				putimage(man.x, man.y, &man.fm);
				Sleep(25);
			}
			man.survival = false;
		}
	}
}

DWORD time1()                          //核心部分，鼠标的按键计时
{
	DWORD t1, t2;
	MOUSEMSG mouse;
	while (1) 
	{
		mouse = GetMouseMsg();

		switch (mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
			t1 = timeGetTime();
			mciSendString(TEXT("open ./res/音乐2.mp3 alias music2"), 0, 0, 0); //增加了按键音效，降低游戏难度
			mciSendString("play music2", 0, 0, 0);
			break;
		case WM_LBUTTONUP:
			t2 = timeGetTime();
			mciSendString("close music2", 0, 0, 0);
			if (t2 - t1 >100) 
			        {   
				if (t2-t1<5000)
					return t2 - t1;
				else
					return 0;
				   }
			else
				break;
		}
	}
}

void end(Man& man)
{
	cleardevice();//清屏

	TCHAR ch[20];
	_stprintf(ch, _T("最终成绩为：%d"), man.grade);
	settextstyle(50, 0, TEXT("幼圆"));
	settextcolor(RGB(100, 120, 120));
	outtextxy(250, 250, ch);
	//settextstyle(25, 0, TEXT("幼圆"));
	mciSendString("close music", 0, 0, 0);
	if (man.grade >= 20)                         //角色死亡播放音乐，看分数高低播放不同的音乐
	{
		mciSendString(TEXT("open ./res/鼓掌.mp3 alias music3"), 0, 0, 0);
	}
	else
	{
		mciSendString(TEXT("open ./res/加油.mp3 alias music3"), 0, 0, 0);
	}
	mciSendString("play music3", 0, 0, 0);

	Sleep(3500);
	mciSendString("close music3", 0, 0, 0);
}

void move(Man& man,Brick& brick,int& red,int& green,int& blue,int& width0)
{	
	int p, q;
	IMAGE sm1;
	setfillcolor(getpixel(100, 100));
	solidrectangle(550, 470, 595, 490);//挡分数
	getimage(&sm1,0,100,800,301);//注意301，给游戏区域截图，后面移动这个图片实现整个部分的左移
	
	settextstyle(20, 0, TEXT("幼圆"));
	outtextxy(450, 470, TEXT("Grades:"));
	char s[5];
	sprintf(s, "%d", man.grade);
	outtextxy(550, 470, s);
	
	for (int i = brick.x ; i > 50; i--)//此时brick.x是第二块板的横坐标，最终把第二块砖移到x=50的位置，就是第一块砖的位置
	{
		man.x--;//保证小人是从相对原砖不变的位置作为起跳点挑起的
		putimage(i - brick.x,100, &sm1);// 将sm1对象显示在绘图窗口中，实现板的左移 坐标还可以是负的
		line(0, 400, 799, 400);
		Sleep(1);
	}
	
	q = 200 + (rand() % 300);
	p = 50 + (rand() % 75);
	drawbrick(q, p, red, green, blue, width0, brick);
}

void game(int& judge2,int& width0,int& red,int& green,int& blue,Man& man,Brick& brick)
{
	int st;
	st = (time1() / 5);               //时间变量转换为长度变量
	jump(st,judge2,width0,red,green,blue,man,brick);
}

bool gameover()
{
	char gameovertext[256];

	sprintf(gameovertext, "Game Over\n(Yes to Retry,No to Exit)");

	if (MessageBox(GetHWnd(), gameovertext, "Game Over", MB_YESNO) == IDYES)//显示一个模态对话框，消息框中返回一个整数值，该值指示用户单击了哪个按钮
	{                                                                       
		return false;
	}
	else
	{
		return true;
	}
}

void save(Man& man)                 //保存本次游戏分数，at表示接着txt文件里的内容保存
{
	FILE *fp;

	fp = fopen("rank.txt", "at");
	if (!fp)
		return;

	fprintf(fp, "%d\n", man.grade);
}

void createOneDimensionalVector()
{
	int n, i;
	int *arr;
	scanf_s("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		arr[i] = i;
	for (i = 0; i < n; i++)
		printf("%d\t", arr[i]);
}

void read()
{
	FILE *fp;//文件指针  
	char ch;
	if ((fp = fopen("rank.txt", "r")) == NULL)//文件的路径  
	{
		printf("Can not open this file!\n");//找不到文件时结束
		exit(0);
	}
	ch = fgetc(fp);//获取文件中的字符  
	fclose(fp);//关闭文件 
}

void outfile()
{
	int k = 1;//行数，最后一行结束时不进入循环，所以初值为1  
	FILE *fp;//文件指针  
	if ((fp = fopen("rank.txt", "r")) == NULL)//文件的路径  
	{
		printf("Can not open this file!\n");//找不到文件时结束 
		exit(0);
	}
	int c;
	while ((c = fgetc(fp)) != EOF)//获取文件总行数  
	{
		if (c == '\n')//文件到达换行符时行数加1  
		{
			k++;
		}
	}
	fclose(fp);
	FILE *fp1;//文件指针  
	if ((fp1 = fopen("rank.txt", "r")) == NULL)//文件的路径  
	{
		printf("Can not open this file!\n");//找不到文件时结束 
		exit(0);
	}

	//int i, a[k];

	int i;
	int *arr;
	arr = (int*)malloc(sizeof(int)*k);
	for (i = 0; !feof(fp); i++)//判断是否到达文件末尾  
	{
		fscanf_s(fp, "%d", &arr[i]);
	}
	fclose(fp1);
	sort(arr, k);

	char paihangbang[256];
	sprintf(paihangbang, "排行榜:\n %d\n %d\n %d\n %d\n %d\n OK to continue", arr[0], arr[1], arr[2], arr[3], arr[4]);
	MessageBox(GetHWnd(), paihangbang, "排行榜", MB_OK);
}

void sort(int a[], int n)
{
	int i, j, temp;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (a[j] < a[j + 1])//交换数据  
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}


}
