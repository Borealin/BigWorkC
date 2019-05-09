//
// Created by Borealin on 2019/5/7.
//

#ifndef BIGWORK_DRAWUTILS_H
#define BIGWORK_DRAWUTILS_H

int Direction[16][2];
int TetrominoShape[8][4];
int TetrominoDirectionMod[8];

typedef struct {
    int x, y;
    int direction;
    int type;
} Tetromino;

typedef struct {
    int x, y;
} Point;

typedef struct {
    double x, y;
} DoublePoint;

const double BlockLength;

void DrawTetromino(Tetromino x);

void DrawFrame(double x, double y);

void DrawLayers(int head[12][22]);

void DrawGameOver();

#endif //BIGWORK_DRAWUTILS_H
