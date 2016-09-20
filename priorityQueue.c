#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"

//Place smallest node vals at front
void insertNode( PriorityQueue *queue, Node *inNode ) {
    inNode->prevNode = NULL;
    inNode->nextNode = NULL;
    Node *thisNode = queue->head;
    if ( queue->head == NULL ) {
        queue->head = inNode;
        return;
    }


    //If we need to insert to very front of list
    if ( inNode->timestamp < thisNode->timestamp ) {
        queue->head = inNode;
        inNode->nextNode = thisNode;
        thisNode->prevNode = inNode;
        return;
    }


    while ( ( thisNode->timestamp ) <= ( inNode->timestamp ) ) {

        if ( thisNode->nextNode == NULL ) {
            thisNode->nextNode = inNode;
            inNode->prevNode = thisNode;
            inNode->nextNode = NULL;
            return;
        }
        thisNode = thisNode->nextNode;
    }
    thisNode->prevNode->nextNode = inNode;
    inNode->nextNode = thisNode;
    inNode->prevNode = thisNode->prevNode;
    thisNode->prevNode = inNode;

    //Now, thisNode->timestamp is >= inNode

}

Node *removeFirstElement( PriorityQueue *queue ) {
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

PriorityQueue *createNewLinkedList() {
    PriorityQueue *linkedList = malloc( sizeof( PriorityQueue ));
    linkedList->head = NULL;
    return linkedList;
}

void freeMem( PriorityQueue *queue ) {
    Node *thisNode = queue->head;
    while ( thisNode != NULL ) {
        Node *tmp = thisNode->nextNode;
        free( thisNode->entity );
        free( thisNode );
        thisNode = tmp;
    }
    free( queue );
}
