#ifndef __FifoQueue_H
#define __FifoQueue_H

#include "Node.h"

/**
 * Specifies the FIFO Queue used by service stations in a Discrete Event Simulator
 * FIFO Queues contain Entities (further details see Node.h)
 */
typedef struct FifoQueue FifoQueue;

struct FifoQueue {
    //head and tail are phantom nodes
    Entity *head;
    Entity *tail;
};

/**
 * Inserts an Entity Node to the FIFO Queue specified
 */
void insertNodeFifo( FifoQueue *queue, Entity *inNode );

/**
 * Returns whether the FIFO Queue is empty (has no elements besides the phantom nodes)
 */
static inline int isEmptyFifo( FifoQueue *queue ) { return queue->head->next == queue->tail ? 1 : 0; }

/**
 * Removes the Entity Node that entered the FIFO queue first
 */
Entity *removeFirstFifo( FifoQueue *queue );

/**
 * Constructor for a new FIFO Queue, allocates memory
 */
FifoQueue *createNewQueueFifo();

/**
 * Destructor for a FIFO Queue, frees all the Entity Nodes and the queue itself
 */
void freeMemFifo( FifoQueue *queue );

#endif
