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
    
} Parkhaus;



#endif