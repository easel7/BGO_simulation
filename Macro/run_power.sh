exe=/Users/xiongzheng/software/B4/B4c/build/exampleB4c
Tag=(Proton Deuteron Electron Helium4 Carbon Helium3) #Proton Deuteron Electron Helium4 Carbon Helium3 

for i in "${!Tag[@]}"; 
do
    echo  /Users/xiongzheng/software/B4/B4c/Macro/${Tag[$i]}_PowerLaw.mac
    ${exe} -m  /Users/xiongzheng/software/B4/B4c/Macro/${Tag[$i]}_PowerLaw.mac
done