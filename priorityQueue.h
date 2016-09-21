#ifndef __PriorityQueue_H
#define __PriorityQueue_H
#include <stdlib.h>
#include "Node.h"
#include "fifoQueue.h"

/**
 * Specifies Priority Queues for implementing the Future Event List
 * Priority Queue is implemented as a Doubly Linked List
 * The Struct of a Priority Queue has a pointer to its head node
 * Elements of the Priority Queue are Event Nodes (see Node.h documentations)
 * Elements are sorted by their Timestamp property, from low to high
 */
typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue {
    Node *head;
};

/**
 * Returns whether a Priority Queue is empty
 */
static inline int isEmpty( PriorityQueue *queue ) { return queue->head == NULL ? 1 : 0; }

/**
 * Insert an Event Node to a Priority Queue at the correct location
 */
void insertNode( PriorityQueue *queue, Node *inNode );

/**
 * Removes the first element (smallest element) from the Priority Queue
 * Returns a pointer to the removed Event Node
 */
Node *removeFirstElement( PriorityQueue *queue );

/**
 * Allocates memory for a new Priority Queue instance
 */
PriorityQueue *createNewLinkedList();

/**
 * Destructor for a Priority Queue, frees all nodes and the queue itself
 */
void freeMem( PriorityQueue *queue );

#endif
