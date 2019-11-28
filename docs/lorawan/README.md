---
description: "Door onze data af te beelden op een web dashboard kunnen we een mooi overzicht maken. Daarvoor hebben we natuurlijk een webserver nodig."
---

# LoRaWAN

![LoRaWAN Architectuur](./img/lorawan.jpg)

## Wat is LoRaWAN

LoRaWAN (Long Range Wide Area Network) is een specificatie voor telecommunicatie geschikt voor langeafstandscommunicatie met weinig vermogen. De technologie wordt gebruikt voor machine-naar-machine communicatie en het Internet of Things.

De architectuur bestaat uit *gateways*, *netwerkservers* en *applicatieservers*. Er worden RF-chips van Semtech gebruikt die een spread spectrum uitzenden. De nodes versturen een versleuteld bericht via radio. In Europa is deze frequentie 868 MHz. Dit bericht wordt ontvangen door de gateway. De gateway is verbonden met het Internet en stuurt het bericht door naar de netwerkservers. De berichten kunnen worden opgehaald door een applicatieserver. Die kan bepalen of er data teruggezonden moet worden, of de data dient opslagen te worden in een database, ... . Een webapplicatie doet dan dienst als interface voor de gebruiker.

## The Things Network

The Things Network bouwt een globaal gedistribueerd, crowd-sourced en open IoT datanetwerk dat eigendom is, en opgezet wordt door zijn gebruikers. Door gebruik te maken van LoRaWAN technologie voorziet The Things Network een end-to-end stack: van sensoren (de nodes), gateways, netwerk servers, sensor beheer en integratie met cloud providers en IoT platformen. Alles is volledig veilig geïmplementeerd en configureerbaar door de eindgebruiker.

Vooraleer je met dit alles aan de slag kan dien je echter wel eerst een account te maken op [The Things Network](https://www.thethingsnetwork.org/). Druk bovenaan op `Sign Up` en vul je gegevens in.

### Nieuwe TTN applicatie bouwen

Sensoren kunnen communiceren met een `applicatie` van The Things Network waarin ze geregistreerd worden. Om sensoren te registreren moet er eerst een applicatie gebouwd worden.

Je kan een applicatie bouwen door te surfen naar The Things Network [console](https://console.thethingsnetwork.org/applications/add). Daar dien je een aantal gegevens in te geven:

* **Application ID**: Hier kies je zelf een uniek *ID* dat bestaat uit kleine alfanumerieke letters. Spaties zijn niet toegestaan, maar een `-` teken wel.
* **Application description**: Hier kan je een kleine beschrijving plaatsen over de applicatie die je wil toevoegen.

![Applicatie toevoegen](./img/add-application.png)

Klik dan op **Add Application** om te eindigen. Je zal doorverwezen worden naar de toegevoegde applicatie pagina. Hier zal je de gegenereerde **App EUI** en **Access Keys** terugvinden (deze hebben we later nog nodig).

### Nieuwe sensor toevoegen

Vooralleer een sensor kan communiceren met The Things Network moeten we deze registreren in een applicatie.

Open de applicatie in The Things Network [console](https://console.thethingsnetwork.org/applications/) en klik op **Register device**. Er zullen een aantal gegevens gevraagd worden:

* **Device ID**: Hier kies je zelf een uniek *ID* dat bestaat uit kleine alfanumerieke letters. Spaties zijn niet toegestaan, maar een `-` teken wel.
* **Device EUI**: Druk op het :twisted_rightwards_arrows: icoontje om een willekeurige EUI te berekenen bij het aanmaken van de sensor.
* **App Key**: Deze laten we ook automatisch genereren.

![Registreer sensor](./img/register-device.png)

Klik op **Register** om te eindigen. Je zal doorverwezen worden naar de overzichtspagina van de nieuwe sensor. Daar kan je de nodige gegevens (`DevEUI`, `AppEUI` en `AppKey`) vinden die we straks in de code zullen moeten gebruiken.

## Sodaq LoRaWAN voorbeeld

`Hello world` voorbeelden zijn bij programmeren de meest eenvoudige voorbeelden om iets aan te tonen. Dit voorbeeld geeft het meest eenvoudige programma om de temperatuur van de ingebouwde sensor te verzenden via LoRaWAN.

::: tip
In de code staat hier en daar wat commentaar met de tekst `TODO:`. Deze tekst wordt door programmeurs gebruikt om zich er aan te herinneren dat er nog iets gedaan moet worden. Kijk dus uit naar `TODO:` tekst, je zal daar optioneel of verplicht nog iets moeten aanpassen.
:::

## DevEUI, AppEUI en AppKey

Elke LoRaWAN toepassing heeft een aantal instellingen die in de code juist ingesteld moeten worden.

* **DevEUI**: Unieke identificatie van de sensor.
* **AppEUI**: Identificatie van de `App` waartoe de sensor behoort.
* **AppKey**: Encryptiesleutel voor de `App` zodat niemand jouw gegevens kan zien.

Zonder de juiste gegevens komen jouw sensorwaarden niet aan bij de juist applicatie. Vergeet deze dus zeker niet aan te passen in je code. De exacte waarden kan je terug vinden in de console van de Things Network.

Nu de sensor geconfigureerd is kunnen we deze ook gaan programmeren. Dit doen we in de Arduino IDE.

Bibliotheken: Zorg dat de benodigde bibliotheken geïnstalleerd zijn via de Arduino bibliotheken manager:

`Schets -> Bibliotheek gebruiken -> Bibliotheken beheren`

Installeer de `Sodaq_RN2483` en `Sodaq_wdt` bibliotheken.

Zorg er ook voor dat het juiste `Board` geselecteerd (`SODAQ Explorer`) is onder `Hulpmiddelen -> Board:`

### Eenvoudig LoRaWAN verzenden voorbeeld

```cpp
#include <Sodaq_RN2483.h>

#define debugSerial SerialUSB
#define loraSerial Serial2

//**********************************************************
// TODO: verander de waarden van DevEUI, AppEUI en APPkey
//**********************************************************
static uint8_t DevEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t AppEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t AppKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//**********************************************************
// TODO: De poort waarop de data wordt verzonden
//       Andere poort per type sensor
//**********************************************************
const int LORAWAN_PORT = 1;

//**********************************************************
// WARNING:   Niet aanpassen. Maakt de buffer voor data.
//**********************************************************
const int SIZE_OF_BUFFER = 32;
uint8_t buffer[SIZE_OF_BUFFER];
uint8_t numberOfDataBytes = 1;

//**********************************************************
// TODO: De setup van Arduino, wordt in het begin van je
//       sketch 1x uitgevoerd.
//       Als je sensor moet initializeren, doe je dit hier
//**********************************************************
void setup()
{
    pinMode(LED_BLUE, OUTPUT);         // Blauwe LED als uitgang
    pinMode(LED_RED, OUTPUT);          // Rode LED als uitgang
    pinMode(LED_GREEN, OUTPUT);        // Groene LED als uitgang

    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    
    SerialUSB.begin(115200);
    while ((!SerialUSB) && (millis() < 5000));
    debugSerial.println("Starting LoRaWAN");

    // Configuratie button op Sodaq
    pinMode(BUTTON, INPUT);        // Digitale pin als ingang

    // Configuratie van LoRaWAN
    loraSerial.begin(LoRaBee.getDefaultBaudRate());
    LoRaBee.init(loraSerial, LORA_RESET);
    setupLoRa();
}

//**********************************************************
// TODO: De loop van Arduino, deze blijft telkens herhalen
//       Hier kies je een type sensor:
//           - perdiodiek uitgelezen (met delay erin)
//           - event gebasseerde sensoren (zonder delay erin)
//**********************************************************
void loop()
{
    // Periodiek sensor uitlezen
    getSensorValue();
    // OF
    // Event gebasseerde sensor, blocking - delay in commentaar zetten!
    // waitForEvent();

    // Verzenden met LoRa
    sendWithLoRa();

    // Delay verwijderen bij event-gebasseerde sensoren
    delay(10000);     // Tijd om te wachten (milliseconden)
}

//**********************************************************
// TODO: Uitlezen van een periodieke sensor en vullen van buffer.
//       Dit moet worden aangepast naargelang de sensor
//**********************************************************
void getSensorValue()
{
    //10mV per C, 0C is 500mV
    float mVolts = (float)analogRead(TEMP_SENSOR) * 3300.0 / 1023.0;
    float temperature = (mVolts - 500.0) / 10.0;

    // Uitschrijven in console
    debugSerial.println(temperature);

    // Buffer vullen met onze data (temperatuur)
    buffer[0] = ((int)(temperature * 100) >> 8) & 0xFF;
    buffer[1] = ((int)(temperature * 100) >> 0) & 0xFF;
    numberOfDataBytes = 2;
}

//**********************************************************
// TODO: Wachten op een verandering voor een event gebasseerde
//       sensor.
//**********************************************************
void waitForEvent()
{
  // Lees de huidige stand van de drukknop
  int previousState = digitalRead(BUTTON);
  int state = previousState;

  debugSerial.println("Wachten voor event");

  // Wachten op verandering van de staat van de knop.
  // We wachten ook zolang de knop ingedrukt is (state == HIGH)
  //    (loslaten negeren we dus, enkel indrukken)
  while (state == previousState || state  == HIGH) {
    previousState = state;          // Nieuwe staat opslaan in oude staat
    state = digitalRead(BUTTON);    // Nieuwe staat inlezen
    delay(10);    // Even wachten voor ontdendering
  }

  debugSerial.println("Event is gebeurt");

  // Opslaan in buffer om te verzenden
  buffer[0] = HIGH;
  numberOfDataBytes = 1;
}

//**********************************************************
// WARNING:   Vanaf hier dien je niets meer aan te passen.
//            Dit zijn de functies die de LoRa data verzenden.
//**********************************************************
void setupLoRa()
{
    if (LoRaBee.initOTA(loraSerial, DevEUI, AppEUI, AppKey, true)) {
        debugSerial.println("Network connection successful.");
        digitalWrite(LED_BLUE, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
    }
    else {
        debugSerial.println("Network connection failed!");
    }
    LoRaBee.setSpreadingFactor(7);
}

void sendWithLoRa() {
    switch (LoRaBee.send(LORAWAN_PORT, buffer, numberOfDataBytes))
    {
        case NoError:
          debugSerial.println("Successful transmission.");
          break;
        case NoResponse:
          debugSerial.println("There was no response from the device.");
          break;
        case Timeout:
          debugSerial.println("Connection timed-out. Check your serial connection to the device! Sleeping for 20sec.");
          delay(20000);
          break;
        case PayloadSizeError:
          debugSerial.println("The size of the payload is greater than allowed. Transmission failed!");
          break;
        case InternalError:
          debugSerial.println("Oh No! This shouldn not happen. Something is really wrong! The program will reset the RN module.");
          setupLoRa();
          break;
        case Busy:
          debugSerial.println("The device is busy. Sleeping for 10 extra seconds.");
          delay(10000);
          break;
        case NetworkFatalError:
          debugSerial.println("There is a non-recoverable error with the network connection. The program will reset the RN module.");
          setupLoRa();
          break;
        case NotConnected:
          debugSerial.println("The device is not connected to the network. The program will reset the RN module.");
          setupLoRa();
          break;
        case NoAcknowledgment:
          debugSerial.println("There was no acknowledgment sent back!");
          break;
        default:
          break;
    }
}
```

### The Things Network Decoder

Wanneer de data op de TTN binnenkomt dan zijn dit ruwe bytes. Dit is vrij low-level en zou de eindapplicatie dwingen om de ruwe data om te zetten naar eigenlijke informatie. We kunnen dit proces door de TTN laten doen. Dit maakt debuggen makkelijker en zorgt er ook voor dat een applicatie die gebruik wil maken van de data dit niet meer hoeft te doen.

Open je applicatie op de [console](https://console.thethingsnetwork.org/applications) van The Things Network.

![Console TTN](./img/ttn-console-app.png)

Klik bovenaan rechts op `Payload Formats`. We kunnen nu in het venster een stukje JavaScript code plaatsen die de raw bytes omzet naar een meer leesbaar en verwerkbaar formaat. Typisch gebruiken we voor deze dingen JSON.

Kopieer onderstaande JS code en plaats dit in het `decoder` venster.

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 1) {
    decoded.temperature = (bytes[1] + bytes[0]*256)/100.0;
  }

  return decoded;
}
```

Later zullen we deze nog moeten uitbreiden voor de andere sensoren.

![Console TTN](./img/ttn-payload-decoder.png)

Klik vervolgens op `Save`.

### Decoders Sensoren

Controlleer voor alle zekerheid dat de `port` van de decoder dezelfde is als deze van je applicatie op de Sodaq.

#### Push Button

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 17 || port == 28 || port == 31) {
    decoded.state = (bytes[0] == 0xFF ? true : false);
    decoded.event = true;
  }

  return decoded;
}
```

#### Switch (P)

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 17 || port == 28 || port == 31) {
    decoded.state = (bytes[0] == 0xFF ? true : false);
    decoded.event = true;
  }

  return decoded;
}
```

#### Q Touch Sensor

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 17 || port == 28 || port == 31) {
    decoded.state = (bytes[0] == 0xFF ? true : false);
    decoded.event = true;
  }

  return decoded;
}
```

#### RFID 125kHz Reader

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 25) {
    var id = "";
    for (var i = 0; i < bytes.length; i++) {
      id += String.fromCharCode(bytes[i]);
    }
    decoded.id = id;
    decoded.single_byte = bytes[0] | bytes[1];
  }

  return decoded;
}
```

#### Bewegingssensor

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 16) {
    decoded.motion = bytes[0];
  }

  return decoded;
}
```

#### Rotatiesensor

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 11) {
    decoded.rotation = bytes[0];
  }

  return decoded;
}
```

#### Temperatuur, druk en vochtigheidssensor

```js
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  if (port == 10) {
    decoded.temperature = (bytes[1] + bytes[0]*256)/100.0;
    decoded.pressure = (bytes[4] + bytes[3]*256 + bytes[2]*256*256) / 100.0;
    decoded.humidity = bytes[5];
  }

  return decoded;
}
```
