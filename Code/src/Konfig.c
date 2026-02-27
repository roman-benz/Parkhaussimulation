#include "../include/Konfig.h"
#include <stdio.h>

// Pseudocode für Konfig.c

Function int_wert_einlesen(prompt, min_wert, max_wert, out_wert)
    WHILE TRUE
        PRINT "..."
        value <- Benutzereingabe als int
        IF Eingabe ungültig
        PRINT "Ungültige Eingabe. Bitte eine ganze Zahl eingeben."
            Eingabepuffer leeren
            CONTINUE