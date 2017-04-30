/*
 * implementation: general list functions
 */
#include <stdlib.h>
#include <limits.h>

#include "../headers/updater.h"
#include "../headers/list.h"
#include "../headers/utils.h"

void initList(void) {
    sharedList = (list_p) malloc(sizeof (list_s));
    sharedList->head = createListNode(INT_MIN, INT_MIN);
    sharedList->tail = createListNode(INT_MAX, INT_MAX);
    sharedList->head->next = sharedList->tail;
}

int isEmptyList(void) {
    return (sharedList->head->next == sharedList->tail);
}

listNode_p createListNode(int fileID, int fileSize) {
    listNode_p node = (listNode_p) malloc(sizeof (listNode_s));
    node->fileID = fileID;
    node->fileSize = fileSize;
    node->marked = 0;
    initMutex(&(node->mutex));
    node->next = NULL;
    return node;
}

void printList(void) {
    listNode_p curr = sharedList->head->next;
    listNode_p tail = sharedList->tail;

    if (isEmptyList()) {
        printf("Empty List\n");
    } else {
        printf("\nFILESYSTEM: \n");
        while (curr != tail) {
            printListNode(curr);
            curr = curr->next;
        }
        printf("Total operations: %d\n", total_operations);
    }
}

void printListNode(listNode_p node) {
    printf("%d : %d", node->fileID, node->fileSize);
    if (node->next != sharedList->tail) {
        printf(",\n");
    } else {
        printf("\n");
    }
}

void cleanList(void) {
    //TODO osa ginontai delete na mpainoun se stack/list gia clean sto telos
    listNode_p curr = sharedList->head->next;
    listNode_p tail = sharedList->tail;
    listNode_p tmp;
    while (curr != tail) {
        tmp = curr;
        curr = curr->next;
        cleanListNode(tmp);
    }

    cleanListNode(sharedList->head);
    cleanListNode(tail);

    free(sharedList);
    sharedList = NULL;
}

void cleanListNode(listNode_p node) {
    destroyMutex(&(node->mutex));
    free(node);
    node = NULL;
}