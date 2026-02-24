#ifndef PARKHAUS_H
#define PARKHAUS_H

typedef struct {
    int fahrzeug_id;                 /* Eindeutige ID des Fahrzeugs */
    int verbleibende_parkdauer;      /* Restdauer der Parkzeit */
    int eintritts_zeit;              /* Zeitschritt beim Einfahren */
    int wartezeit;                   /* Wartezeit vor Einfahrt */
} Fahrzeug;

typedef struct
{
   Fahrzeug *p_stellplaetze;        /* Pointer auf Stellplatz-Array */
   int maximale_kapazitaet;         /* Maximale Anzahl an Stellplätzen */
   int belegte_stellplaetze;        /* Aktuell belegte Stellplätze */ 
} Parkhaus;



#endif