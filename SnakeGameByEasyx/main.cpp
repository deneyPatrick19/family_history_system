#include "Game.h"
#include "Graph.h"

int main() 
{
	/*设置时间种子*/
	srand(time(NULL));
	InitGraph();
	
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
				case WM_LBUTTONDOWN:
					if (msg.x > 350 && msg.x < 550 && msg.y < 320 && msg.y > 260)
					{
						Game();
						closegraph();
						InitGraph();
						break;
					}
					else if (msg.x > 350 && msg.x < 550 && msg.y < 390 && msg.y > 330)
					{
						closegraph();
						InitGraph();
						break;
					}
					else if (msg.x > 350 && msg.x < 550 && msg.y < 460 && msg.y > 400)
					{
						closegraph();
						return 0;
					}
					break;
				default :
					break;
			}
		}
	}

	return 0;
}
void InitGraph()
{
	//初始化图形界面
	initgraph(600, 600, 0);
	/*设置背景颜色*/
	setbkcolor(RGB(210,255,220));
	/*设置背景为透明*/
	setbkmode(TRANSPARENT);
	cleardevice();
	
	//载入图片
	IMAGE picture;
	loadimage(&picture, "kn91ibvmir.jpg", 600, 600);
	putimage(0, 0, &picture);
	
	settextcolor(0);
	settextstyle(70, 32, "Ink Free");
	outtextxy(280, 65, "Snake Game");
	
	setlinecolor(WHITE);
	setfillcolor(LIGHTGRAY);
	fillrectangle(350, 260, 550, 320);
	fillrectangle(350, 330, 550, 390);
	fillrectangle(350, 400, 550, 460);
	
	settextstyle(0, 0, "Ink Free");
	outtextxy(380, 280, "START GAME");
	outtextxy(380, 350, "RECORD");
	outtextxy(380, 420, "EXIT GAME");
}