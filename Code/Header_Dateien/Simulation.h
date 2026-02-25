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
 * 
 * @param p_garage Zeiger auf die zu initialisierende Parkhausstruktur
 * @param maximale_kapazitaet Maximale Anzahl der Stellplätze
 */
void initialisierung_garage(Parkhaus *p_garage, int maximale_kapazitaet);

/**
 * @brief Führt einen einzelnen Simulationsschritt aus.
 * 
 * @param aktueller_schritt Nummer des aktuellen Simulationsschritts
 * @param p_konfiguration Zeiger auf die Simulationskonfiguration
 * @param p_garage Zeiger auf das Parkhaus
 * @param p_queue Zeiger auf die Warteschlange
 * @param p_daten Zeiger auf die Datenstruktur zur Speicherung der Ergebnisse
 */
void ausfuehren_simulationsschritt(
    int aktueller_schritt,
    const Simulationskonfiguration *p_konfiguration,
    Parkhaus *p_garage,
    Queue *p_queue,
    Simulationdaten *p_daten
);

/**
 * @brief Gibt die Simulationsdaten eines Schritts auf der Konsole aus.
 * 
 * @param aktueller_schritt Nummer des aktuellen Simulationsschritts
 * @param p_daten Zeiger auf die auszugebenden Simulationsdaten
 */
void simulationsschrittdaten_ausgeben(int aktueller_schritt, const Simulationdaten *p_daten);

/**
 * @brief Führt die komplette Parkhaus-Simulation aus.
 * 
 * @param p_konfiguration Zeiger auf die Simulationskonfiguration
 */
void start_simulation(const Simulationskonfiguration *p_konfiguration);

#endif