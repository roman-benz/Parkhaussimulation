#include "../Include/Simulation.h"
#include <stdlib.h>
#include <stdio.h>

Function initialisierung_garage(Parkhaus *p_garage, int maximale_kapazitaet)
	IF (p_garage == NULL OR maximale_kapazitaet <= 0)
		RETURN;     //Ungueltige Eingabe -> Abbruch
	END IF

	p_garage->maximale_kapazitaet = maximale_kapazitaet;
	p_garage->belegte_stellplaetze = 0;

	//Speicher fuer Stellplaetze reservieren
	p_garage->p_stellplaetze = malloc(sizeof(Fahrzeug) * maximale_kapazitaet);

	IF (p_garage->p_stellplaetze == NULL)
		p_garage->maximale_kapazitaet = 0;
		RETURN;     //Speicher konnte nicht reserviert werden
	END IF

	//Alle Stellplaetze mit for Schleife mit Leerwerten initialisieren
	FOR i = 0 TO maximale_kapazitaet - 1 DO
		p_garage->p_stellplaetze[i].fahrzeug_id = -1; //-1 steht für einen leeren Parkplatz
		p_garage->p_stellplaetze[i].verbleibende_parkdauer = 0;
		p_garage->p_stellplaetze[i].eintritts_zeit = 0;
		p_garage->p_stellplaetze[i].wartezeit = 0;
	END FOR
END

Function einparken_fahrzeug(Parkhaus *p_garage, const Fahrzeug *p_fahrzeug)
	IF (p_garage == NULL OR p_fahrzeug == NULL)
		RETURN 0;   //Ungueltige Eingaben
	END IF

	IF (p_garage->belegte_stellplaetze >= p_garage->maximale_kapazitaet)
		RETURN 0;   //Parkhaus ist voll
	END IF

	//Ersten freien Stellplatz suchen (frei = fahrzeug_id == -1)
	FOR i = 0 TO p_garage->maximale_kapazitaet - 1 DO
		IF (p_garage->p_stellplaetze[i].fahrzeug_id == -1) //Prüfung ob Parkplatz frei ist
			p_garage->p_stellplaetze[i] = *p_fahrzeug; //Fahrzeugdaten auf Parkplatzplatz kopieren
			p_garage->belegte_stellplaetze = p_garage->belegte_stellplaetze + 1;
			RETURN 1;   //Einparken erfolgreich
		END IF
	END FOR

	RETURN 0;   //Sicherheitsreturn (kein freier Platz gefunden)
END

Function ausparken_fahrzeug(Parkhaus *p_garage, int fahrzeug_id)
	IF (p_garage == NULL OR fahrzeug_id < 0)
		RETURN 0;   //Ungueltige Eingaben
	END IF

	//Fahrzeug mit passender ID suchen
	FOR i = 0 TO p_garage->maximale_kapazitaet - 1 DO
		IF (p_garage->p_stellplaetze[i].fahrzeug_id == fahrzeug_id)
			//Stellplatz wieder auf Leerzustand setzen
			p_garage->p_stellplaetze[i].fahrzeug_id = -1;
			p_garage->p_stellplaetze[i].verbleibende_parkdauer = 0;
			p_garage->p_stellplaetze[i].eintritts_zeit = 0;
			p_garage->p_stellplaetze[i].wartezeit = 0;

			IF (p_garage->belegte_stellplaetze > 0)
				p_garage->belegte_stellplaetze = p_garage->belegte_stellplaetze - 1;
			END IF

			RETURN 1;   //Ausparken erfolgreich
		END IF
	END FOR

	RETURN 0;   //Fahrzeug-ID wurde nicht gefunden
END

