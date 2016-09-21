#include "fifoQueue.h"
#include "priorityQueue.h"
#include "RNG.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

//Defines max simulation clock, simulation terminates after this is reached
#define MAX_TIME 100000.0
//Defines the mean service time of each station
#define SERVICE_TIME 10.0
//Defines warmup time for the simulation, statistics will only be recorded after this time has reached
#define WARMUP_TIME 100.0

/**
 * Takes in inter-arrival time as parameter
 * Returns an array, the first element being the average time in system,
 * the second element being the average time in queue
 */
double *sim( double interarrivalTime, int STATIONS );

double *sim( double interarrivalTime, int STATIONS ) {
    srand((unsigned) time(NULL)); //init random seed

    //Initialize FIFO queue at each station and FEL
    PriorityQueue *eventQueue = createNewLinkedList();
    FifoQueue **fifoQueues = (FifoQueue **) calloc((size_t) STATIONS, sizeof( FifoQueue ));
    for ( int i = 0; i < STATIONS; i++ ) fifoQueues[i] = createNewQueueFifo();
    double curSimTime = 0.0;
    double totalTimeInSystem = 0.0;
    double totalTimeInQueue = 0.0;
    int numberOfEntities = 0;
    int *available = (int *) calloc((size_t) STATIONS, sizeof( int ));
    for ( int i = 0; i < STATIONS; i++ ) available[i] = 1;

    //Generate first entity, push the initial arrival to FEL
    Entity *firstEntity = createNewEntity( 0, 0.0 );
    Node *firstEvent = createNewNode( firstEntity, ARRIVE, 0, curSimTime );
    insertNode( eventQueue, firstEvent );

    //Simulation body
    while ( curSimTime < MAX_TIME ) {
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
            Node *newArrival = createNewNode( newEntity, ARRIVE, 0, curSimTime + randexp( interarrivalTime ));
            insertNode( eventQueue, newArrival );
        }

        //Arrival at a station
        if ( curEvent->event == ARRIVE ) {
            //Station is available with no line
            if ( available[curStation] ) {
                double processTime = randexp( SERVICE_TIME );
                curEvent->entity->timeInSystem += processTime;
                curEvent->event = DEPART;
                curEvent->timestamp = curSimTime + processTime;
                insertNode( eventQueue, curEvent );
                available[curStation] = 0;
            }
            else {
                //Station is not available, queue the entity to the station's FIFO line
                curEvent->entity->timeEnteredQueue = curSimTime;
                insertNodeFifo( fifoQueues[curStation], curEvent->entity );
                free( curEvent );
            }
        }
        else {
            //Departure from a station
            if ( !isEmptyFifo( fifoQueues[curStation] )) {
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
                if ( curEvent->timestamp > WARMUP_TIME ) {
                    numberOfEntities++;
                    totalTimeInSystem += curEvent->entity->timeInSystem;
                    totalTimeInQueue += curEvent->entity->timeInQueue;
                }
                free( curEvent->entity );
                free( curEvent );
            }
        }
    }

    //Calculate stats as return values
    double *ret = (double *) calloc( 2, sizeof( double ));
    ret[0] = totalTimeInSystem / (double) numberOfEntities;
    ret[1] = totalTimeInQueue / (double) numberOfEntities;

    //Free the queues
    for ( int i = 0; i < STATIONS; i++ ) freeMemFifo( fifoQueues[i] );
    free( fifoQueues );
    freeMem( eventQueue );
    free( available );

    return ret;
}

/**
 * Simulation Runner, runs the simulation for interarrival times ranging from 11.0 to 50.0
 * Output the simulation results and theoretical results to output.csv
 * Once the execution is complete, output.csv can be obtained from the same directory of the executable
 * Use "-singleStation" argument to run the simulation for only 1 station
 * Single station simulation output CSV file is singleStation.csv
 */
int main( int argc, char **argv ) {
    //Check if singleServer arg is present
    int STATIONS = 3;
    if ( argc == 2 && !strcmp( argv[1], "-singleStation" )) STATIONS = 1;

    //write to csv
    FILE *file;
    file = STATIONS == 3 ? fopen( "output.csv", "w+" ) : fopen( "singleStation.csv", "w+" );
    char output[8192] = "Interarrival Time, Arrival Rate, Avg. Time in System,Avg. Time in Queue,Theoretical Time in Queue\n";
    for ( double interarrivalTime = 11.0; interarrivalTime < 51.0; interarrivalTime += 1.0 ) {
        double *ret = sim( interarrivalTime, STATIONS );
        double arrivalRate = 1.0 / interarrivalTime;
        double avgTimeInSystem = ret[0];
        double avgTimeInQueue = ret[1];
        double utilization = SERVICE_TIME / interarrivalTime;
        double theoreticalTimeInQueue = utilization / ( 1.0 - utilization ) * SERVICE_TIME * STATIONS;
        printf( "Avg. Time in System: %.2f\nAvg. Time in queue: %.2f\n", avgTimeInSystem, avgTimeInQueue );
        char row[50];
        sprintf( row, "%.2f,%.4f,%f,%f,%f\n", interarrivalTime, arrivalRate, avgTimeInSystem, avgTimeInQueue,
                 theoreticalTimeInQueue );
        strcat( output, row );
        free( ret );
    }
    fputs( output, file );
    fclose( file );
    STATIONS == 3 ? printf( "output.csv generated\n" ) : printf( "singleStation.csv generated\n" );
    return 0;
}
