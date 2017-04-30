/*
 * implementation: Lazy Synchronization
 */
#include <stdlib.h>
#include <limits.h>

#include "../headers//updater.h"
#include "../headers/list.h"
#include "../headers/utils.h"
#include "listLazySync.h"

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