#ifndef QUEUE_H
#define QUEUE_H

#include "Parkhaus.h"

typedef struct QueueNode 
{
    Fahrzeug einFahrzeug;
    int enqueue_zeitschritt;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue 
{
    QueueNode *head;
    QueueNode *tail;
    int length;
} Queue;

void queue_enqueue(Queue *eineQueue, Fahrzeug *einFahrzeug, int enqueue_zeitschritt);


#endif