set terminal pngcairo size 1000,700
set output 'plot_endergebnis.png'

if (!exists("werte_datei")) werte_datei='simulation_ende.txt'
if (!exists("auslastung_datei")) auslastung_datei='auslastung.txt'
if (system(sprintf('if exist "%s" (echo 1) else (echo 0)',werte_datei))+0!=1) { print 'Fehler: werte_datei fehlt'; exit }
if (system(sprintf('if exist "%s" (echo 1) else (echo 0)',auslastung_datei))+0!=1) { print 'Fehler: auslastung_datei fehlt'; exit }

set output
