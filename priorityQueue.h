#include <stdlib.h>
#include "Node.c"
#include "fifoQueue.c"

typedef struct PriorityQueue PriorityQueue;

struct PriorityQueue {
    Node *head;
};

void insertNode( PriorityQueue *queue, Node *inNode );

void removeFirstElement( PriorityQueue *queue );

void printQueue( PriorityQueue *queue );

void printQueueReverse( PriorityQueue *queue );

PriorityQueue *createNewLinkedList();

void freeMem( PriorityQueue *queue );

void moveTopFromPriorityToFifo( PriorityQueue *priority, FifoQueue *fifo );
