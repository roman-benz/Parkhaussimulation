#include "../Code/Header_Dateien/Queue.h"
#include <stdlib.h>

Function queue_init(Queue *queue) 
{  
    queue->head <- NULL;
    queue->tail <- NULL;
    queue->length <- 0;
}