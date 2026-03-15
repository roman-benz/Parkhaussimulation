/* test_Simulation.c – Unit Tests fuer Parkhaussimulation der Simulation.c*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Include/Simulation.h"


void test_simulationsschritt_ankunft_geht_in_queue_wenn_voll(void)
{
    Parkhaus garage;
    initialisierung_garage(&garage, 1);

    Fahrzeug geparktes_auto = {1, 99, 0, 0}; 
    einparken_fahrzeug(&garage, &geparktes_auto);

    Queue queue;
    queue_init(&queue);

    Simulationdaten daten = {0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0};

    Simulationskonfiguration konfig = {1, 10, 100, 100, 42};
    srand(konfig.zufalls_seed);

    ausfuehren_simulationsschritt(1, &konfig, &garage, &queue, &daten);

    assert(daten.gesamt_ankuenfte == 1);   
    assert(queue.length == 1);             
    assert(daten.gesamt_geparkt == 0);      
    assert(garage.belegte_stellplaetze == 1); 

    free(garage.p_stellplaetze);
    queue_destroy(&queue);
    printf("simulationsschritt_ankunft_geht_in_queue_wenn_voll: OK\n");
}

int main(void)
{
    test_simulationsschritt_ankunft_geht_in_queue_wenn_voll();
    return 0;
}
