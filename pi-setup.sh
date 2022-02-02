#!/usr/bin/env bash

# Call me with: 
#   bash <(curl -sL http://bit.do/lorawan-workshop)

function pause() {
   read -p "$* [ENTER TO CONTINUE]"
}

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
echo "Installing basic dependencies"
echo "-------------------------------------------"
sudo apt -y install git
sudo apt -y install mosquitto
sudo apt -y install build-essential curl

cd
if [ ! -d "lorawan-twin-workshop" ];
then
  echo "-------------------------------------------"
  echo "Cloning LoRaWAN TWIN Workshop repo"
  echo "-------------------------------------------"
  git clone https://github.com/99-bugs/lorawan-twin-workshop.git
else
  echo "LoRaWAN TWIN Workshop dir already exists. Skipping ...."
fi

cd
if [ ! -d "arduino-1.8.19" ];
then
  echo "-------------------------------------------"
  echo "Downloading arduino IDE portable"
  echo "-------------------------------------------"
  curl -L -o portable-arduino-1.8.19-linuxaarch64.tar.xz "https://filesender.belnet.be/download.php?token=9118b6de-c395-41e2-a115-83f1c2ca9c4b&files_ids=955787"
  tar -xf portable-arduino-1.8.19-linuxaarch64.tar.xz
  cd arduino-1.8.19
  ./install.sh
else
  echo "Arduino IDE is already installed. Skipping ...."
fi

## HOW TO CREATE THE ARDUINO PORTABLE FILE?
# # Based on https://www.arduino.cc/en/Guide/PortableIDE
# cd && curl -O "https://downloads.arduino.cc/arduino-1.8.19-linuxaarch64.tar.xz"
# tar -xf arduino-1.8.19-linuxaarch64.tar.xz
# cd arduino-1.8.19
# mkdir portable
# echo "boardsmanager.additional.urls=http://downloads.sodaq.net/package_sodaq_samd_index.json" >> portable/preferences.txt
# # Launch the IDE and install the SODAQ SAMD Board Package. This will take some time.

# # Install some Arduino libraries via Libray Manager
# # Sodaq_wdt v1.0.2
# # Sodaq_RN2483 v1.1.0

# cd && tar -czf portable-arduino-1.8.19-linuxaarch64.tar.xz arduino-1.8.19

cd
if [ ! -d ".node-red" ];
then
  echo "-------------------------------------------"
  echo "Installing node-RED and packages"
  echo "-------------------------------------------"
  yes | bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
  cd ~/.node-red
  npm install node-red-contrib-influxdb
  npm install node-red-dashboard
  sudo systemctl enable nodered.service
else
  echo "node-RED is already installed. Skipping ...."
fi

apt search influxdb2 | grep 'installed' &>> /dev/null
if [ "$?" -ne 0 ];
then
  echo "-------------------------------------------"
  echo "Installing InfluxDB"
  echo "-------------------------------------------"
  curl https://repos.influxdata.com/influxdb.key | gpg --dearmor | sudo tee /usr/share/keyrings/influxdb-archive-keyring.gpg >/dev/null
  echo "deb [signed-by=/usr/share/keyrings/influxdb-archive-keyring.gpg] https://repos.influxdata.com/debian $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
  sudo apt update
  sudo apt -y install influxdb2
  sudo systemctl unmask influxdb
  sudo systemctl enable influxdb
  sudo systemctl start influxdb
else
  echo "InfluxDB2 is already installed. Skipping ...."
fi

cd

echo "-------------------------------------------"
echo "Done ..."
echo "-------------------------------------------"

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
