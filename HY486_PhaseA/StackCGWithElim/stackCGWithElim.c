/*
 * implementation: Coarse Grained Stack with elimination array
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

#include "stackCGWithElim.h"
#include "../headers/stack.h"
#include "../headers/utils.h"
#include "../headers/updater.h"

void initStack(void) {
    modStack = (stack_p) malloc(sizeof (stack_s));
    modStack->top = NULL;
    initMutex(&(modStack->mutex));
    initMutex(&printStackMutex);

    initMutex(&exchangeMutex);
    minRange = totalThreads;
    maxRange = minRange * 2;
    initExchanger();

    TIMEOUT_S = createStackNode(-1, -1, -1);

    initMutex(&successMutex);
    totalSuccess = 0;

    initMutex(&failureMutex);
    totalFailure = 0;
}

void initExchanger(void) {
    int i;
    time_t t;
    srand((unsigned) time(&t)); // should only be called once

    exchanger = (exchangerNode_p*) malloc(maxRange * sizeof (exchangerNode_p));
    for (i = 0; i < maxRange; ++i) {
        exchanger[i] = createExchangerNode(NULL, EMPTY);
    }
}

exchangerNode_p createExchangerNode(stackNode_p data, int state) {
    exchangerNode_p node = (exchangerNode_p) malloc(sizeof (exchangerNode_s));
    node->node = data;
    node->state = state;

    return node;
}

int calculateRange(void) {
    int retVal;

    double failurePerc = totalFailure % 10000;
    double successPerc = totalSuccess % 100;

    retVal = maxRange - failurePerc + successPerc;

    if (retVal < minRange) {
        retVal = minRange;
    } else if (retVal > maxRange) {
        retVal = maxRange;
    }
    return retVal;
}

long calculateDuration(void) {
    long retVal;
    long minDuration, maxDuration;
    minDuration = 1.0;
    maxDuration = 1.2;

    long failurePerc = totalFailure % 5000;
    long successPerc = totalSuccess % 10;

    retVal = maxDuration + (0.01) * failurePerc - (0.01) * successPerc;

    if (retVal < minDuration) {
        retVal = minDuration;
    } else if (retVal > maxDuration) {
        retVal = maxDuration;
    }
    return (long) retVal * 1000000000;
}

void recordSuccess(void) {
    lock(&successMutex);
    totalSuccess += 1;
    unlock(&successMutex);
}

void recordFailure(void) {
    lock(&failureMutex);
    totalFailure += 1;
    unlock(&failureMutex);
}

stackNode_p visit(stackNode_p value, int range, long duration) {
    //int el = (rand() % range); // returns a pseudo-random integer between 0 and RAND_MAX
    int el = random() % range;
    return (exchange(exchanger[el], value, duration));
}

stackNode_p exchange(exchangerNode_p slot, stackNode_p myItem, long timeout) {
    long timeBound;
    stackNode_p yourItem;
    int state;

    timeBound = getNanos() + timeout;
    while (1) {
        if (getNanos() > timeBound) return TIMEOUT_S;
        lock(&exchangeMutex);
        state = slot->state;
        yourItem = slot->node;
        switch (state) {
            case EMPTY:
                slot->node = myItem;
                slot->state = WAITING;
                unlock(&exchangeMutex);
                while (getNanos() < timeBound) {
                    state = slot->state;
                    yourItem = slot->node;
                    if (state == BUSY) {
                        slot->node = NULL;
                        slot->state = EMPTY;
                        return yourItem;
                    }
                }
                if (state == WAITING && slot->node == myItem) {
                    slot->node = NULL;
                    slot->state = EMPTY;
                    return TIMEOUT_S;
                } else {
                    lock(&exchangeMutex);
                    state = slot->state;
                    yourItem = slot->node;

                    slot->node = NULL;
                    slot->state = EMPTY;
                    unlock(&exchangeMutex);
                    return yourItem;
                }
            case WAITING:
                slot->node = myItem;
                slot->state = BUSY;
                unlock(&exchangeMutex);
                return yourItem;
            case BUSY:
                unlock(&exchangeMutex);
                break;
            default:
                assert(0);
        }
    }
}

void pushStack(stackNode_p node) {
    stackNode_p otherValue;

    otherValue = visit(node, calculateRange(), calculateDuration());
    if (otherValue == NULL) {
        recordSuccess();
        return;
    } else if (otherValue == TIMEOUT_S) {
        recordFailure();
    }
    lock(&(modStack->mutex));
    node->next = modStack->top;
    modStack->top = node;
    unlock(&(modStack->mutex));
}

stackNode_p popStack(void) {
    stackNode_p otherValue;

    otherValue = visit(NULL, calculateRange(), calculateDuration());
    if (otherValue == TIMEOUT_S) {
        recordFailure();
    } else if (otherValue != NULL) {
        assert(otherValue != TIMEOUT_S);
        recordSuccess();
        return otherValue;
    }

    lock(&(modStack->mutex));
    otherValue = modStack->top;
    if (otherValue != NULL) {
        modStack->top = otherValue->next;
    }
    unlock(&(modStack->mutex));
    return otherValue;
}

long getNanos(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (long) now.tv_sec * 1000000000 + now.tv_nsec;
}

void cleanExchanger(void) {
    int i = 0;
    exchangerNode_p current;
    for (i = 0; i < maxRange; ++i) {
        current = exchanger[i];
        free(current->node);
        current->node = NULL;
        free(current);
        current = NULL;
    }

    free(exchanger);
    exchanger = NULL;
}

void cleanStack(void) {
    //free the stack
    stackNode_p current = modStack->top, tmp;
    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp);
        tmp = NULL;
    }

    destroyMutex(&(modStack->mutex));
    destroyMutex(&printStackMutex);

    //clean exchanger mutex and array
    destroyMutex(&exchangeMutex);
    cleanExchanger();

    free(modStack);
    modStack = NULL;

    free(TIMEOUT_S);
    TIMEOUT_S = NULL;

    printf("Succeed: %d\n", totalSuccess);
    printf("Failure: %d\n", totalFailure);
}