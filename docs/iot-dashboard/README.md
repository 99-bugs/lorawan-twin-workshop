---
description: "Hier maken we gebruik van een klein framework om een mooi dashboard te bouwen waar onze data ter beschikking wordt gesteld. Deze hosten we dan natuurlijk op onze eigen Raspberry Pi's."
---

# Bouwen van een eigen IoT dashboard

HTML, CSS, JavaScript

## HTML document bouwen

De webserver zal alle document die in de map `/var/www/html` staan automatisch gaan *hosten*. Dat wil zeggen dat je vanaf nu naar [http://localhost](http://localhost) kan surfen en daar de documenten uit die map kunt raadplegen.

In de map `/var/www/html` staat reeds een `index.html` document. We zullen dit document eerst verwijderen en zelf een nieuw document  met de naam `index.html` maken. In dit document zullen we zelf de HTML code gaan plaatsen die hieronder beschreven staat.

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
  <script src="https://cdn.jsdelivr.net/npm/axios@0.18.0/dist/axios.min.js"></script>
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

In bovenstaande code staat HTML code die een betekenis toevoegt aan bepaalde woorden of waarden. Om dit correct weer te geven worden een aantal CSS bestanden geladen die de stijl en presentatie van de HTML gaan aanpassen. Met andere woorden de CSS zorgt ervoor dat alles er mooi gaat uitzien.

Er wordt ook wat JavaScript code geladen (staat in `.js` bestanden). Dit is een programmeertaal waarmee we ons document _dynamisch_ kunnen maken. In het document staat nog niet alles, zo weten wet nog niet welke sensoren we willen weergeven, en welke waarden zij hebben. Dit lossen we op door met de JavaScript code de waarden en sensoren te gaan ophalen en in het document te plaatsen.

Als je meer wil weten over hoe het document opgebouwd is en hoe het werkt, of als je het document wil aanpassen, dan kan je via deze link wat meer informatie vinden: [details HTML document](./html-details.md).

## Webpagina dynamisch maken met JavaScript

HTML definities zijn héél statisch. Ze geven betekenis aan inhoud. Waarden van sensoren binnenlezen en communiceren met andere elementen is dus niet mogelijk. JavaScript biedt daarbij een oplossing. Het maakt mogelijk HTML documenten aan te passen eens ze geladen zijn. Voor dit project zullen we twee extra bestanden toevoegen. De belangrijkste reden om dit op te splitsen is de code overzichtelijk te houden en structuur in het project te steken.

* **Code**: `/var/www/html/js/app.js` met de JavaScript code die de verwerking van de gegevens zal voorzien
* **Configuratie**: `/var/www/html/sensors.json` met de configuratie van de verschillende sensoren die we wensen te visualiseren.

We zullen eerst de verwerking van de gegevens opbouwen. Onderstaande code zullen we dus programmeren in een bestand `app.js` dat we in een nieuwe map `js/` zullen plaatsen (`/var/www/html/js/app.js`).

```js
document.addEventListener('DOMContentLoaded', () => {
  axios.get('sensors.json').then((response) => {
    const config = response.data;
    Vue.use(VueMqtt.default, `mqtt://${config.mqtt.broker}:${config.mqtt.port}`)
    let app = new Vue({
      el: '#app',
      data: {
        sensors: config.sensors,
      },
      mounted() {
        this.sensors.forEach((sensor) => {
          this.$mqtt.subscribe(sensor.topic);
        });
      },
      mqtt: {
        '#': function mqttResponse(data, topic) {
          const value = new TextDecoder('utf-8').decode(data);
          const sensor = this.sensors.find(s => s.topic === topic);
          if (sensor) {
            sensor.value = value.toString();
          }
        },
      },
    });
  });
});
```

De JavaScript zal zich _abonneren_ op de mqtt topics die we via Node-Red ingesteld hebben. Indien er data ontvangen wordt zal de code ervoor zorgen dat onze HTML aangepast wordt en dat de verstuurde waarden in de webpagina terecht komen.

Als je meer wil weten over hoe de JavaScript code opgebouwd is en hoe het werkt, of als je de code wil aanpassen, dan kan je via deze link wat meer informatie vinden: [details JavaScript code](./javascript-details).

## Configuratie

Als laatste dienen we nog wat informatie in een configuratiebestand te plaatsen. Deze configuratie wordt dan door onze applicatie gebruikt om zijn werk te kunnen uitvoeren.

Er zijn twee belangrijke zaken die we in deze configuratie moeten verwerken:

* Instellingen voor de MQTT broker
* Informatie over welke sensoren we wensen weer te geven

Deze configuratie zullen we plaatsen in het `/var/www/html/sensors.json` bestand.

### Instellingen

We zullen een MQTT topic, en het ip-adres met poort moeten instellen in onze toepassing. Hiervoor kunnen we twee constanten declareren en een waarde toekennen. Het ip-adres zal je wel moeten aanpassen naar het ip-adres dat jouw eigen Raspberry Pi gekregen heeft (je kan dit nagaan met het `ifconfig` commando. Het ip-address staat dan vermeld bij `eth0` en `inet`).

Wanneer je website op je Raspberry Pi staat, kan je evenwel gebruik maken van `localhost` in plaats van het IP adres van je Pi.

Als we de mqtt en sensoren wensen te configureren krijgen we bijvoorbeeld volgende configuratiebestand dat we in een nieuw `sensor.json` zullen plaatsen. (`/var/www/html/sensors.json`):

```json
{
  "mqtt": {
    "broker": "localhost",
    "port": "9001"
  },
  "sensors": [
    {
      "name": "Foo",
      "value": "-",
      "unit": "°C",
      "topic": "workshop/foo"
    },
    {
      "name": "Bar",
      "value": "-",
      "unit": "%",
      "topic": "workshop/bar"
    },
    {
      "name": "Baz",
      "value": "off",
      "unit": "",
      "topic": "workshop/baz"
    }
  ]
}
```

In het configuratie bestand kan je nu volgende zaken aanpassen voor je eigen sensoren.

* **name**: Is de naam die we aan onze sensor geven. Deze informatie zal zichtbaar zijn op de webpagina. Bijvoorbeeld, temperatuur, druk, schakelaar, NFC,...
* **value**: Dit is de waarde die de sensor *kan* hebben. De echte waarde zal van de sensor zelf komen, maar indien er geen communicatie is, zal deze waarde getoond worden.
* **unit**: Verschillende sensoren hebben verschillende eenheden. Deze informatie kunnen we hier invullen. Bijvoorbeeld thermometer: `°C`, druk: `hPa`,... Indien je geen eenheid hebt, kan je gewoon de waarde `""` opgeven.
* **topic**: Dit is het MQTT topic dat de sensor gebruikt om zijn waarde te publiceren. Dit is wat we reeds eerder in Node-RED opgegeven hebben.

Je kan extra sensoren toevoegen door het deel tussen de `{` en `}` te gaan herhalen met nieuwe waarden. Of indien je minder sensoren hebt, kan je deze blokken gerust verwijderen.

Als je een andere mqtt mqtt server zou gebruiken kan je bvb als broker `mqtt.labict.be` en als port `1884` op te geven.
