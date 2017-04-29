#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct listNode {
    int fileID; //Key
    int fileSize;
    int marked; // true = 1 --- false = 0
    int modify;
    pthread_mutex_t mutex;
    struct listNode *next;
} *listNode_p, listNode_s;

typedef struct list {
    listNode_p head;
    listNode_p tail;
} *list_p, list_s;

list_p sharedList;

void initList(void);

int isEmptyList(void);

listNode_p createListNode(int fileID, int fileSize);

int insertList(int fileID, int fileSize);

int deleteList(int fileID);

int lookupList(int fileID);

int modifyList(int fileID, int newFileSize);

int validateList(listNode_p pred, listNode_p curr);

void printList(void);

void printListNode(listNode_p node);

void cleanList(void);

void cleanListNode(listNode_p node);
#endif // LIST_H

