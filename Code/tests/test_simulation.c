/* test_Simulation.c – Unit Tests fuer Parkhaussimulation der Simulation.c*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/Simulation.h"

static void aktiviere_stillen_modus(void)
{
#ifdef _WIN32
    _putenv("PARKHAUS_SILENT=1");
#else
    setenv("PARKHAUS_SILENT", "1", 1);
#endif
}



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


// Prüft, ob ein Fahrzeug korrekt eingeparkt wird, wenn Platz ist
void test_einparken_fahrzeug_erfolgreich(void)
{
    Parkhaus garage;
    int init_erfolg = initialisierung_garage(&garage, 2);
    assert(init_erfolg == 1);

    Fahrzeug auto1 = {1, 10, 1, 0};

    int park_erfolg = einparken_fahrzeug(&garage, &auto1);

    assert(park_erfolg == 1);
    assert(garage.belegte_stellplaetze == 1);
    assert(garage.p_stellplaetze[0].fahrzeug_id == 1);
    assert(garage.p_stellplaetze[0].verbleibende_parkdauer == 10);
    assert(garage.p_stellplaetze[0].eintritts_zeit == 1);

    free(garage.p_stellplaetze);
    printf("test_einparken_fahrzeug_erfolgreich: OK\n");
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
    Simulationskonfiguration konfig = {1, 10, 0, 0, 123}; // 0% Ankunft, damit nur die Abfahrt getestet wird
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

int dateiinhalt_ist_exakt(const char *dateipfad, const char *erwarteter_inhalt)
{
    // Bei NULL-Guards wollen wir strikt prüfen, dass sich der Inhalt gar nicht verändert.
    // Exakte Übereinstimmung der kompletten Datei mit einem bekannten Referenztext.
    FILE *datei = fopen(dateipfad, "r");
    char inhalt[1024];
    size_t gelesen;

    if (datei == NULL)
    {
        return 0;
    }

    gelesen = fread(inhalt, 1, sizeof(inhalt) - 1, datei);
    inhalt[gelesen] = '\0';
    fclose(datei);

    if (strcmp(inhalt, erwarteter_inhalt) == 0)
    {
        return 1;
    }

    return 0;
}

void test_simulationsschrittdaten_ausgeben_schreibt_auslastungszeile(void)
{
    // Die Schrittausgabe ist Grundlage für die spätere Auslastungsanalyse.
    // Ein Simulationsschritt schreibt die erwartete Zeile "Schritt\tAuslastung" in die Datei.
    Simulationdaten daten = {8, 5, 3, 2, 4, 3, 0.7500, 1.2500, 0.5000};

    remove("Output/data/auslastung.txt");

    simulationsschrittdaten_ausgeben(3, &daten);

    assert(datei_enthaelt_text("Output/data/auslastung.txt", "3\t0.7500"));
    printf("test_simulationsschrittdaten_ausgeben_schreibt_auslastungszeile: OK\n");
}

void test_simulationsschrittdaten_ausgeben_null_schreibt_nicht(void)
{
    // Bei ungültigem Pointer darf die Ausgabefunktion keine Seiteneffekte verursachen.
    // Bei p_daten == NULL bleibt eine bestehende Datei exakt unverändert.
    FILE *datei = fopen("Output/data/auslastung.txt", "w");

    assert(datei != NULL);
    fprintf(datei, "TEST\n");
    fclose(datei);

    simulationsschrittdaten_ausgeben(99, NULL);

    assert(dateiinhalt_ist_exakt("Output/data/auslastung.txt", "TEST\n"));
    printf("test_simulationsschrittdaten_ausgeben_null_schreibt_nicht: OK\n");
}

void test_end_simulationsdaten_ausgeben_schreibt_alle_enddaten(void)
{
    // Die Endausgabe muss alle Kennzahlen vollständig bereitstellen (Dokumentation/Plot-Auswertung).
    // Alle Pflichtfelder werden als "key = value" in simulation_ende.txt geschrieben.
    Simulationdaten daten = {12, 9, 7, 2, 5, 4, 0.8000, 1.3333, 0.6125};

    remove("Output/data/simulation_ende.txt");

    end_simulationsdaten_ausgeben(&daten);

    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "gesamt_ankuenfte = 12"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "gesamt_geparkt = 9"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "gesamt_abfahrten = 7"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "aktuell_belegte_stellplaetze = 4"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "warteschlangen_laenge = 2"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "maximale_warteschlangen_laenge = 5"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "auslastungsrate = 0.8000"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "durchschnittliche_wartezeit = 1.3333"));
    assert(datei_enthaelt_text("Output/data/simulation_ende.txt", "durchschnittliche_auslastung = 0.6125"));
    printf("test_end_simulationsdaten_ausgeben_schreibt_alle_enddaten: OK\n");
}

void test_end_simulationsdaten_ausgeben_null_schreibt_nicht(void)
{
    // Auch die Endausgabe muss bei NULL robust abbrechen, statt Dateien zu überschreiben.
    // Bei p_daten == NULL bleibt der vorhandene Dateiinhalt exakt erhalten.
    FILE *datei = fopen("Output/data/simulation_ende.txt", "w");

    assert(datei != NULL);
    fprintf(datei, "TEST\n");
    fclose(datei);

    end_simulationsdaten_ausgeben(NULL);

    assert(dateiinhalt_ist_exakt("Output/data/simulation_ende.txt", "TEST\n"));
    printf("test_end_simulationsdaten_ausgeben_null_schreibt_nicht: OK\n");
}


int main(void)
{
    aktiviere_stillen_modus();

    test_initialisierung_garage_erfolgreich_setzt_grundzustand();
    test_initialisierung_garage_ungueltige_kapazitaet_liefert_fehler();
    test_einparken_fahrzeug_parkt_und_blockiert_bei_voll();
    test_einparken_fahrzeug_erfolgreich();
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
