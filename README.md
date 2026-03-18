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

## Kompilieren und Ausfuehren mit CMake

Im Projektverzeichnis ausfuehren:

```bash
cmake -S . -B build
cmake --build build
./build/parkhaus
```

Hinweis fuer Windows (PowerShell):

```powershell
cmake -S . -B build
cmake --build build
.\build\parkhaus.exe
```

## Codespaces Hinweis

Der erste Start eines Codespaces kann deutlich laenger dauern (mehrere Minuten).
Das ist normal, weil Container-Image, Features und Abhaengigkeiten zuerst geladen und gebaut werden.

## Output Hinweis

Der Output der Simulation befindet sich unter .\Output\data , dort befindet sich eine plot_endergebnis.png welche die Enddaten mit Auslastungsgraph darstellt. 
Die anderen txt Dateien sind Primär für das Programm und nicht für den Endnutzer. Die auslastung.txt gibt die Auslastung für jeden Zeitschritt an und die schrittdaten.txt die Simulationsdaten für jeden Zeitschritt. In der simulation_ende.txt sind die Enddaten geschrieben.

## Tests mit CMake

Einzelne Test-Binaries bauen und starten:

```bash
cmake -S . -B build
cmake --build build
./build/test_queue
./build/test_simulation
./build/test_konfig
```

Hinweis fuer Windows (PowerShell):

```powershell
cmake -S . -B build
cmake --build build
.\build\test_queue.exe
.\build\test_simulation.exe
.\build\test_konfig.exe
```

## Projektstruktur

```
Parkhausimulation/
├── CMakeLists.txt
├── Code/
│   ├── Include/
│   │   ├── Konfig.h              Struct Simulationskonfiguration, Prototypen fuer Eingabe
│   │   ├── Parkhaus.h            Struct Fahrzeug, Struct Parkhaus
│   │   ├── Queue.h               Struct QueueNode, Struct Queue, Prototypen fuer Warteschlange
│   │   └── Simulation.h          Struct Simulationdaten, Prototypen fuer Simulationsablauf
│   ├── src/
│   │   ├── Main.c                Programmstart und Ablaufsteuerung
│   │   ├── Konfig.c              Eingabevalidierung und Konfigurationseinlesung
│   │   ├── Queue.c               Warteschlangen-Operationen (init, enqueue, dequeue, destroy)
│   │   └── Simulation.c          Simulationsschritt, Ein-/Ausparken, Statistikausgabe
│   └── tests/
│       ├── test_konfig.c         Unit-Tests fuer Konfiguration und Eingabepruefung
│       ├── test_queue.c          Unit-Tests fuer Queue-Operationen
│       └── test_simulation.c     Unit-Tests fuer Simulationslogik und Ausgabe
├── build/
│   └── bin/                      Build-Ausgabeverzeichnis
├── docs/
│   ├── Dokumentation_Dateistruktur.pdf           Begruendung der Modulaufteilung
│   ├── geplante_Statistiken.pdf                  Uebersicht Statistiken und Ausgabeformat
│   ├── Flussdiagramm_ausfuehren_simulationsschritt.drawio
│   ├── Flussdiagramm_ausführen_simulationsschritt.jpg
│   ├── Flussdiagramm_int_wert_einlesen.drawio / .jpg
│   └── Flussdiagramm_Queue_enqueue.drawio / .jpg
├── Information/
│   ├── TSA-TSL25_Programmieren-I_Programmentwurf_Parkhaus-Simulation-Teil1.pdf
│   ├── TSA-TSL25_Programmieren-I_Programmentwurf_Parkhaus-Simulation-Teil2 (3).pdf
│   └── c_coding_conventions.md
├── Output/
│   ├── data/
│   │   ├── auslastung.txt
│   │   ├── simulation_ende.txt
│   │   └── plot_endergebnis.png
│   └── gnuplot/
│       └── plot_endergebnis.gp
├── LICENSE
└── README.md
```
