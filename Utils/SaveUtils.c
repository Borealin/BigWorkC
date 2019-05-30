//
// Created by Borealin on 2019/5/14.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <genlib.h>
#include <GameUtils.h>
/*
   函数名称：SaveGame
   调用变量：
   函数功能：将游戏存档
 */
void SaveGame() {
    FILE *data;
    data = fopen("save.dat", "wb");
    fwrite(&current, sizeof(Tetromino), 1, data);
    fwrite(&next, sizeof(Tetromino), 1, data);
    fwrite(&hold, sizeof(Tetromino), 1, data);
    fwrite(&Score, sizeof(int), 1, data);
    fwrite(&Level, sizeof(int), 1, data);
    fwrite(&CanHold, sizeof(int), 1, data);
    fwrite(&AllClearedLayer, sizeof(int), 1, data);
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 22; ++j) {
            fwrite(&TetrominoMap[i][j], sizeof(int), 1, data);
        }
    }
    ListNodePtr currentNode = RankList->next;
    while (currentNode != NULL) {
        fwrite(&currentNode->name, NAMELENGTH * sizeof(char), 1, data);
        fwrite(&currentNode->score, sizeof(int), 1, data);
        currentNode = currentNode->next;
    }
    char end[NAMELENGTH] = "#";
    fwrite(&end, NAMELENGTH * sizeof(char), 1, data);
    fclose(data);
}

/*
   函数名称：RecoverGame
   调用变量：
   函数功能：读取先前的游戏存档
 */
int RecoverGame() {
    FILE *data;
    data = fopen("save.dat", "rb");
    if (data == NULL) {
        return 0;
    }
    fread(&current, sizeof(Tetromino), 1, data);
    fread(&next, sizeof(Tetromino), 1, data);
    fread(&hold, sizeof(Tetromino), 1, data);
    fread(&Score, sizeof(int), 1, data);
    fread(&Level, sizeof(int), 1, data);
    fread(&CanHold, sizeof(int), 1, data);
    fread(&AllClearedLayer, sizeof(int), 1, data);
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 22; ++j) {
            int tmp;
            fread(&tmp, sizeof(int), 1, data);
            TetrominoMap[i][j] = tmp;
        }
    }
    char tmpname[NAMELENGTH];
    int tmpscore;
    ListNodePtr head = CreateList();
    fread(&tmpname, NAMELENGTH * sizeof(char), 1, data);
    while (tmpname[0] != '#') {
        fread(&tmpscore, sizeof(int), 1, data);
        head = InsertNode(head, tmpscore, tmpname);
        fread(&tmpname, NAMELENGTH * sizeof(char), 1, data);
    }
    fclose(data);
    RankList = head;
    return 1;
}
