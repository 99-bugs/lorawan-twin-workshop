# TWIN Workshop

Welkom op de LoRaWAN Workshop door de VIVES hogeschool - Campus Xaverianenstraat.

Deze workshop geeft een introductie in de draadloze communicatietechnologie LoRaWAN. Voor deze workshop maken we gebruik van een [Arduino](https://www.arduino.cc/) compatibel ontwikkelbord, namelijk de [Sodaq ExpLoRer](https://shop.sodaq.com/explorer.html). Dit bord laat heel makkelijk toe [Grove](http://wiki.seeedstudio.com/Grove/) sensoren aan te koppelen.

Tijdens het eerste deel van de deze workshop gaan we de sensoren inlezen en de informatie draadloos verzenden via LoRaWAN. We zullen hierbij gebruik maken van [The Things Network](https://www.thethingsnetwork.org/) om onze gegevens beschikbaar te stellen. Vervolgens gaan we deze gegevens binnenhalen met een Node-RED flow die deze beschikbaar zal stellen via MQTT.

In het tweede deel van deze workshop bouwen we zelf een dashboard dat de gegevens kan visualiseren. Deze webpagina zullen we zelf gaan hosten op een [Raspberry Pi](https://www.raspberrypi.org/).

## VuePress

De documentatie van deze workshop is op basis van [VuePress](https://v2.vuepress.vuejs.org/) gebouwd. Om de site lokaal beschikbaar te stellen dien je NodeJS te installeren en volgende commando's uit te voeren in directory van dit project:

```bash
npm install
npm run docs:dev
```

## License

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
