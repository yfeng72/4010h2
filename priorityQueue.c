#include <stdlib.h>
#include "priorityQueue.h"

//Place smallest node vals at front
void insertNode( PriorityQueue *queue, Node *inNode ) {
    printf( "Inserting node\n" );
    Node *thisNode = queue->head;
    if ( queue->head == NULL ) {
        queue->head = inNode;
        return;
    }


    //If we need to insert to very front of list
    if ( inNode->timestamp <= thisNode->timestamp ) {
        queue->head = inNode;
        inNode->nextNode = thisNode;
        thisNode->prevNode = inNode;
        return;
    }


    while ((thisNode->timestamp) < (inNode->timestamp)) {

        if ( thisNode->nextNode == NULL ) {
            thisNode->nextNode = inNode;
            inNode->prevNode = thisNode;
            return;
        }
        thisNode = thisNode->nextNode;
    }
    thisNode->prevNode->nextNode = inNode;
    //thisNode->prevNode = inNode;
    inNode->nextNode = thisNode;
    inNode->prevNode = thisNode->prevNode;
    thisNode->prevNode = inNode;

    //Now, thisNode->timestamp is >= inNode

}

void removeFirstElement( PriorityQueue *queue ) {
    Node *firstNode = queue->head;
    if ( firstNode == NULL )
        return;

    if ( firstNode->nextNode == NULL ) {
        free( firstNode );
        queue->head = NULL;
    }
    else {
        Node *tmp = firstNode->nextNode;
        free( firstNode );
        tmp->prevNode = NULL;
        queue->head = tmp;
    }
}

void moveTopFromPriorityToFifo( PriorityQueue *priority, FifoQueue *fifo ) {
    //Deletes top element of priority queue and pushes to back of fifo
    Node *nodeToMove = priority->head;
    Node *tmp = nodeToMove->nextNode;
    //nodeToMove->nextNode = NULL;
    insertNodeFifo( fifo, priority->head );
    //Seems like we left it dangling, but really just swapped to fifo and memory management will be handled there
    priority->head = tmp;
}


void printQueue( PriorityQueue *queue ) {
    Node *thisNode = queue->head;
    while ( thisNode != NULL ) {
        printf( "%f\n", thisNode->timestamp );
        thisNode = thisNode->nextNode;
    }

}

void printQueueReverse( PriorityQueue *queue ) {
    Node *thisNode = queue->head;
    while ( thisNode->nextNode != NULL ) {
        thisNode = thisNode->nextNode;
    }
    //Since no tail pointer, iterate to back, then go backwards from there
    ;
    while ( thisNode != NULL ) {
        printf( "Backwards: %f\n", thisNode->timestamp );
        thisNode = thisNode->prevNode;
    }

}

PriorityQueue *createNewLinkedList() {
    PriorityQueue *linkedList = malloc( sizeof( PriorityQueue ));
    linkedList->head = NULL;
    return linkedList;
}

void freeMem( PriorityQueue *queue ) {
    Node *thisNode = queue->head;
    while ( thisNode != NULL ) {
        Node *tmp = thisNode->nextNode;
        free( thisNode );
        thisNode = tmp;
    }
    free( queue );
}
