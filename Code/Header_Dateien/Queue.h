#ifndef QUEUE_H
#define QUEUE_H

#include "Parkhaus.h"

typedef struct QueueNode 
{
    Fahrzeug einFahrzeug;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue 
{
    QueueNode *head;
    QueueNode *tail;
    int length;
} Queue;


#endif