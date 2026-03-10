#include "../include/Konfig.h"
#include <stdio.h>

/*
 * File: Konfig.c
 * Description: Implementierung der Funktionen zur Eingabe und Validierung der Simulationskonfiguration.
 */

int int_wert_einlesen(const char *prompt, int min_wert, int max_wert, int *p_out_wert)
{
    int value;
    int eingabe_erfolg;
    char c;
    
}







/*
                                       PSEUDOCODE 

Function int_wert_einlesen(prompt, min_wert, max_wert, p_out_wert) 


    Liest eine Ganzzahl vom Benutzer ein und prüft, ob sie gültig ist. Fragt bei falscher Eingabe erneut nach.
    Die Schleife stellt sicher, dass nur gültige Werte akzeptiert werden und verhindert fehlerhafe Simulationen durch falsche Eingaben.

    WHILE TRUE  // Endlosschleife, Wiederholt Eingabe bis eine gültige ankommt
        PRINT "..."
        value <- Benutzereingabe als int
        IF Eingabe ungültig
        PRINT "Ungültige Eingabe. Bitte eine ganze Zahl eingeben."
            Eingabepuffer leeren
            CONTINUE While   // Schleife springt zum Anfang zurück und fragt erneut nach Eingabe
        END IF
        IF value < min_wert OR value > max_wert
            PRINT "Wert außerhalb des erlaubten Bereichs (min_wert bis max_wert)."
            CONTINUE While   // Schleife springt zum Anfang zurück und fragt erneut nach Eingabe
        END IF
        p_out_wert <- value
        RETURN TRUE
    END WHILE
END


Function konfiguration_einlesen(p_konfiguration)
    int benutzereingabe_seed = 0 // Speichert den eingegebenen Seed-Wert temporär
    int_wert_einlesen("Anzahl Parkplätze (1-1000): ", 1, 1000, &p_konfiguration.anzahl_parkplaetze)
    int_wert_einlesen("Maximale Parkdauer (1-1000): ", 1, 1000, &p_konfiguration.max_parkdauer_minuten)
    int_wert_einlesen("Simulationsdauer in Schritten (1-100000): ", 1, 100000, &p_konfiguration.anzahl_simulationsschritte)
    int_wert_einlesen("Ankunftswahrscheinlichkeit in % (0-100): ", 0, 100, &p_konfiguration.ankunftswahrscheinlichkeit_prozent)
    int_wert_einlesen("Zufalls-Seed (0-2147483647): ", 0, 2147483647, &benutzereingabe_seed)
    p_konfiguration.zufalls_seed <- benutzereingabe_seed
    RETURN TRUE

END
*/