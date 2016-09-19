#include "fifoQueue.h"
#include "priorityQueue.h"
#include <time.h>
#include <stdio.h>
#include <math.h>


double urand() {
    //Subtract 1 so that we don't get value of 1 when dividing by max
    double val = ( ( (double) rand() - 1 ) / (double) RAND_MAX );
    if ( val < 0.0 ) {
        val = 0.0;
    }
    return val;
}

double randexp() {
    double U = 10.0;
    return -U * ( log( 1.0 - urand() ) );
}


int main() {
    srand( time( NULL ) );
    PriorityQueue *queue = createNewLinkedList();
    insertNode( queue, createNewNode() );
    insertNode( queue, createNewNode() );
    insertNode( queue, createNewNode() );
    insertNode( queue, createNewNode() );
    insertNode( queue, createNewNode() );

    printQueue( queue );
    //printQueueReverse(queue);



    printf( "\n\nFifo:\n\n" );
    FifoQueue *queue2 = createNewQueueFifo();
    insertNodeFifo( queue2, createNewNode() );
    insertNodeFifo( queue2, createNewNode() );
    insertNodeFifo( queue2, createNewNode() );
    insertNodeFifo( queue2, createNewNode() );
    insertNodeFifo( queue2, createNewNode() );
    printQueueFifo( queue2 );

    //removeFirstElementFifo(queue2);
    //removeFirstElementFifo(queue2);
    printf( "\n\nMoving top 2 elements to fifo\n\n" );
    moveTopFromPriorityToFifo( queue, queue2 );
    moveTopFromPriorityToFifo( queue, queue2 );

    printQueueFifo( queue2 );
    printf( "\n\n" );
    printQueue( queue );
    freeMem( queue );
    freeMemFifo( queue2 );
    return 0;
}
