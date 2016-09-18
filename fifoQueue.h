#ifndef __FifoQueue_H
#define __FifoQueue_H

#include "Node.c"

typedef struct FifoQueue FifoQueue;

struct FifoQueue {
    Node *head;
};

void insertNodeFifo( FifoQueue *queue, Node *inNode );

void removeFirstElementFifo( FifoQueue *queue );

void printQueueFifo( FifoQueue *queue );

FifoQueue *createNewQueueFifo();

void freeFifoMem( FifoQueue *queue );

#endif
