//
// Created by Borealin on 2019/5/9.
//
#include <graphics.h>
#include <imgui.h>
#include <DrawUtils.h>
#include <extgraph.h>
#include <windows.h>
#include <random.h>
#include <JudgeUtils.h>
#include <GameUtils.h>
#include <ListUtils.h>

ListNodePtr RankList;

int accel = 0;

int stop = 0;

double DownSpeed = 600;

Tetromino current = {12, 20, 0, 1};
Tetromino next = {21, 16, 0, 1};

char Name[NAMELENGTH];

int Score;
int ScoreAdd[5] = {
        10, 100, 200, 400, 800
};
int Level;

void RefreshCurrent();

void RefreshDisplay();

void DisplayClear(void);

void DrawResult();

void KeyboardEventProcess(int key, int event)/*每当产生键盘消息，都要执行*/
{
    uiGetKeyboard(key,event);
    switch (event) {
        case KEY_DOWN:
            if (!stop) {
                switch (key) {
                    case VK_SPACE:
                        while (JudgeBorder(current, 3)) {
                            current.y--;
                        }
                        current.y++;
                        RefreshDisplay();
                        if (JudgeGameOver(current)) {
                            cancelTimer(NORMAL_DOWN);
                            cancelTimer(ACCELRATE_DOWN);
                            cancelTimer(SPEEDUP);
                            stop = 1;
                            RefreshDisplay();
                            DrawGameOver();
                            return;
                        }
                        RefreshCurrent();
                        RefreshDisplay();
                        break;
                    case VK_DOWN:
                        if (!accel) {
                            accel = 1;
                            cancelTimer(NORMAL_DOWN);
                            startTimer(ACCELRATE_DOWN, 60);
                            RefreshDisplay();
                        }
                        break;
                    case VK_RIGHT:
                        current.x++;
                        if (!JudgeBorder(current, 2)) {
                            current.x--;
                        }
                        RefreshDisplay();
                        break;
                    case VK_LEFT:
                        current.x--;
                        if (!JudgeBorder(current, 0)) {
                            current.x++;
                        }
                        RefreshDisplay();
                        break;
                    case VK_UP:
                        current.direction = (current.direction + 1) % 4;
                        if (!JudgeBorder(current, 1)) {
                            current.direction = ((current.direction - 1) % 4 + 4) % 4;
                        }
                        RefreshDisplay();
                        break;
                    case VK_ESCAPE:
                        break;
                    default:
                        break;
                }
            }
            break;
        case KEY_UP:
            if (!stop) {
                switch (key) {
                    case VK_DOWN:
                        if (accel) {
                            accel = 0;
                            cancelTimer(ACCELRATE_DOWN);
                            startTimer(NORMAL_DOWN, (int) DownSpeed);
                        }
                        RefreshDisplay();
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

void MouseEventProcess(int x, int y, int button, int event) {
    uiGetMouse(x, y, button, event);
    if (stop) {
        RefreshDisplay();
        DrawGameOver();
    }
}

void TimerEventProcess(int timerID) {
    switch (timerID) {
        case SPEEDUP:
//            DownSpeed=DownSpeed*0.8;
//            cancelTimer(NORMAL_DOWN);
//            startTimer(NORMAL_DOWN,(int)DownSpeed);
            break;
        default:
            current.y--;
            if (!JudgeBorder(current, 3)) {
                current.y++;
                if (JudgeGameOver(current)) {
                    cancelTimer(NORMAL_DOWN);
                    cancelTimer(ACCELRATE_DOWN);
                    cancelTimer(SPEEDUP);
                    stop = 1;
                    RefreshDisplay();
                    DrawGameOver();
                    return;
                }
                RefreshCurrent();
            }
            RefreshDisplay();
            break;
    }
}

void CharEventProcess(char ch) {
    uiGetChar(ch); // GUI字符输入
    if (stop) {
        RefreshDisplay();
        DrawGameOver();
    }
}

void RefreshCurrent() {
    current.x = 12;
    current.y = 20;
    current.direction = 0;
    current.type = next.type;
    next.type = RandomInteger(1, 7);
}

void RefreshDisplay() {
    DisplayClear();
    DrawLayers(TetrominoMap);
    DrawTetromino(current);
    if (!stop) {
        DrawResult();
    }
    DrawTetromino(next);
    DrawFrame(0, 0);
}

void NewRound() {
    stop = 0;
    DisplayClear();
    LayerInit();
    DrawLayers(TetrominoMap);
    for(int i=0;i< sizeof(Name);i++){
        Name[i]=0;
    }
    Score = 0;
    Level = 0;
    current.x = 12;
    current.y = 20;
    current.type = RandomInteger(1, 7);
    next.type = RandomInteger(1, 7);
    DrawTetromino(current);
    DrawTetromino(next);
    DrawFrame(0, 0);
    startTimer(NORMAL_DOWN, (int) DownSpeed);
}

void DrawResult() {
    Tetromino tmp = current;
    while (JudgeBorder(tmp, 1)) {
        tmp.y--;
    }
    tmp.y++;
    DrawTetrominoOutline(tmp);
}

void UpdateRank() {
    if(RankList==NULL){
        RankList=CreateList();
    }
    InsertNode(RankList,Score,Name);
    DeleteNode(RankList);
}