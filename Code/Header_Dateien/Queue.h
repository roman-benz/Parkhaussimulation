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

void queue_dequeue(Queue *queue, Fahrzeug *einparkendesFahrzeug, int *einparken_zeitschritt);

void queue_destroy(Queue *queue);


#endif