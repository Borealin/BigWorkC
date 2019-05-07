//
// Created by Borealin on 2019/5/7.
//

#ifndef BIGWORKC_LISTUTILS_H
#define BIGWORKC_LISTUTILS_H

struct ListNode {
    int *sto;
    struct ListNode *next;
};
typedef struct ListNode *ListNodePtr;

ListNodePtr createList(void);

void freeList(ListNodePtr head);

ListNodePtr InsertNode(ListNodePtr head, ListNodePtr node, int *val);

ListNodePtr DeleteNode(ListNodePtr head);

#endif //BIGWORKC_LISTUTILS_H
