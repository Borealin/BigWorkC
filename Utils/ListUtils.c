//
// Created by Borealin on 2019/5/7.
//

#define _CRT_SECURE_NO_WARNINGS
#include <ListUtils.h>
#include <stdio.h>
#include <stdlib.h>
#include <genlib.h>
#include <string.h>

ListNodePtr CreateList(void) {
    ListNodePtr head = New(ListNodePtr);
    head->next = NULL;
    return head;
}
/*
 * 函数名称：freeList
 * 调用变量：ListNodePtr head
 * 函数功能：清空以head为头节点的链表
 */
void freeList(ListNodePtr head) {
    ListNodePtr current, next;
    current = head;
    while (current != NULL) {
        next = current->next;
        FreeBlock(current);
        current = next;
    }
}
/*
 * 函数名称：InsertNode
 * 调用变量：ListNodePtr head, int val, char*
 * 函数功能：将新的用户名和用户得分按得分排行插入到原有的链表中
 */
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
