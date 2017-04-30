#include <stdlib.h>
#include <limits.h>

#include "../src/list.h"
#include "../src/utils.h"
#include "../src/updater.h"

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

int insertList(int fileID, int fileSize) {
    listNode_p pred, curr;
    int result;
    int return_flag = 0;

    while (1) {
        pred = sharedList->head;
        curr = pred->next;
        while (curr->fileID < fileID) {
            pred = curr;
            curr = curr->next;
        }
        lock(&(pred->mutex));
        lock(&(curr->mutex));
        if (validateList(pred, curr)) {
            if (fileID == curr->fileID) {
                result = 0;
            } else {
                listNode_p node = createListNode(fileID, fileSize);
                node->next = curr;
                pred->next = node;
                result = 1;
            }
            return_flag = 1;
        }
        unlock(&(pred->mutex));
        unlock(&(curr->mutex));
        if (return_flag) {
            return result;
        }
    }
}

int deleteList(int fileID) {
    listNode_p pred, curr;
    int result;
    int return_flag = 0;

    while (1) {
        pred = sharedList->head;
        curr = pred->next;
        while (curr->fileID < fileID) {
            pred = curr;
            curr = curr->next;
        }
        lock(&(pred->mutex));
        lock(&(curr->mutex));
        if (validateList(pred, curr)) {
            if (fileID == curr->fileID) {
                curr->marked = 1;
                pred->next = curr->next;
                result = curr->fileSize;
            } else {
                result = -1;
            }
            return_flag = 1;
        }
        unlock(&(pred->mutex));
        unlock(&(curr->mutex));
        if (return_flag) {
            return result;
        }
    }
}

int lookupList(int fileID) {
    listNode_p curr;
    int result;
    int return_flag = 0;

    while (1) {
        curr = sharedList->head;
        while (curr->fileID < fileID) {
            curr = curr->next;
        }
        result = curr->fileSize; //[*]
        if (curr->marked == 0 &&
                fileID == curr->fileID) {//[*]
            if (result == curr->fileSize) { //On succeed then linearized at line 104 {result = curr->fileSize;}
                return_flag = 1; //on fail linearized at 105 line {if (curr->marked == 0 && fileID == curr->fileID)}
            }
        } else { // same linearize point with course material pdf 5
            result = -1;
            return_flag = 1;
        }
        if (return_flag) {
            return result;
        }
    }
}

int modifyList(int fileID, int newFileSize) {
    listNode_p pred, curr;
    int result;
    int return_flag = 0;

    while (1) {
        pred = sharedList->head;
        curr = pred->next;
        while (curr->fileID < fileID) {
            pred = curr;
            curr = curr->next;
        }

        lock(&(pred->mutex));
        lock(&(curr->mutex));
        if (validateList(pred, curr)) {
            if (fileID == curr->fileID) {
                result = curr->fileSize;
                curr->fileSize = newFileSize;
            } else {
                result = -1;
            }
            return_flag = 1;
        }
        unlock(&(pred->mutex));
        unlock(&(curr->mutex));
        if (return_flag) {
            return result;
        }
    }
}

int validateList(listNode_p pred, listNode_p curr) {
    if (pred->marked == 0 &&
            curr->marked == 0 &&
            pred->next == curr) {
        return 1;
    } else {
        return 0;
    }
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