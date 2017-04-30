#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>

char* filepath;
pthread_barrier_t clientBarrier;

void initClients(char *file, int clients);

void* clientLogic(void * id);

void clientInsert(int threadID, int id, int fileID, int fileSize);

void clientLookup(int threadID, int id, int fileID);

void clientModify(int threadID, int id, int fileID, int newFileSize);

void clientDelete(int threadID, int id, int fileID);

void barrier(int threadID, int wait);

void cleanClient(void);
#endif // CLIENT_H

