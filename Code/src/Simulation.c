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

	//Alle Stellplaetze mit Leerwerten initialisieren
	FOR i = 0 TO maximale_kapazitaet - 1
		p_garage->p_stellplaetze[i].fahrzeug_id = -1;
		p_garage->p_stellplaetze[i].verbleibende_parkdauer = 0;
		p_garage->p_stellplaetze[i].eintritts_zeit = 0;
		p_garage->p_stellplaetze[i].wartezeit = 0;
	END FOR
END

