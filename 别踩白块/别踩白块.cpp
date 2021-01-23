#include<stdio.h>
#include<graphics.h> //ͼ�ο��ͷ�ļ� ��װeasyX���
#include<conio.h>
#include<time.h>
#include<mmsystem.h>//��ý��ͷ�ļ�
#pragma comment(lib,"winmm.lib")

HWND hwnd; //���ھ��

//�������
int score = 0;

int arr[4] = { 0 };
//��ʼ��һά����
void initArr()
{
	//�����������
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 4; i++)
	{
		arr[i] = rand() % 4;//�������һά�����Ԫ��:α�����ÿ����������һ��
	}
}

//���Ƶ�ͼ
void drawMap()
{
	setlinestyle(PS_SOLID, 2);
	//�����ߵ���ɫ
	setlinecolor(BLACK);
	//���� 5+5=10
	for (int i=0;i<5;i++)
	{
		//������
		line(0, 100 + i * 200, 400, 100 + i * 200);
		//������
		line(i * 100, 100, i * 100, 900);
	}
	//���ڿ�:������
	for (int i = 0; i < 4; i++)
	{
		setfillcolor(BLACK);
		int x = arr[i] * 100;
		int y = 100 + i * 200;
		fillrectangle(x, y, x + 100, y + 200);
	}
}
//��Ϸ���̣�������
void playGame()
{

	int flag = 0;

	//���������Ϣ����
	MOUSEMSG m;
	while (1)
	{
		settextstyle(26, 0, "����");
		//����������ɫ
		settextcolor(RGB(51, 201, 255));
		//�������
		outtextxy(120, 10, "��Ȱ׿�");

		//��ȡ�����Ϣ
		m = GetMouseMsg();

		switch (m.uMsg)//�ж���굱ǰ��Ϣ
		{
		case WM_LBUTTONDOWN:

			int x = arr[3] * 100;
			int y = 700;
			//������������
			if (m.x > x && m.x<x + 100 && m.y>y && m.y < y + 200)
			{
				cleardevice();
				//�����ƶ�
				for (int i = 3; i >= 1; i--)
				{
					arr[i] = arr[i - 1];
				}
				arr[0] = rand() % 4;

				score += 10;//��������
				drawMap();
			}
			//����˰׿飺��Ϸ����
			else
			{
				flag = 1;

				//��ʾ��������ʽ��sprintf
				char grade[20] = "";
				sprintf_s(grade, "������%d��",score);
				outtextxy(50, 50, grade);

				break;
			}
			break;
		}
		if (flag == 1)
		{
			mciSendString("close M", 0, 0, 0);
			MessageBox(hwnd, "��Ȱ׿��ˣ���Ϸ������", "gameOver!",MB_OK);
			break;
		}
	}
}

int main()
{
	//��ʼ��ͼ�λ���
	initgraph(400,900);       //����ͼ�δ���(���)
	//���ñ�������ɫ
	setbkcolor(WHITE);
	cleardevice();			//����

	mciSendString("open ÿ�����߹���ʦ�Ĵ�ǰ.mp3 alias M", 0, 0, 0);
	mciSendString("play M repeat", 0, 0, 0);
	initArr();
	drawMap();
	playGame();
	_getch();
	//while (1);              //����
	closegraph();
	return 0;
}
