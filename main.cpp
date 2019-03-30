#include "stdafx.h"
#include <stdlib.h>
#include <memory.h>
#include "Data.h"
#include "PriorQ.h"


int FindShortestPath(Vertex* city, int nSize);


int main(int argc, char** argv)
{
	if (argc != 2){
		printf("nieprawidlowa liczba argumentow\n");
		return 1;
	}

	Vertex* city = NULL;
	int vertices = ReadData(argv[1], &city);
	if (!vertices){
		printf("brak wierzcholkow grafu\n");
		return 1;
	}

	int* visited = (int*)calloc(vertices, sizeof(int));
	if (!visited){
		printf("blad przy alokowaniu pamieci\n");
		return 1;
	}

	DFS(city, 0, visited);

	if (!FindShortestPath(city, vertices)){
		printf("drogi nie ma");
		return 1;
	}

	PrintData(city, vertices);
	printf("wyniki zapisano w pliku: Results.txt \n");

	for (int i = 0; i < vertices; i++){
		while (ListItem* tmp = city[i].pListOfNeighbours->pHead){
			city[i].pListOfNeighbours->pHead = tmp->pNext;
			free(tmp);
		}
	}
	free(visited);
	free(city);
	visited = NULL;
	city = NULL;
	return 0;
}


int FindShortestPath(Vertex* city, int nSize){
	for (int i = 0; i < nSize; i++){
		if (!city[i].Type){ 
			city[i].ShopDistance = PathFinder(city, nSize, i); //najkrótsza droga
			city[i].ShopTime = city[i].ShopDistance / SPEED; //oblicza czas drogi do sklepu

			int* Path = (int*)calloc(nSize, sizeof(int));
			if (!Path){
				printf("blad przy alokowaniu pamieci\n");
				return 0;
			}

			int temp = city[i].ShopVertex;

			int p = 1;
			Path[0] = temp;
			while (p< nSize && Path[p - 1] != i){//zapisanie œcie¿ki (wpisuj dopóki nie dojdziesz do wierzcho³ka z którego wyszed³eœ)
				Path[p++] = temp;
				temp = city[i].ShopRoad[temp];
			}

			for (int j = 0; j < (p / 2); j++){ //odwracanie tablicy œcie¿ki
				temp = Path[j];
				Path[j] = Path[p - 1 - j];
				Path[p - 1 - j] = temp;
			}
			free(city[i].ShopRoad);
			city[i].ShopRoad = Path;
		}
	}
	return 1;
}