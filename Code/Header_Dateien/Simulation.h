#ifndef SIMULATION_H
#define SIMULATION_H

#include "Parkhaus.h"
#include "Konfig.h"
#include "Queue.h"

typedef struct {
    int gesamt_ankuenfte;
    int gesamt_geparkt;
    int gesamt_abfahrten;
    int gesamt_abgewiesen;
    int warteschlangen_laenge;
    double auslastungsrate;
    double durchschnittliche_wartezeit;
} Simulationdaten;

/**
 * @brief Initialisiert Parkhausdatenstrukturen für die Simulation.
 */
void initialisierung_garage(Parkhaus *garage, int maximale_kapazitaet);

void ausführen_simulationsschritt(
    int aktueller_schritt,
    const Simulationskonfiguration *p_konfiguration,
    Parkhaus *garage,
    Queue *queue,
    Simulationdaten *p_daten
);

void simulationsschrittdaten_ausgeben(int aktueller_schritt, const Simulationdaten *p_daten);

void run_simulation(const Simulationskonfiguration *p_konfiguration);

#endif