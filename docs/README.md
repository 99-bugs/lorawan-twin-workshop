# LoRaWAN Workshop

Welkom op de LoRaWAN Workshop door de VIVES hogeschool - Campus Brugge Station.

Deze workshop geeft een introductie in de draadloze communicatietechnologie LoRaWAN. Voor deze workshop maken we gebruik van een [Arduino](https://www.arduino.cc/) compatibel ontwikkelbord, namelijk de [Sodaq ExpLoRer](https://shop.sodaq.com/explorer.html). Dit bord laat heel makkelijk toe [Grove](http://wiki.seeedstudio.com/Grove/) sensoren aan te koppelen.

Tijdens het eerste deel van de deze workshop gaan we de sensoren inlezen en de informatie draadloos verzenden via LoRaWAN. We zullen hierbij gebruik maken van [The Things Network](https://www.thethingsnetwork.org/) om onze gegevens te bundelen en beschikbaar te stellen voor visualisatie. Vervolgens kunnen we dan gebruik maken van [AllThingsTalk](https://www.allthingstalk.com/) Maker om een grafisch dashboard te bouwen om zo onze sensorwaarden te visualiseren.

In het tweede deel van deze workshop bouwen we dan zelf een webpagina die de gegevens kan visualiseren. Deze webpagina zullen we zelf gaan hosten op een [Raspberry Pi](https://www.raspberrypi.org/).

![Situatieschets](./img/setup_diagram.png)

Wat gaan we dus allemaal doen:

1. Arduino en SODAQ ExpLoRer
2. Grove sensoren uitlezen
3. De uitgelezen sensorwaarden verzenden met LoRaWAN
4. Deze gegevens opvangen met *The Things Network*
5. Visualiseren van de sensorwaarden met een *AllThingsTalk* dashboard
6. Bouwen van een eigen webpagina
7. Webserver opzetten op de Raspberry Pi

## Arduino en SODAQ ExpLoRer

We starten hier met het opzetten van Arduino en het SODAQ ExpLoRer ontwikkelingsbord.

[Arduino opzetten voor SODAQ ExpLoRer](./sodaq-explorer/README.md)

## Sensoren

Grove sensoren uitlezen is een koud kunstje. We hebben hier voor jullie een aantal sensoren voorzien met bijhorende starter sketches. Op deze manier kan je heel snel aan de slag.

[Grove sensoren uitlezen](./sensors/README.md)

## LoRaWAN

Onze sensorwaarden dienen draadloos verstuurd te worden naar The Things Network, als het ware "The Cloud" voor onze sensordata. Dit doen we via LoRaWAN, een Internet of Things communicatietechnologie gemaakt voor low-power devices.

[LoRaWAN](./lorawan/README.md)

## Opzetten van een Webserver

Door onze data af te beelden op een web dashboard kunnen we een mooi overzicht maken. Daarvoor hebben we natuurlijk een webserver nodig.

[Opzetten van een LAMP stack](./lamp/README.md)

## MQTT Broker

Als we onze data ter beschikking stellen via MQTT kan elke geïnteresseerde partij (web app, mobiele app, ...) deze raadplegen.

[Mosquitto](./mosquitto/README.md)

## Node-RED

Node-RED, een grafische flow programmatie, legt de connectie tussen The Things Network en onze MQTT broker.

[Node-RED](./node-red/README.md)

## Eigen webpagina

Hier maken we gebruik van een klein framework om een mooi dashboard te bouwen waar onze data ter beschikking wordt gesteld. Deze hosten we dan natuurlijk op onze eigen Raspberry Pi's.

[IoT Dashboard](./iot-dashboard/README.md)

## PHP en MySQL

Als er tijd over is kunnen we onze data ook opslaan in een database.

[PHP en MySQL](./php-mysql/README.md)