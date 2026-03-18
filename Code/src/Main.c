#include "../Include/Konfig.h"
#include "../Include/Simulation.h"
#include <stdio.h>

/*
 * File: Main.c
* Description: Initialisiert die Konfiguration, startet die Simulation und steuert den Ablauf.
 */


/**
 * @brief Hauptfunktion der Parkhaus-Simulation
 *
 * Initialisiert die Konfiguration, prüft die Benutzereingaben und startet die Simulation.
 *
 * @return 0 bei regulärem Programmende, 1 bei Fehler
 */
int main(void)
{
    Simulationskonfiguration konfiguration; // Hier werden alle Eingabewerte gespeichert

    printf("\n==== Parkhaus-Simulation ====\n");

    if (!konfiguration_einlesen(&konfiguration))  // Konfiguration einlesen und prüfen
    {
        printf("Fehler: Konfiguration konnte nicht eingelesen werden.\n");
        return 1;   // Fehlercode zurückgeben
    }
   
    start_simulation(&konfiguration); // Simulation starten

    return 0;  // Programm erfolgreich beendet
    
}

/*
                                    PSEUDOCODE     

Function main()
    // Initialisiere Konfigurationsstrukt
    Simulationskonfiguration konfiguration

    PRINT " Parkhaus-Simulation "
    
    IF NOT konfiguration_einlesen(&konfiguration)
        PRINT "Konfiguration konnte nicht eingelesen werden"
        RETURN 1
    END IF

    // Starte die Simulation mit der geladenen Konfiguration
    start_simulation(&konfiguration)

    RETURN 0
END
*/
