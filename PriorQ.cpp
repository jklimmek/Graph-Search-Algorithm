#include "stdafx.h"
#include <stdlib.h>
#include "PriorQ.h"


void UpdateDown(PQueue* q, int l, int p){
	if (l == p) return;
	int i = l;
	int j = 2 * i + 1;
	PQItem tmp = q->pQueue[i];
	while (j <= p){
		if (j < p)
			if (q->pQueue[j].nPrior > q->pQueue[j + 1].nPrior)
				j++;

		if (tmp.nPrior < q->pQueue[j].nPrior) break;

		q->pQueue[i] = q->pQueue[j];
		i = j;
		j = 2 * i + 1;
	}
	q->pQueue[i] = tmp;
}



void UpdateUp(PQueue* q, int l, int p){
	if (l == p) return;
	int i = p;
	int j = (i - 1) / 2;
	PQItem tmp = q->pQueue[i];
	while ((i > 0) && (q->pQueue[j].nPrior > tmp.nPrior)){
		q->pQueue[i] = q->pQueue[j];
		i = j;
		j = (i - 1) / 2;
	}
	q->pQueue[i] = tmp;
}


PQueue* PQInit(int nSize){
	PQueue* q = (PQueue*)calloc(1, sizeof(PQueue));
	if (!q){
		printf("Blad! PQInit\n");
		return NULL;
	}

	q->pQueue = (PQItem*)calloc(nSize, sizeof(PQItem));
	if (!q->pQueue){
		printf("Blad! PQInit\n");
		return NULL;
	}

	q->PQCurrSize = 0;
	q->PQSize = nSize;

	return q;
}


int PQisEmpty(PQueue* q){
	return !(q->PQCurrSize);
}



void PQEnqueue(PQueue* q, int nKey, double nPrior){
	if (q->PQCurrSize == q->PQSize){
		printf("Blad! PQEnqueue\n");
		return;
	}
	int i = q->PQCurrSize++;
	q->pQueue[i].nKey = nKey;
	q->pQueue[i].nPrior = nPrior;
	UpdateUp(q, 0, i);
}



int PQDequeue(PQueue* q){
	if (PQisEmpty(q)){
		printf("Blad! PQDequeue\n");
		return 0;
	}

	int i = --q->PQCurrSize;
	int x = q->pQueue[0].nKey;
	q->pQueue[0].nKey = q->pQueue[i].nKey; 
	q->pQueue[0].nPrior = q->pQueue[i].nPrior; 
	UpdateDown(q, 0, i);  

	return x;
}



void PQClearQueue(PQueue* q){
	memset(q->pQueue, 0, q->PQSize * sizeof(PQItem));
	q->PQCurrSize = 0;
}



void PQRelease(PQueue** q){
	PQClearQueue(*q);
	free((*q)->pQueue);
	free(*q);
	*q = NULL;
}




void PQPrint(PQueue* q){
	for (int i = 0; i < q->PQCurrSize; i++)
		printf("%d ", q->pQueue[i].nKey);
}



void DecreaseKey(PQueue* q, int nKey, double nPrior){
	if (nPrior < q->pQueue[nKey].nPrior){
		q->pQueue[nKey].nPrior = nPrior;
		UpdateDown(q, nKey, q->PQCurrSize - 1);
	}
}



void IncreaseKey(PQueue* q, int nKey, double nPrior){
	if (nPrior > q->pQueue[nKey].nPrior){
		q->pQueue[nKey].nPrior = nPrior;
		UpdateUp(q, 0, nKey);
	}
}

