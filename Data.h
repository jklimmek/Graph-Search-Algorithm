#ifndef DATA_H
#define DATA_H

#include "stdafx.h"
#include <stdlib.h>
#include "graph.h"

#define REALLOC 3
#define SPEED 5

int ReadData(const char* sFileName, Vertex** pBuildings);
int AllocAddMem(Vertex** pBuildings, int nCurrentSize);
void PrintData(Vertex* buildings, int nSize);

#endif // !DATA_H
