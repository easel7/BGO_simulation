#!/bin/bash
Tag=Helium4
particle=alpha
# Loop through energy values from 10 to 100 GeV with a step of 10
for energy in $(seq 10 10 100)
do
  # Generate the corresponding macro file for the current energy value
  cat <<EOL > "${Tag}_${energy}GeV.mac"
/run/initialize
/analysis/setFileName ../Root/${Tag}_${energy}GeV
/gun/particle ${particle}
/gun/energy ${energy} GeV
/run/printProgress 10000
/run/beamOn 10000
EOL
done

for energy in $(seq 200 100 1000)
do
  # Generate the corresponding macro file for the current energy value
  cat <<EOL > "${Tag}_${energy}GeV.mac"
/run/initialize
/analysis/setFileName ../Root/${Tag}_${energy}GeV
/gun/particle ${particle}
/gun/energy ${energy} GeV
/run/printProgress 10000
/run/beamOn 10000
EOL
done

