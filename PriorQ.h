#pragma once
#ifndef PRIORQ_H
#define PRIORQ_H

#include <stdlib.h>
#include <stdio.h>

typedef struct{
	int nKey;
	double nPrior;
} PQItem;

typedef struct{
	PQItem* pQueue;
	int PQSize;
	int PQCurrSize;
} PQueue;


PQueue* PQInit(int nSize);
int PQisEmpty(PQueue* q);
void PQEnqueue(PQueue* q, int nKey, double nPrior);
int PQDequeue(PQueue* q);
void PQClearQueue(PQueue* q);
void PQPrint(PQueue* q);
void DecreaseKey(PQueue* q, int nKey, double nPrior);
void IncreaseKey(PQueue* q, int nKey, double nPrior);
void PQRelease(PQueue** q);

#endif