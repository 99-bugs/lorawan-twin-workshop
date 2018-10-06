# Bouwen van een eigen IoT dashboard

HTML, CSS, JavaScript


## HTML document bouwen

De webserver zal alle document die in de map `/var/www/html` staan automatisch gaan *hosten*. Dat wil zeggen dat je vanaf nu naar [http://localhost](http://localhost) kan surfen en daar de documenten uit die map kunt raadplegen.

In de map `/var/www/html` staat reeds een `index.html` document. We zullen dit document eerst verwijderen en zelf een nieuw document  met de naam `index.html` maken. In dit document zullen we zelf de HTML code gaan schrijven zoals hieronder beschreven.

### Basisstructuur

Elk HTML document heeft een minimum structuur nodig. Elk HTML document heeft een `<html>` element nodig waarin alle HTML code zit. 

Elk HTML document bestaat ook uit een `<head>` en een `<body>`. In de `<head>` kan extra informatie bijgehouden worden dat de browser kan gebruiken voor het weergeven van de pagina, maar niet rechtstreeks op de website getoond moet worden. In de `<body>` komt dan de informatie te zitten dat wel aan de gebruiker getoond moet worden.

In de `<head>` worden een aantal `<meta>` elementen gebplaatst die de browser meer vertellen over hoe het document weergegeven moet worden.

Daarnaast kunnen we ook een `<title>` opgeven die in het tabblad weergegeven wordt van de browser. In dit geval is die titel `IoT Dashboard`.

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
</head>
<body>
  
</body>
</html>
```

We kunnen deze code al eens testen door naar de website te surfen [http://localhost](http://localhost). Je zal nog niet veel zien. Enkel een witte pagina. In het tabblad zou wel de titel al reeds zichtbaar moeten zijn.

### Bibliotheken laden

We zullen niet alle code zelf vanaf nul gaan schrijven. Op het internet zijn heel wat bibliotheken en raamwerken beschikbaar waar we gebruik kunnen van maken. Deze bibliotheken en raamwerken bieden functies aan die vaak voorkomende problemen reeds oplossen. Bijvoorbeeld een mooie stijl voor het document opbouwen, of interactiviteit toevoegen.

Wij zullen voor deze toepassing de volgende bibliotheken en raamwerken gebruiken:

* **[Materialize](https://materializecss.com/)**: Is een CSS raamwerk die voor ons een mooie stijl zal geven aan het document. We hoeven dus zelf geen CSS meer te schrijven.
* **[Material Icons](https://materializecss.com/icons.html)**: Een set met kant en klare iconen die we in onze toepassing kunnen gebruiken.
* **[vue.js](https://vuejs.org/)**: Is een JavaScript raamwerk dat het eenvoudig maakt om interactieve toepassingen te bouwen in de browser.
* **[Vue-Mqtt](https://github.com/nik-zp/Vue-Mqtt)**: Is een bibliotheek die MQTT integreert in een Vue toepassing.
* **App.js**: Is het bestand waar wij onze eigen JavaScript code zullen in plaatsen die eigen is aan deze toepassing.

```html
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
<link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
<script src="https://vuejs.org/js/vue.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/vue-mqtt@2.0.2/dist/build.js"></script>
<script src="js/app.js"></script>
```

Laten we nu wat inhoud gaan toevoegen.

### Container toevoegen

Om de webpagina mooi op te maken zullen we gebruik maken van een Materialize *container*. Dit element zorgt ervoor dat onze webpagina mooi gecentreerd in het midden van ons scherm komt te staan. Het zal een marge links en rechts voorzien en zal zich ook aanpassen afhankelijk vanop welk toestel we de pagina bekijken. Zo worden de marges een pak kleiner op een smart-phone om de nuttige ruimte optimaal te benutten.

```html
<div class="container" id="app">
  
</div>
```

### Titel toevoegen

Nu kunnen we een titel toevoegen in de container die wel zichtbaar zal zijn voor de gebruiker. We zullen ook gebruik maken van het `dashboard` icoon van de `material-icons` bibliotheek.

Onder de titel zullen we een horizontale regel tonen, dit kan met het `<hr>` element.

```html
<h1><i class="material-icons medium">dashboard</i> IoT dashboard</h1>
<hr>
```

Bekijk gerust het resultaat eens in de browser.

### Rijen en kolommen

Met onze pagina gaan we verschillende sensorgegevens kunnen voorstellen. We zullen de weergave van deze sensoren dan ook in een soort rooster structuur gaan weergeven met rijen (`row`) en kolommen (`col`). 

We zullen de tekst ook wit maken door een `class` attribuut `white-text` en de tekst centreren door `class` attribuut `center-align` toe te voegen aan de rij definitie.

Voor elke sensor zullen we ook een kolom toevoegen. Dit kunnen we doen door de het attribuut `v-for="sensor in sensors"` te gebruiken.

```html
<div class="row white-text center-align">
  <div class="col s12 m6 l4" v-for="sensor in sensors">

  </div>
</div>
```

### Cards voor elke sensor

Om de sensorgegevens weer te geven zullen we gebruik maken van een Materialize [Card Panel](https://materializecss.com/cards.html). Dit zal een gekleurd vak weergeven met de gegevens (naam, eenheid en waarde) van onze sensor in. 

We kunnen ook de achtergrondkleur van de cards bepalen. We maken hiervoor gebruik van de kleuren uit Materialize [Colors](https://materializecss.com/color.html). In dit geval gebruiken we het kleur `teal`, maar andere kleurnamen kunnen gerust ook gebruikt worden. (`red`, `pink`, `purple`, `deep-purple`, `indigo`, `blue`, `light-blue`, `cyan`, `teal`, `green`, `light-green`, `lime`, `yellow`, `amber`, `orange`, `deep-orange`, `brown`, `grey`, `blue-gray`, `black`)

```html
<div class="card-panel  teal darken-1">
  <div style="font-size: 3rem">{{sensor.value}} {{sensor.unit}}</div>
  <div>{{sensor.name}}</div>
</div>
```

Omdat we tot nu toe nog geen sensoren hebben gedefinieerd (doen we straks in JavaScript) kunnen we voorlopig nog geen resultaat zien van bovenstaande code.

### Resultaat

Als we alles goed samenvoegen dan krijgen we onderstaande resultaat. Deze code zou in het bestand `/var/www/html/index.html` terecht moeten komen.

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
  <script src="https://vuejs.org/js/vue.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/vue-mqtt@2.0.2/dist/build.js"></script>
  <script src="js/app.js"></script>
  <title>IoT Dasboard</title>
</head>
<body>
  <div class="container" id="app">
    <h1><i class="material-icons medium">dashboard</i> IoT dashboard</h1>
    <hr>
    <div class="row white-text center-align">
      <div class="col s12 m6 l4" v-for="sensor in sensors">
        <div class="card-panel  teal darken-1">
          <div style="font-size: 3rem">{{sensor.value}} {{sensor.unit}}</div>
          <div>{{sensor.name}}</div>
        </div>
      </div>
    </div>
  </div>
</body>
</html>
```

## Webpagina dynamisch maken met JavaScript

HTML definities zijn héél statisch. Ze geven betekenis aan inhoud. Waarden van sensoren binnenlezen en communiceren met andere elementen is dus niet mogelijk. JavaScript biedt daarbij een oplossing. Het maakt mogelijk HTML documenten aan te passen eens ze geladen zijn.  We dienen dus nog een extra bestand toe te voegen aan ons project. We zullen een `app.js` bestand moeten maken in een submap `js` van ons project. 

Onderstaande code zullen we dus programmeren in een bestand `/var/www/html/js/app.js`

### App voorbereiden

We zullen een `app` object moeten maken in onze applicatie. We kunnen deze variable reeds declareren, maar nog geen object aan toekennen. 

Variabelen in JavaScript kunnen worden gedeclareerd met het `let` sleutelwoord.

```js
let app = null;
```

### Instellingen

We zullen een MQTT topic, en het ip-adres met poort moeten instellen in onze toepassing. Hiervoor kunnen we twee constanten declareren en een waarde toekennen. Het ip-adres zal je wel moeten aanpassen naar het ip-adres dat jouw eigen Raspberry Pi gekregen heeft (je kan dit nagaan met het `ifconfig` commando. Het ip-address staat dan vermeld bij `eth0` en `inet`).

```js
const topic = 'workshop/+'
const mqttServer = 'mqtt://192.168.1.158:9001'
```

### Lijst met sensoren

We kunnen het aantal sensoren aan de hand van een sensorlijst opmaken. Elke sensor die we hier toevoegen zal zichtbaar worden op onze webpagina. Voor elke sensor dienen we een paar eigenschappen op te geven:

* **name**: Is de naam die we aan onze sensor geven. Deze informatie zal zichtbaar zijn op de webpagina. Bijvoorbeeld, temperatuur, druk, schakelaar, NFC,...
* **value**: Dit is de waarde die de sensor *kan* hebben. De echte waarde zal van de sensor zelf komen, maar indien er geen communicatie is, zal deze waarde getoond worden.
* **unit**: Verschillende sensoren hebben verschillende eenheden. Deze informatie kunnen we hier invullen. Bijvoorbeeld thermometer: `°C`, druk: `hPa`,... Indien je geen eenheid hebt, kan je gewoon de waarde `""` opgeven.
* **topic**: Dit is het MQTT topic dat de sensor gebruikt om zijn waarde te publiceren. Dit is wat we reeds eerder in Node-RED opgegeven hebben.

Het configuratiebestand kan er dan bijvoorbeeld zo gaan uitzien:

```js
const sensorList = [
        {
          name: "hello",
          value: "-",
          unit: '°C',
          topic: 'workshop/temperature'
        },
        {
          name: "foo",
          value: "-",
          unit: '%',
          topic: 'workshop/foo'
        },
        {
          name: "bar",
          value: "-",
          unit: "hPa",
          topic: 'workshop/bar'
        }
      ]  
```

### Sensor informatie updaten

Om de sensorwaarden te kunnen weergeven op onze pagina hebben we een aantal functies nodig om ons te helpen. 

Waarde van een sensor aanpassen:

```js
function updateSensorValue(sensor, value) {
  sensor.value = value.toString()
}
```

De juiste sensor uit de weergegeven sensoren gaan ophalen:

```js
function findSensor(topic){
  return app.$data.sensors.find(sensor => {
    return sensor.topic == topic
  })
}
```

Data dat via MQTT ontvangen is gaan verwerken (byts omzetten naar JavaScript variabelen)

```js
function parseData(data){
  let json = (new TextDecoder("utf-8").decode(data))    
  return JSON.parse(json)                               
}
```

### Nieuwe app bouwen

Nu zijn we klaar met het voorbereiden van onze Vue applicatie. We kunnen deze nu opbouwen met onderstaande code.

```js
document.addEventListener("DOMContentLoaded",function(){

  Vue.use(VueMqtt.default, mqttServer)

  // Create a new Vue application. 
  app = new Vue({
    el: '#app',

  });
});
```

We vertellen hier dat we moeten wachten tot alle code geladen is door de browser (`DOMContentLoaded` event).

We vertellen Vue ook dat we de Vue-Mqtt bibliotheek willen gebruiken met onze ingestelde server.

Daarna kunnen we een nieuwe Vue applicatie bouwen (`new Vue()`)

#### App data

Onze Vue applicatie bestaat uit een aantal onderdelen. 

* **data**: Dit onderdeel bevat alle gegevens die door onze applicatie beheerd moeten worden. In ons geval is dit een lijst met sensoren.
* **mounted**: Dit onderdeel bevat de code die uitgevoerd moet worden bij het opstarten van onze Vue applicatie. Hier gaan we ons gaan abonneren op het MQTT topic waarop we de gegevens wensen te ontvangen.
* **mqtt**: Hier staat de code die we willen uitvoeren wanneer een nieuw pakket met data via MQTT ontvangen is. Hier roepen we de functies aan de we eerder gedefinieerd hebben.

Lijst met data in onze app:

```js
data: {
  sensors: sensorList 
},
```

Opstarten van de app:

```js
mounted () {
  this.$mqtt.subscribe(topic) 
},
```

Ontvangen van MQTT gegevens:

```js
mqtt: {
  [topic]: function (data, topic){        
    let message = parseData(data)
    let sensor = findSensor(topic)
    updateSensorValue(sensor, message)
  }
}
```

### Resultaat

Wanneer we alles samengooien zouden we een code bestand moeten krijgen zoals hieronder voorgesteld. Deze code komt dan terecht in het `/var/www/html/js/app.js` bestand.

```js
let app = null;

const topic = 'workshop/+'
const mqttServer = 'mqtt://192.168.1.158:9001'
const sensorList = [
        {
          name: "hello",
          value: "-",
          unit: '°C',
          topic: 'workshop/temperature'
        },
        {
          name: "foo",
          value: "-",
          unit: '%',
          topic: 'workshop/foo'
        },
        {
          name: "bar",
          value: "-",
          unit: "hPa",
          topic: 'workshop/bar'
        }
      ]  

document.addEventListener("DOMContentLoaded",function(){

  Vue.use(VueMqtt.default, mqttServer)

  app = new Vue({
    el: '#app',         
    data: {             
      sensors: sensorList 
    },
    mounted () {
      this.$mqtt.subscribe(topic)       
    },
    mqtt: {
      [topic]: function (data, topic){
        let message = parseData(data)
        let sensor = findSensor(topic)
        updateSensorValue(sensor, message)
      }
    }
  });
});

function updateSensorValue(sensor, value) {
  sensor.value = value.toString()
}

function findSensor(topic){
  return app.$data.sensors.find(sensor => {
    return sensor.topic == topic
  })
}

function parseData(data){
  let json = (new TextDecoder("utf-8").decode(data))    
  return JSON.parse(json)                               
```