//
// Created by B on 2019/5/9.
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
#include <SaveUtils.h>

ListNodePtr RankList;

int IsAccelerate = 0;

int IsStop = 0;

int IsPause = 0;

int CanHold = 1;

double DownSpeed = 600;

int TetrominoMap[12][22];
Tetromino current = {12, 20, 0, 1};
Tetromino next = {21, 16, 0, 1};
Tetromino hold = {21, 9, 0, 0};

char Name[NAMELENGTH];

int Score;
int ScoreAdd[5] = {
        10, 100, 200, 400, 800
};
int Level;

int InitPage = 1;

int CanContinue = 0;

int AllClearedLayer = 0;

int ClearedLayer = 0;

int LevelSpeed[13] = {
        800, 750, 700, 650, 600, 550, 500, 450, 400, 375, 350, 325, 300
};

int ControlDown = 0;

void RefreshCurrent();

void DrawResult();

void SwitchHold();

int HaveSwitch = 0;

int ShowAbout = 0;

int ShowHelp = 0;

char StatusBarBuff[100] = {0};

char* MessageStr[30]={
        "MOVE LEFT",
        "MOVE RIGHT",
        "SPIN",
        "FALL",
        "SPEED UP FALL",
        "FALL TO BOTTOM",
        "SWITCH HOLD",
        "SAVE",
        "LOAD",
        "NEW GAME",
        "CONTINUE",
        "EXIT",
        "PAUSE",
        "RESUME",
        "ABOUT",
        "HELP",
        "ENABLE HOLD",
        "DISABLE HOLD",
        "NEW ROUND",
        "LEVEL UP",
        "LEVEL DOWN",
        "GAME OVER"
};

void GameOver();

/*
	函数名：KeyboardEventProcess
	功能：每当产生键盘消息时，执行对应的功能，对应俄罗斯方块的各项游戏功能
	输入参数：
*/
void KeyboardEventProcess(int key, int event)/* 每当产生键盘消息，都要执行 */
{
    uiGetKeyboard(key, event);
    if (InitPage) {
        return;
    }
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case VK_CONTROL:
                    if (!ControlDown) {
                        ControlDown = 1;
                    }
                    break;
                case VK_ESCAPE:
                    IsPause ? GameResume() : GamePause();
                    break;
                case VK_DOWN:
                    if (ControlDown) {
                        LogStatusBar(LEVEL_DOWN);
                        Level = Level < 1 ? 0 : Level - 1;
                        ResetDownTimer();
                        RefreshDisplay();
                    }
                    break;
                case VK_UP:
                    if (ControlDown) {
                        LogStatusBar(LEVEL_UP);
                        Level = Level > 11 ? 12 : Level + 1;
                        ResetDownTimer();
                        RefreshDisplay();
                    }
                    break;
                default:
                    break;
            }
            if (!IsStop && !IsPause) {
                switch (key) {
                    case VK_SPACE:
                        LogStatusBar(FALL_TO_BOTTOM);
                        while (JudgeBorder(current, 3)) {
                            current.y--;
                        }
                        current.y++;
                        RefreshDisplay();
                        if (JudgeGameOver(current)) {
                            GameOver();
                            return;
                        }
                        RefreshCurrent();
                        RefreshDisplay();
                        break;
                    case VK_DOWN:
                        if (!ControlDown) {
                            if (!IsAccelerate) {
                                LogStatusBar(SPEED_UP_FALL);
                                IsAccelerate = 1;
                                cancelTimer(NORMAL_DOWN);
                                startTimer(ACCELRATE_DOWN, 50);
                                RefreshDisplay();
                            }
                        }
                        break;
                    case VK_RIGHT:
                        LogStatusBar(MOVE_RIGHT);
                        current.x++;
                        if (!JudgeBorder(current, 2)) {
                            current.x--;
                        }
                        RefreshDisplay();
                        break;
                    case VK_LEFT:
                        LogStatusBar(MOVE_LEFT);
                        current.x--;
                        if (!JudgeBorder(current, 0)) {
                            current.x++;
                        }
                        RefreshDisplay();
                        break;
                    case VK_UP:
                        LogStatusBar(SPIN);
                        if (!ControlDown) {
                            current.direction = (current.direction + 1) % 4;
                            if (!JudgeBorder(current, 1)) {
                                current.direction = ((current.direction - 1) % 4 + 4) % 4;
                            }
                            RefreshDisplay();
                        }
                        break;
                    default:
                        break;
                }
            }
            break;
        case KEY_UP:
            switch (key) {
                case VK_CONTROL:
                    ControlDown = 0;
                    break;
                default:
                    break;
            }
            if (!IsStop && !IsPause) {
                switch (key) {
                    case VK_DOWN:
                        if (IsAccelerate) {
                            IsAccelerate = 0;
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

/*
	函数名：MouseEventProcess
	功能：每当产生鼠标消息时，执行对应的功能
	输入参数：
*/
void MouseEventProcess(int x, int y, int button, int event) {
    uiGetMouse(x, y, button, event);
    if (!IsStop && !IsPause && !InitPage) {
        return;
    }
    RefreshDisplay();
}

/*
	函数名：TimerEventProcess
	功能：每当产生计时器消息时，执行对应的功能
	输入参数：
*/
void TimerEventProcess(int timerID) {
    if (InitPage) {
        return;
    }
    switch (timerID) {
        case STOPREFRESH:
            RefreshDisplay();
            DrawGameOver();
            break;
        case NORMAL_DOWN:
            LogStatusBar(FALL);
        default:
            current.y--;
            if (!JudgeBorder(current, 3)) {
                current.y++;
                RefreshDisplay();
                if (JudgeGameOver(current)) {
                    GameOver();
                    return;
                }
                RefreshCurrent();
            }
            RefreshDisplay();
            break;
    }
}

/*
	函数名：CharEventProcess
	功能：每当产生字符串消息时，执行对应的功能
	输入参数：ch
*/
void CharEventProcess(char ch) {
    uiGetChar(ch); // GUI字符输入
    if (InitPage) {
        return;
    }
    if (ControlDown) {
        switch (ch) {
            case 'e':
                GameExit(1);
                break;
            case 'E':
                GameExit(1);
                break;
            case 's':
                SaveGame();
                break;
            case 'S':
                SaveGame();
                break;
            case 'n':
                NewRound();
                break;
            case 'N':
                NewRound();
                break;
            case 'x':
                CanHold = CanHold ? 0 : 1;
                RefreshDisplay();
                break;
            case 'X':
                CanHold = CanHold ? 0 : 1;
                RefreshDisplay();
                break;
        }
    }
    switch (ch) {
        case 'x':
            if (CanHold) {
                SwitchHold();
            }
            RefreshDisplay();
            break;
        case 'X':
            if (CanHold) {
                SwitchHold();
            }
            RefreshDisplay();
            break;
        default:
            break;
    }
}

/*
	函数名：RefreshCurrent
	功能：重置参数
	输入参数：
*/
void RefreshCurrent() {
    current.x = 12;
    current.y = 20;
    current.direction = 0;
    current.type = next.type;
    next.type = RandomInteger(1, 7);
    HaveSwitch = 0;
}

/*
	函数名：RefreshDisplay
	功能：清除上次游戏排列的方块，重新绘出游戏界面
	输入参数：
*/
void RefreshDisplay() {
    DisplayClear();
    DrawStatusBar();
    if (!InitPage) {
        if (!IsPause && !IsStop) {
            DrawLayers(TetrominoMap);
            DrawTetromino(current);
            DrawTetromino(next);
            DrawResult();
            if (CanHold) {
                DrawTetromino(hold);
            }
        }
        DrawFrame(0, 0);
    }
    if (IsStop) {
        DrawGameOver();
    }
    if (IsPause) {
        DrawGamePause();
    }
    if(InitPage){
        DrawInitPage();
    }
    if (ShowAbout) {
        DrawAbout();
    }
    if (ShowHelp) {
        DrawHelp();
    }
}

/*
	函数名：NewRound
	功能：初始化参数，开始新的一轮游戏
	输入参数：
*/
void NewRound() {
    LogStatusBar(NEW_ROUND);
    cancelTimer(STOPREFRESH);
    IsStop = 0;
    AllClearedLayer = 0;
    ClearedLayer = 0;
    DownSpeed = LevelSpeed[0];
    LayerInit();
    for (int i = 0; i < sizeof(Name); i++) {
        Name[i] = 0;
    }
    Score = 0;
    Level = 0;
    current.x = 12;
    current.y = 20;
    current.type = RandomInteger(1, 7);
    next.type = RandomInteger(1, 7);
    hold.type = 0;
    RefreshDisplay();
    startTimer(NORMAL_DOWN, (int) DownSpeed);
}

/*
	函数名：DrawResult
	功能：当游戏结束时执行相对应的功能
	输入参数：
*/
void DrawResult() {
    Tetromino tmp = current;
    while (JudgeBorder(tmp, 1)) {
        tmp.y--;
    }
    tmp.y++;
    DrawTetrominoOutline(tmp);
}

/*
	函数名：UpdateRank
	功能：若无排名则新建，若有排名则更新
	输入参数：
*/
void UpdateRank() {
    if (RankList == NULL) {
        RankList = CreateList();
    }
    InsertNode(RankList, Score, Name);
    DeleteNode(RankList);
}

/*
	函数名：SwitchHold
	功能：实现游戏中的"Hold"功能，当“Hold”预览窗为空时，将"Next One"预览窗中的方块保留至“Hold”区域，
    并刷新”Next One"预览窗；当”Hold“预览窗非空时，使"Hold"预览窗中的俄罗斯方块成为下一个下落的俄罗斯方块，
    并清空“Hold”预览窗。
	输入参数：
*/
void SwitchHold() {
    LogStatusBar(SWITCH_HOLD);
    if (!hold.type) {
        hold.type = current.type;
        RefreshCurrent();
    } else {
        if (!HaveSwitch) {
            int tmp = current.type;
            current.type = hold.type;
            current.x = 12;
            current.y = 20;
            current.direction = 0;
            hold.type = tmp;
            HaveSwitch = 1;
        }
    }
}

/*
	函数名：GameOver
	功能：调用函数，完成当次游戏结束时的各项功能
	输入参数：
*/
void GameOver() {
    LogStatusBar(GAME_OVER);
    PauseTimer();
    IsStop = 1;
    RefreshDisplay();
    DrawGameOver();
    startTimer(STOPREFRESH, 100);
}

/*
	函数名：GamePause
	功能：暂停游戏
	输入参数：
*/
void GamePause() {
    LogStatusBar(PAUSE);
    PauseTimer();
    IsPause = 1;
    RefreshDisplay();
    DrawGamePause();
}

/*
	函数名：GameResume
	功能：重新开始游戏
	输入参数：
*/
void GameResume() {
    LogStatusBar(RESUME);
    startTimer(NORMAL_DOWN, (int) DownSpeed);
    IsPause = 0;
    RefreshDisplay();
}

/*
	函数名：GameExit
	功能：保存本次游戏内容并关闭游戏界面
	输入参数：int save
*/
void GameExit(int save) {
    LogStatusBar(EXIT);
    if (save) {
        SaveGame();
    }
    ExitGraphics();
}
/*
	函数名：GameContinue
	功能：继续之前被暂停的游戏
	输入参数：
*/
void GameContinue() {
    LogStatusBar(CONTINUE);
    InitPage = 0;
    RefreshDisplay();
    startTimer(NORMAL_DOWN, (int) DownSpeed);
}
/*
	函数名：PauseTimer
	功能：使计时器NORMAL_DOWN和ACCELRATE暂停工作
	输入参数：
*/
void PauseTimer() {
    cancelTimer(NORMAL_DOWN);
    cancelTimer(ACCELRATE_DOWN);
}
/*
	函数名：ResumeTimer
	功能：使计时器NORMAL_DOWN重新开始工作
	输入参数：
*/
void ResumeTimer() {
    startTimer(NORMAL_DOWN, (int) DownSpeed);
}
/*
	函数名：UpdateLevel
	功能：计算并更新玩家当前的等级
	输入参数：int count
*/
void UpdateLevel(int count) {
    AllClearedLayer += count;
    ClearedLayer += count;
    Level = Level + (ClearedLayer / 10) > 12 ? 12 : Level + (ClearedLayer / 10);
    ClearedLayer = ClearedLayer % 10;
    ResetDownTimer();
}
/*
	函数名：ResetDownTimer
	功能：根据玩家当前的等级调整方块下落的速度并重置NORMAL_DOWN计时器
	输入参数：
*/
void ResetDownTimer() {
    DownSpeed = LevelSpeed[Level];
    cancelTimer(NORMAL_DOWN);
    if (!IsStop && !IsPause) {
        startTimer(NORMAL_DOWN, (int) DownSpeed);
    }
}
/*
	函数名：LogStatusBar
	功能：更新下方状态栏消息
	输入参数：
*/
void LogStatusBar(MessageTypes MessageType){
    strcpy(StatusBarBuff,MessageStr[MessageType]);
}
