#include "fifoQueue.c"
#include "priorityQueue.c"
#include <time.h>

int main() {
    srand( time(NULL) );
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
