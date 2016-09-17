#ifndef __Node_H
#define __Node_H

#include <stdlib.h>

typedef struct Node Node;

struct Node{
    double timestamp;
    Node * nextNode;
    Node * prevNode;
};

Node * createNewNode();

double urand();

double randexp();

#endif
