#include "Game.h"

#define ROWS 400	//高度像素数
#define COLS 600	//宽度像素数

//位置
typedef struct position{
	int x;
	int y;
}pos;

//蛇 结构体
struct snake
{
	pos position[(ROWS/10) * (COLS / 10)];
	int size;
	int direction;
}Snake;

//食物 结构体
struct food{
	pos position;
	int flag;
}Food;

//方向枚举
enum direction
{
	RIGHT,LEFT,UP,DOWN,SPACE
};

/*速度*/
int sleepsec = 320;

/*分数*/
int score = 0;

/*难度*/
int level = 1;

/*按下按键得到的坐标值*/
int kx = 0;
int ky = 0;

/*分数及等级的字符串形式*/
char scores[4];
char levels[2];


void Game()
{
	score = 0;
	kx = 0;
	ky = 0;
	sleepsec = 320;
	
	//开始双缓冲
	BeginBatchDraw();
	InitSnake();
	GenerateFood();
	while(1)
	{
		if (PlayGame() == -1)
		{
			break;
		}
		Sleep(sleepsec);
	}
	GameOver();
	EndBatchDraw();				//结束双缓冲
	_getch();
}

/*蛇的初始化*/
void InitSnake()
{
	Snake.size = 2;				//长度为2
	
	Snake.position[0].x = COLS/2;    	//初始蛇头
	Snake.position[0].y = ROWS/2;
	
	Snake.position[1].x = COLS/2 - 10; 	//初始一个蛇身 蛇身向右
	Snake.position[1].y = ROWS/2;
	
	Snake.direction = RIGHT;
}

/*生成食物*/
void GenerateFood()
{
	int i;
	int numOfFood = 0;
	
	int number1, number2;
	
	while (1)
	{
		numOfFood = 0;
		number1 = rand() % (COLS/10 -1);	//随机产生x坐标
		number2 = rand() % (ROWS/10 -1);	//随机产生y坐标
		
		for (i = 0;i < Snake.size; i++)
		{
			if (Snake.position[i].x == number1*10 && Snake.position[i].y == number2*10)
			{
				numOfFood++;
			}
		}
		
		if (numOfFood == 0)
		{
			Food.position.x = number1 * 10;
			Food.position.y = number2 * 10;
			break;
		}
	}
}

/*画蛇和食物 并显示分数和等级*/
void Draw()
{
	int i;
	
	cleardevice();
	
	setlinecolor(WHITE);
	
	//蛇 蛇头为绿色 蛇身为红色
	setfillcolor(GREEN);
	fillrectangle(Snake.position[0].x, Snake.position[0].y, Snake.position[0].x+10, Snake.position[0].y+10);
	setfillcolor(RED);
	for (i = 1; i < Snake.size; i++)
	{	
		fillrectangle(Snake.position[i].x, Snake.position[i].y, Snake.position[i].x+10, Snake.position[i].y+10);
	}
	
	//食物
	setfillcolor(BLACK);
	fillrectangle(Food.position.x, Food.position.y, Food.position.x+10, Food.position.y+10);
	
	/*显示分数及等级*/
	setlinecolor(RED);
	line(0, 400, 600, 400);

	/*将分数及等级转化为字符串*/
	strcpy(scores,itoa(score, scores, 10));
	strcpy(levels,itoa(level, levels, 10));
	
	/*打印分数等级*/
	settextcolor(RED);
	settextstyle(0, 0, "Courier New");
	outtextxy(40, 420, "Your Score: ");
	outtextxy(40, 450, "Level: ");
	settextcolor(0);
	outtextxy(40 + textwidth("Your Score: "), 420, scores);
	outtextxy(40 + textwidth("Level: "), 450, levels);
	FlushBatchDraw();		//显示一帧
}

void GameOver()
{
	int i;
	
	cleardevice();


	//蛇 蛇头为绿色 蛇身为红色
	setfillcolor(GREEN);
	fillrectangle(Snake.position[0].x, Snake.position[0].y, Snake.position[0].x+10, Snake.position[0].y+10);
	setfillcolor(RED);
	for (i = 1; i < Snake.size; i++)
	{	
		fillrectangle(Snake.position[i].x, Snake.position[i].y, Snake.position[i].x+10, Snake.position[i].y+10);
	}
	
	//食物
	setfillcolor(BLACK);
	fillrectangle(Food.position.x, Food.position.y, Food.position.x+10, Food.position.y+10);
	
	/*显示分数及等级*/
	setlinecolor(RED);
	line(0, 400, 600, 400);

	/*将分数及等级转化为字符串*/
	strcpy(scores,itoa(score, scores, 10));
	strcpy(levels,itoa(level, levels, 10));
	
	/*打印分数等级*/
	settextcolor(RED);
	settextstyle(0, 0, "Courier New");
	outtextxy(40 , 420, "Game Over!  Your Final Score:");
	outtextxy(40 + textwidth("Game Over!  Your Final Score:"), 420, scores);
	
	FlushBatchDraw();		//显示一帧
}

int PlayGame()
{
	
	int i = 0;
	
	/*判断是否撞墙*/
	if (! (Snake.position[0].x < COLS && Snake.position[0].x >= 0 && Snake.position[0].y < ROWS && Snake.position[0].y >= 0) ) 
	{
		return -1;
	}
	
	/*画蛇和食物 并显示分数和等级*/
	Draw();
	
	/*检测用户方向输入 改变方向*/
	UserKey();
	
	/*方向判断*/
	switch (Snake.direction)
	{
		//蛇头坐标根据用户按键修改
		case UP:
			kx = 0;
			ky = -10;
			break;
		case DOWN:
			kx = 0;
			ky = 10;
			break;
		case LEFT:
			kx = -10;
			ky = 0;
			break;
		case RIGHT:
			kx = 10;
			ky = 0;
			break;
		default:
			break;
	}
	
	//蛇撞身体 蛇头坐标和任意一节身体的坐标完全一致
	for (i = 1; i < Snake.size; i++)
	{
		if (Snake.position[0].x == Snake.position[i].x && Snake.position[0].y  == Snake.position[i].y)
		{
			return -1;      //游戏结束
		}
	}		
	
	//蛇头撞食物
	if (Snake.position[0].x == Food.position.x && Snake.position[0].y == Food.position.y)
	{
		//食物消失
		GenerateFood();
		//身体增长
		Snake.size++;
		//分数增加
		score += 1;
		//加速
		if (score < 20 && score >= 0)
		{
			sleepsec = 320;
			level = 1;
		}
		else if (score < 35 && score >= 20)
		{
			sleepsec = 250;
			level = 2;
		}
		else if (score < 45 && score >= 35)
		{
			sleepsec = 160;
			level = 3;
		}
		else
		{
			sleepsec = 100;
			level = 4;
		}
	}
	
	/*
	蛇身体移动 坐标转化 后面跟着前面
	蛇前一节身体给后一节身体赋值
	*/
	for (i = Snake.size-1; i > 0; i--)
	{
		Snake.position[i].x = Snake.position[i - 1].x;
		Snake.position[i].y = Snake.position[i - 1].y;
	}
	
	//蛇头坐标根据用户按键修改
	Snake.position[0].x += kx;
	Snake.position[0].y += ky;
		
	return 0;
}

/*输入方向*/
void UserKey()
{
	char key;
	
	if (kbhit())		//检测是否有按键按下
	{
		key = getch();
	}
	switch (key)
	{
		case 'W':
		case 'w':
		case 72:
			if (Snake.direction != DOWN)
			{
				Snake.direction = UP;
			}
			break;
		case 'S':
		case 's':
		case 80:
			if (Snake.direction != UP)
			{
				Snake.direction = DOWN;
			}
			break;
		case 'A':
		case 'a':
		case 75:
			if (Snake.direction != RIGHT)
			{
				Snake.direction = LEFT;
			}
			break;
		case 'D':
		case 'd':
		case 77:
			if (Snake.direction != LEFT)
			{
				Snake.direction = RIGHT;
			}
			break;
		case 32:
			while (getch() != 32);
			break;
		default: 
			break;
	}
}

