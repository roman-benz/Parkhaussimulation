/* test_queue.c – Unit Tests fuer Parkhaussimulation der Queue.c*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/Simulation.h"


void test_queue_init_setzt_felder_auf_null(void)
{
    Queue q; //Random Queue mit Garbage-Werten
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

//Testet ob die Funktion queue_enqueue das FIFO Prinzip einhaelt indem sie die Fahrzeuge in der richtigen Reihenfolge der Warteschlange hinzufuegt
void test_queue_enqueue_fifo_verkettung(void)
{
    Queue q;
    queue_init(&q);

    Fahrzeug a1 = {1, 10, 0, 0};       //Random Fahrzeuge mit unterschiedlichen IDs
    Fahrzeug a2 = {2, 10, 0, 0};
    Fahrzeug a3 = {3, 10, 0, 0};

    queue_enqueue(&q, &a1, 1);          //Funktionsaufruf
    queue_enqueue(&q, &a2, 2);
    queue_enqueue(&q, &a3, 3);

    assert(q.head->p_einFahrzeug->fahrzeug_id == 1);    //Prüft ob die Fahrzeuge in der richtigen Reihenfolge in der Warteschlange sind
    assert(q.head->next->p_einFahrzeug->fahrzeug_id == 2);
    assert(q.tail->p_einFahrzeug->fahrzeug_id == 3);
    assert(q.head->next->next == q.tail);   //Prüft ob die Verkettung der Knoten korrekt ist und tail richtig gesetzt ist
    assert(q.tail->next == NULL); //Prüft ob der Tail der Warteschlange auf NULL zeigt

    queue_destroy(&q);
    printf("test_queue_enqueue_fifo_verkettung: OK\n");     //Ausgabe
}

//wichtig weil queue_dequeue den zeitschritt braucht um wartezeit auszurechnen
//wenn der Wert falsch gespeichert wird merkt man das erstmal gar nicht
void test_queue_enqueue_zeitschritt_gespeichert(void)
{
    Queue q;
    queue_init(&q);

    //3 Autos, unterschiedliche Zeitschritte damit man sie auseinanderhalten kann
    Fahrzeug a1 = {1, 10, 0, 0};
    Fahrzeug a2 = {2, 10, 0, 0};
    Fahrzeug a3 = {3, 10, 0, 0};

    queue_enqueue(&q, &a1, 10);
    queue_enqueue(&q, &a2, 25);
    queue_enqueue(&q, &a3, 42);

    //jeder Knoten muss seinen eigenen Zeitschritt behalten
    assert(q.head->enqueue_zeitschritt == 10);
    assert(q.head->next->enqueue_zeitschritt == 25);
    assert(q.tail->enqueue_zeitschritt == 42);

    queue_destroy(&q);
    printf("test_queue_enqueue_zeitschritt_gespeichert: OK\n");
}

int main(void)
{
    test_queue_init_setzt_felder_auf_null();
    test_queue_init_null_pointer_kein_crash();
    test_queue_enqueue_fifo_verkettung();
    test_queue_enqueue_zeitschritt_gespeichert();

    printf("Alle Tests erfolgreich!\n");
    return 0;
}

