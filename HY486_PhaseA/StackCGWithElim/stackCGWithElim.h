#ifndef STACKCGWITHELIM_H
#define STACKCGWITHELIM_H

#include <sys/types.h>

#include "../headers/stack.h"
#include "../headers/utils.h"

#define EMPTY 1
#define WAITING 2
#define BUSY 3

typedef struct exchangerNode {
    stackNode_p node;
    int state;
} *exchangerNode_p, exchangerNode_s;

exchangerNode_p *exchanger;
pthread_mutex_t exchangeMutex;

pthread_mutex_t successMutex;
int totalSuccess;

pthread_mutex_t failureMutex;
int totalFailure;

int minRange;
int maxRange;

stackNode_p TIMEOUT_S;

void initExchanger(void);

exchangerNode_p createExchangerNode(stackNode_p data, int state);

int calculateRange(void);

long calculateDuration(void);

void recordSuccess(void);

void recordFailure(void);

stackNode_p visit(stackNode_p value, int range, long duration);

stackNode_p exchange(exchangerNode_p slot, stackNode_p myItem, long timeout);

long getNanos(void);

void cleanExchanger(void);
#endif // STACKCGWITHELIM_H

