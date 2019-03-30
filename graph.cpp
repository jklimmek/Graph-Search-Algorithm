#include <math.h>
#include "graph.h"
#include "PriorQ.h"
#include "Data.h"

double PathFinder(Vertex* city, int nSize, int nFirst){
	PQueue* pQ = PQInit(nSize);
	double* distance = (double*)calloc(1, nSize * sizeof(double));

	city[nFirst].ShopRoad = (int*)calloc(nSize, sizeof(int));

	if (!distance || !(city[nFirst].ShopRoad)){
		printf("blad przy alokowaniu pamieci\n");
		return 1;
	}

	for (int i = 0; i < nSize; i++){
		distance[i] = INFINITY;	//  max dystans 
		city[nFirst].ShopRoad[i] = -1;
	}

	double length = 0;
	distance[nFirst] = 0;
	PQEnqueue(pQ, nFirst, 0);
	while (!PQisEmpty(pQ)){
		int u = PQDequeue(pQ);
		if (city[u].Type){
			city[nFirst].ShopVertex = u;
			length = distance[u];
			PQRelease(&pQ);
			break;
		}
		else{
			ListItem* neighbour = city[u].pListOfNeighbours->pHead;
			while (neighbour){
				int i = neighbour->nKey;
				if (distance[i] > distance[u] + neighbour->length){
					distance[i] = distance[u] + neighbour->length; //dystans
					city[nFirst].ShopRoad[i] = u; //poprzednik
					PQEnqueue(pQ, i, distance[i]);
				}
				neighbour = neighbour->pNext;
			}
		}
	}
	free(distance);
	return length;
}


void DFS(Vertex* city, int v, int* visited){
	ListItem* u = city[v].pListOfNeighbours->pHead;
	visited[v] = 1;
	while (u){
		u->time = u->length / SPEED;
		if (!visited[u->nKey])
			DFS(city, u->nKey, visited);
		u = u->pNext;
	}
}
