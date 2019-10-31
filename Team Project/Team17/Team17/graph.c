#include "graph.h"
#include "Queue.h"
#include <stdlib.h>
#include <time.h>

void CreateGraph(Graph *pgraph, int num) {
	srand(time(NULL));
	pgraph->num = num;
	pgraph->heads = (GNode **)malloc(sizeof(GNode *) * num);
	for (int i = 0; i < num; i++) {
		pgraph->heads[i] = (GNode *)malloc(sizeof(GNode));
		pgraph->heads[i]->path.length = rand() % 10 + 5;
		pgraph->heads[i]->next = NULL;
	}
}
void DestroyGraph(Graph *pgraph) {
	GNode* cur, *temp;
	for (int i = 0; i < pgraph->num; i++) {
		cur = pgraph->heads[i];
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;
			free(temp);
		}
	}
	free(pgraph->heads);
}
void AddEdge(Graph *pgraph, int src, int dest, int path_id, int length, int transportationfee) {
	GNode *newNode1, *newNode2, *cur;
	srand(time(NULL));
	newNode1 = (GNode *)malloc(sizeof(GNode));
	newNode1->id = dest;
	newNode1->path.path_id = path_id;
	newNode1->path.length = length;
	newNode1->path.fee = transportationfee;
	newNode1->next = NULL;

	cur = pgraph->heads[src];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode1;

	// Create a node for src in dest.
	newNode2 = (GNode *)malloc(sizeof(GNode));
	newNode2->id = src;
	newNode2->path.path_id = path_id;
	newNode2->path.length = length;
	newNode2->path.fee = newNode1->path.fee;
	
	newNode2->next = NULL;

	cur = pgraph->heads[dest];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode2;
}
void PrintGraph(Graph *pgraph) {
	GNode *cur;
	for (int i = 0; i < pgraph->num; i++) {
		int tour = pgraph->heads[i]->path.length;
		printf("%d (%d) : ", i, tour);
		cur = pgraph->heads[i]->next;
		while (cur != NULL) {
			printf("\tc%d-t%d:%dKM", cur->id, cur->path.path_id, cur->path.length);
			cur = cur->next;
		}
		printf("\n");
	}
}
void MakeHotelInfo(GNode *city, struct HNode *Hotel) {
	city->hotel = Hotel;
}
int BFS(Graph *pgraph, int start_c, int end_c) {
	Queue queue;
	int *visited = (int *)malloc(sizeof(int) * pgraph->num);
	for (int i = 0; i < pgraph->num; i++)
		visited[i] = 0;

	InitQueue(&queue);
	EnQueue(&queue, start_c);
	while (!IsQEmpty(&queue)) {
		GNode *cur;
		int vtx = QPeek(&queue);
		DeQueue(&queue);
		if (visited[vtx]) continue;
		else {
			visited[vtx] = 1;
			//printf("%d ", vtx);
		}
		cur = pgraph->heads[vtx]->next;
		while (cur != NULL) {
			if (!visited[cur->id])
				EnQueue(&queue, cur->id);
			cur = cur->next;
		}
	}
	int connect = 0;
	if (visited[start_c] == 1 && visited[end_c] == 1)
		connect = 1;
	else if (visited[end_c] == 0) 
		connect = 0;
	return connect;
}