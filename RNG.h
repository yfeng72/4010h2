#ifndef INC_4010H2_RNG_H
#define INC_4010H2_RNG_H

/**
 * Library for RNG functions, includes Uniform(0,1) and Exponential(Lambda) RNGs
 */

/**
 * Uniform(0,1) RNG
 */
double urand();

/**
 * RNG for Exponential distribution with Lambda = 1/mean
 */
double randexp( double mean );


#endif //INC_4010H2_RNG_H
