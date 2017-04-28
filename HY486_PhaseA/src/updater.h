#ifndef UPDATER_H
#define UPDATER_H

int total_operations;
int clientsDone;

void* updaterLogic(void * threadID);

void updaterInsert(int threadID, int id, int fileID, int fileSize);

void updaterLookup(int threadID, int id, int fileID);

void updaterModify(int threadID, int id, int fileID, int newFileSize);

void updaterDelete(int threadID, int id, int fileID);

void updaterPrint(int threadID, int id);
#endif // UPDATER_H

