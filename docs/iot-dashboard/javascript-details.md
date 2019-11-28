
# JavaScript details

## Wachten op de browser tot alles geladen is

Het is belangrijk te wachten op de browser tot deze alle bestanden geladen heeft om code te gaan uitvoeren. We doen dit door te wachten op een *event* waarmee de browser ons verwittigd dat alles klaar is. Dit event heet `DOMContentLoaded`.

```javascript
document.addEventListener('DOMContentLoaded', () => {

});
```

De code die ons effectieve programma zal uitvoeren dienen we tussen de `{` `}` tekens te plaatsen.

## Configuratiebestand ophalen

Het eerste wat we nu dienen te doen is het configuratiebestand gaan ophalen. Dit bestand bevat de informatie over de MQTT broker, maar ook over welke sensoren weergegeven kunnen worden op ons IoT Dashboard.

We maken hiervoor gebruik van de `axios` bibliotheek die voor ons het bestand zal ophalen en de inhoud zal teruggeven als het het bestand gevonden heeft.

De configuratie kunnen we dan in de `data` eigenschap van de `response` terugvinden. We kunnen dit opslaan in een constante (variabele die niet zal veranderen) `config`. We kunnen later dan deze configuratie uitlezen wanneer we deze nodig hebben.

```javascript
...
  axios.get('sensors.json').then((response) => {
    const config = response.data;

  });
...
```

## Nieuwe app bouwen

Nu zijn we klaar met het voorbereiden van onze Vue applicatie. We kunnen deze nu opbouwen met onderstaande code.

We moeten nog vertellen dat `Vue` de `Vue-Mqtt` bibliotheek moet gebruiken met onze instellingen voor onze MQTT server. De effectieve instellingswaarden geven we hier nog niet op, maar zullen we later in ons configuratiebestand opgeven. Als we dan ooit een aanpassing moeten doen moeten we geen code uit dit bestand meer aanpassen, maar enkel in de configuratie.

Daarna kunnen we een nieuwe Vue applicatie bouwen (`new Vue()`)

```js
...
  Vue.use(VueMqtt.default, `mqtt://${config.mqtt.broker}:${config.mqtt.port}`)
  let app = new Vue({
    el: '#app',

    ...

  })
...
```

Elke Vue app moet een HTML element hebben waarin het werkzaam is. Dit geven we hier op door te vertellen dat er in de `index.html` een element bestaat met een `id` attribuut dat de waarde `app` heeft (`#app`).

### App data

Onze Vue applicatie bestaat uit een aantal onderdelen. 

* **data**: Dit onderdeel bevat alle gegevens die door onze applicatie beheerd moeten worden. In ons geval is dit een lijst met sensoren.
* **mounted**: Dit onderdeel bevat de code die uitgevoerd moet worden bij het opstarten van onze Vue applicatie. Hier gaan we ons gaan abonneren op het MQTT topic waarop we de gegevens wensen te ontvangen.
* **mqtt**: Hier staat de code die we willen uitvoeren wanneer een nieuw pakket met data via MQTT ontvangen is. Hier roepen we de functies aan de we eerder gedefinieerd hebben.

### Lijst met data in onze app

Hier geven we op dat de sensoren in de Vue app moeten geladen worden uit ons configuratiebestand.

```js
data: {
  sensors: config.sensors,
},
```

### Na het opstarten van de app

Eens de Vue app volledig opgestart is kunnen we alle sensoren uit de lijst overlopen en kunnen we ons gaan *abonneren* via MQTT op updates van hun gegevens. We zullen dan automatisch verwittigd worden van nieuwe waarden.

```js
mounted () {
  this.sensors.forEach((sensor) => {
    this.$mqtt.subscribe(sensor.topic);
  });
},
```

### Ontvangen van MQTT gegevens

Wanneer we dan effectief ook gegevens gaan ontvangen van de verschillende sensoren moeten we deze nog gaan verwerken. 

```js
mqtt: {
  '#': function mqttResponse(data, topic) {
    const value = new TextDecoder('utf-8').decode(data);
    const sensor = this.sensors.find(s => s.topic === topic);
    if (sensor) {
      sensor.value = value.toString();
    }
  },
},
```

De `#` duid op het feit dat deze functie gegevens van alle *topics* zal gaan verwerken, dit wil zeggen van elke sensor, ongeacht het type, soort of toepassing. Wanneer een sensor nieuwe informatie gaat gaan publiceren, dan worden we verwittigd van die `data`, maar ook van het `topic` waarop de informatie gepubliceerd is.

De data is binair en wordt aan de hand van bytes ter beschikking gesteld in de applicatie. We dienen deze bytes nog om te zetten naar een leesbaar formaat zoals tekst. Dit doen we aan de hand van een `TextDecoder`.

Daarna gaan we in de lijst met sensoren op zoek naar het topic dat overeenkomt met het topic waarop we net informatie verkregen hebben.

Als er een sensor gevonden is met een overeenkomstig topic, dan kunnen we de waarde (`value`) van deze sensor gaan aanpassen met de nieuwe waarde.
