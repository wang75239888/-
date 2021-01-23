#include<stdio.h>
#include<graphics.h> //图形库的头文件 安装easyX插件
#include<conio.h>
#include<time.h>
#include<mmsystem.h>//多媒体头文件
#pragma comment(lib,"winmm.lib")

HWND hwnd; //窗口句柄

//定义分数
int score = 0;

int arr[4] = { 0 };
//初始化一维数组
void initArr()
{
	//随机函数种子
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 4; i++)
	{
		arr[i] = rand() % 4;//随机生成一维数组的元素:伪随机：每次随机结果都一样
	}
}

//绘制地图
void drawMap()
{
	setlinestyle(PS_SOLID, 2);
	//设置线的颜色
	setlinecolor(BLACK);
	//画线 5+5=10
	for (int i=0;i<5;i++)
	{
		//画横线
		line(0, 100 + i * 200, 400, 100 + i * 200);
		//画竖线
		line(i * 100, 100, i * 100, 900);
	}
	//画黑块:填充矩形
	for (int i = 0; i < 4; i++)
	{
		setfillcolor(BLACK);
		int x = arr[i] * 100;
		int y = 100 + i * 200;
		fillrectangle(x, y, x + 100, y + 200);
	}
}
//游戏过程：鼠标操作
void playGame()
{

	int flag = 0;

	//定义鼠标消息变量
	MOUSEMSG m;
	while (1)
	{
		settextstyle(26, 0, "宋体");
		//设置字体颜色
		settextcolor(RGB(51, 201, 255));
		//文字输出
		outtextxy(120, 10, "别踩白块");

		//获取鼠标消息
		m = GetMouseMsg();

		switch (m.uMsg)//判断鼠标当前消息
		{
		case WM_LBUTTONDOWN:

			int x = arr[3] * 100;
			int y = 700;
			//动起来的条件
			if (m.x > x && m.x<x + 100 && m.y>y && m.y < y + 200)
			{
				cleardevice();
				//整体移动
				for (int i = 3; i >= 1; i--)
				{
					arr[i] = arr[i - 1];
				}
				arr[0] = rand() % 4;

				score += 10;//分数增加
				drawMap();
			}
			//点击了白块：游戏结束
			else
			{
				flag = 1;

				//显示分数：格式化sprintf
				char grade[20] = "";
				sprintf_s(grade, "分数：%d分",score);
				outtextxy(50, 50, grade);

				break;
			}
			break;
		}
		if (flag == 1)
		{
			mciSendString("close M", 0, 0, 0);
			MessageBox(hwnd, "你踩白块了，游戏结束！", "gameOver!",MB_OK);
			break;
		}
	}
}

int main()
{
	//初始化图形环境
	initgraph(400,900);       //创建图形窗口(宽高)
	//设置背景的颜色
	setbkcolor(WHITE);
	cleardevice();			//清屏

	mciSendString("open 每当我走过老师的窗前.mp3 alias M", 0, 0, 0);
	mciSendString("play M repeat", 0, 0, 0);
	initArr();
	drawMap();
	playGame();
	_getch();
	//while (1);              //卡屏
	closegraph();
	return 0;
}
