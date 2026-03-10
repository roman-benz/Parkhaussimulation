#include "../include/Konfig.h"
#include "../include/Simulation.h"
#include <stdio.h>

/*
 * File: Main.c
* Description: Initialisiert die Konfiguration, startet die Simulation und steuert den Ablauf.
 */


int main(void)
{
    Simulationskonfiguration konfiguration; 

    printf("\n==== Parkhaus-Simulation ===="\n);

    if (!konfiguration_einlesen(&konfiguration))
    {
        printf("Fehler: Konfiguration konnte nicht eingelesen werden.\n");
        return 1; 
    }
   
    start_simulation(&konfiguration);

    return 0; 
    
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
