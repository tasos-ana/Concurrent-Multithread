/*
 * implementation: Fine Grained Synchronization
 */
#include <stdlib.h>

#include "../headers/list.h"
#include "../headers/utils.h"

int insertList(int fileID, int fileSize) {
    listNode_p pred, curr;
    int result;
    lock(&(sharedList->head->mutex));
    pred = sharedList->head;
    curr = pred->next;
    lock(&(curr->mutex));
    while (curr->fileID < fileID) {
        unlock(&(pred->mutex));
        pred = curr;
        curr = curr->next;
        lock(&(curr->mutex));
    }
    if (fileID == curr->fileID) {
        result = 0;
    } else {
        listNode_p node = createListNode(fileID, fileSize);
        node->next = curr;
        pred->next = node;
        result = 1;
    }
    unlock(&(pred->mutex));
    unlock(&(curr->mutex));

    return result;
}

int deleteList(int fileID) {
    listNode_p pred, curr;
    int result;

    lock(&(sharedList->head->mutex));
    pred = sharedList->head;
    curr = pred->next;
    lock(&(curr->mutex));

    while (curr->fileID < fileID) {
        unlock(&(pred->mutex));
        pred = curr;
        curr = curr->next;
        lock(&(curr->mutex));
    }
    if (fileID == curr->fileID) {
        pred->next = curr->next;
        result = curr->fileSize;
    } else {
        result = -1;
    }
    unlock(&(pred->mutex));
    unlock(&(curr->mutex));

    return result;
}

int lookupList(int fileID) {
    listNode_p curr, pred;
    int result;

    lock(&(sharedList->head->mutex));
    pred = sharedList->head;
    curr = pred->next;
    lock(&(curr->mutex));
    while (curr->fileID < fileID) {
        unlock(&(pred->mutex));
        pred = curr;
        curr = curr->next;
        lock(&(curr->mutex));
    }
    if (fileID == curr->fileID) {
        result = curr->fileSize;
    } else {
        result = -1;
    }
    unlock(&(pred->mutex));
    unlock(&(curr->mutex));

    return result;
}

int modifyList(int fileID, int newFileSize) {
    listNode_p curr, pred;
    int result;

    lock(&(sharedList->head->mutex));
    pred = sharedList->head;
    curr = pred->next;
    lock(&(curr->mutex));
    while (curr->fileID < fileID) {
        unlock(&(pred->mutex));
        pred = curr;
        curr = curr->next;
        lock(&(curr->mutex));
    }
    if (fileID == curr->fileID) {
        result = curr->fileSize;
        curr->fileSize = newFileSize;
    } else {
        result = -1;
    }
    unlock(&(pred->mutex));
    unlock(&(curr->mutex));

    return result;
}