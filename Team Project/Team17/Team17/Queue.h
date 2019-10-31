#ifndef _QUEUE_H
#define _QUEUE_H

#define MAX_QUEUE	300

#include "graph.h"

typedef struct {
	int front, rear;
	int items[MAX_QUEUE];
} Queue;

void InitQueue(Queue *pqueue);

int IsQFull(Queue *pqueue);

int IsQEmpty(Queue *pqueue);

int QPeek(Queue *pqueue);

void EnQueue(Queue *pqueue, int item);

void DeQueue(Queue *pqueue);

#endif _QUEUE_H