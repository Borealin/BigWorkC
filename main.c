#include <graphics.h>
#include <imgui.h>
#include <DrawUtils.h>
#include <extgraph.h>
#include <windows.h>
#include <random.h>
#include <JudgeUtils.h>
#include <GameUtils.h>

void Main() {
    SetWindowSize(BlockLength * 26, BlockLength * 24);
    InitGraphics();
    InitGUI();
    Randomize();
    current.type = RandomInteger(1, 7);
    next.type = RandomInteger(1, 7);
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    registerTimerEvent(TimerEventProcess);
    startTimer(NORMAL_DOWN, (int) DownSpeed);
}
