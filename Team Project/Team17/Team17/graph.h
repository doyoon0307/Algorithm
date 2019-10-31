# ifndef GRAPH_H
# define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "RBT_hotel.h"

//typedef enum { false, true } bool;

typedef struct _TRANSPORT {
	int path_id;
	int length;
	int fee;
} TRANSPORT;

typedef struct _GNode {
	int id;
	TRANSPORT path;
	int money;
	struct _GNode *next;
	struct HNode *hotel;
} GNode;

typedef struct {
	int num;
	GNode **heads;
} Graph;

void CreateGraph(Graph *pgraph, int num);

void DestroyGraph(Graph *pgraph);

void AddEdge(Graph *pgraph, int src, int dest, int path_id, int length, int transportationfee);

void PrintGraph(Graph *pgraph);

void MakeHotelInfo(GNode *city, struct HNode *Hotel);

int BFS(Graph *pgraph, int start_c, int end_c);
#endif