#ifndef __FifoQueue_H
#define __FifoQueue_H

#include "Node.h"

typedef struct FifoQueue FifoQueue;

struct FifoQueue {
    //head and tail are phantom nodes
    Entity *head;
    Entity *tail;
};

void insertNodeFifo( FifoQueue *queue, Entity *inNode );

static inline int isEmptyFifo( FifoQueue *queue ) { return queue->head->next == queue->tail ? 1 : 0; }

Entity *removeFirstFifo( FifoQueue *queue );

void printQueueFifo( FifoQueue *queue );

FifoQueue *createNewQueueFifo();

void freeMemFifo( FifoQueue *queue );

#endif
