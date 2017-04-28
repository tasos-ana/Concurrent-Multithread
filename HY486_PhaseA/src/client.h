#ifndef CLIENT_H
#define CLIENT_H

char* filepath;

void* clientLogic(void * threadID);

int clientInsert(int threadID, int id, int fileID, int fileSize);

int clientLookup(int threadID, int id, int fileID);

int clientModify(int threadID, int id, int fileID, int newFileSize);

int clientDelete(int threadID, int id, int fileID);

void barrier(int threadID, int wait);

#endif // CLIENT_H

