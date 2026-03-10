set terminal pngcairo size 1000,700
set output 'plot_endergebnis.png'

if (!exists("werte_datei")) werte_datei='simulation_ende.txt'
if (!exists("auslastung_datei")) auslastung_datei='auslastung.txt'
if (system(sprintf('if exist "%s" (echo 1) else (echo 0)',werte_datei))+0!=1) { print 'Fehler: werte_datei fehlt'; exit }
if (system(sprintf('if exist "%s" (echo 1) else (echo 0)',auslastung_datei))+0!=1) { print 'Fehler: auslastung_datei fehlt'; exit }

load werte_datei
stats auslastung_datei using 2 nooutput
avg = STATS_mean
stats auslastung_datei using 1 nooutput
xmax = STATS_max
davg = (exists("durchschnittliche_auslastung") ? durchschnittliche_auslastung*100.0 : avg)

set multiplot

set size 1,0.30; set origin 0,0.70
unset key; unset border; unset xtics; unset ytics; unset grid
set xrange [0:1]; set yrange [0:1]
set title 'Simulationsergebnisse Rauenegg' font ',20'
set label 1 sprintf('%-31s %6d', 'Gesamt Ankuenfte:', gesamt_ankuenfte) at 0.06,0.66 left font 'Consolas,12'
set label 2 sprintf('%-31s %6d', 'Gesamt Abfahrten:', gesamt_abfahrten) at 0.06,0.46 left font 'Consolas,12'
set label 3 sprintf('%-31s %6d', 'Aktuell belegt:', (exists("aktuell_belegt") ? aktuell_belegt : aktuell_belegte_stellplaetze)) at 0.06,0.26 left font 'Consolas,12'
set label 4 sprintf('%-31s %6.0f %%', 'Auslastungsrate:', auslastungsrate*100.0) at 0.06,0.08 left font 'Consolas,12'
set label 5 sprintf('%-31s %6d', 'Warteschlangen Laenge:', warteschlangen_laenge) at 0.53,0.66 left font 'Consolas,12'
set label 6 sprintf('%-31s %6d', 'Maximale Warteschlange:', (exists("maximale_warteschlange") ? maximale_warteschlange : maximale_warteschlangen_laenge)) at 0.53,0.46 left font 'Consolas,12'
set label 7 sprintf('%-31s %6.1f min', 'Durchschnittliche Wartezeit:', durchschnittliche_wartezeit) at 0.53,0.26 left font 'Consolas,12'
set label 8 sprintf('%-31s %6.0f %%', 'Durchschnittliche Auslastung:', davg) at 0.53,0.08 left font 'Consolas,12'
plot NaN notitle

unset title; unset label
set size 1,0.70; set origin 0,0
set key outside right; set border; set xtics; set ytics; set grid
set xlabel 'x'; set ylabel 'Auslastung (%)'
set xrange [0:xmax]; set yrange [0:100]
plot auslastung_datei using 1:2 with linespoints lw 2 pt 7 title 'Momentanauslastung', \
	avg with lines lw 2 dt 2 title 'Durchschnitt'

unset multiplot
set output
print 'Fertig: plot_endergebnis.png wurde erstellt.'
