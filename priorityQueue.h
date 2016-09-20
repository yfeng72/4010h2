#ifndef __PriorityQueue_H
#define __PriorityQueue_H
#include <stdlib.h>
#include "Node.h"
#include "fifoQueue.h"

typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue {
    Node *head;
};

static inline int isEmpty( PriorityQueue *queue ) { return queue->head == NULL ? 1 : 0; }

void insertNode( PriorityQueue *queue, Node *inNode );

Node *removeFirstElement( PriorityQueue *queue );

void printQueue( PriorityQueue *queue );

void printQueueReverse( PriorityQueue *queue );

PriorityQueue *createNewLinkedList();

void freeMem( PriorityQueue *queue );

#endif
