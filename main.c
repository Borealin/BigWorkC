#include <graphics.h>
#include <imgui.h>
#include <DrawUtils.h>
#include <extgraph.h>
#include <windows.h>
#include <random.h>
#include <JudgeUtils.h>
#define NORMAL_DOWN 1
#define ACCELRATE_DOWN 2
#define SPEEDUP 3

int accel=0;
double DownSpeed = 1000;
Tetromino current = {13, 20, 0, 1};
Tetromino next = {21,16,0,1};

void RefreshCurrent();
void RefreshDisplay();

void KeyboardEventProcess(int key, int event);/*键盘消息回调函数*/
void TimerEventProcess(int timerID);/*定时器消息回调函数*/
void DisplayClear(void);

void Main() {
    SetWindowSize(BlockLength * 26, BlockLength * 24);
    InitGraphics();
    InitGUI();
    Randomize();
    current.type = RandomInteger(1,7);
    next.type = RandomInteger(1,7);
    registerKeyboardEvent(KeyboardEventProcess);
    registerTimerEvent(TimerEventProcess);
    startTimer(NORMAL_DOWN, (int)DownSpeed);
    startTimer(SPEEDUP,60000);
}

void KeyboardEventProcess(int key, int event)/*每当产生键盘消息，都要执行*/
{
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case SPACEPARITY:

                    break;
                case VK_DOWN:
                    if(!accel){
                        accel=1;
                        cancelTimer(NORMAL_DOWN);
                        startTimer(ACCELRATE_DOWN,60);
                        RefreshDisplay();
                    }
                    break;
                case VK_RIGHT:
                    current.x++;
                    if(!JudgeBorder(current,2)){
                        current.x--;
                    }
                    RefreshDisplay();
                    break;
                case VK_LEFT:
                    current.x--;
                    if(!JudgeBorder(current,0)){
                        current.x++;
                    }
                    RefreshDisplay();
                    break;
                case VK_UP:
                    current.direction = (current.direction + 1) % 4;
                    if(!JudgeBorder(current,1)){
                        current.direction = (current.direction - 1) % 4;
                    }
                    RefreshDisplay();
                    break;
                case VK_ESCAPE:
                    current.x = 12;
                    current.y = 19;
                    current.direction = 0;
                    current.type = RandomInteger(1,7);
                    RefreshDisplay();
                    break;
                default:
                    break;
            }
            break;
        case KEY_UP:
            switch (key) {
                case VK_DOWN:
                    if (accel){
                        accel=0;
                        cancelTimer(ACCELRATE_DOWN);
                        startTimer(NORMAL_DOWN,(int)DownSpeed);
                    }
                    RefreshDisplay();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void TimerEventProcess(int timerID) {
    switch(timerID){
        case NORMAL_DOWN:
            current.y--;
            if(!JudgeBorder(current,3)){
                current.y++;
                RefreshCurrent();
            }
            RefreshDisplay();
            break;
        case ACCELRATE_DOWN:
            current.y--;
            if(!JudgeBorder(current,3)){
                current.y++;
                RefreshCurrent();
            }
            RefreshDisplay();
            break;
        case SPEEDUP:
//            DownSpeed=DownSpeed*0.8;
//            cancelTimer(NORMAL_DOWN);
//            startTimer(NORMAL_DOWN,(int)DownSpeed);
            break;
        default:
            break;
    }
}

void RefreshCurrent(){
    current.x = 13;
    current.y = 20;
    current.direction = 0;
    current.type = next.type;
    next.type = RandomInteger(1,7);
}

void RefreshDisplay() {
    DisplayClear();
    DrawLayers(TetrominoMap);
    DrawTetromino(current);
    DrawTetromino(next);
    DrawFrame(0, 0);
}