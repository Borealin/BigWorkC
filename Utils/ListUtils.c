//
// Created by Borealin on 2019/5/7.
//
#include <ListUtils.h>
#include <stdio.h>
#include <stdlib.h>
#include <genlib.h>
#include <mem.h>

#define New(type) ((type) GetBlock(sizeof *((type) NULL)))

ListNodePtr CreateList(void) {
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

ListNodePtr InsertNode(ListNodePtr head,int val,char* name) {
    ListNodePtr current,previous;
    current=head->next;
    previous = head;
    while(current!=NULL&&current->score>=val){
        previous=current;
        current=current->next;
    }
    ListNodePtr NewNode=New(ListNodePtr);
    NewNode->score=val;
    strncpy(NewNode->name,name, sizeof(NewNode->name));
    previous->next=NewNode;
    NewNode->next=current;
    return head;
}

ListNodePtr DeleteNode(ListNodePtr head) {
    ListNodePtr current;
    current = head;
    int count=0;
    while (current->next != NULL&&count<10) {
        current = current->next;
        count++;
    }
   current->next=NULL;
    return head;
}
