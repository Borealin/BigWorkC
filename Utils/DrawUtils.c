//
// Created by B on 2019/5/7.
//
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <DrawUtils.h>
#include <ListUtils.h>
#include <JudgeUtils.h>
#include "graphics.h"
#include "imgui.h"
#include "extgraph.h"
#include "SaveUtils.h"
#include <GameUtils.h>

#define DEFAULT_COLOR "White"
#define FRAME_COLOR "Light Gray"

const double BlockLength = 0.5;

DoublePoint FrameLeftCorner;

int Direction[16][2] = {
        {0,  0},
        {-1, 0},
        {-2, 0},
        {-1, 1},
        {0,  0},
        {0,  1},
        {0,  2},
        {1,  1},
        {0,  0},
        {1,  0},
        {2,  0},
        {1,  -1},
        {0,  0},
        {0,  -1},
        {0,  -2},
        {-1, -1}
};


char *TetrominoColor[8] = {
        "White",
        "Cyan",
        "Blue",
        "Orange",
        "Yellow",
        "Green",
        "Violet",
        "Red"
};

int TetrominoShape[8][4] = {
        {0, 0, 0,  0},
        {0, 1, 9,  10},
        {0, 1, 3,  9},
        {0, 1, 9,  7},
        {0, 9, 11, 13},
        {0, 1, 5,  7},
        {0, 1, 5,  9},
        {0, 3, 5,  9}
};

int TetrominoDirectionMod[8] = {
        1, 2, 4, 4, 1, 4, 4, 4
};

void DrawBlocks(int x, int y, int r, int c, char *InnerColor, char *OuterColor);

void DrawOutline(int x, int y, int r, int c, char *Color);


void DrawRankList();

void SetDefaultStyle();

void DrawMenu();


/*
	函数名：DrawTetromino
	功能：根据输入的X的参数，画出具体的下落的一种俄罗斯方块
	输入参数：名为X的Teromino类型的结构体
*/
void DrawTetromino(Tetromino x) {
    int dir = x.direction % TetrominoDirectionMod[x.type];
    for (int i = 0; i < 4; i++) {
        DrawBlocks(x.x + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][0],
                   x.y + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][1],
                   1, 1, TetrominoColor[x.type],
                   DEFAULT_COLOR);
    }
}

/*
	函数名：DrawTetrominoOutline
	功能：
	输入参数：名为X的Teromino类型的结构体
*/
void DrawTetrominoOutline(Tetromino x) {
    int dir = x.direction % TetrominoDirectionMod[x.type];
    for (int i = 0; i < 4; i++) {
        DrawOutline(x.x + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][0],
                    x.y + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][1],
                    1, 1, TetrominoColor[x.type]);
    }
}

/*
	函数名：DrawFrame
	功能：以输入的（x,y)确认新的坐标原点以绘制游戏的整体框架   （x,y)默认为（0，0）
	输入参数：x,y
*/
void DrawFrame(double x, double y) {
    FrameLeftCorner.x = x;
    FrameLeftCorner.y = y + BlockLength;
    SetPenColor(DEFAULT_COLOR);
    DrawBlocks(0, 0, 26, 2, FRAME_COLOR, DEFAULT_COLOR);
    int column[] = {
            0, 7, 18, 25
    };
    for (int i = 0; i < sizeof(column) / sizeof(column[0]); i++) {
        DrawBlocks(column[i], 2, 1, 20, FRAME_COLOR, DEFAULT_COLOR);
    }
    DrawBlocks(19, 2, 6, 4, FRAME_COLOR, DEFAULT_COLOR);
    DrawBlocks(0, 22, 26, 2, FRAME_COLOR, DEFAULT_COLOR);
    SetPenColor("Red");
    drawBox(FrameLeftCorner.x + 1 * BlockLength, FrameLeftCorner.y + 20 * BlockLength, BlockLength * 6, BlockLength * 2,
            0, "Score", 'M', "Red");
    drawBox(FrameLeftCorner.x + 1 * BlockLength, FrameLeftCorner.y + 16 * BlockLength, BlockLength * 6, BlockLength * 2,
            0, "Level", 'M', "Red");
    drawBox(FrameLeftCorner.x + 1 * BlockLength, FrameLeftCorner.y + 12 * BlockLength, BlockLength * 6, BlockLength * 2,
            0, "Rank List", 'M', "Red");
    drawBox(FrameLeftCorner.x + 19 * BlockLength, FrameLeftCorner.y + 20 * BlockLength, BlockLength * 6,
            BlockLength * 2, 0, "Next One", 'M', "Red");
    drawBox(FrameLeftCorner.x + 19 * BlockLength, FrameLeftCorner.y + 12 * BlockLength, BlockLength * 6,
            BlockLength * 2, 0, "Hold", 'M', "Red");
    char *ScoreText = (char *) malloc(sizeof(char));
    char *LevelText = (char *) malloc(sizeof(char));
    itoa(Score, ScoreText, 10);
    itoa(Level, LevelText, 10);
    SetPenColor("Blue");
    drawBox(FrameLeftCorner.x + 1 * BlockLength, FrameLeftCorner.y + 18 * BlockLength, BlockLength * 6, BlockLength * 2,
            0, ScoreText, 'L', "Blue");
    drawBox(FrameLeftCorner.x + 1 * BlockLength, FrameLeftCorner.y + 14 * BlockLength, BlockLength * 6, BlockLength * 2,
            0, LevelText, 'L', "Blue");
    DrawRankList();
    DrawMenu();
}

/*
	函数名：DrawMenu
	功能：绘制游戏菜单
	输入参数：
*/
void DrawMenu() {
    SetDefaultStyle();
    static char *menuListFile[] = {
            "File",
            "Save | Ctrl-S",
            "Exit | Ctrl-E"};
    static char *menuListTool[] = {
            "Tool",
            "Enable Hold | Ctrl-X",
            "New Round | Ctrl-N",
            "Level Up | Ctrl-Up",
            "Level Down | Ctrl-Down",
            "Pause | Esc"};
    static char *menuListHelp[] = {
            "Other",
            "Help",
            "About"};

    double x = FrameLeftCorner.x;
    double y = FrameLeftCorner.y + 25 * BlockLength;
    double h = BlockLength; // 控件高度
    double w = BlockLength * 26 / 3; // 控件宽度
    double wlist = BlockLength * 26 / 3;
    int selection;

    // File 菜单
    selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile,
                         sizeof(menuListFile) / sizeof(menuListFile[0]));
    if (selection == 1) {
        SaveGame();
    }
    if (selection == 2) {
        GameExit(1);
    }

    // Tool 菜单
    menuListTool[1] = CanHold ? "Disable Hold | Ctrl-X" : "Enable Hold | Ctrl-X";
    menuListTool[5] = IsPause ? "Resume | Esc" : "Pause | Esc";
    selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListTool,
                         sizeof(menuListTool) / sizeof(menuListTool[0]));
    switch (selection) {
        case 1:
            CanHold = CanHold ? (LogStatusBar(DISABLE_HOLD), 0) : (LogStatusBar(ENABLE_HOLD), 1);
            break;
        case 2:
            NewRound();
            break;
        case 3:
            LogStatusBar(LEVEL_UP);
            Level = Level > 11 ? 12 : Level + 1;
            ResetDownTimer();
            break;
        case 4:
            LogStatusBar(LEVEL_DOWN);
            Level = Level < 1 ? 0 : Level - 1;
            ResetDownTimer();
            break;
        case 5:
            IsPause ? GameResume() : GamePause();
            break;
        default:
            break;
    }
    selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp,
                         sizeof(menuListHelp) / sizeof(menuListHelp[0]));
    switch (selection) {
        case 1:
            LogStatusBar(HELP);
            ShowHelp = ShowHelp ? 0 : 1;
            RefreshDisplay();
            break;
        case 2:
            LogStatusBar(ABOUT);
            ShowAbout = ShowAbout ? 0 : 1;
            RefreshDisplay();
            break;
        default:
            break;
    }
}

/*
	函数名：DrawBlocks
	功能：根据输入参数，在确定的位置绘出确定颜色的方块，xyrc为确认在何位置画出多少数量的方块，字符串变量则以确定颜色
	输入参数：x, y, r, c, InnerColor, OuterColor
*/
void DrawBlocks(int x, int y, int r, int c, char *InnerColor, char *OuterColor) {
    SetPenColor(InnerColor);
    for (int i = x; i < x + r; i++) {
        for (int j = y; j < y + c; ++j) {
            drawRectangle(FrameLeftCorner.x + i * BlockLength, FrameLeftCorner.y + j * BlockLength, BlockLength,
                          BlockLength, 1);
        }
    }
    SetPenColor(OuterColor);
    for (int i = x; i < x + r; i++) {
        for (int j = y; j < y + c; ++j) {
            drawRectangle(FrameLeftCorner.x + i * BlockLength, FrameLeftCorner.y + j * BlockLength, BlockLength,
                          BlockLength, 0);
            drawRectangle(FrameLeftCorner.x + (i + 0.25) * BlockLength, FrameLeftCorner.y + (j + 0.25) * BlockLength,
                          BlockLength / 2,
                          BlockLength / 2, 0);
            MovePen(FrameLeftCorner.x + i * BlockLength, FrameLeftCorner.y + j * BlockLength);
            DrawLine(BlockLength / 4, BlockLength / 4);
            MovePen(FrameLeftCorner.x + (i + 1) * BlockLength, FrameLeftCorner.y + j * BlockLength);
            DrawLine((-1) * BlockLength / 4, BlockLength / 4);
            MovePen(FrameLeftCorner.x + i * BlockLength, FrameLeftCorner.y + (j + 1) * BlockLength);
            DrawLine(BlockLength / 4, (-1) * BlockLength / 4);
            MovePen(FrameLeftCorner.x + (i + 1) * BlockLength, FrameLeftCorner.y + (j + 1) * BlockLength);
            DrawLine((-1) * BlockLength / 4, (-1) * BlockLength / 4);
        }
    }

}

/*
	函数名：DrawOutline
	功能：绘制图形的轮廓线，可参考DrawBlocks的注释
	输入参数：x, y, r, c, Color
*/
void DrawOutline(int x, int y, int r, int c, char *Color) {
    SetPenColor(Color);
    for (int i = x; i < x + r; i++) {
        for (int j = y; j < y + c; ++j) {
            drawRectangle(FrameLeftCorner.x + i * BlockLength, FrameLeftCorner.y + j * BlockLength, BlockLength,
                          BlockLength, 0);
        }
    }
}

/*
	函数名：DrawLayers
	功能：行初始化后绘制整体的格子
	输入参数：
*/
void DrawLayers(int head[12][22]) {
    if (!head[0][0]) {
        LayerInit();
    }
    for (int j = 1; j < 21; ++j) {
        for (int i = 1; i < 11; ++i) {
            if (head[i][j]) {
                DrawBlocks(X_CORNER + i, Y_CORNER + j, 1, 1, TetrominoColor[head[i][j]], DEFAULT_COLOR);
            }
        }
    }
}

/*
	函数名：DrawGameOver
	功能：当游戏结束时，提示玩家游戏结束并输入姓名，并弹出“Click to Retey”字样提示玩家单击即可重新运行游戏
	输入参数：
*/
void DrawGameOver() {
    SetPenColor("Gray");
    drawBox(FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 13 * BlockLength, 8 * BlockLength,
            1 * BlockLength, 1, "Game Over", 'M', "White");
    SetPenColor("Gray");
    drawBox(FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 12 * BlockLength, 8 * BlockLength,
            1 * BlockLength, 1, "Please Input Your Name", 'M', "White");
    SetDefaultStyle();
    textbox(GenUIID(0), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 11 * BlockLength, 8 * BlockLength,
            1 * BlockLength, Name,
            sizeof(Name));
    if (button(GenUIID(1), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 10 * BlockLength, 8 * BlockLength,
               1 * BlockLength, "Click to Retry")) {
        UpdateRank();
        NewRound();
    }
}

/*
	函数名：DrawRankList
	功能：绘制排行榜，并在左边显示玩家名字，右边显示玩家得分
	输入参数：本次游戏的得分currentNode->score及玩家输入的名字currentNode->name
*/
void DrawRankList() {
    char RankScoreText[10];
    if (RankList == NULL) {
        RankList = CreateList();
    }
    ListNodePtr currentNode = RankList->next;
    int i = 0;
    while (currentNode != NULL) {
        i++;
        for (int j = 0; j < sizeof(RankScoreText); ++j) {
            RankScoreText[j] = 0;
        }
        itoa(currentNode->score, RankScoreText, 10);
        SetPenColor("Orange");
        drawBox(FrameLeftCorner.x + 1 * BlockLength, FrameLeftCorner.y + (12 - i) * BlockLength, BlockLength * 3,
                BlockLength * 1, 0, currentNode->name, 'L', "Red");
        drawBox(FrameLeftCorner.x + 4 * BlockLength, FrameLeftCorner.y + (12 - i) * BlockLength, BlockLength * 3,
                BlockLength * 1, 0, RankScoreText, 'R', "Red");
        currentNode = currentNode->next;
    }
}

/*
	函数名：DrawGamePause
	功能：当玩家按下ESC时，弹出重新开始及退出两个选项
	输入参数：
*/
void DrawGamePause() {
    SetDefaultStyle();
    if (button(GenUIID(2), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 12 * BlockLength, 8 * BlockLength,
               2 * BlockLength, "Resume")) {
        GameResume();
    }
    if (button(GenUIID(3), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 10 * BlockLength, 8 * BlockLength,
               2 * BlockLength, "Exit")) {
        GameExit(1);
    }
}

/*
	函数名：SetDefaultStyle
	功能：为按钮以及内置文字的方块设置初始颜色，并预置内部填充
	输入参数：
*/
void SetDefaultStyle() {
    setMenuColors("Gray", "White", "Dark Gray", "Black", 1);
    setTextBoxColors("Gray", "White", "Dark Gray", "Black", 1);
    setButtonColors("Gray", "White", "Dark Gray", "Black", 1);
}

/*
	函数名：DrawInitPage
	功能：绘制游戏的初始界面
	输入参数：
*/
void DrawInitPage() {
    SetDefaultStyle();
    int Title[7][35] = {
            {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
            {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    };
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 35; ++j) {
            if (Title[i][j]) {
                SetPenColor(TetrominoColor[randuint(1, 7)]);
                drawRectangle(FrameLeftCorner.x + (8.5 + j) * BlockLength / 2,
                              FrameLeftCorner.y + (32 + i) * BlockLength / 2, BlockLength / 2,
                              BlockLength / 2, 1);
            }
        }
    }
    if (button(GenUIID(4), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 11 * BlockLength, 8 * BlockLength,
               2 * BlockLength, "New Game")) {
        LogStatusBar(NEW_GAME);
        InitPage = 0;
        UpdateRank();
        NewRound();
    }
    if (CanContinue) {
        if (button(GenUIID(5), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 8 * BlockLength,
                   8 * BlockLength,
                   2 * BlockLength, "Continue")) {
            GameContinue();
        }
    }
    if (button(GenUIID(6), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 5 * BlockLength, 8 * BlockLength,
               2 * BlockLength, "Help")) {
        LogStatusBar(HELP);
        ShowHelp = ShowHelp ? 0 : 1;
        RefreshDisplay();
    }
    if (button(GenUIID(7), FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 2 * BlockLength, 8 * BlockLength,
               2 * BlockLength, "Exit")) {
        GameExit(1);
    }
}

/*
	函数名：DrawClearBlink
	功能：使即将被清除的满行闪烁
	输入参数：Clear[],n
*/
void DrawClearBlink(int Clear[], int n) {
    PauseTimer();
    if (n) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 1; k < 11; ++k) {
                    DrawBlocks(X_CORNER + k, Y_CORNER + Clear[j], 1, 1, TetrominoColor[TetrominoMap[k][Clear[j]]],
                               DEFAULT_COLOR);
                }
            }
            Pause(0.08);
            for (int j = 0; j < n; ++j) {
                for (int k = 1; k < 11; ++k) {
                    DrawBlocks(X_CORNER + k, Y_CORNER + Clear[j], 1, 1, "White", DEFAULT_COLOR);
                }
            }
            Pause(0.08);
        }
    }
    ResumeTimer();
}

/*
	函数名：DrawAbout
	功能：绘制游戏菜单中的About栏
	输入参数：
*/
void DrawAbout() {
    SetPenColor("Light Gray");
    drawRectangle(FrameLeftCorner.x + 1.5 * BlockLength, FrameLeftCorner.y + 14.5 * BlockLength, 5 * BlockLength,
                  3 * BlockLength, 1);
    SetPenColor("Black");
    MovePen(FrameLeftCorner.x + 3.5 * BlockLength, FrameLeftCorner.y + 17 * BlockLength);
    DrawTextString("About");
    MovePen(FrameLeftCorner.x + 2 * BlockLength, FrameLeftCorner.y + 16 * BlockLength);
    DrawTextString("Contributor:XK,WYD,SCN");
    MovePen(FrameLeftCorner.x + 2 * BlockLength, FrameLeftCorner.y + 15 * BlockLength);
    DrawTextString("CopyRight:Grp-14");
}

/*
	函数名：DrawHelp
	功能：绘制游戏菜单中的Help栏
	输入参数：
*/
void DrawHelp() {
    SetPenColor("Light Gray");
    drawRectangle(FrameLeftCorner.x + 19.5 * BlockLength, FrameLeftCorner.y + 11.5 * BlockLength, 5 * BlockLength,
                  6 * BlockLength, 1);
    SetPenColor("Black");
    MovePen(FrameLeftCorner.x + 21.5 * BlockLength, FrameLeftCorner.y + 17 * BlockLength);
//    SetPointSize(5);
//    SetStyle(Bold);
    DrawTextString("Help");
    MovePen(FrameLeftCorner.x + 19.5 * BlockLength, FrameLeftCorner.y + 16 * BlockLength);
//    SetPointSize(1);
//    SetStyle(Normal);
    DrawTextString("up arrow to spin");
    MovePen(FrameLeftCorner.x + 19.5 * BlockLength, FrameLeftCorner.y + 15 * BlockLength);
    DrawTextString("left and right arrow to move");
    MovePen(FrameLeftCorner.x + 19.5 * BlockLength, FrameLeftCorner.y + 14 * BlockLength);
    DrawTextString("down arrow to speed up fall");
    MovePen(FrameLeftCorner.x + 19.5 * BlockLength, FrameLeftCorner.y + 13 * BlockLength);
    DrawTextString("space to  fall to the bottom");
    MovePen(FrameLeftCorner.x + 19.5 * BlockLength, FrameLeftCorner.y + 12 * BlockLength);
    DrawTextString("x to hold tetromino");
}

/*
	函数名：DrawStatusBar
	功能：绘制状态栏
	输入参数：
*/
void DrawStatusBar() {
    drawBox(0, 0, BlockLength * 26, BlockLength * 1, 0, StatusBarBuff, 'M', "Black");
}

void InitColor() {
    DefineColor("Yellow",1,0.694,0.106);
    DefineColor("Cyan",0.199,0.648,0.719);
    DefineColor("Green",0.102,0.574,0.430);
    DefineColor("Red",0.813,0.352,0.430);
    DefineColor("Violet",0.594,0.426,0.695);
    DefineColor("Blue",0.316,0.656,0.863);
    DefineColor("Orange",0.926,0.469,0.289);
}