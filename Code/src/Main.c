#include "../include/Konfig.h"
#include "../include/Simulation.h"
#include <stdio.h>


Function main()
    // Initialisiere Konfigurationsstrukt
    Simulationskonfiguration konfiguration

    PRINT " Parkhaus-Simulation "
    
    IF NOT 
    konfiguration_einlesen(&konfiguration)
        PRINT "Konfiguration konnte nicht eingelesen werden"
        RETURN 1
    END IF

    // Starte die Simulation mit der geladenen Konfiguration
    start_simulation(&konfiguration)

    
    RETURN 0
END