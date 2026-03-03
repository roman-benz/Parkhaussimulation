# Parkhaus-Simulation Rauenegg

Programmentwurf im Rahmen der Vorlesung **Programmieren 1** an der DHBW Ravensburg.
Simulation des Parkhauses "Rauenegg" zur Bewertung der Auslastung und moeglicher baulicher Erweiterungen.

## Team

Marc Born, Julien Armbruster, Roman Benz

| | |
|---|---|
| Kurs | TSA/TSL 25 |
| Studiengang | Embedded Systems |
| Quartal | Q1 2026 |
| Sprache | C |

## Projektstruktur

```
Parkhausimulation/
├── Code/
│   ├── Include/
│   │   ├── Konfig.h              Struct Simulationskonfiguration, Prototypen fuer Eingabe
│   │   ├── Parkhaus.h            Struct Fahrzeug, Struct Parkhaus
│   │   ├── Queue.h               Struct QueueNode, Struct Queue, Prototypen fuer Warteschlange
│   │   └── Simulation.h          Struct Simulationdaten, Prototypen fuer Simulationsablauf
│   └── src/
│       ├── Main.c                Programmstart und Ablaufsteuerung
│       ├── Konfig.c              Eingabevalidierung und Konfigurationseinlesung
│       ├── Queue.c               Warteschlangen-Operationen (init, enqueue, dequeue, destroy)
│       └── Simulation.c          Simulationsschritt, Ein-/Ausparken, Statistikausgabe
├── docs/
│   ├── Dokumentation_Dateistruktur.pdf           Begruendung der Modulaufteilung
│   ├── geplante_Statistiken.pdf                  Uebersicht Statistiken und Ausgabeformat
│   ├── Flussdiagramm_ausfuehren_simulationsschritt.drawio / .jpg
│   ├── Flussdiagramm_int_wert_einlesen.drawio / .jpg
│   └── Flussdiagramm_Queue_enqueue.drawio / .jpg
├── Information/
│   ├── TSA-TSL25_Programmieren-I_Programmentwurf_Parkhaus-Simulation-Teil1.pdf
│   └── c_coding_conventions.md
├── LICENSE
└── README.md
```
