#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

/*函数声明*/
void Game();
void InitSnake();
void GenerateFood();
void Draw();
void GameOver();
int PlayGame();
void UserKey();

#endif
