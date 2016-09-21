#include <stdio.h>
#include "Node.h"

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

Entity *createNewEntity( int entityId, double timeEnteredQueue ) {
    Entity *newEntity = (Entity*) malloc( sizeof( Entity ) );
    newEntity->timeEnteredQueue = timeEnteredQueue;
    newEntity->timeInQueue = 0.0;
    newEntity->timeInSystem = 0.0;
    newEntity->entityId = entityId;
    return newEntity;
}



