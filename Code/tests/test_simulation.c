/* test_Simulation.c – Unit Tests fuer Parkhaussimulation der Simulation.c*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/Simulation.h"

//Testet, ob ein Fahrzeug bei vollem Parkhaus korrekt in die Warteschlange aufgenommen wird
void test_simulationsschritt_ankunft_geht_in_queue_wenn_voll(void)
{
    Parkhaus garage;       
    initialisierung_garage(&garage, 1); //Neues Parkhaus mit einem Parkplatz wird initialisiert

    Fahrzeug geparktes_auto = {1, 99, 0, 0}; 
    einparken_fahrzeug(&garage, &geparktes_auto);   //Fahrzeug wird auf dem einziegen Parkplatz geparkt

    Queue queue;
    queue_init(&queue);    //Neue Warteschlange wird initialisiert

    Simulationdaten daten = {0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0};  //Alle Statisitken werden auf 0 gesetzt

    Simulationskonfiguration konfig = {1, 10, 100, 100, 42};    //Setzt unter anderem die Ankunftwahrscheinlichkeit von 100% fest
    srand(konfig.zufalls_seed);

    ausfuehren_simulationsschritt(1, &konfig, &garage, &queue, &daten);

    assert(daten.gesamt_ankuenfte == 1);   //Gesamtankünfte muss 1 sein
    assert(queue.length == 1);             //Warteschlangelänge muss 1 sein
    assert(daten.gesamt_geparkt == 0);     //Neue Eingeparkte Fahrzeuge muss 0 sein
    assert(garage.belegte_stellplaetze == 1); //eingeparktes Fahrzeug von vor start muss noch da sein

    free(garage.p_stellplaetze);
    queue_destroy(&queue);
    printf("simulationsschritt_ankunft_geht_in_queue_wenn_voll: OK\n");
}

void test_simulationsschritt_abfahrt_entfernt_fahrzeug_korrekt(void)
{
    Parkhaus garage;
    initialisierung_garage(&garage, 1);

    Fahrzeug kurzparker = {7, 1, 0, 0};
    einparken_fahrzeug(&garage, &kurzparker);

    Queue queue;
    queue_init(&queue);

    Simulationdaten daten = {0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0};
    Simulationskonfiguration konfig = {1, 10, 0, 100, 123};
    srand(konfig.zufalls_seed);

    ausfuehren_simulationsschritt(1, &konfig, &garage, &queue, &daten);

    assert(daten.gesamt_abfahrten == 1);
    assert(garage.belegte_stellplaetze == 0);
    assert(daten.aktuell_belegte_stellplaetze == 0);
    assert(daten.gesamt_ankuenfte == 0);
    assert(daten.gesamt_geparkt == 0);
    assert(queue.length == 0);
    assert(daten.auslastungsrate == 0.0);
    assert(daten.durchschnittliche_auslastung == 0.0);

    free(garage.p_stellplaetze);
    queue_destroy(&queue);
    printf("simulationsschritt_abfahrt_entfernt_fahrzeug_korrekt: OK\n");
}

int main(void)
{
    test_simulationsschritt_ankunft_geht_in_queue_wenn_voll();
    test_simulationsschritt_abfahrt_entfernt_fahrzeug_korrekt();
    return 0;
}
