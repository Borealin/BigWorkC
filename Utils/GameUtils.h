//
// Created by B on 2019/5/9.
//

#ifndef BIGWORKC_GAMEUTILS_H
#define BIGWORKC_GAMEUTILS_H

#include <DrawUtils.h>
#include <ListUtils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned int uint;

#define NORMAL_DOWN 1
#define ACCELRATE_DOWN 2
#define STOPREFRESH 3

typedef enum{
    MOVE_LEFT = 0,
    MOVE_RIGHT,
    SPIN,
    FALL,
    SPEED_UP_FALL,
    FALL_TO_BOTTOM,
    SWITCH_HOLD,
    SAVE,
    LOAD,
    NEW_GAME,
    CONTINUE,
    EXIT,
    PAUSE,
    RESUME,
    ABOUT,
    HELP,
    ENABLE_HOLD,
    DISABLE_HOLD,
    NEW_ROUND,
    LEVEL_UP,
    LEVEL_DOWN,
    GAME_OVER,
}MessageTypes;

char* MessageStr[30];

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
int AllClearedLayer;
int ShowAbout;
int ShowHelp;
char StatusBarBuff[100];

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

void PauseTimer();

void ResumeTimer();

void UpdateLevel(int count);

void ResetDownTimer();

void RefreshDisplay();

void LogStatusBar(MessageTypes MessageType);

#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
void init_by_array(unsigned long init_key[], int key_length);
uint randuint(uint a,uint b);
#endif //BIGWORKC_GAMEUTILS_H
