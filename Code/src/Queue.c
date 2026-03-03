/*
 * File: Queue.c
 * Description: Pseudocoder der Funktionen für Warteschlangenverwaltung im Parkhaus
*/
#include "../Include/Queue.h"
#include <stdlib.h>

Function queue_init(Queue *queue) 
    queue->head <- NULL;
    queue->tail <- NULL;
    queue->length <- 0;
END 

Function queue_enqueue(Queue *eineQueue, Fahrzeug *einFahrzeug, int enqueue_zeitschritt)
    //Neuer Listenelement für das Fahrzeug mit Malloc reserviert
    QueueNode *fahrzeugknoten <- malloc(sizeof fFahrzeugknoten);
    IF (malloc() erfolgreich?)
        //Das Fahrzeug das der Schlange hinzugefügt werden soll wird hier dem Knoten zugewiesen
        Fahrzeugknoten->einFahrzeug <- einFahrzeug;
        Fahrzeugknoten->next <- NULL;   //Um Garbage-Werte zu vermeiden
        Fahrzeugknoten->enqueue_zeitschritt <- enqueue_zeitschritt; //Fuer spätere Berechnung der Wartezeit

        IF eineQueue.Length == 0    //Wenn die Warteschlange leer ist, dann ist das ankommende Fahrzeug head und tail der Warteschlange
            eineQueue.head <- Fahrzeugknoten;
            eineQueue.tail <- Fahrzeugknoten;
        ELSE 
            eineQueue->tail->next <- Fahrzeugknoten;   //Wenn Fahrzeuge schon in der Warteschlange sind, dann soll das ankommende Fahrzeug an den Tail angehängt werden
            eineQueue->tail <- Fahrzeugknoten;
            
        END IF 
        eineQueue->length <- eineQueue->length + 1; //Warteschlangenlaenge um 1 erhöhen

    ELSE 
        END //Abbruch
    END IF 
END

Function queue_dequeue(Queue *eineQueue, int einparken_zeitschritt)
    //Wenn die Warteschlange leer ist -> Abbruch
    IF eineQueue->length == 0
        return NULL;        //Abbruch
    END IF
    //Wenn Warteschlange nicht leer ist
    QueueNode *entfernterKnoten <- eineQueue->head;     //neuen Knoten definieren, der Head entspricht
    einparkendesFahrzeug <- entfernterKnoten->einFahrzeug;      //Das Fahrzeug festlegen, um später das Fahrzeug returnen zu können
    einparkendesFahrzeug->wartezeit <- einparken_zeitschritt - entfernterKnoten->enqueue_zeitschritt;       //Wartezeit ausrechnen (Zeitschritt beim Einfahren ins Parkhaus - Zeitschritt beim Eintritt in Warteschlange)
    
    eineQueue->head <- entfernterKnoten->next;      //Den Head auf das nächste Fahrzeug in der Warteschlange legen
    IF eineQueue->head == NULL
        eineQueue->tail = NULL;
    END IF
    free(entfernterKnoten);     //Den Speicher des Knoten des einparkenden Autos freigeben
    eineQueue->length <- eineQueue->length - 1;     //Die Länge der Warteschlange um 1 reduzieren
    return einparkendesFahrzeug;        //Das einzuparkende Auto returnen
    
END

Function queue_destroy(Queue *queue)
int platzhalter_Zeitschritt = 0;        //Platzhalter, da queue_dequeue einen Zeitschritt braucht
    while queue_dequeue(queue, Platzhalter_Zeitschritt) IS NOT NULL       //Solange Queue_dequeue nicht NULL zurückliefert, wird die Funktion erneut aufgerufen
END     //ACHTUNG -> NUR AUFRUFEN WENN WARTEZEIT EINS FAHRZEUGES NICHT MEHR RELEVANT IST, da queue_destroy die Wartezeit falsch überschreibt