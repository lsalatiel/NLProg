#ifndef FIRST_PROGRAM_H
#define FIRST_PROGRAM_H

typedef struct Indexes Indexes;

Indexes* ReadTrainFile(Indexes* indexes, char** argv);
Indexes* AllocateIndexes(Indexes* indexes);
void FreeIndexes(Indexes* indexes);

#endif