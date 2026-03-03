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
    Fahrzeug *einFahrzeug;
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

/**
 * @brief Initialisiert die Queue
 * 
 * Die Funktion setzt alle Parameter der Queue auf NULL, um Garbage-Werte zu vermeiden.
 * 
 * @param[out] queue Zeiger auf die zu initialisierende Queue
 * @return void
 */
void queue_init(Queue *queue);    

/**
 * @brief Fügt ein Fahrzeug in die Warteschlange ein
 * 
 * Die Funktion erstellt einen neuen Knoten mit den Informationen des Fahrzeugs und fügt diesen am Ende der Queue hinzu.
 * 
 * @param[in, out] eineQueue Zeiger auf die Queue, in die das Fahrzeug eingefügt werden soll
 * @param[in] einFahrzeug Zeiger auf das Fahrzeug, das in die Queue eingefügt werden soll
 * @param[in] enqueue_zeitschritt der Zeitschritt, zu dem das Fahrzeug in die Queue eingefügt wurde (fuer spaetere Berechnung der Wartezeit!)
 * @return void
 */
void queue_enqueue(Queue *eineQueue, Fahrzeug *einFahrzeug, int enqueue_zeitschritt);

/**
 * @brief Entfernt ein Fahrzeug aus der Warteschlange
 * 
 * Die Funktion entfernt den Knoten am Anfang der Queue und gibt das darin enthaltene Fahrzeug zurück.
 * 
 * @param[in, out] eineQueue Zeiger auf die Queue, aus der das Fahrzeug entfernt werden soll
 * @param[out] einparkendesFahrzeug Zeiger auf das Fahrzeug, das aus der Queue entfernt werden soll
 * @param[in] einparken_zeitschritt Zeitschritt, zu dem das Fahrzeug aus der Queue entfernt wurde (fuer spaetere Berechnung der Wartezeit!)
 * @return Das entfernte Fahrzeug
 */
Fahrzeug* queue_dequeue(Queue *eineQueue, int einparken_zeitschritt);

/**
 * @brief Gibt den Speicher der Queue frei
 * 
 * Die Funktion entfernt alle Knoten der Queue und gibt den Speicher frei.
 * 
 * @param[in, out] queue Zeiger auf die Queue, deren Speicher freigegeben werden soll
 * @return void
 */
void queue_destroy(Queue *queue);   


#endif