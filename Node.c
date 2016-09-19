#include <math.h>
#include <stdio.h>
#include "Node.h"

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

Node *createNewNode( Entity *entity, Event event, int stationId, double timestamp ) {

    Node *retNode = malloc( sizeof( Node ) );
    retNode->entity = entity;
    retNode->event = event;
    retNode->stationId = stationId;
    retNode->nextNode = NULL;
    retNode->prevNode = NULL;
    retNode->timestamp = timestamp;
    return retNode;
}



