/* * * * * * * * * * * * * * *\
 *                           *
 * General functions of list *
 *                           *
 * File:    headers/list.h   *
 * Author:  Tasos Anastasas  *
 * A.M:     3166             *
 * Course:  CS486            *
 * Project: 2017             *
 * Phase:   1                *
\* * * * * * * * * * * * * * */
#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <sys/types.h>

typedef struct listNode {
    int fileID; //Key
    int fileSize;
    int marked; // true = 1 --- false = 0
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

void printList(void);

void printListNode(listNode_p node);

void cleanList(void);

void cleanListNode(listNode_p node);
#endif // LIST_H

