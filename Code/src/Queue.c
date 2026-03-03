/*
 * File: Queue.c
 * Description: Pseudocode der Funktionen für Warteschlangenverwaltung im Parkhaus
*/
#include "../Include/Queue.h"
#include <stdlib.h>

/*
    Die Funktion queue_init verhindert, dass die Zeiger auf Garbage-Werte zeigen.
    Das könnte später zu Fehlern und Abstürzen führen, wenn sie nicht vorher mit NULL initialisiert werden.
*/
Function queue_init(Queue *queue) 
    queue->head <- NULL;
    queue->tail <- NULL;
    queue->length <- 0;
END 

/*
    Die Aufgabenstellung verlangt eine Warteschlange vorm Parkhaus bei vollem Parkhaus. 
    Da die Anzahl der ankommenden Fahrzeuge dynamisch (dynamisch wegen des Zufallsprinzips) ist, braucht man eine dynamische Datengröße.
    Eine LinkedList operiert nach dem FIFO (First in First out) Prinzip und ist in ihrer Größe dynamisch. Somit ist sie ein idealer Datentyp für die Warteschlange
    Bei queue_enqueue wird ein Fahrzeug immer an das Ende der Liste gehängt, was das FIFO Prinzip sicher stellt.
*/
Function queue_enqueue(Queue *p_eineQueue, Fahrzeug *p_einFahrzeug, int enqueue_zeitschritt)
    //Neues Listenelement für das Fahrzeug mit Malloc reserviert
    QueueNode *fahrzeugknoten <- malloc(sizeof fFahrzeugknoten);
    IF (malloc() erfolgreich?)
        //Das Fahrzeug das der Schlange hinzugefügt werden soll wird hier dem Knoten zugewiesen
        fahrzeugknoten->p_einFahrzeug <- p_einFahrzeug;
        fahrzeugknoten->next <- NULL;   //Um Garbage-Werte zu vermeiden
        fahrzeugknoten->enqueue_zeitschritt <- enqueue_zeitschritt; //Fuer spätere Berechnung der Wartezeit

        IF p_eineQueue->length == 0    //Wenn die Warteschlange leer ist, dann ist das ankommende Fahrzeug head und tail der Warteschlange
            p_eineQueue->head <- fahrzeugknoten;
            p_eineQueue->tail <- fahrzeugknoten;
        ELSE 
            p_eineQueue->tail->next <- fahrzeugknoten;   //Wenn Fahrzeuge schon in der Warteschlange sind, dann soll das ankommende Fahrzeug an den Tail angehängt werden
            p_eineQueue->tail <- fahrzeugknoten;    //Der Tail der Warteschlange wird auf das neu hinzugefügte Fahrzeug gesetzt
            
        END IF 
        p_eineQueue->length <- p_eineQueue->length + 1; //Warteschlangenlaenge um 1 erhöhen

    ELSE 
        END //Abbruch -> Programmende
    END IF 
END

/*
    Die Funktion queue_dequeue stellt ebenfalls das FIFO-Prinzip sicher. Sie entfernt immer das am längsten wartende Auto aus der Liste,
    in dem Fall das erste Element der Liste, den Head. Sie returnt ein Pointer auf das Fahrzeug, das nun in das Parkhaus einfahren darf.
    Wichtig ist den Speicher des entfernten Knotens freizugeben!
*/
Function queue_dequeue(Queue *p_eineQueue, int einparken_zeitschritt)
    //Wenn die Warteschlange leer ist -> Abbruch
    IF eineQueue->length == 0
        return NULL;        //Abbruch
    END IF
    //Wenn Warteschlange nicht leer ist
    QueueNode *entfernterKnoten <- eineQueue->head;     //neuen Knoten definieren, der Head entspricht
    einparkendesFahrzeug <- entfernterKnoten->p_einFahrzeug;      //Das Fahrzeug festlegen, um später das Fahrzeug returnen zu können
    einparkendesFahrzeug->wartezeit <- einparken_zeitschritt - entfernterKnoten->enqueue_zeitschritt;       //Wartezeit ausrechnen (Zeitschritt beim Einfahren ins Parkhaus - Zeitschritt beim Eintritt in Warteschlange)
    
    p_eineQueue->head <- entfernterKnoten->next;      //Den Head auf das nächste Fahrzeug in der Warteschlange legen
    IF p_eineQueue->head == NULL
        p_eineQueue->tail <- NULL;
    END IF
    free(entfernterKnoten);     //Den Speicher des Knoten des einparkenden Autos freigeben
    p_eineQueue->length <- p_eineQueue->length - 1;     //Die Länge der Warteschlange um 1 reduzieren
    return einparkendesFahrzeug;        //Das einzuparkende Auto returnen
    
END

/*
    Am Simulationsende muss jeglicher Speicher freigegeben werden. Das passiert hier, in dem wir jeden Knoten mithilfe von queue_dequeue freigeben.
    queue_dequeue gibt den Speicher des jeweiligen Knotens frei.
*/
Function queue_destroy(Queue *p_queue)
int platzhalter_zeitschritt = 0;        //Platzhalter, da queue_dequeue einen Zeitschritt braucht
    while queue_dequeue(p_queue, platzhalter_zeitschritt) IS NOT NULL       //Solange Queue_dequeue nicht NULL zurückliefert, wird die Funktion erneut aufgerufen
END     //ACHTUNG -> NUR AUFRUFEN WENN WARTEZEIT EINES FAHRZEUGES NICHT MEHR RELEVANT IST, da queue_destroy die Wartezeit falsch überschreibt