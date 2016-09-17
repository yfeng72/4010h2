#ifndef __Node_C
#define __Node_C


#include <math.h>
#include <stdio.h>
#include <float.h>
#include "Node.h"

double urand()
{
    //Subtract 1 so that we don't get value of 1 when dividing by max
    double val = (((double) rand() - 1) / (double) RAND_MAX);
    if(val < 0.0)
    {
        val = 0.0;
    }
    return val;
}
double randexp()
{   
    double U = 10.0;
    return -U*(log(1.0-urand()));
}
Node * createNewNode()
{
    
    Node * retNode = malloc(sizeof(Node)); 
    retNode->nextNode = NULL;
    retNode->prevNode = NULL;
    double thisRand = randexp();
    printf("Using val %f\n",thisRand);
    retNode->timestamp = thisRand;
    return retNode;
}
#endif



