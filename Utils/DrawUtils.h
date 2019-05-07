//
// Created by Borealin on 2019/5/7.
//

#ifndef BIGWORK_DRAWUTILS_H
#define BIGWORK_DRAWUTILS_H

typedef struct {
    int x,y;
    int direction;
    int type;
}Tetromino;

typedef struct {
    double x, y;
} Point;

double BlockLength;

void DrawTetromino(Tetromino x);

void DrawFrame(double x, double y);

#endif //BIGWORK_DRAWUTILS_H
