#!/usr/bin/env bash

# Call me with: 
#    curl -sL http://bit.do/lorawan-workshop | bash -s --

echo "----------------------------------------------";
echo "  _          ___      __      __ _    _  _    ";
echo " | |    ___ | _ \ __ _\ \    / //_\  | \| |   ";
echo " | |__ / _ \|   // _\` |\ \/\/ // _ \ | .\` |   ";
echo " |____|\___/|_|_\\\__,_| \_/\_//_/ \_\|_|\_|   ";
echo " \ \    / /___  _ _ | |__ ___| |_   ___  _ __ ";
echo "  \ \/\/ // _ \| '_|| / /(_-<| ' \ / _ \| '_ \\";
echo "   \_/\_/ \___/|_|  |_\_\/__/|_||_|\___/| .__/";
echo "                                        |_|   ";
echo "----------------------------------------------";
echo "Setting up Raspberry Pi for the LoRaWAN workshop"
echo "Sit back, this is going to take a while ..."

echo "-------------------------------------------"
echo "Updating the system"
echo "-------------------------------------------"
sudo apt update
sudo apt upgrade -y

echo "-------------------------------------------"
echo "Downloading and installing arduino"
echo "Using latest version - may fix lib manager"
echo "-------------------------------------------"
cd && curl -o arduino.tar.xz https://downloads.arduino.cc/arduino-1.8.7-r1-linuxarm.tar.xz
tar -xf arduino.tar.xz
cd arduino-1.8.7
./install.sh

echo "-------------------------------------------"
echo "Installing LAMP"
echo "-------------------------------------------"
sudo apt -y install apache2 php libapache2-mod-php mysql-server php-mysql

echo "-------------------------------------------"
echo "Installing mosquitto"
echo "-------------------------------------------"
sudo apt -y install mosquitto

echo "-------------------------------------------"
echo "Installing leafpad"
echo "-------------------------------------------"
sudo apt -y install leafpad

echo "-------------------------------------------"
echo "Installing node-RED"
echo "-------------------------------------------"
yes | bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
cd $HOME/.node-red
npm install node-red-contrib-ttn
sudo systemctl enable nodered.service

echo "-------------------------------------------"
echo "Installing some Arduino libraries"
echo "-------------------------------------------"
cd && sudo rm -rf ~/Arduino/libraries

mkdir -p Arduino/libraries

cd ~/Arduino/libraries
git clone https://github.com/SodaqMoja/Sodaq_wdt.git
cd Sodaq_wdt
git checkout v1.0.1

cd ~/Arduino/libraries
git clone https://github.com/SodaqMoja/Sodaq_RN2483.git
cd Sodaq_RN2483
git checkout v1.0.11

cd ~/Arduino/libraries
git clone https://github.com/Seeed-Studio/Seeed_QTouch.git
cd Seeed_QTouch
git checkout 1.0.0

cd ~/Arduino/libraries
git clone https://github.com/adafruit/Adafruit_Sensor.git
cd Adafruit_Sensor
git checkout 1.0.2

cd ~/Arduino/libraries
git clone https://github.com/adafruit/Adafruit_BME280_Library.git
cd Adafruit_BME280_Library
git checkout 1.0.7

echo "-------------------------------------------"
echo "Installing xscreensave"
echo "-------------------------------------------"
sudo apt -y install xscreensaver
echo "Disable screensaver: Preferences > Screensaver > Select disable screen saver from the dropdown."

cd

echo "-------------------------------------------"
echo "Done ..."
echo "-------------------------------------------"

clear

echo "----------------------------------------------";
echo "  _          ___      __      __ _    _  _    ";
echo " | |    ___ | _ \ __ _\ \    / //_\  | \| |   ";
echo " | |__ / _ \|   // _\` |\ \/\/ // _ \ | .\` |   ";
echo " |____|\___/|_|_\\\__,_| \_/\_//_/ \_\|_|\_|   ";
echo " \ \    / /___  _ _ | |__ ___| |_   ___  _ __ ";
echo "  \ \/\/ // _ \| '_|| / /(_-<| ' \ / _ \| '_ \\";
echo "   \_/\_/ \___/|_|  |_\_\/__/|_||_|\___/| .__/";
echo "                                        |_|   ";
echo "----------------------------------------------";
echo "Done with setup of Raspberry Pi system"
