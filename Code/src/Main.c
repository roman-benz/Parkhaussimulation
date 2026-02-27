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

    RETURN 0
END