#ifndef __Node_H
#define __Node_H


#include <stdlib.h>

typedef enum {
    ARRIVE,
    DEPART
} Event;

typedef struct entity_t {
    int entityId;
    int timeInQueue;
    int timeInSystem;
} Entity;

typedef struct Node Node;

struct Node {
    double timestamp;
    Entity *entity;
    Event event;
    int stationId;
    Node *nextNode;
    Node *prevNode;
};

/**
 * Creates a new event
 */
Node *createNewNode( Entity *entity, Event event, int stationId, double timestamp );

double urand();

double randexp();

#endif
