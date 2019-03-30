#include "stdafx.h"
#include <stdlib.h>
#include "graph.h"
#include "Data.h"

int ReadData(const char* sFileName, Vertex** city){
	FILE* fin = NULL;
	if (!(fin = fopen(sFileName, "r"))){
		perror("nie mozna otworzyc pliku\n");
		return 0;
	}

	int VertexNumber = 0; //Liczba wierzcho³ków
	int tabSize = 0; //aktualny rozmiar tablicy

	Vertex* pCopyCity = *city;

	while (!feof(fin)){
		if (VertexNumber == tabSize){
			tabSize += AllocAddMem(&pCopyCity, VertexNumber);
			if (VertexNumber == tabSize) break;
		}

		Vertex* newVertex = &(pCopyCity[VertexNumber++]);
		fscanf(fin, "%d %d %d", &newVertex->VertexNumber, &newVertex->Type, &newVertex->NumOfNeighbours);

		newVertex->pListOfNeighbours = (List*)calloc(1, sizeof(List));
		if (!newVertex->pListOfNeighbours){
			perror("blad przy alokowaniu pamieci\n");
			return 0;
		}
		List* pList = newVertex->pListOfNeighbours;
		char c;

		while (((c = fgetc(fin)) != '\n') && (c != EOF)){
			ungetc(c, fin);
			ListItem* neighbour = (ListItem*)calloc(1, sizeof(ListItem));
			if (!neighbour){
				printf("blad przy alokowaniu pamieci\n");
				return 0;
			}
			fscanf(fin, "%d %lf", &neighbour->nKey, &neighbour->length);

			if (!pList->pHead)			//Jeœli nie ma ¿adnego s¹siada
				pList->pHead = neighbour;
			else
				pList->pTail->pNext = neighbour;
			pList->pTail = neighbour;
		}
	}
	fclose(fin);
	*city = pCopyCity;
	return VertexNumber;
}


int AllocAddMem(Vertex** city, int nCurrentSize){
	int newSize = nCurrentSize + REALLOC;
	Vertex* pTemp = (Vertex*)realloc(*city, newSize * sizeof(Vertex));
	if (!pTemp){
		printf("blad przy alokowaniu pamieci\n");
		return 0;
	}
	*city = pTemp;
	memset(*city + nCurrentSize, 0, REALLOC * sizeof(Vertex));
	return REALLOC;
}


void PrintData(Vertex* city, int nSize){
	FILE* fout = NULL;
	if (!(fout = fopen("Result.txt", "w+"))){
		printf("blad przy zapisie do pliku\n");
		return;
	}
	fprintf(fout, "Vertex:  Shop:  Distance: \t Time: \t\tPath:");
	for (int i = 0; i < nSize; i++){
		if (city[i].Type) continue;
		fprintf(fout, "\n%d\t", city[i].VertexNumber);
		fprintf(fout, "%d\t", city[i].ShopVertex);
		fprintf(fout, "%.2lf km\t\t", city[i].ShopDistance);
		fprintf(fout, "%.2lf\tmin\t", city[i].ShopTime * 60);
		int j = 0;

		while (city[i].ShopRoad[j] != city[i].ShopVertex)
			fprintf(fout, "%d -> ", city[i].ShopRoad[j++]);
		fprintf(fout, "%d ", city[i].ShopRoad[j]);
	}
	fclose(fout);
}
