#ifndef KONFIG_H
#define KONFIG_H

/*
 * File: Konfig.h
* Description: Definition der Struktur und Parameter für die Konfiguration der Parkhaussimulation.
 */


/**
 * @brief Umfasst alle zur Laufzeit konfigurierbaren Simulationsparameter.
 */
typedef struct
{
    int anzahl_parkplaetze;
    int max_parkdauer_minuten;
    int anzahl_simulationsschritte;
    int ankunftswahrscheinlichkeit_prozent;
    unsigned int zufalls_seed; 
} Simulationskonfiguration;


/**
 * @brief Liest alle Eingaben aus dem Terminal und validiert diese.
 *
 * @param[out] p_konfiguration Zielstruktur für die eingelesenen Parameter.
 * @return true, wenn eine gültige Konfiguration eingelesen wurde.
 */
int konfiguration_einlesen(Simulationskonfiguration *p_konfiguration);


/**
 * @brief Liest einen ganzzahligen Wert vom Terminal ein und prüft, ob er im erlaubten Bereich liegt.
 *
 * @param[in] prompt Der Text, der dem Benutzer angezeigt wird.
 * @param[in] min_wert Der minimale erlaubte Wert.
 * @param[in] max_wert Der maximale erlaubte Wert.
 * @param[out] p_out_wert Zeiger auf die Variable, in die der eingelesene Wert geschrieben wird.
 * @return true, wenn ein gültiger Wert eingelesen wurde, sonst false.
 */
int int_wert_einlesen(const char *prompt, int min_wert, int max_wert, int *p_out_wert);


#endif
