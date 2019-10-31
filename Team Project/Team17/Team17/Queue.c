#include "Queue.h"
#include <stdlib.h>

void InitQueue(Queue *pqueue) {
	pqueue->front = pqueue->rear = 0;
}
int IsQFull(Queue *pqueue) {
	return pqueue->front
		== (pqueue->rear + 1) % MAX_QUEUE;
}
int IsQEmpty(Queue *pqueue) {
	return pqueue->front == pqueue->rear;
}
int QPeek(Queue *pqueue) {
	if (IsQEmpty(pqueue))
		exit(1); 
	return pqueue->items[pqueue->front];
}
void EnQueue(Queue *pqueue, int item) {
	if (IsQFull(pqueue))
		exit(1); 
	pqueue->items[pqueue->rear] = item;
	pqueue->rear = (pqueue->rear + 1) % MAX_QUEUE;
}
void DeQueue(Queue *pqueue) {
	if (IsQEmpty(pqueue))
		exit(1); 
	pqueue->front = (pqueue->front + 1) % MAX_QUEUE;
}


