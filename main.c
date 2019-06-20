#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h> 
#include "imgui.h"
#include "DrawUtils.h"
#include <extgraph.h>
#include <windows.h>
#include <JudgeUtils.h>
#include <GameUtils.h>
#include <SaveUtils.h>

void Main() {
    SetWindowSize(BlockLength * 26, BlockLength * 26);
    InitGraphics();
    InitGUI() ;
    SetWindowTitle("Tetris");
//    Randomize();
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    InitColor();
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    registerTimerEvent(TimerEventProcess);
    registerCharEvent(CharEventProcess);
    CanContinue = RecoverGame();
    DrawInitPage();
}
