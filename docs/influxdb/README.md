# InfluxDB

[InfluxDB](https://www.influxdata.com/) is een open-source tijdreeksdatabase (TSDB), met andere woorden een database die specifiek is ontworpen voor het bijhouden van tijdsgebonden data. InfluxDB blinkt uit voor het opslaan en ophalen van tijdreeksgegevens - denk maar aan monitoring gegevens, applicatiestatistieken, Internet of Things-sensorgegevens en realtime analyses.

Ook binnen de domotica-wereld wordt er veel gebruik gemaakt van InfluxDB. Zo heeft zowel [OpenHAB](https://www.openhab.org/) als [Home Assistant](https://www.home-assistant.io/) een InfluxDB instantie draaien in de achtergrond voor het bijhouden van al hun tijdsgebonden data.

Voor het visualiseren van tijdsgebonden data wordt ook heel dikwijls gebruik gemaakt van [Grafana](https://grafana.com/), een multi-platform open source dashboarding applicatie die heel makkelijk te koppelen is aan een InfluxDB.

Naast uitgebreide documentatie bestaan er ook tal van libraries om vanuit allerhande programmeertalen een koppeling te leggen met een InfluxDB database, alsook vanuit Node-RED.

::: warning InfluxDB v1.x vs v2.x
Merk op dat er twee versies bestaan van InfluxDB, namelijk v1.x en v2.x. De laatste versie brengt heel wat nieuwe zaken met zich mee en is niet meer compatibel met de vorige versie. Zo wordt er onder andere gebruik gemaakt van een nieuwe query-language. Wij maken voor deze workshop gebruik van de nieuwe versie, zijnde v2.x.
:::

## Installatie van InfluxDB

InfluxDB kan je makkelijk installeren op de Raspberry Pi via *apt*. Om dit mogelijk te maken dient de repo van influx eerst worden toegevoegd:

```bash
curl https://repos.influxdata.com/influxdb.key | gpg --dearmor | sudo tee /usr/share/keyrings/influxdb-archive-keyring.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/influxdb-archive-keyring.gpg] https://repos.influxdata.com/debian $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
sudo apt update
```

Vervolgens kan je `influxdb2` installeren:

```bash
sudo apt -y install influxdb2
```

Om de influxdb service te starten en ook automatisch te laten starten wanneer de Rasbian boot, kan je gebruik maken van volgende commands:

```bash
sudo systemctl unmask influxdb
sudo systemctl enable influxdb
sudo systemctl start influxdb
```

Aan de hand van het volgende command kan je dan nagaan of de service succesvol kon worden opgestart:

```bash
sudo systemctl status influxdb
```

## Configuratie van InfluxDB

Zodra InfluxDB is geinstalleerd kunnen we van slag gaan via de web interface om de configuratie te voltooien.

Je kan hiervoor surfen naar [http://localhost:8086](http://localhost:8086).

Vervolgens dien je volgende gegevens op te geven:

* `Username` en `Password`: deze account is nodig om via de webinterface toegang te krijgen tot je data en de management ervan te doen. Zorg dat je deze niet kwijt speelt gedurende de tijd van de workshop.
* `Initial Organization Name`: een organizatie is eigenlijk een groepering van gebruikers. Hier kan je bv. `workshop` ingeven.
* `Initial Bucket Name`: dit is de naam van je initiele database (dit wordt een bucket genoemt bij influx).

Zodra je alles hebt ingevuld kan je op `Continue` klikken om verder te gaan.

![Initial Setup](./img/initial_setup.png)

Vervolgens mag je klikken op `Configure Later`.

## Installatie Node-RED InfluxDB

Wanneer we vanuit Node-RED willen communiceren met InfluxDB, dienen we dit via nodes te doen. Standaard is er echter geen ondersteuning vanuit Node-RED voor InfluxDB. Gelukkig is er een library hiervoor beschikbaar.

Klik rechts bovenaan op de menu-knop (drie strepen onder elkaar) en kies de optie `Manage Palette`. Open vervolgens het tabblad `Install` en zoek naar `influxdb`. Vervolgens klik je de `Install` knop voor de module `node-red-contrib-influxdb`.

![Install InfluxDB Module](./img/influxdb_install_palette.png)

Als alles gelukt is zou er nu naast de module `Installed` moeten verschijnen. Klik op `Close` om de overlay te sluiten en terug te keren naar de flow-editor.

In Node-RED vind je nu links tussen de andere nodes in de categorie `storage` de nodes `influxdb in` en `influxdb out`.

## Wegschrijven Data

Data webschrijven naar InfluxDB vanuit Node-RED is heel eenvoudig. Het enige dat we dienen te doen is een `influxdb out` node te koppelen aan onze huidige flow en deze correct te configureren.

Koppel een `influxdb out` node zoals hieronder aangegeven aan de `Filter temperatuur` node:

![InfluxDB out node](./img/influxdb_out_node.png)

Voor de configuratie dienen we eerst en vooral een koppeling te maken met de InfluxDB service. Dit doen we door een nieuwe connectie toe te voegen:

![InfluxDB new connection](./img/new_influx_connection.png)

Daar vul je volgende parameters in:

* Name: `InfluxDB2`, vrij te kiezen kies een duidelijke naam.
* Version: `2.0` (noodzakelijk aangezien we met de nieuwe InfluxDB v2.x werken)
* URL: `http://localhost:8086` is correct als je de InfluxDB service op dezelfde Raspberry Pi hebt draaien.

Vooraleer we het API token (dit is een soort authenticatie sleutel) kunnen invullen, dienen we zo een token te genereren via de web portal [http://localhost:8086/](http://localhost:8086/) van InfluxDB. Als je daar navigeert naar `Data => API Tokens` en bovenaan rechts klikt op `Generate API Token => Read/Write API Token`, kan je voor de `iot` bucket - selecteer de bucket door er op te klikken - een API token genereren. Geef je API token ook een beschrijvende naam vooraleer je op `Save` klikt.

![InfluxDB API Token](./img/influx-api-token.png)

Het token kan je dan raadplegen door op de naam te klikken en vervolgens op `Copy to Clipboard` te kliken. Nu kan je het pasten in het `Token` field van je Node-RED InfluxDB connectie.

![InfluxDB connection params](./img/influxdb_connection_done.png)

Eens tevreden met de configuratie, kan je op `Add` klikken.

Voor de node zelf vullen we volgende configuratie parameters in:

* Name: `temperatuur`, een beschrijvende naam voor de functie van de node
* Server: `[v2.0] InfluxDB2`, de connectie die we net gemaakt hebben
* Organization: `workshop`, dit is de organisatie die je hebt gemaakt bij de initiele configuratie van InfluxDB
* Bucket: `iot`, de naam van onze "database"
* Measurement: `temperatuur`, de naam die we onze gemeten waarde geven

Dan zou je tot dit resultaat moeten komen:

![InfluxDB out temperature](./img/influxdb_out_temperatuur.png)

Indien alles goed gaat zou je geen foutmeldingen mogen zien verschijnen.

### Data Raadplegen via Web Portal

Via de web portal [http://localhost:8086/](http://localhost:8086/) van InfluxDB kunnen we nu controleren of onze data wel degelijk in de `iot` bucket terecht komt. Navigeer naar de web portal en begeef je vervolgens naar de `Explorer`.

Hier kunnen we nu via de data explorer heel makkelijk een grafiek genereren van onze data. Dit doe je door volgende selecties te maken:

* FROM: `iot`, de bucket waaruit we onze data willen halen
* Filter: `_measurement` en `temperatuur`, de measurement die we willen raadplegen. Dit is de reeks van gemeten waarden.
* Filter: `_field_` en `value`, het veld van de measurement die we willen ophalen.
* Time Range (rechts naast `Script Editor`): `Past 1h`, geeft aan in welke tijdsrange we geinteresseerd zijn.

Wanneer je op `Submit` drukt zou je nu de grafiek moeten zien verschijnen.

![Temperatuur Grafiek InfluxDB](./img/temperature_graph_influx.png)

Wanneer je op `Script Editor` klikt kan je de echte *query* zien die wordt gebruikt om de data op te halen. Dit gaan we straks nog nodig hebben.

## Ophalen Data

<!-- TODO: Die query opstellen via web interface van influx ... -->

## Grafiek Historiek

<!-- Hoe moet onze data er uit zien ?

Dit kan op twee manieren.

* Meer javascript
* Meer Node-RED -->

