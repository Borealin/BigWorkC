//
// Created by Borealin on 2019/5/7.
//

#ifndef BIGWORKC_LISTUTILS_H
#define BIGWORKC_LISTUTILS_H
#define NAMELENGTH 16

struct ListNode {
    int score;
    char name[NAMELENGTH];
    struct ListNode *next;
};
typedef struct ListNode *ListNodePtr;

ListNodePtr CreateList(void);

void freeList(ListNodePtr head);

ListNodePtr InsertNode(ListNodePtr head, int val, char *name);

ListNodePtr DeleteNode(ListNodePtr head);

#endif //BIGWORKC_LISTUTILS_H
