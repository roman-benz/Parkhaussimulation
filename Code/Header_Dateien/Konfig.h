#ifndef CONFIG_H
#define CONFIG_H


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


#endif
