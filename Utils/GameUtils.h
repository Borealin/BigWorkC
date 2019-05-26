//
// Created by Borealin on 2019/5/9.
//

#ifndef BIGWORKC_GAMEUTILS_H
#define BIGWORKC_GAMEUTILS_H

#include <DrawUtils.h>
#include <ListUtils.h>

#define NORMAL_DOWN 1
#define ACCELRATE_DOWN 2
#define SPEEDUP 3
#define STOPREFRESH 4


double DownSpeed;

int TetrominoMap[12][22];
Tetromino current;
Tetromino next;
Tetromino hold;

ListNodePtr RankList;
char Name[NAMELENGTH];
int Score;
int ScoreAdd[5];
int Level;
int IsStop;
int IsPause;
int CanHold;
int InitPage;
int CanContinue;

void KeyboardEventProcess(int key, int event);/*键盘消息回调函数*/

void MouseEventProcess(int x, int y, int button, int event);

void CharEventProcess(char ch);

void TimerEventProcess(int timerID);

void NewRound();

void UpdateRank();

void GamePause();

void GameResume();

void GameContinue();

void GameExit(int save);

#endif //BIGWORKC_GAMEUTILS_H
