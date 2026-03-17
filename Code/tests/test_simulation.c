/* test_Simulation.c – Unit Tests fuer Parkhaussimulation der Simulation.c*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/Simulation.h"



// Prüft erfolgreiche Initialisierung und definierten Startzustand aller Stellplätze
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


// Prüft ungültige Kapazität gibt einen Fehler zurück
void test_initialisierung_garage_ungueltige_kapazitaet_liefert_fehler(void)
{
    Parkhaus garage;

    int erfolg = initialisierung_garage(&garage, 0);

    assert(erfolg == 0);
    assert(garage.p_stellplaetze == NULL);
    assert(garage.maximale_kapazitaet == 0);
    assert(garage.belegte_stellplaetze == 0);

    printf("test_initialisierung_garage_ungueltige_kapazitaet_liefert_fehler: OK\n");   
}


// Prüft erfolgreiches Einparken und korrektes Verhalten bei vollem Parkhaus
void test_einparken_fahrzeug_parkt_und_blockiert_bei_voll(void)
{
    Parkhaus garage;
    int init_erfolg = initialisierung_garage(&garage, 1);
    assert(init_erfolg == 1);

    Fahrzeug auto1 = {10, 5, 1, 0};
    Fahrzeug auto2 = {11, 3, 2, 0};

    int park_erfolg = einparken_fahrzeug(&garage, &auto1);
    int park_fehlschlag = einparken_fahrzeug(&garage, &auto2);

    assert(park_erfolg == 1);
    assert(park_fehlschlag == 0);
    assert(garage.belegte_stellplaetze == 1);
    assert(garage.p_stellplaetze[0].fahrzeug_id == 10);
    assert(garage.p_stellplaetze[0].verbleibende_parkdauer == 5);
    assert(garage.p_stellplaetze[0].eintritts_zeit == 1);

    free(garage.p_stellplaetze);
    printf("test_einparken_fahrzeug_parkt_und_blockiert_bei_voll: OK\n");
}


// Prueft Ausparken per ID und Fehlfall bei nicht vorhandener Fahrzeug-ID.
void test_ausparken_fahrzeug_gibt_platz_frei_und_fehlt_bei_unbekannter_id(void)
{
    Parkhaus garage;
    int init_erfolg = initialisierung_garage(&garage, 2);
    assert(init_erfolg == 1);

    Fahrzeug auto1 = {5, 2, 1, 0};
    int park_erfolg = einparken_fahrzeug(&garage, &auto1);
    assert(park_erfolg == 1);

    int auspark_erfolg = ausparken_fahrzeug(&garage, 5);
    int auspark_fehlschlag = ausparken_fahrzeug(&garage, 999);

    assert(auspark_erfolg == 1);
    assert(auspark_fehlschlag == 0);
    assert(garage.belegte_stellplaetze == 0);
    assert(garage.p_stellplaetze[0].fahrzeug_id == -1);
    assert(garage.p_stellplaetze[0].verbleibende_parkdauer == 0);
    assert(garage.p_stellplaetze[0].eintritts_zeit == 0);
    assert(garage.p_stellplaetze[0].wartezeit == 0);

    free(garage.p_stellplaetze);
    printf("test_ausparken_fahrzeug_gibt_platz_frei_und_fehlt_bei_unbekannter_id: OK\n");
}


// Prueft, dass start_simulation mit NULL ohne Absturz zurückkehrt
void test_start_simulation_null_pointer_kein_crash(void)
{
    start_simulation(NULL);
    printf("test_start_simulation_null_pointer_kein_crash: OK\n");
}


// Prüft dass die übergebene Konfiguration nur gelesen und nicht verändert wird
void test_start_simulation_veraendert_konfiguration_nicht(void)
{
    Simulationskonfiguration konfig = {1, 5, 0, 50, 1234};
    Simulationskonfiguration vorher = konfig;

    start_simulation(&konfig);

    assert(konfig.anzahl_parkplaetze == vorher.anzahl_parkplaetze);
    assert(konfig.max_parkdauer_minuten == vorher.max_parkdauer_minuten);
    assert(konfig.anzahl_simulationsschritte == vorher.anzahl_simulationsschritte);
    assert(konfig.ankunftswahrscheinlichkeit_prozent == vorher.ankunftswahrscheinlichkeit_prozent);
    assert(konfig.zufalls_seed == vorher.zufalls_seed);

    printf("test_start_simulation_veraendert_konfiguration_nicht: OK\n");
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

int datei_enthaelt_text(const char *dateipfad, const char *suchtext)
{
    // Für Ausgabetests reicht oft "enthält erwarteten Teilstring" statt kompletter Dateivergleich.
    // Ob ein erwarteter Wert/Schlüssel irgendwo in der Datei geschrieben wurde.
    FILE *datei = fopen(dateipfad, "r");
    char zeile[512];

    if (datei == NULL)
    {
        return 0;
    }

    while (fgets(zeile, sizeof(zeile), datei) != NULL)
    {
        if (strstr(zeile, suchtext) != NULL)
        {
            fclose(datei);
            return 1;
        }
    }

    fclose(datei);
    return 0;
}


int main(void)
{
    test_initialisierung_garage_erfolgreich_setzt_grundzustand();
    test_initialisierung_garage_ungueltige_kapazitaet_liefert_fehler();
    test_einparken_fahrzeug_parkt_und_blockiert_bei_voll();
    test_ausparken_fahrzeug_gibt_platz_frei_und_fehlt_bei_unbekannter_id();
    test_start_simulation_null_pointer_kein_crash();
    test_start_simulation_veraendert_konfiguration_nicht();
    test_simulationsschritt_ankunft_geht_in_queue_wenn_voll();
    test_simulationsschritt_abfahrt_entfernt_fahrzeug_korrekt();
    test_simulationsschrittdaten_ausgeben_schreibt_auslastungszeile();
    test_simulationsschrittdaten_ausgeben_null_schreibt_nicht();
    test_end_simulationsdaten_ausgeben_schreibt_alle_enddaten();
    test_end_simulationsdaten_ausgeben_null_schreibt_nicht();
    return 0;
}
