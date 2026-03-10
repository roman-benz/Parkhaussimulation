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

set output
