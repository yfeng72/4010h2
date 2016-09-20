#ifndef __FifoQueue_C
#define __FifoQueue_C

#include <stdio.h>
#include "fifoQueue.h"


void insertNodeFifo( FifoQueue *queue, Entity *inNode ) {
    //insert at the end
    Entity *last = queue->tail->prev;
    last->next = inNode;
    inNode->prev = last;
    inNode->next = queue->tail;
    queue->tail->prev = inNode;
}


Entity *removeFirstFifo( FifoQueue *queue ) {
    Entity *firstNode = queue->head->next;
    if ( firstNode == queue->tail ) return NULL;
    firstNode->next->prev = queue->head;
    queue->head->next = firstNode->next;
    return firstNode;
}

void printQueueFifo( FifoQueue *queue ) {

    Entity *thisNode = queue->head->next;
    while ( thisNode != queue->tail ) {
        printf( "%f\n", thisNode->entityId );
        thisNode = thisNode->next;
    }

}

FifoQueue *createNewQueueFifo() {
    FifoQueue *linkedList = (FifoQueue*) malloc( sizeof( FifoQueue ) );
    linkedList->head = createNewEntity( -1, -1.0 );
    linkedList->tail = createNewEntity( -2, -2.0 );
    linkedList->head->next = linkedList->tail;
    linkedList->head->prev = NULL;
    linkedList->tail->prev = linkedList->head;
    linkedList->tail->next = NULL;
    return linkedList;
}


void freeMemFifo( FifoQueue *queue ) {
    Entity *thisNode = queue->head;
    while ( thisNode != NULL ) {
        Entity *tmp = thisNode->next;
        free( thisNode );
        thisNode = tmp;
    }
    free( queue );
}

#endif
