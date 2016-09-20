#ifndef __Node_H
#define __Node_H


#include <stdlib.h>

typedef enum {
    ARRIVE,
    DEPART
} Event;

typedef struct entity_t {
    int entityId;
    double timeEnteredQueue;
    double timeInQueue;
    double timeInSystem;
    struct entity_t *next;
    struct entity_t *prev;
} Entity;

typedef struct Node_t {
    double timestamp;
    Entity *entity;
    Event event;
    int stationId;
    struct Node_t *nextNode;
    struct Node_t *prevNode;
} Node;

/**
 * Creates a new event
 */
Node *createNewNode( Entity *entity, Event event, int stationId, double timestamp );

/**
 * Creates a new entity
 */
Entity *createNewEntity( int entityId, double timeEnteredQueue );

#endif
