#include "../Include/Simulation.h"
#include <stdlib.h>
#include <stdio.h>

Function initialisierung_garage(Parkhaus *p_garage, int maximale_kapazitaet)
	IF (p_garage == NULL)
		RETURN 0;   //Ungueltiger Zeiger
	END IF

	//Immer zuerst in sicheren Grundzustand setzen
	p_garage->p_stellplaetze = NULL;
	p_garage->maximale_kapazitaet = 0;
	p_garage->belegte_stellplaetze = 0;

	IF (maximale_kapazitaet <= 0)
		RETURN 0;   //Ungueltige Kapazitaet
	END IF

	p_garage->maximale_kapazitaet = maximale_kapazitaet;

	//Speicher fuer Stellplaetze reservieren
	p_garage->p_stellplaetze = malloc(sizeof(Fahrzeug) * maximale_kapazitaet);

	IF (p_garage->p_stellplaetze == NULL)
		p_garage->maximale_kapazitaet = 0;
		RETURN 0;   //Speicher konnte nicht reserviert werden
	END IF

	//Alle Stellplaetze mit for Schleife mit Leerwerten initialisieren
	FOR i = 0 TO maximale_kapazitaet - 1 DO
		p_garage->p_stellplaetze[i].fahrzeug_id = -1; //-1 steht für einen leeren Parkplatz
		p_garage->p_stellplaetze[i].verbleibende_parkdauer = 0;
		p_garage->p_stellplaetze[i].eintritts_zeit = 0;
		p_garage->p_stellplaetze[i].wartezeit = 0;
	END FOR

	RETURN 1;   //Initialisierung erfolgreich
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
			p_garage->p_stellplaetze[i].fahrzeug_id = -1; //Stellplatz freigeben
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

Function ausfuehren_simulationsschritt(
	int aktueller_schritt,
	const Simulationskonfiguration *p_konfiguration,
	Parkhaus *p_garage,
	Queue *p_queue,
	Simulationdaten *p_daten
)
	IF (p_konfiguration == NULL OR p_garage == NULL OR p_queue == NULL OR p_daten == NULL)
		RETURN;     //Ungueltige Eingaben
	END IF

	//TEIL 1: Abfahrten bearbeiten
	FOR i = 0 TO p_garage->maximale_kapazitaet - 1 DO
		IF (p_garage->p_stellplaetze[i].fahrzeug_id != -1) //Stellplatz belegt?
			p_garage->p_stellplaetze[i].verbleibende_parkdauer = p_garage->p_stellplaetze[i].verbleibende_parkdauer - 1;

			IF (p_garage->p_stellplaetze[i].verbleibende_parkdauer <= 0) //Parkdauer abgelaufen?
				erfolg_ausparken = ausparken_fahrzeug(p_garage, p_garage->p_stellplaetze[i].fahrzeug_id); //ausführen der ausparken_fahrzeug Funktion
				IF (erfolg_ausparken == 1)
					p_daten->gesamt_abfahrten = p_daten->gesamt_abfahrten + 1;
				END IF
			END IF
		END IF
	END FOR

	//TEIL 2: Fahrzeuge aus der Queue einparken
	//Solange freie Plaetze vorhanden sind und die Queue nicht leer ist,
	//wird immer das vorderste Fahrzeug aus der Queue geholt.
	WHILE (p_garage->belegte_stellplaetze < p_garage->maximale_kapazitaet AND p_queue->length > 0)
		//Separater Wert, damit aktueller_schritt nicht versehentlich ueberschrieben wird
		einparken_zeitschritt = aktueller_schritt;

		//Wartezeit wird in queue_dequeue berechnet und im Fahrzeug gesetzt
		wartendes_fahrzeug = queue_dequeue(p_queue, &einparken_zeitschritt);

		erfolg_einparken = einparken_fahrzeug(p_garage, &wartendes_fahrzeug);
		IF (erfolg_einparken == 1)
			p_daten->gesamt_geparkt = p_daten->gesamt_geparkt + 1;
			//Durchschnittliche Wartezeit als laufender Mittelwert aktualisieren
			p_daten->durchschnittliche_wartezeit = (
				(p_daten->durchschnittliche_wartezeit * (p_daten->gesamt_geparkt - 1))
				+ wartendes_fahrzeug.wartezeit
			) / p_daten->gesamt_geparkt;
		END IF
	END WHILE

	//TEIL 3: Neue Ankunft verarbeiten
	//Pro Zeitschritt wird per Zufall entschieden, ob ein neues Fahrzeug ankommt.
	zufallswert = rand() % 100;
	IF (zufallswert < p_konfiguration->ankunftswahrscheinlichkeit_prozent)
		p_daten->gesamt_ankuenfte = p_daten->gesamt_ankuenfte + 1;

		//Neues Fahrzeug mit Basisdaten vorbereiten
		neues_fahrzeug.fahrzeug_id = p_daten->gesamt_ankuenfte;
		neues_fahrzeug.verbleibende_parkdauer = (rand() % p_konfiguration->max_parkdauer_minuten) + 1; //durch das +1 wird eine unrealistische Parkdauer von 0 vermiden
		neues_fahrzeug.eintritts_zeit = aktueller_schritt;
		neues_fahrzeug.wartezeit = 0;

		//Wenn ein Platz frei ist, direkt einparken. Sonst in die Queue stellen.
		IF (p_garage->belegte_stellplaetze < p_garage->maximale_kapazitaet)
			erfolg_einparken = einparken_fahrzeug(p_garage, &neues_fahrzeug);
			IF (erfolg_einparken == 1)
				p_daten->gesamt_geparkt = p_daten->gesamt_geparkt + 1;
				//Direkte Einfahrt hat Wartezeit 0, geht aber in den Mittelwert ein
				p_daten->durchschnittliche_wartezeit = (
					(p_daten->durchschnittliche_wartezeit * (p_daten->gesamt_geparkt - 1))
					+ neues_fahrzeug.wartezeit
				) / p_daten->gesamt_geparkt;
			END IF
		ELSE
			queue_enqueue(p_queue, &neues_fahrzeug, aktueller_schritt);
		END IF
	END IF

	//TEIL 4: Kennzahlen aktualisieren
	p_daten->warteschlangen_laenge = p_queue->length;

	IF (p_garage->maximale_kapazitaet > 0) //um sicher eine division durch null zu vermeiden
		p_daten->auslastungsrate = (double)p_garage->belegte_stellplaetze / p_garage->maximale_kapazitaet;
	ELSE
		p_daten->auslastungsrate = 0.0;
	END IF

	//Durchschnittliche Auslastung als laufenden Mittelwert ueber alle Schritte berechnen
	IF (aktueller_schritt > 0)
		p_daten->durchschnittliche_auslastung = (
			(p_daten->durchschnittliche_auslastung * (aktueller_schritt - 1))
			+ p_daten->auslastungsrate
		) / aktueller_schritt;
	ELSE
		p_daten->durchschnittliche_auslastung = p_daten->auslastungsrate;
	END IF
END

Function simulationsschrittdaten_ausgeben(int aktueller_schritt, const Simulationdaten *p_daten)
	IF (p_daten == NULL)
		RETURN;     //Ohne Daten keine Ausgabe moeglich
	END IF

	PRINT "===== SIMULATIONSSCHRITT ", aktueller_schritt, " =====";
	PRINT "Gesamtankuenfte: ", p_daten->gesamt_ankuenfte;
	PRINT "Gesamt geparkt: ", p_daten->gesamt_geparkt;
	PRINT "Gesamtabfahrten: ", p_daten->gesamt_abfahrten;
	PRINT "Warteschlangenlaenge: ", p_daten->warteschlangen_laenge;
	PRINT "Aktuelle Auslastungsrate: ", p_daten->auslastungsrate;
	PRINT "Durchschnittliche Wartezeit: ", p_daten->durchschnittliche_wartezeit;
	PRINT "Durchschnittliche Auslastung: ", p_daten->durchschnittliche_auslastung;
END

Function end_simulationsdaten_ausgeben(const Simulationdaten *p_daten) //gibt am Ende der Simulation die Daten aus
	IF (p_daten == NULL)
		RETURN;     //Ohne Daten keine Ausgabe moeglich
	END IF

	PRINT "===== ENDE DER SIMULATION =====";
	PRINT "Gesamtankuenfte: ", p_daten->gesamt_ankuenfte;
	PRINT "Gesamt geparkt: ", p_daten->gesamt_geparkt;
	PRINT "Gesamtabfahrten: ", p_daten->gesamt_abfahrten;
	PRINT "Warteschlangenlaenge (aktuell): ", p_daten->warteschlangen_laenge;
	PRINT "Aktuelle Auslastungsrate: ", p_daten->auslastungsrate;
	PRINT "Durchschnittliche Wartezeit: ", p_daten->durchschnittliche_wartezeit;
	PRINT "Durchschnittliche Auslastung: ", p_daten->durchschnittliche_auslastung;
END

Function start_simulation(const Simulationskonfiguration *p_konfiguration)
	IF (p_konfiguration == NULL)
		RETURN;     //Ohne Konfiguration kann keine Simulation gestartet werden
	END IF

	//1) Zufallsgenerator mit konfiguriertem Seed initialisieren
	srand(p_konfiguration->zufalls_seed);

	//2) Lokale Datenstrukturen vorbereiten
	Parkhaus garage;
	Queue warteschlange;
	Simulationdaten daten;
	erfolg_init = 0;

	//Garage direkt in sicheren Startzustand setzen
	garage.p_stellplaetze = NULL;
	garage.maximale_kapazitaet = 0;
	garage.belegte_stellplaetze = 0;

	erfolg_init = initialisierung_garage(&garage, p_konfiguration->anzahl_parkplaetze);
	IF (erfolg_init == 0)
		RETURN;     //Bei fehlgeschlagener Initialisierung Simulation abbrechen
	END IF

	queue_init(&warteschlange);

	//3) Simulationsdaten auf Startwerte setzen
	daten.gesamt_ankuenfte = 0;
	daten.gesamt_geparkt = 0;
	daten.gesamt_abfahrten = 0;
	daten.warteschlangen_laenge = 0;
	daten.auslastungsrate = 0.0;
	daten.durchschnittliche_wartezeit = 0.0;
	daten.durchschnittliche_auslastung = 0.0;

	//4) Alle Simulationsschritte nacheinander ausfuehren
	FOR schritt = 1 TO p_konfiguration->anzahl_simulationsschritte DO
		ausfuehren_simulationsschritt(schritt, p_konfiguration, &garage, &warteschlange, &daten);
		simulationsschrittdaten_ausgeben(schritt, &daten);
	END FOR

	//5) Endergebnis ausgeben
	end_simulationsdaten_ausgeben(&daten);

	//6) Speicher aufraeumen
	queue_destroy(&warteschlange);
	free(garage.p_stellplaetze);
END

