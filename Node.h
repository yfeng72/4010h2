#ifndef __Node_H
#define __Node_H

#include <stdlib.h>

/**
 * Specifies an event type, either it's an arrival event or a departure event
 */
typedef enum {
    ARRIVE,
    DEPART
} Event;

/**
 * Specifies an Entity for a discrete event simulation.
 * The entity has a unique ID, as well as tallies on time in queue, time in system, and time it entered a queue
 * Entities also have pointers to entities before and after them in a FIFO queue.
 */
typedef struct entity_t {
    int entityId;
    double timeEnteredQueue;
    double timeInQueue;
    double timeInSystem;
    struct entity_t *next;
    struct entity_t *prev;
} Entity;

/**
 * Specifies a node for the Future Event List Priority Queue.
 * The node has a timestamp, a pointer to an entity, an event type, and the related station
 * Nodes also have pointers to nodes before and after them in a Priority Queue
 */
typedef struct Node_t {
    double timestamp;
    Entity *entity;
    Event event;
    int stationId;
    struct Node_t *nextNode;
    struct Node_t *prevNode;
} Node;

/**
 * Creates a new Event Node
 */
Node *createNewNode( Entity *entity, Event event, int stationId, double timestamp );

/**
 * Creates a new Entity Node
 */
Entity *createNewEntity( int entityId, double timeEnteredQueue );

#endif
