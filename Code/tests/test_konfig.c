/* test_konfig.c – Unit Tests fuer Parkhaussimulation der Konfig.c */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/Konfig.h"


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


void test_konfiguration_einlesen_null_pointer(void)
{
	assert(konfiguration_einlesen(NULL) == 0);
	printf("test_konfiguration_einlesen_null_pointer: OK\n");
}


void test_konfiguration_einlesen_gueltige_eingaben(void)
{

}