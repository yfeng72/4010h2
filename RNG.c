#include "RNG.h"
#include <stdlib.h>
#include <math.h>

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