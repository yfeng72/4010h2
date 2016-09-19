#ifndef __FifoQueue_C
#define __FifoQueue_C

#include <stdio.h>
#include "fifoQueue.h"


void insertNodeFifo( FifoQueue *queue, Node *inNode ) {
    Node *thisNode = queue->head;
    if ( thisNode == NULL ) {
        queue->head = inNode;
        printf( "Inserted into head\n" );
        return;
    }

    while ( thisNode->nextNode != NULL ) {
        thisNode = thisNode->nextNode;
    }
    thisNode->nextNode = inNode;
    if ( inNode == NULL )
        printf( "This is null???\n" );
    inNode->prevNode = thisNode;
    inNode->nextNode = NULL; //Since always inserted at back
}


Node *removeFirstElementFifo( FifoQueue *queue ) {
    Node *firstNode = queue->head;
    if ( firstNode == NULL )
        return NULL;

    if ( firstNode->nextNode == NULL ) {
        queue->head = NULL;
        return firstNode;
    }
    else {
        Node *tmp = firstNode->nextNode;
        tmp->prevNode = NULL;
        queue->head = tmp;
        return firstNode;
    }
}

void printQueueFifo( FifoQueue *queue ) {

    Node *thisNode = queue->head;
    while ( thisNode != NULL ) {
        printf( "%f\n", thisNode->timestamp );
        thisNode = thisNode->nextNode;
    }

}

FifoQueue *createNewQueueFifo() {
    FifoQueue *linkedList = malloc( sizeof( FifoQueue ));
    linkedList->head = NULL;
    return linkedList;
}


void freeMemFifo( FifoQueue *queue ) {
    Node *thisNode = queue->head;
    while ( thisNode != NULL ) {
        Node *tmp = thisNode->nextNode;
        free( thisNode );
        thisNode = tmp;
    }
    free( queue );
}

#endif
