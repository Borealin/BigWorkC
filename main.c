#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h> 
#include "imgui.h"
#include "DrawUtils.h"
#include <extgraph.h>
#include <windows.h>
#include <random.h>
#include <JudgeUtils.h>
#include <GameUtils.h>
#include <SaveUtils.h>

void Main() {
    SetWindowSize(BlockLength * 26, BlockLength * 26);
    InitGraphics();
    InitGUI() ;
    SetWindowTitle("Tetris");
    Randomize();
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    registerTimerEvent(TimerEventProcess);
    registerCharEvent(CharEventProcess);
    CanContinue = RecoverGame();
    DrawInitPage();
}
