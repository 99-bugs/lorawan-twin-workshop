# Details HTML document

## Basisstructuur

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

## Bibliotheken laden

We zullen niet alle code zelf vanaf nul gaan schrijven. Op het internet zijn heel wat bibliotheken en raamwerken beschikbaar waar we gebruik kunnen van maken. Deze bibliotheken en raamwerken bieden functies aan die vaak voorkomende problemen reeds oplossen. Bijvoorbeeld een mooie stijl voor het document opbouwen, of interactiviteit toevoegen.

Wij zullen voor deze toepassing de volgende bibliotheken en raamwerken gebruiken:

* **[Materialize](https://materializecss.com/)**: Is een CSS raamwerk die voor ons een mooie stijl zal geven aan het document. We hoeven dus zelf geen CSS meer te schrijven.
* **[Material Icons](https://materializecss.com/icons.html)**: Een set met kant en klare iconen die we in onze toepassing kunnen gebruiken.
* **[vue.js](https://vuejs.org/)**: Is een JavaScript raamwerk dat het eenvoudig maakt om interactieve toepassingen te bouwen in de browser.
* **[Vue-Mqtt](https://github.com/nik-zp/Vue-Mqtt)**: Is een bibliotheek die MQTT integreert in een Vue toepassing.
* **Axios**: Is een bibliotheek die toelaat op de achtergrond extra bestanden in te laden, bijvoorbeeld configuratie.
* **App.js**: Is het bestand waar wij onze eigen JavaScript code zullen in plaatsen die eigen is aan deze toepassing.

Door onderstaande link en script tags in de head te plaatsen worden deze bibliotheken automatisch geladen.

```html
<head>
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
  <script src="https://vuejs.org/js/vue.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/vue-mqtt@2.0.2/dist/build.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/axios@0.18.0/dist/axios.min.js"></script>
  <script src="js/app.js"></script>
</head>
```

Laten we nu wat inhoud gaan toevoegen binnen de body.

## Container toevoegen

Om de webpagina mooi op te maken zullen we gebruik maken van een Materialize *container*. Dit element zorgt ervoor dat onze webpagina mooi gecentreerd in het midden van ons scherm komt te staan. Het zal een marge links en rechts voorzien en zal zich ook aanpassen afhankelijk vanop welk toestel we de pagina bekijken. Zo worden de marges een pak kleiner op een smart-phone om de nuttige ruimte optimaal te benutten. Dit element dient binnen in de body tags geplaatst te worden.

```html
<body>
  <div class="container" id="app">

  </div>
</body>
```

## Titel toevoegen

Nu kunnen we een titel toevoegen in de container die wel zichtbaar zal zijn voor de gebruiker. We zullen ook gebruik maken van het `dashboard` icoon van de `material-icons` bibliotheek.

Onder de titel zullen we een horizontale regel tonen, dit kan met het `<hr>` element.

```html
<body>
  <div class="container" id="app">
    <h1><i class="material-icons medium">dashboard</i> IoT dashboard</h1>
    <hr>

  </div>
</body>
```

Bekijk gerust het resultaat eens in de browser.

## Rijen en kolommen

Met onze pagina gaan we verschillende sensorgegevens kunnen voorstellen. We zullen de weergave van deze sensoren dan ook in een soort rooster structuur gaan weergeven met rijen (`row`) en kolommen (`col`). 

We zullen de tekst ook wit maken door een `class` attribuut `white-text` en de tekst centreren door `class` attribuut `center-align` toe te voegen aan de rij definitie.

Voor elke sensor zullen we ook een kolom toevoegen. Dit kunnen we doen door de het attribuut `v-for="sensor in sensors"` te gebruiken.

```html
<body>
  <div class="container" id="app">
    <h1><i class="material-icons medium">dashboard</i> IoT dashboard</h1>
    <hr>

    <div class="row white-text center-align">
      <div class="col s12 m6 l4" v-for="sensor in sensors">

      </div>
    </div>

  </div>
</body>
```

## Cards voor elke sensor

Om de sensorgegevens weer te geven zullen we gebruik maken van een Materialize [Card Panel](https://materializecss.com/cards.html). Dit zal een gekleurd vak weergeven met de gegevens (naam, eenheid en waarde) van onze sensor in. 

We kunnen ook de achtergrondkleur van de cards bepalen. We maken hiervoor gebruik van de kleuren uit Materialize [Colors](https://materializecss.com/color.html). In dit geval gebruiken we het kleur `teal`, maar andere kleurnamen kunnen gerust ook gebruikt worden. (`red`, `pink`, `purple`, `deep-purple`, `indigo`, `blue`, `light-blue`, `cyan`, `teal`, `green`, `light-green`, `lime`, `yellow`, `amber`, `orange`, `deep-orange`, `brown`, `grey`, `blue-gray`, `black`)

```html
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
```

Omdat we tot nu toe nog geen sensoren hebben gedefinieerd (doen we straks in JavaScript) kunnen we voorlopig nog geen resultaat zien van bovenstaande code.
