//
// Created by Borealin on 2019/5/7.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <DrawUtils.h>
#include "graphics.h"
#include "imgui.h"
#include "extgraph.h"
#include <windef.h>
#include <wingdi.h>

double BlockLength = 0.3;

Point FrameLeftCorner;

int Direction[4][2] = {
        {-1, 0},
        {0,  1},
        {1,  0},
        {0,  -1}
};

int Score;

int Level;

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

void DrawBlocks(int x, int y, int r, int c, char *InnerColor, char *OuterColor);

void DrawTetromino(Tetromino x) {
    SetPenColor(TetrominoColor[x.type]);
    switch (x.type) {
        case 1:
            x.direction = x.direction % 2;
            DrawBlocks(x.x, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[x.direction][0], x.y + Direction[x.direction][1], 1, 1, TetrominoColor[x.type],
                       "Black");
            DrawBlocks(x.x + Direction[(x.direction + 2) % 4][0], x.y + Direction[(x.direction + 2) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + 2 * Direction[(x.direction + 2) % 4][0], x.y + 2 * Direction[(x.direction + 2) % 4][1], 1,
                       1, TetrominoColor[x.type], "Black");
            break;
        case 2:
            DrawBlocks(x.x, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[x.direction][0], x.y + Direction[x.direction][1], 1, 1, TetrominoColor[x.type],
                       "Black");
            DrawBlocks(x.x + Direction[x.direction][0] + Direction[(x.direction + 1) % 4][0],
                       x.y + Direction[x.direction][1] + Direction[(x.direction + 1) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 2) % 4][0], x.y + Direction[(x.direction + 2) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            break;
        case 3:
            DrawBlocks(x.x, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[x.direction][0], x.y + Direction[x.direction][1], 1, 1, TetrominoColor[x.type],
                       "Black");
            DrawBlocks(x.x + Direction[(x.direction + 2) % 4][0] + Direction[(x.direction + 1) % 4][0],
                       x.y + Direction[(x.direction + 2) % 4][1] + Direction[(x.direction + 1) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 2) % 4][0], x.y + Direction[(x.direction + 2) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            break;
        case 4:
            DrawBlocks(x.x, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + 1, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x, x.y + 1, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + 1, x.y + 1, 1, 1, TetrominoColor[x.type], "Black");
            break;
        case 5:
            x.direction = x.direction % 2;
            DrawBlocks(x.x, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 2) % 4][0], x.y + Direction[(x.direction + 2) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 3) % 4][0], x.y + Direction[(x.direction + 3) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[x.direction][0] + Direction[(x.direction + 3) % 4][0],
                       x.y + Direction[x.direction][1] + Direction[(x.direction + 3) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            break;
        case 6:
            DrawBlocks(x.x, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[x.direction][0], x.y + Direction[x.direction][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 1) % 4][0], x.y + Direction[(x.direction + 1) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 2) % 4][0], x.y + Direction[(x.direction + 2) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            break;
        case 7:
            x.direction = x.direction % 2;
            DrawBlocks(x.x, x.y, 1, 1, TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[x.direction][0], x.y + Direction[x.direction][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 3) % 4][0], x.y + Direction[(x.direction + 3) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            DrawBlocks(x.x + Direction[(x.direction + 2) % 4][0] + Direction[(x.direction + 3) % 4][0],
                       x.y + Direction[(x.direction + 2) % 4][1] + Direction[(x.direction + 3) % 4][1], 1, 1,
                       TetrominoColor[x.type], "Black");
            break;
        default:
            break;
    }
}

void DrawFrame(double x, double y) {
    FrameLeftCorner.x = x;
    FrameLeftCorner.y = y;
    SetPenColor("Black");
    DrawBlocks(0, 0, 26, 2, "White", "Black");
    int column[] = {
            0, 7, 18, 25
    };
    for (int i = 0; i < sizeof(column) / sizeof(column[0]); i++) {
        DrawBlocks(column[i], 2, 1, 20, "White", "Black");
    }
    DrawBlocks(19, 2, 6, 11, "White", "Black");
    DrawBlocks(1, 2, 6, 8, "White", "Black");
    DrawBlocks(19, 2, 6, 11, "White", "Black");
    DrawBlocks(0, 22, 26, 2, "White", "Black");
    SetPenColor("Red");
    drawBox(x + 1 * BlockLength, y + 19 * BlockLength, BlockLength * 6, BlockLength * 3, 0, "Score", 'M', "Red");
    drawBox(x + 1 * BlockLength, y + 13 * BlockLength, BlockLength * 6, BlockLength * 3, 0, "Level", 'M', "Red");
    drawBox(x + 19 * BlockLength, y + 19 * BlockLength, BlockLength * 6, BlockLength * 3, 0, "Next One", 'M', "Red");
    setTextBoxColors("Blue", "Red", "Blue", "Red", 0);
    char *ScoreText = malloc(sizeof(char));
    char *LevelText = malloc(sizeof(char));
    itoa(Score, ScoreText, 10);
    itoa(Level, LevelText, 10);
    textbox(GenUIID(0), x + 1 * BlockLength, y + 16 * BlockLength, BlockLength * 6, BlockLength * 3, ScoreText, 20);
    textbox(GenUIID(1), x + 1 * BlockLength, y + 10 * BlockLength, BlockLength * 6, BlockLength * 3, LevelText, 20);
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
        }
    }
}
