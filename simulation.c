#include "fifoQueue.h"
#include "priorityQueue.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

#define STATIONS 3
#define MAXTIME 10000.0
#define SERVICE_TIME 10.0

double urand();
double randexp( double U );
double *sim( double interarrivalTime );

/**
 * Uniform distribution (0,1) RNG
 */
double urand() {
    //Subtract 1 so that we don't get value of 1 when dividing by max
    double val = ( ( (double) rand() - 1 ) / (double) RAND_MAX );
    return val < 0.0 ? 0.0 : val;
}

/**
 * RNG for Exponential distribution with Lambda = 1/mean
 */
double randexp( double mean ) {
    return -mean * ( log( 1.0 - urand() ) );
}

/**
 * Takes in inter-arrival time as parameter
 * Returns an array, the first element being the average time in system,
 * the second element being the average time in queue
 */
double *sim( double interarrivalTime ) {
    srand( (unsigned) time( NULL ) ); //init random seed

    //init FIFO queue at each station and FEL
    PriorityQueue *eventQueue = createNewLinkedList();
    FifoQueue **fifoQueues = (FifoQueue**) calloc( STATIONS, sizeof( FifoQueue ) );
    for ( int i = 0; i < STATIONS; i++ ) fifoQueues[i] = createNewQueueFifo();
    double curSimTime = 0.0;
    double totalTimeInSystem = 0.0;
    double totalTimeInQueue = 0.0;
    int numberOfEntities = 0;
    int available[STATIONS] = {1, 1, 1};


    //generate first entity, push the initial arrival to FEL
    Entity *firstEntity = createNewEntity( 0, 0.0 );
    Node *firstEvent = createNewNode( firstEntity, ARRIVE, 0, curSimTime );
    insertNode( eventQueue, firstEvent );

    //simulation body
    while ( curSimTime < MAXTIME ) {
        Node *curEvent = removeFirstElement( eventQueue );

        //Update simulation clock
        curSimTime = curEvent->timestamp;
        int curStation = curEvent->stationId;

        //Print out debug outputs to show progress
        printf( "Time %.2f: ", curSimTime );
        printf( "Entity %d ", curEvent->entity->entityId );
        curEvent->event == ARRIVE ?
            printf( " arrived at station %d\n", curStation ) : printf( " departed from station %d\n", curStation );


        //Queue new arrival if this event is an arrival at the first station
        if ( curStation == 0 && curEvent->event == ARRIVE ) {
            Entity *newEntity = createNewEntity( curEvent->entity->entityId + 1, 0.0 );
            Node *newArrival = createNewNode( newEntity, ARRIVE, 0, curSimTime + randexp( interarrivalTime ) );
            insertNode( eventQueue, newArrival );
        }

        //Arrival at a station
        if ( curEvent->event == ARRIVE ) {
            //station is free with no line
            if ( available[curStation] ) {
                double processTime = randexp( SERVICE_TIME );
                curEvent->entity->timeInSystem += processTime;
                curEvent->event = DEPART;
                curEvent->timestamp = curSimTime + processTime;
                insertNode( eventQueue, curEvent );
                available[curStation] = 0;
            }
            else {
                //station is not free, queue the entity to the station's FIFO line
                curEvent->entity->timeEnteredQueue = curSimTime;
                insertNodeFifo( fifoQueues[curStation], curEvent->entity );
                free( curEvent );
            }
        }
        else {
            //Departure from a station
            if ( !isEmptyFifo( fifoQueues[curStation] ) ) {
                //Pull next entity from queue, calculates its stats related to this station
                Entity *nextInLine = removeFirstFifo( fifoQueues[curStation] );
                nextInLine->timeInQueue += curSimTime - nextInLine->timeEnteredQueue;
                nextInLine->timeInSystem += curSimTime - nextInLine->timeEnteredQueue;
                double processTime = randexp( SERVICE_TIME );
                nextInLine->timeInSystem += processTime;
                Node *departureEvent = createNewNode( nextInLine, DEPART, curStation, curSimTime + processTime );
                insertNode( eventQueue, departureEvent );
            }
            else {
                //Queue is empty for this station, mark it as available
                available[curStation] = 1;
            }
            if ( curStation < STATIONS - 1 ) {
                //Departed from a station that's not the last, arrive at next station
                curEvent->event = ARRIVE;
                curEvent->stationId++;
                insertNode( eventQueue, curEvent );
            }
            else {
                //Departed from last station, calculate stats, destruct the entity
                numberOfEntities++;
                totalTimeInSystem += curEvent->entity->timeInSystem;
                totalTimeInQueue += curEvent->entity->timeInQueue;
                free( curEvent->entity );
                free( curEvent );
            }
        }
    }

    //Calculate stats as return values
    double *ret = (double*) calloc( 2, sizeof( double ) );
    ret[0] = totalTimeInSystem / (double) numberOfEntities;
    ret[1] = totalTimeInQueue / (double) numberOfEntities;

    //Free the queues
    for ( int i = 0; i < STATIONS; i++ ) freeMemFifo( fifoQueues[i] );
    free( fifoQueues );
    freeMem( eventQueue );

    return ret;
}

int main( int argc, char **argv ) {
    double *ret = sim( 20.0 );
    printf( "Avg. Time in System: %.2f\nAverage. Time in queue: %.2f\n", ret[0], ret[1] );
    return 0;
}
