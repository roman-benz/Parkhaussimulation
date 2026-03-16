/* test_Simulation.c – Unit Tests fuer Parkhaussimulation der Simulation.c*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/Simulation.h"

void test_initialisierung_garage_erfolgreich_setzt_grundzustand(void)
{
    Parkhaus garage;
    int kapazitaet = 3;

    int erfolg = initialisierung_garage(&garage, kapazitaet);

    assert(erfolg == 1);
    assert(garage.p_stellplaetze != NULL);
    assert(garage.maximale_kapazitaet == kapazitaet);
    assert(garage.belegte_stellplaetze == 0);

    for (int i = 0; i < kapazitaet; i++)
    {
        assert(garage.p_stellplaetze[i].fahrzeug_id == -1);
        assert(garage.p_stellplaetze[i].verbleibende_parkdauer == 0);
        assert(garage.p_stellplaetze[i].eintritts_zeit == 0);
        assert(garage.p_stellplaetze[i].wartezeit == 0);
    }

    free(garage.p_stellplaetze);
    printf("test_initialisierung_garage_erfolgreich_setzt_grundzustand: OK\n");
}


void test_initialisierung_garage_ungueltige_kapazitaet_liefert_fehler(void)
{
    
}


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

//Prüft ob ein Fahrzeug bei abgelaufener Parkdauer korrekt ausgeparkt wird
void test_simulationsschritt_abfahrt_entfernt_fahrzeug_korrekt(void)
{
    Parkhaus garage;
    initialisierung_garage(&garage, 1); //Initialisiert Garage mit einem Stellplatz

    Fahrzeug kurzparker = {7, 1, 0, 0};
    einparken_fahrzeug(&garage, &kurzparker);   //Fahrzeug mit einem Zeitschritt als verbleibende Parkdauer einparken

    Queue queue;
    queue_init(&queue);

    Simulationdaten daten = {0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0};  //Setzt Statistiken zurück
    Simulationskonfiguration konfig = {1, 10, 0, 100, 123};
    srand(konfig.zufalls_seed);

    ausfuehren_simulationsschritt(1, &konfig, &garage, &queue, &daten); //Fahrzeug sollte in diesem Schritt ausgeparkt werden

    assert(daten.gesamt_abfahrten == 1);        //Hier wird mit asser jeweils geprüft, ob die neuen Statistiken nach dem ausgeführten Simulationsschritt passen
    assert(garage.belegte_stellplaetze == 0);   //0 belegte Plätze
    assert(daten.aktuell_belegte_stellplaetze == 0);
    assert(daten.gesamt_ankuenfte == 0);
    assert(daten.gesamt_geparkt == 0);
    assert(queue.length == 0);  //Leere Warteschlange
    assert(daten.auslastungsrate == 0.0);
    assert(daten.durchschnittliche_auslastung == 0.0);

    free(garage.p_stellplaetze);
    queue_destroy(&queue);
    printf("simulationsschritt_abfahrt_entfernt_fahrzeug_korrekt: OK\n");
}


int main(void)
{
    test_start_simulation_veraendert_konfiguration_nicht();
    test_simulationsschritt_ankunft_geht_in_queue_wenn_voll();
    test_simulationsschritt_abfahrt_entfernt_fahrzeug_korrekt();
    return 0;
}
