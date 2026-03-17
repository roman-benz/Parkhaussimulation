/* test_konfig.c – Unit Tests fuer Parkhaussimulation der Konfig.c */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/Konfig.h"


// Prüft, dass eine gültige Zahl korrekt eingelesen wird
void test_int_wert_einlesen_gueltige_eingabe(void)
{
    const char *pfad = "test_input_int_ok.txt";
	int out_wert = -1;

	assert(stdin_auf_datei_setzen(pfad, "42\n") == 1);

	assert(int_wert_einlesen("Test: ", 1, 100, &out_wert) == 1);
	assert(out_wert == 42);

	remove(pfad);
	printf("test_int_wert_einlesen_gueltige_eingabe: OK\n");
}


// Prüft, dass ein Wert ausserhalb des Bereichs abgelehnt wird
void test_int_wert_einlesen_wert_ausserhalb_bereich(void)
{
	const char *pfad = "test_input_int_out_of_range.txt";
	int out_wert = -7;

	assert(stdin_auf_datei_setzen(pfad, "150\n") == 1);

	assert(int_wert_einlesen("Test: ", 1, 100, &out_wert) == 0);
	assert(out_wert == -7);

	remove(pfad);
	printf("test_int_wert_einlesen_wert_ausserhalb_bereich: OK\n");
}


// Prüft, dass ein NULL-Pointer als Zielstruktur abgefangen wird
void test_konfiguration_einlesen_null_pointer(void)
{
	assert(konfiguration_einlesen(NULL) == 0);
	printf("test_konfiguration_einlesen_null_pointer: OK\n");
}


// Prüft, dass alle Konfigurationswerte korrekt eingelesen werden
void test_konfiguration_einlesen_gueltige_eingaben(void)
{
	const char *pfad = "test_input_konfig_ok.txt";
	Simulationskonfiguration konfig = {0, 0, 0, 0, 0};

	assert(stdin_auf_datei_setzen(pfad, "10\n120\n500\n35\n12345\n") == 1);

	assert(konfiguration_einlesen(&konfig) == 1);
	assert(konfig.anzahl_parkplaetze == 10);
	assert(konfig.max_parkdauer_minuten == 120);
	assert(konfig.anzahl_simulationsschritte == 500);
	assert(konfig.ankunftswahrscheinlichkeit_prozent == 35);
	assert(konfig.zufalls_seed == 12345u);

	remove(pfad);
	printf("test_konfiguration_einlesen_gueltige_eingaben: OK\n");
}


int main(void)
{
	test_int_wert_einlesen_gueltige_eingabe();
	test_int_wert_einlesen_wert_ausserhalb_bereich();
	test_konfiguration_einlesen_null_pointer();
	test_konfiguration_einlesen_gueltige_eingaben();
	printf("Alle Konfig-Tests erfolgreich!\n");
	return 0;
}