#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
    int anzahl_parkplaetze;
    int max_parkdauer_minuten;
    int anzahl_simulationsschritte;
    int ankunftswahrscheinlichkeit_prozent;
    unsigned int zufalls_seed; 
} Simulatiionskonfiguration;

bool lese_und_validiere_konfiguration(imulationskonfiguration *p_konfiguration);

#endif