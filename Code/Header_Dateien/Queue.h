#ifndef QUEUE_H
/*
 * File: Queue.h
 * Description: Datentypdefinitionen für Warteschlangenverwaltung im Parkhaus
*/

#define QUEUE_H

#include "Parkhaus.h"

/**
 * @brief Repräsentiert ein einzelnen Knoten in der Warteschlange
*/

typedef struct QueueNode 
{
    Fahrzeug einFahrzeug;
    int enqueue_zeitschritt;
    struct QueueNode *next;
} QueueNode;


/**
 * @brief Repräsentiert die Warteschlange durch die Aufsammlung der Knoten
*/
typedef struct 
{
    QueueNode *head;
    QueueNode *tail;
    int length;
} Queue;


void queue_init(Queue *queue);      //Initialisiert die Queue, um Garbage Werte zu vermeiden

void queue_enqueue(Queue *eineQueue, Fahrzeug *einFahrzeug, int enqueue_zeitschritt);

void queue_dequeue(Queue *queue, Fahrzeug *einparkendesFahrzeug, int *einparken_zeitschritt);

void queue_destroy(Queue *queue);   //Gibt speicher frei


#endif