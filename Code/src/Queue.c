#include "../Code/Header_Dateien/Queue.h"
#include <stdlib.h>

Function queue_init(Queue *queue) 

    queue->head <- NULL;
    queue->tail <- NULL;
    queue->length <- 0;
END 

Function queue_enqueue(Queue *eineQueue, Fahrzeug *einFahrzeug, int enqueue_zeitschritt)
    QueueNode *Fahrzeugknoten <- malloc(sizeof);
    IF (malloc() erfolgreich?)

        Fahrzeugknoten->einFahrzeug <- einFahrzeug;
        IF eineQueue.Length == 0
            eineQueue.head <- Fahrzeugknoten;
            eineQueue.tail <- Fahrzeugknoten;
            Fahrzeugknoten->next <- NULL;
            Fahrzeugknoten->enqueue_zeitschritt <- enqueue_zeitschritt;
        ELSE 
            eineQueue->tail->next <- Fahrzeugknoten;    
            eineQueue->tail <- Fahrzeugknoten;
            Fahrzeugknoten->next <- NULL;
            Fahrzeugknoten->enqueue_zeitschritt <- enqueue_zeitschritt;
        END IF 
        eineQueue->length <- eineQueue->(length+1); 

    ELSE 
        END 
    END IF 
    END
