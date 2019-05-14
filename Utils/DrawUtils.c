//
// Created by Borealin on 2019/5/7.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <DrawUtils.h>
#include <ListUtils.h>
#include <JudgeUtils.h>
#include "graphics.h"
#include "imgui.h"
#include "extgraph.h"
#include <GameUtils.h>

#define DEFAULT_COLOR "Black"
#define FRAME_COLOR "Gray"

const double BlockLength = 0.3;

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
        1, 2, 4, 4, 1, 2, 4, 2
};

void DrawBlocks(int x, int y, int r, int c, char *InnerColor, char *OuterColor);

void DrawOutline(int x, int y, int r, int c, char *Color);

void DrawRankList();

void SetDefaultStyle();

void DrawTetromino(Tetromino x) {
    int dir = x.direction % TetrominoDirectionMod[x.type];
    for (int i = 0; i < 4; i++) {
        DrawBlocks(x.x + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][0],
                   x.y + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][1],
                   1, 1, TetrominoColor[x.type],
                   DEFAULT_COLOR);
    }
}

void DrawTetrominoOutline(Tetromino x) {
    int dir = x.direction % TetrominoDirectionMod[x.type];
    for (int i = 0; i < 4; i++) {
        DrawOutline(x.x + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][0],
                    x.y + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][1],
                    1, 1, TetrominoColor[x.type]);
    }
}

void DrawFrame(double x, double y) {
    FrameLeftCorner.x = x;
    FrameLeftCorner.y = y;
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
    drawBox(x + 1 * BlockLength, y + 20 * BlockLength, BlockLength * 6, BlockLength * 2, 0, "Score", 'M', "Red");
    drawBox(x + 1 * BlockLength, y + 16 * BlockLength, BlockLength * 6, BlockLength * 2, 0, "Level", 'M', "Red");
    drawBox(x + 1 * BlockLength, y + 12 * BlockLength, BlockLength * 6, BlockLength * 2, 0, "Rank List", 'M', "Red");
    drawBox(x + 19 * BlockLength, y + 20 * BlockLength, BlockLength * 6, BlockLength * 2, 0, "Next One", 'M', "Red");
    drawBox(x + 19 * BlockLength, y + 12 * BlockLength, BlockLength * 6, BlockLength * 2, 0, "Hold", 'M', "Red");
    char *ScoreText = (char *) malloc(sizeof(char));
    char *LevelText = (char *) malloc(sizeof(char));
    itoa(Score, ScoreText, 10);
    itoa(Level, LevelText, 10);
    SetPenColor("Blue");
    drawBox(x + 1 * BlockLength, y + 18 * BlockLength, BlockLength * 6, BlockLength * 2, 0, ScoreText, 'L', "Blue");
    drawBox(x + 1 * BlockLength, y + 14 * BlockLength, BlockLength * 6, BlockLength * 2, 0, LevelText, 'L', "Blue");
    DrawRankList();
}


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

void DrawOutline(int x, int y, int r, int c, char *Color) {
    SetPenColor(Color);
    for (int i = x; i < x + r; i++) {
        for (int j = y; j < y + c; ++j) {
            drawRectangle(FrameLeftCorner.x + i * BlockLength, FrameLeftCorner.y + j * BlockLength, BlockLength,
                          BlockLength, 0);
        }
    }
}

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

void DrawGameOver() {
    SetPenColor("Magenta");
    drawBox(FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 13 * BlockLength, 8 * BlockLength,
            1 * BlockLength, 1, "Game Over", 'M', "Black");
    SetPenColor("Magenta");
    drawBox(FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 12 * BlockLength, 8 * BlockLength,
            1 * BlockLength, 1, "Please Input Your Name", 'M', "Black");
    SetDefaultStyle();
    textbox(0, FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 11 * BlockLength, 8 * BlockLength,
            1 * BlockLength, Name,
            sizeof(Name));
    if (button(1, FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 10 * BlockLength, 8 * BlockLength,
               1 * BlockLength, "Click to Retry")) {
        UpdateRank();
        NewRound();
    }
}

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
                BlockLength * 1, 0, currentNode->name, 'L', "Magenta");
        drawBox(FrameLeftCorner.x + 4 * BlockLength, FrameLeftCorner.y + (12 - i) * BlockLength, BlockLength * 3,
                BlockLength * 1, 0, RankScoreText, 'R', "Magenta");
        currentNode = currentNode->next;
    }
}

void DrawGamePause() {
    SetDefaultStyle();
    if (button(2, FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 12 * BlockLength, 8 * BlockLength,
               2 * BlockLength, "Resume")) {
        GameResume();
    }
    if (button(3, FrameLeftCorner.x + 9 * BlockLength, FrameLeftCorner.y + 10 * BlockLength, 8 * BlockLength,
               2 * BlockLength, "Exit")) {
        GameExit();
    }
}

void SetDefaultStyle() {
    setTextBoxColors("Magenta", "Black", "Dark Gray", "Gray", 1);
    setButtonColors("Magenta", "Black", "Dark Gray", "Gray", 1);
}