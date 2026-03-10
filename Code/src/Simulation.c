#include "../Include/Simulation.h"
#include <stdlib.h>
#include <stdio.h>

/*
File: Simulation.c
Description:
Implementiert die Kernlogik der Parkhaussimulation.
Die Datei verwaltet die Initialisierung des Parkhauses,
das Ein- und Ausparken von Fahrzeugen sowie die Ausführung
einzelner Simulationsschritte (Abfahrten, Queue-Verarbeitung,
Neuzugänge und Kennzahlenberechnung).
Zusätzlich werden Schritt- und Endergebnisse im Terminal
ausgegeben und in Ausgabedateien für die spätere Auswertung
(mit Gnuplot) geschrieben.
*/

Function initialisierung_garage(Parkhaus *p_garage, int maximale_kapazitaet)
/*
Sicherer Startzustand mit Eingabeprüfung und Speicherreservierung,
damit bei Fehlern keine inkonsistenten Zustände oder ungültigen
Speicherzugriffe entstehen.
*/

IF (p_garage == NULL)
		RETURN 0;   //Ungueltiger Zeiger
	END IF

	//Zuerst in sicheren Grundzustand setzen
	p_garage->p_stellplaetze = NULL;
	p_garage->maximale_kapazitaet = 0;
	p_garage->belegte_stellplaetze = 0;

	IF (maximale_kapazitaet <= 0)
		RETURN 0;   //Ungueltige Kapazitaet
	END IF

	p_garage->maximale_kapazitaet = maximale_kapazitaet;

	//Speicher fuer Stellplaetze reservieren (mit calloc da wir ein Array benutzen, da uns die größe des Parkhaus bereits bekannt ist)
	p_garage->p_stellplaetze = calloc(maximale_kapazitaet, sizeof(Fahrzeug));

	IF (p_garage->p_stellplaetze == NULL)
		p_garage->maximale_kapazitaet = 0;
		RETURN 0;   //Speicher konnte nicht reserviert werden
	END IF

	//Alle Stellplaetze als leer markieren
	FOR i = 0 TO maximale_kapazitaet - 1 DO
		p_garage->p_stellplaetze[i].fahrzeug_id = -1; //-1 steht für einen leeren Parkplatz, da -1 auserhalb des gültigen ID Bereichs ist und so mit sicher gestellt wird,
		//das ein freier Parkplatz als frei angesehen wird
	END FOR

	RETURN 1;   //Initialisierung erfolgreich
END

Function einparken_fahrzeug(Parkhaus *p_garage, const Fahrzeug *p_fahrzeug)
/*
Frühe Validierung, damit nur gültige Fahrzeuge in freie Plätze übernommen werden
und der Belegungszähler konsistent bleibt.
*/
	IF (p_garage == NULL OR p_fahrzeug == NULL)
		RETURN 0;   //Ungueltige Eingaben
	END IF

	IF (p_garage->belegte_stellplaetze >= p_garage->maximale_kapazitaet)
		RETURN 0;   //Parkhaus ist voll
	END IF

	//Ersten freien Stellplatz suchen (frei = fahrzeug_id == -1)
	FOR i = 0 TO p_garage->maximale_kapazitaet - 1 DO
		IF (p_garage->p_stellplaetze[i].fahrzeug_id == -1) //Prüfung ob Parkplatz frei ist
			p_garage->p_stellplaetze[i] = *p_fahrzeug; //Fahrzeugdaten auf Parkplatz kopieren
			p_garage->belegte_stellplaetze = p_garage->belegte_stellplaetze + 1;
			RETURN 1;   //Einparken erfolgreich
		END IF
	END FOR

	RETURN 0;   //Sicherheitsreturn (kein freier Platz gefunden)
END

Function ausparken_fahrzeug(Parkhaus *p_garage, int fahrzeug_id)
/*
Fahrzeugentfernung über eindeutige ID und vollständiges Zurücksetzen
des Platzes, da die Werte, wie Eintrittszeit oder Parkdauer nicht auf dem 
Fahrzeug sondern auf dem Stellplatz gespeichert werden.
*/
	IF (p_garage == NULL OR fahrzeug_id < 0)
		RETURN 0;   //Ungueltige Eingaben
	END IF

	//Fahrzeug wird über die passende ID gesucht
	FOR i = 0 TO p_garage->maximale_kapazitaet - 1 DO
		IF (p_garage->p_stellplaetze[i].fahrzeug_id == fahrzeug_id)
			//Stellplatz wieder auf Leerzustand setzen
			p_garage->p_stellplaetze[i].fahrzeug_id = -1; //Stellplatz freigeben
			p_garage->p_stellplaetze[i].verbleibende_parkdauer = 0;
			p_garage->p_stellplaetze[i].eintritts_zeit = 0; //Werte des Stellplatz zurücksetzen
			p_garage->p_stellplaetze[i].wartezeit = 0;

			IF (p_garage->belegte_stellplaetze > 0)//Sicherheitsüberprüfung damit es nicht negativ wird
				p_garage->belegte_stellplaetze = p_garage->belegte_stellplaetze - 1; 
			END IF

			RETURN 1;   //Ausparken erfolgreich
		END IF
	END FOR

	RETURN 0;   //Fahrzeug-ID wurde nicht gefunden
END

Function ausfuehren_simulationsschritt(
/*
Feste Reihenfolge des Schritts (Abfahrten, Queue, Ankünfte, Kennzahlen),
damit jeder Zeitschritt deterministisch und fachlich korrekt
verarbeitet wird.
*/
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
	FOR i = 0 TO p_garage->maximale_kapazitaet - 1 DO //Parkhaus Array durch iterieren 
		IF (p_garage->p_stellplaetze[i].fahrzeug_id != -1) //Stellplatz belegt?
			p_garage->p_stellplaetze[i].verbleibende_parkdauer = p_garage->p_stellplaetze[i].verbleibende_parkdauer - 1; //Parkdauer dekrementieren

			IF (p_garage->p_stellplaetze[i].verbleibende_parkdauer <= 0) //Parkdauer abgelaufen?
				erfolg_ausparken = ausparken_fahrzeug(p_garage, p_garage->p_stellplaetze[i].fahrzeug_id); //ausführen der ausparken_fahrzeug Funktion
				IF (erfolg_ausparken == 1)//Sicherheitsüberprüfung
					p_daten->gesamt_abfahrten = p_daten->gesamt_abfahrten + 1; //gesamte Abfahrten um eins erhöhen
				END IF
			END IF
		END IF
	END FOR

	//TEIL 2: Fahrzeuge aus der Queue einparken
	//Solange freie Plaetze vorhanden sind und die Queue nicht leer ist, wird immer das vorderste Fahrzeug aus der Queue geholt.
	WHILE (p_garage->belegte_stellplaetze < p_garage->maximale_kapazitaet AND p_queue->length > 0)


		//Wartezeit wird in queue_dequeue berechnet und im Fahrzeug gespeichert
		wartendes_fahrzeug = queue_dequeue(p_queue,aktueller_schritt);

		erfolg_einparken = einparken_fahrzeug(p_garage, &wartendes_fahrzeug);
		IF (erfolg_einparken == 1)//Sicherheitsüberprüfung
			p_daten->gesamt_geparkt = p_daten->gesamt_geparkt + 1; //gesamt geparkt um eins erhöhen
			//Durchschnittliche Wartezeit als laufender Mittelwert aktualisieren
			p_daten->durchschnittliche_wartezeit = (
				(p_daten->durchschnittliche_wartezeit * (p_daten->gesamt_geparkt - 1))
				+ wartendes_fahrzeug.wartezeit
			) / p_daten->gesamt_geparkt;
		END IF
	END WHILE

	//TEIL 3: Neue Ankunft verarbeiten
	//Pro Zeitschritt wird per Zufall entschieden, ob ein neues Fahrzeug ankommt.
	zufallswert = rand() % 100;//Modulo 100, damit man es mit dem Zufallswert von 0-100 vergleichen kann
	IF (zufallswert < p_konfiguration->ankunftswahrscheinlichkeit_prozent)
		p_daten->gesamt_ankuenfte = p_daten->gesamt_ankuenfte + 1; //Ankünfte um eins erhöhen

		//Neues Fahrzeug mit Basisdaten vorbereiten
		neues_fahrzeug.fahrzeug_id = p_daten->gesamt_ankuenfte;
		neues_fahrzeug.verbleibende_parkdauer = (rand() % p_konfiguration->max_parkdauer_minuten) + 1; //durch das +1 wird eine unrealistische Parkdauer von 0 vermieden
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
		ELSE //In Warteschlange parken
			queue_enqueue(p_queue, &neues_fahrzeug, aktueller_schritt);
		END IF
	END IF

	//TEIL 4: Kennzahlen aktualisieren und in Datenstruct einheitlich abspeichern
	p_daten->warteschlangen_laenge = p_queue->length;
	p_daten->aktuell_belegte_stellplaetze = p_garage->belegte_stellplaetze;

	IF (p_daten->warteschlangen_laenge > p_daten->maximale_warteschlangen_laenge)//Maximale Wartschlange aktualisieren
		p_daten->maximale_warteschlangen_laenge = p_daten->warteschlangen_laenge;
	END IF

	IF (p_garage->maximale_kapazitaet > 0) //um sicher eine division durch null zu vermeiden
		p_daten->auslastungsrate = (double)p_garage->belegte_stellplaetze / p_garage->maximale_kapazitaet;//Momentanauslastung berechnen (belegt/kapazitaet)
	
	END IF

	//Durchschnittliche Auslastung als laufenden Mittelwert ueber alle Schritte berechnen
	IF (aktueller_schritt > 1)
		p_daten->durchschnittliche_auslastung = ((p_daten->durchschnittliche_auslastung * (aktueller_schritt - 1)) + p_daten->auslastungsrate) / aktueller_schritt;
	ELSE
		p_daten->durchschnittliche_auslastung = p_daten->auslastungsrate;//beim ersten Schritt ist die durchschnittliche Auslastung die Momentanauslastung
	END IF
END

void simulationsschrittdaten_ausgeben(int aktueller_schritt, const Simulationdaten *p_daten)
{
	FILE *datei_auslastung;

	if (p_daten == NULL)
	{
		return;
	}

	printf("===== SIMULATIONSSCHRITT %d =====\n", aktueller_schritt);
	printf("Gesamtankuenfte: %d\n", p_daten->gesamt_ankuenfte);
	printf("Gesamt geparkt: %d\n", p_daten->gesamt_geparkt);
	printf("Gesamtabfahrten: %d\n", p_daten->gesamt_abfahrten);
	printf("Aktuell belegt: %d\n", p_daten->aktuell_belegte_stellplaetze);
	printf("Warteschlangenlaenge: %d\n", p_daten->warteschlangen_laenge);
	printf("Maximale Warteschlangenlaenge: %d\n", p_daten->maximale_warteschlangen_laenge);
	printf("Aktuelle Auslastungsrate: %.4f\n", p_daten->auslastungsrate);
	printf("Durchschnittliche Wartezeit: %.4f\n", p_daten->durchschnittliche_wartezeit);
	printf("Durchschnittliche Auslastung: %.4f\n", p_daten->durchschnittliche_auslastung);

	
	datei_auslastung = fopen("Output/data/auslastung.txt", "a");
	if (datei_auslastung != NULL)
	{
		fprintf(datei_auslastung, "%d\t%.4f\n", aktueller_schritt, p_daten->auslastungsrate);
		fclose(datei_auslastung);
	}

	/*
	Function simulationsschrittdaten_ausgeben(int aktueller_schritt, const Simulationdaten *p_daten)
		Trennung von Simulationslogik und Ausgabe,
		damit Laufdaten sichtbar bleiben,für bessere Erweiterbarkeit und Übersicht.
		IF (p_daten == NULL)
			RETURN;     //Ohne Daten keine Ausgabe moeglich
		END IF
		//Ausgabe im Terminal
		PRINT "===== SIMULATIONSSCHRITT ", aktueller_schritt, " =====";
		PRINT "Gesamtankuenfte: ", p_daten->gesamt_ankuenfte;
		PRINT "Gesamt geparkt: ", p_daten->gesamt_geparkt;
		PRINT "Gesamtabfahrten: ", p_daten->gesamt_abfahrten;
		PRINT "Aktuell belegt: ", p_daten->aktuell_belegte_stellplaetze;
		PRINT "Warteschlangenlaenge: ", p_daten->warteschlangen_laenge;
		PRINT "Maximale Warteschlangenlange: ", p_daten->maximale_warteschlangen_laenge;
		PRINT "Aktuelle Auslastungsrate: ", p_daten->auslastungsrate;
		PRINT "Durchschnittliche Wartezeit: ", p_daten->durchschnittliche_wartezeit;
		PRINT "Durchschnittliche Auslastung: ", p_daten->durchschnittliche_auslastung;

		//Zeitschritt und Auslastungsrate an externe Datei für gnuplot übergeben mit "a" damit datei nicht überschreiben wird
		datei_auslastung = DATEI_ÖFFNEN("auslastung.txt", "a");
		IF (datei_auslastung != NULL)
			SCHREIBE_WERT(aktueller_schritt, p_daten->auslastungsrate) IN (datei_auslastung);
			DATEI_SCHLIESSEN(datei_auslastung);
		END IF
	END
	*/
}

void end_simulationsdaten_ausgeben(const Simulationdaten *p_daten)
{
	FILE *datei_ende;

	if (p_daten == NULL)
	{
		return;
	}

	printf("===== ENDE DER SIMULATION =====\n");
	printf("Simulationsergebnisse finden Sie in der externen Ergebnisdatei.\n");

	datei_ende = fopen("Output/data/simulation_ende.txt", "w");
	if (datei_ende != NULL)
	{
		fprintf(datei_ende, "metrik\twert\n");
		fprintf(datei_ende, "gesamt_ankuenfte\t%d\n", p_daten->gesamt_ankuenfte);
		fprintf(datei_ende, "gesamt_geparkt\t%d\n", p_daten->gesamt_geparkt);
		fprintf(datei_ende, "gesamt_abfahrten\t%d\n", p_daten->gesamt_abfahrten);
		fprintf(datei_ende, "aktuell_belegte_stellplaetze\t%d\n", p_daten->aktuell_belegte_stellplaetze);
		fprintf(datei_ende, "warteschlangen_laenge\t%d\n", p_daten->warteschlangen_laenge);
		fprintf(datei_ende, "maximale_warteschlangen_laenge\t%d\n", p_daten->maximale_warteschlangen_laenge);
		fprintf(datei_ende, "auslastungsrate\t%.4f\n", p_daten->auslastungsrate);
		fprintf(datei_ende, "durchschnittliche_wartezeit\t%.4f\n", p_daten->durchschnittliche_wartezeit);
		fprintf(datei_ende, "durchschnittliche_auslastung\t%.4f\n", p_daten->durchschnittliche_auslastung);
		fclose(datei_ende);
	}

	/*
	Function end_simulationsdaten_ausgeben(const Simulationdaten *p_daten) //gibt am Ende der Simulation die Daten aus
		Zentralisierte Endausgabe in Datei und Terminal.
		Durch die externe Gnuplot ausgabe entsteht eine bessere Visualisierung.
		IF (p_daten == NULL)
			RETURN;     //Ohne Daten keine Ausgabe moeglich
		END IF
		//Ausgabe ins Terminal
		PRINT "===== ENDE DER SIMULATION =====";
		PRINT "Simulationsergebnisse finden Sie in der externen Ergebnisdatei";

		//Endwerte extern in neuer Datei speichern um mit Gnuplot eine Ergebnissdatei mit einem Auslastungsgraphen zu erstellen
		datei_ende = DATEI_ÖFFNEN("simulation_ende.txt", "w");
		IF (datei_ende != NULL)
			SCHREIBE_WERT("gesamt_ankuenfte", p_daten->gesamt_ankuenfte) IN (datei_ende);
			SCHREIBE_WERT("gesamt_geparkt", p_daten->gesamt_geparkt) IN (datei_ende);
			SCHREIBE_WERT("gesamt_abfahrten", p_daten->gesamt_abfahrten) IN (datei_ende);
			SCHREIBE_WERT("aktuell_belegte_stellplaetze", p_daten->aktuell_belegte_stellplaetze) IN (datei_ende);
			SCHREIBE_WERT("warteschlangen_laenge", p_daten->warteschlangen_laenge) IN (datei_ende);
			SCHREIBE_WERT("maximale_warteschlangen_laenge", p_daten->maximale_warteschlangen_laenge) IN (datei_ende);
			SCHREIBE_WERT("auslastungsrate", p_daten->auslastungsrate) IN (datei_ende);
			SCHREIBE_WERT("durchschnittliche_wartezeit", p_daten->durchschnittliche_wartezeit) IN (datei_ende);
			SCHREIBE_WERT("durchschnittliche_auslastung", p_daten->durchschnittliche_auslastung) IN (datei_ende);
			DATEI_SCHLIESSEN(datei_ende);

			STARTE_GNUPLOT("plot_simulationsergebnis");
			//Grafik mit Gnuplot erstellen
		END IF
	END
	*/
}

Function start_simulation(const Simulationskonfiguration *p_konfiguration)
	/*
	Führt alles strukturiert zusammen: Initialisierung, Simulationsschleife und Aufräumen,
	damit der gesamte Ablauf robust, nachvollziehbar und
	speichersicher bleibt.
	*/
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

	queue_init(&warteschlange);//Wartschlange initialisieren

	//3) Simulationsdaten auf Startwerte setzen
	daten.gesamt_ankuenfte = 0;
	daten.gesamt_geparkt = 0;
	daten.gesamt_abfahrten = 0;
	daten.warteschlangen_laenge = 0;
	daten.maximale_warteschlangen_laenge = 0;
	daten.aktuell_belegte_stellplaetze = 0;
	daten.auslastungsrate = 0.0;
	daten.durchschnittliche_wartezeit = 0.0;
	daten.durchschnittliche_auslastung = 0.0;

	//Datei für Auslastungszeitreihe neu anlegen oder falls vorhanden überschreiben mit "w"
	datei_auslastung = DATEI_ÖFFNEN("auslastung.txt", "w");
	IF (datei_auslastung != NULL)
		SCHREIBE_ZEILE(datei_auslastung, Zeitschritt Auslastungsrate\n);
		DATEI_SCHLIESSEN(datei_auslastung);
	END IF

	//4) Alle Simulationsschritte nacheinander ausfuehren
	FOR schritt = 1 TO p_konfiguration->anzahl_simulationsschritte DO //läuft ganze Simulation durch
		ausfuehren_simulationsschritt(schritt, p_konfiguration, &garage, &warteschlange, &daten);
		simulationsschrittdaten_ausgeben(schritt, &daten);
	END FOR

	//5) Endergebnis ausgeben
	end_simulationsdaten_ausgeben(&daten);

	//6) Speicher aufraeumen
	queue_destroy(&warteschlange);
	free(garage.p_stellplaetze);
END

