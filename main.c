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

int DownSpeed = 1000;
Tetromino current = {12, 19, 0, 1};
Tetromino next = {21,16,0,1};

void RefreshCurrent();
void RefreshDisplay();

void KeyboardEventProcess(int key, int event);/*键盘消息回调函数*/
void MouseEventProcess(int x, int y, int button, int event);/*鼠标消息回调函数*/
void TimerEventProcess(int timerID);/*定时器消息回调函数*/
void DisplayClear(void);

void Main() {
    SetWindowSize(BlockLength * 26, BlockLength * 24);
    InitGraphics();
    InitGUI();
    Randomize();
    registerKeyboardEvent(KeyboardEventProcess);
    registerTimerEvent(TimerEventProcess);
    startTimer(NORMAL_DOWN, DownSpeed);
    startTimer(SPEEDUP,60000)
}

void KeyboardEventProcess(int key, int event)/*每当产生键盘消息，都要执行*/
{
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case VK_DOWN:
                    cancelTimer(NORMAL_DOWN);
                    Sleep(100);
                    current.y--;
                    if(!JudgeBorder(current,3)){
                        current.y++;
                        RefreshCurrent();
                    }
                    RefreshDisplay();
                    startTimer(NORMAL_DOWN,DownSpeed);
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
    current.y--;
    if(!JudgeBorder(current,3)){
        current.y++;
        RefreshCurrent();
    }
    RefreshDisplay();
}

void RefreshCurrent(){
    current.x = 12;
    current.y = 19;
    current.direction = 0;
    current.type = next.type;
    next.type = RandomInteger(1,7);
}

void RefreshDisplay() {
    DisplayClear();
    DrawFrame(0, 0);
    DrawLayers(TetrominoMap);
    DrawTetromino(current);
    DrawTetromino(next);
}