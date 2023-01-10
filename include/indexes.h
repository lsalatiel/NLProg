#ifndef FIRST_PROGRAM_H
#define FIRST_PROGRAM_H

typedef struct Indexes Indexes;

Indexes* ReadTrainFile(Indexes* indexes, char** argv);
Indexes* AllocateIndexes(Indexes* indexes);
void FreeIndexes(Indexes* indexes);

Indexes* ReadInfo(Indexes* indexes);

Indexes* CreateIndexesFromFile(Indexes* indexes, FILE* file, int document_index);

#endif