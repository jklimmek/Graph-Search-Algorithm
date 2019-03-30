#ifndef GRAPH_H
#define GRAPH_H

typedef struct tagListItem {
	int nKey;					// Numer wierzcho³ka
	double length;
	double time;
	tagListItem* pNext;			// Kolejny sasiad
}ListItem;


typedef struct {
	ListItem* pHead;
	ListItem* pTail;
}List;


typedef struct {
	int VertexNumber;
	List* pListOfNeighbours;	// Lista sasiadow
	int Type;					// 0 - sklep, 1 - dom
	int ShopVertex;				// Najblizszy sklep
	double ShopDistance;		// Dystans do najbli¿szego sklepu
	int* ShopRoad;			// Sciezka do sklepu
	double ShopTime;			// Czas dojscia do najblizszego sklepu
	int NumOfNeighbours;		// Liczba sasiadow
}Vertex;

double PathFinder(Vertex* graph, int nSize, int nFirst);
void DFS(Vertex* graph, int v, int* visited);

#endif // !GRAPH_H