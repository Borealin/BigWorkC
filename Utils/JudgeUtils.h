//
// Created by Borealin on 2019/5/7.
//

#ifndef BIGWORKC_JUDGEUTILS_H
#define BIGWORKC_JUDGEUTILS_H

#include <DrawUtils.h>

const int X_CORNER;
const int Y_CORNER;


int JudgeBorder(Tetromino x, int FallDirection);

void LayerInit();

int JudgeGameOver(Tetromino x);

#endif //BIGWORKC_JUDGEUTILS_H
