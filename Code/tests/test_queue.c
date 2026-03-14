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

//Prueft ob das richtige Auto returnt wird und ob die wartezeit stimmt
//Prueft auch, ob die queue danach korrekt aktualisiert wird (laenge, head, tail)
void test_queue_dequeue_wartezeit_und_reihenfolge(void)
{
    Queue q;
    queue_init(&q);

    //a1 kommt bei zeitschritt 3 an, a2 bei 5
    Fahrzeug a1 = {1, 10, 0, 0};
    Fahrzeug a2 = {2, 10, 0, 0};
    queue_enqueue(&q, &a1, 3);
    queue_enqueue(&q, &a2, 5);

    //bei zeitschritt 10 faehrt a1 ein -> wartezeit muss 10-3=7 sein
    Fahrzeug *ergebnis = queue_dequeue(&q, 10);

    assert(ergebnis->fahrzeug_id == 1);     //a1 war zuerst drin, muss also zuerst raus
    assert(ergebnis->wartezeit == 7);       //10 - 3 = 7
    assert(q.length == 1);                  //a2 ist noch drin
    assert(q.head->p_einFahrzeug->fahrzeug_id == 2);
    assert(q.head == q.tail);              //nur noch ein element, head und tail zeigen auf dasselbe

    queue_destroy(&q);
    printf("test_queue_dequeue_wartezeit_und_reihenfolge: OK\n");
}

void test_queue_dequeue_letztes_element(void)
{
    Queue q;
    queue_init(&q);

    Fahrzeug a1 = {1, 10, 0, 0};
    queue_enqueue(&q, &a1, 2);

    Fahrzeug *ergebnis = queue_dequeue(&q, 6);

    assert(ergebnis->fahrzeug_id == 1);
    assert(ergebnis->wartezeit == 4);
    assert(q.length == 0);
    assert(q.head == NULL);
    assert(q.tail == NULL);

    printf("test_queue_dequeue_letztes_element: OK\n");
}

int main(void)
{
    test_queue_init_setzt_felder_auf_null();
    test_queue_init_null_pointer_kein_crash();
    test_queue_enqueue_fifo_verkettung();
    test_queue_enqueue_zeitschritt_gespeichert();
    test_queue_dequeue_wartezeit_und_reihenfolge();
    test_queue_dequeue_letztes_element();

    printf("Alle Tests erfolgreich!\n");
    return 0;
}

