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
        END IF
        IF value < min_wert OR value > max_wert
            PRINT "Wert außerhalb des erlaubten Bereichs (min_wert bis max_wert)."
            CONTINUE
        END IF
        out_wert <- value
        RETURN TRUE
    END WHILE
END

