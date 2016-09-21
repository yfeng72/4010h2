#include <string.h>
#include <time.h>
#include <stdio.h>

#include "priorityQueue.h"
#include "RNG.h"

//Number of repetitions for simulation
#define SAMPLES 10000

/**
 * Performs the insertion deletion benchmark, returns time in milliseconds
 */
double benchmark( int itemCount );

/**
 * Creates new node with uniform random timestamp
 */
static inline Node *createRandomEvent() { return createNewNode(NULL, ARRIVE, 0, urand()); };


double benchmark( int itemCount ) {
    PriorityQueue *priorityQueue = createNewLinkedList();
    long long totalTime = 0;

    //Initialize the priority queue
    for ( int i = 0; i < itemCount; i++ ) {
        Node *inserted = createRandomEvent();
        insertNode( priorityQueue, inserted );
    }

    //Benchmark body
    for ( int rep = 0; rep < SAMPLES; rep++ ) {
        Node *inserted = createRandomEvent();

        clock_t beforeRun = clock();
        insertNode( priorityQueue, inserted );
        Node *removed = removeFirstElement( priorityQueue );
        clock_t afterRun = clock();

        long long diff = (long long) afterRun - beforeRun;
        totalTime += diff;

        free( removed );
    }

    //Free the Queue
    freeMem( priorityQueue );

    double avgTime = ( (double) totalTime ) / ( (double) SAMPLES ) / ( (double) CLOCKS_PER_SEC ) * 1000.0;
    return avgTime;
}

/**
 * Loops the benchmark with Queue lengths of 0 to 50000 in intervals of 1000
 * Output time statistics to benchmark.csv
 */
int main() {
    //write to csv
    FILE *file;
    file = fopen( "benchmark.csv", "w+" );
    char output[65536] = "Queue Length, Avg. Run Time(ms)\n";
    for ( int length = 0; length < 50001; length += 1000 ) {
        double ret = benchmark( length );
        printf( "Avg. Time for Operation: %f ms\n", ret );
        char row[50];
        sprintf( row, "%d,%f\n", length, ret );
        strcat( output, row );
    }
    fputs( output, file );
    fclose( file );
    printf( "benchmark.csv generated\n" );
    return 0;
}