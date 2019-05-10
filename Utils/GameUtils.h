//
// Created by Borealin on 2019/5/9.
//

#ifndef BIGWORKC_GAMEUTILS_H
#define BIGWORKC_GAMEUTILS_H

#include <DrawUtils.h>

#define NORMAL_DOWN 1
#define ACCELRATE_DOWN 2
#define SPEEDUP 3
double DownSpeed;
Tetromino current;
Tetromino next;
int Score;
int ScoreAdd[5];
int Level;

void KeyboardEventProcess(int key, int event);/*键盘消息回调函数*/

void MouseEventProcess(int x, int y, int button, int event);

void TimerEventProcess(int timerID);

void NewRound();

#endif //BIGWORKC_GAMEUTILS_H
