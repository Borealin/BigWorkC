//
// Created by Borealin on 2019/5/7.
//

#ifndef BIGWORKC_JUDGEUTILS_H
#define BIGWORKC_JUDGEUTILS_H

#include <DrawUtils.h>

int TetrominoMap[12][22];

const int X_CORNER;
const int Y_CORNER;


int JudgeBorder(Tetromino x,int FallDirection);

void LayerInit();

#endif //BIGWORKC_JUDGEUTILS_H
