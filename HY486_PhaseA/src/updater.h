#ifndef UPDATER_H
#define UPDATER_H

#include <sys/types.h>

int total_operations;
int clientsDone;

pthread_mutex_t totalOperationMutex;

void initUpdaters(void);

void* updaterLogic(void * id);

void updaterInsert(int threadID, int fileID, int fileSize);

void updaterLookup(int threadID, int fileID);

void updaterModify(int threadID, int fileID, int newFileSize);

void updaterDelete(int threadID, int fileID);

void increaseOperations(void);

void cleanUpdaters(void);
#endif // UPDATER_H

