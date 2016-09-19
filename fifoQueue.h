#ifndef __FifoQueue_H
#define __FifoQueue_H

#include "Node.h"

typedef struct FifoQueue FifoQueue;

struct FifoQueue {
    Node *head;
};

void insertNodeFifo( FifoQueue *queue, Node *inNode );

inline int isEmptyFifo( FifoQueue *queue ) { return queue->head == NULL ? 1 : 0; }

Node *removeFirstElementFifo( FifoQueue *queue );

void printQueueFifo( FifoQueue *queue );

FifoQueue *createNewQueueFifo();

void freeMemFifo( FifoQueue *queue );

#endif
