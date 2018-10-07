# Call me with: 
#    sudo curl -sL http://bit.do/lorawan-workshop | bash -s --


echo "  _          ___      __      __ _    _  _    ";
echo " | |    ___ | _ \ __ _\ \    / //_\  | \| |   ";
echo " | |__ / _ \|   // _\` |\ \/\/ // _ \ | .\` |   ";
echo " |____|\___/|_|_\\__,_| \_/\_//_/ \_\|_|\_|   ";
echo " \ \    / /___  _ _ | |__ ___| |_   ___  _ __ ";
echo "  \ \/\/ // _ \| '_|| / /(_-<| ' \ / _ \| '_ \\";
echo "   \_/\_/ \___/|_|  |_\_\/__/|_||_|\___/| .__/";
echo "                                        |_|   ";
echo "----------------------------------------------";
echo "Setting up Raspberry Pi for the LoRaWAN workshop"

apt update
apt upgrade -y

apt install arduino mosquitto apache2 php libapache2-mod-php mysql-server php-mysql -y

# Node-RED
bash <(curl -sL https://raw.githubusercontent.com/node-red/raspbian-deb-package/master/resources/update-nodejs-and-nodered)

cd $HOME/.node-red
npm install node-red-contrib-ttn

sudo systemctl enable nodered.service