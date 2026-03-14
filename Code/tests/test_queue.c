/* test_queue.c – Unit Tests fuer Parkhaussimulation der Queue.c*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/Simulation.h"


void test_queue_init_setzt_felder_auf_null(void)
{
    Queue q;
    queue_init(&q);

    assert(q.head == NULL);
    assert(q.tail == NULL);
    assert(q.length == 0);

    printf("test_queue_init_setzt_felder_auf_null: OK\n");
}

void test_queue_init_null_pointer_kein_crash(void)
{
    queue_init(NULL); // darf nicht crashen
    printf("test_queue_init_null_pointer_kein_crash: OK\n");
}

int main(void)
{
    test_queue_init_setzt_felder_auf_null();
    test_queue_init_null_pointer_kein_crash();

    printf("Alle Tests erfolgreich!\n");
    return 0;
}

