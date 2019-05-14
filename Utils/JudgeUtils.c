//
// Created by Borealin on 2019/5/7.
//
#include <stdio.h>
#include <DrawUtils.h>
#include <ListUtils.h>
#include <GameUtils.h>

const int X_CORNER = 7;
const int Y_CORNER = 1;


void ClearFullLayer();

void LayerInit() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 22; ++j) {
            TetrominoMap[i][j] = 0;
        }
    }
    for (int i = 0; i < 12; i++) {
        TetrominoMap[i][0] = 1;
        TetrominoMap[i][21] = 1;
    }
    for (int i = 1; i < 21; i++) {
        TetrominoMap[0][i] = 1;
        TetrominoMap[11][i] = 1;
    }
}

void UpdateLayers(Tetromino x) {
    int dir = x.direction % TetrominoDirectionMod[x.type];
    for (int i = 0; i < 4; ++i) {
        TetrominoMap[x.x + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][0] - X_CORNER][x.y + Direction[
                (TetrominoShape[x.type][i] + 4 * dir) % 16][1] - Y_CORNER + 1] = x.type;
    }
    ClearFullLayer();
}

int JudgeBorder(Tetromino x, int FallDirection) {//0:nothing been blocked 1:down been blocked
    int dir = x.direction % TetrominoDirectionMod[x.type];
    for (int i = 0; i < 4; ++i) {
        int tx = x.x + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][0] - X_CORNER;
        int ty = x.y + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][1] - Y_CORNER;
        if (tx <= 0 || tx >= 11) {
            return 0;
        }
        if (TetrominoMap[tx][ty]) {
            if (FallDirection == 3) {
                UpdateLayers(x);
            }
            return 0;
        }
    }
    return 1;
}

void ClearFullLayer() {
    int count = 0;
    for (int j = 1; j < 21; ++j) {
        int clear = 1;
        for (int i = 1; i < 11; ++i) {
            if (!TetrominoMap[i][j]) {
                clear = 0;
                break;
            }
        }
        if (clear) {
            count++;
            for (int k = j + 1; k < 21; ++k) {
                for (int i = 1; i < 11; ++i) {
                    TetrominoMap[i][k - 1] = TetrominoMap[i][k];
                }
            }
            j--;
        }
    }
    Score += ScoreAdd[count];
}

int JudgeGameOver(Tetromino x) {
    int dir = x.direction % TetrominoDirectionMod[x.type];
    for (int i = 0; i < 4; ++i) {
        if (x.y + Direction[(TetrominoShape[x.type][i] + 4 * dir) % 16][1] - Y_CORNER + 1 >= 20) {
            return 1;
        }
    }
    return 0;
}