# Opzetten van een LAMP stack

Wanneer we een moderne website op een Raspberry Pi (of elke andere machine) willen hosten, hebben we een aantal basiscomponenten nodig zoals:

* **L**inux - het operating systeem waar alles op draait
* **A**pache - een webserver, welke onze pagina's aanbied aan de browser van de gebruiker
* **M**ySQL - een database server die toelaat om gegevens op te slaan
* **P**HP - een scripting taal die toelaat dynamische pagina's te bouwen die op de server worden verwerkt

Deze combinatie van componenten wordt in de webdeveloper wereld een LAMP stack genoemd.

Linux is reeds aanwezig op onze Raspberry Pi onder de vorm van Raspbian. Dus dit hoeven we niet meer te installeren. De andere componenten gaan we wel opzetten.

In volgende paragrafen staan er hoofdzakelijk commando's die dienen te worden uitgevoerd in de terminal. Deze kan je op Raspbian openen door te navigeren naar `Start => Tools => Terminal`. Je krijgt dan volgend scherm te zien. Hier type je de commando's dan gewoon in waarna je op `ENTER` duwt.

## Updaten van Raspbian

Vooraleer te starten is het altijd een goed idee om het besturingssysteem zelf te updaten naar de laatste nieuwe versie.

```shell
sudo apt update
sudo apt upgrade -y
```

Eens klaar met installeren van de updates kan je verder gaan.

## Installeren van de Webserver

Als webserver maken we gebruik van Apache, een heel gekende en bewezen webserver. Een veelvoorkomend alternatief is Nginx (uitgesproken als Engine X), maar Apache is iets makkelijker op te zetten.

```shell
sudo apt install apache2 -y
```

### Webserver testen

Je kan de webserver op dit moment reeds testen door op de Raspberry Pi te surfen naar `http://localhost` en dan zou je onderstaande pagina moeten krijgen.

![Apache works](./img/apache_works.png)

Indien je vanop een andere computer naar de Raspberry Pi wil surfen heb je het IP address van de Pi nodig. Dit kan je achterhalen door het commando `ifconfig` uit te voeren in de terminal. Het IP adres vind je dan bij de `eth0` interface naast `inet`. In het voorbeeld hieronder is het IP adres `172.16.1.228`.

```shell
pi@raspberrypi:~ $ ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.16.1.228  netmask 255.255.0.0  broadcast 172.16.255.255
        inet6 fe80::6f6:6b2a:3fc2:1c1  prefixlen 64  scopeid 0x20<link>
        ...

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        ....

wlan0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        ...
```

Je kan in dit geval dan surfen naar `http://172.16.1.228` waar je het IP adres vervang door dit van de Pi.