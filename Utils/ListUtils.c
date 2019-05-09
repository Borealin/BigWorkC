//
// Created by Borealin on 2019/5/7.
//
#include <ListUtils.h>
#include <stdio.h>
#include <stdlib.h>
#include <genlib.h>

#define New(type) ((type) GetBlock(sizeof *((type) NULL)))

ListNodePtr createList(void) {
    ListNodePtr head = New(ListNodePtr);
    head->next = NULL;
    return head;
}

void freeList(ListNodePtr head) {
    ListNodePtr current, next;
    current = head;
    while (current != NULL) {
        next = current->next;
        FreeBlock(current);
        current = next;
    }
}

ListNodePtr InsertNode(ListNodePtr head, ListNodePtr node, int val) {
    ListNodePtr newNode = New(ListNodePtr);
    if (node == NULL) {//append to the tail
        node = head;
        while (node->next != NULL) {
            node = node->next;
        }
    }
    newNode->score = val;
    newNode->next = node->next;
    node->next = newNode;
    return head;
}

ListNodePtr DeleteNode(ListNodePtr head) {
//    ListNodePtr current, previous;
//    previous = New(ListNodePtr);
//    current = head;
//    head = previous;
//    while (current != NULL) {
//
//        if (tmp) {
//            current = current->next;
//            previous->next = current;
//        }
//        previous = current;
//        current = current->next;
//    }
//    return head->next;
}
