#!/bin/bash
Tag=(Gamma) #Proton Deuteron Electron Helium4 Helium3
particle=(gamma) # proton deuteron e- alpha He3

for i in "${!Tag[@]}"; do
  # Generate the corresponding macro file for the current particle
  cat <<EOL > "${Tag[$i]}_PowerLaw.mac"
/run/initialize
/analysis/setFileName ../Root/${Tag[$i]}_PowerLaw
/gps/particle ${particle[$i]}
/gps/ene/type Pow
/gps/ene/min 10 GeV
/gps/ene/max 4000 GeV
/gps/ene/alpha -1

/gps/pos/type Plane
/gps/pos/shape Square
/gps/pos/halfx 10 cm
/gps/pos/halfy 10 cm
/gps/pos/centre 0. 0. -214.2 mm

/gps/direction 0 0 1

/run/printProgress 1000
/run/beamOn 1000000

EOL
done
