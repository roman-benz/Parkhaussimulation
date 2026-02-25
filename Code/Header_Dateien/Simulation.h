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
} SimulationDaten;

/**
 * @brief Initialisiert Parkhausdatenstrukturen für die Simulation.
 */
void initialisierung_garage(Parkhaus *garage, int maximale_kapazitaet);

void ausführen_simulationsschritt(
    int aktueller_schritt,
    const Simulationskonfiguration *p_konfiguration,
    Parkhaus *garage,
    Queue *queue,
    SimulationDaten *p_daten
);

void simulationsschrittdaten_ausgeben(int aktueller_schritt, const SimulationDaten *p_daten);

#endif