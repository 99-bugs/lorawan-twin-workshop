# LoRaWAN

![LoRaWAN Architectuur](./img/lorawan.jpg)

## Wat is LoRaWAN

LoRaWAN (Long Range Wide Area Network) is een specificatie voor telecommunicatie geschikt voor **lange afstandscommunicatie met weinig vermogen**. De technologie wordt gebruikt voor machine-naar-machine communicatie en het Internet of Things.

De architectuur bestaat uit *gateways*, *netwerkservers* en *applicatieservers*. Er worden RF-chips van Semtech gebruikt die een spread spectrum uitzenden. De nodes versturen een versleuteld bericht via radio. In Europa gebeurt dit op een frequentie van 868 MHz. Dit bericht wordt ontvangen door de gateways in het bereik van de zender. De gateways zijn verbonden met het Internet en sturen het bericht door naar de netwerkservers. Deze berichten kunnen vervolgens worden opgehaald door een applicatieserver. Die kan bepalen of er data teruggezonden moet worden, of de data dient opgeslagen te worden in een database... Een webapplicatie doet dan dienst als interface voor de gebruiker.

## The Things Network

The Things Network bouwt een globaal gedistribueerd, crowd-sourced en open IoT datanetwerk dat eigendom is van, en opgezet wordt door zijn gebruikers. Door gebruik te maken van LoRaWAN technologie voorziet The Things Network een end-to-end stack: van sensoren (de nodes), gateways, netwerk servers, sensor beheer en integratie met cloud providers en IoT platformen. Alles is volledig veilig geïmplementeerd en configureerbaar door de eindgebruiker.

Vooraleer je met dit alles aan de slag kan gaan, dien je echter wel eerst een account te maken op [The Things Network](https://www.thethingsnetwork.org/). Druk bovenaan op `Sign up` en vul je gegevens in.

### Nieuwe TTN applicatie bouwen

Sensoren kunnen communiceren met een *applicatie* van The Things Network waarin ze geregistreerd worden. Om sensoren te registreren moet er eerst een applicatie gebouwd worden.

Je kan een applicatie bouwen door te surfen naar [The Things Network console](https://eu1.cloud.thethings.network/console/applications). Daar dien je een aantal gegevens in te geven:

* **Owner**: De beheerder van de applicatie. Dit ben je in dit geval natuurlijk zelf.
* **Application ID**: Hier kies je zelf een uniek *ID* dat bestaat uit kleine alfanumerieke letters. Spaties zijn niet toegestaan, maar een `-` teken wel.
* **Application name**: Dit kan een meer gebruiksvriendelijk naam zijn voor je applicatie in tegenstelling tot het ID.
* **Description**: Hier kan je een kleine beschrijving plaatsen over de applicatie die je wil toevoegen.

![Applicatie toevoegen](./img/add-application.png)

Klik dan op **Create application** om te eindigen. Je zal doorverwezen worden naar de toegevoegde applicatie pagina. Hier zal je de volledige applicatie en de bijhorende sensoren kunnen beheren. Straks zullen we hier ook de data van onze devices zien binnenstromen.

### Nieuwe sensor toevoegen

Vooralleer een sensor kan communiceren met The Things Network moeten we deze registreren in een applicatie.

Open de applicatie in [The Things Network console](https://eu1.cloud.thethings.network/console/applications) en klik op **Add end device**.

Als je een kant-en-klare LoRaWAN sensor koopt, bestaat de kans dat je deze kan selecteren van de drop down op de huidige pagina.

![Off-the-shelf Device](./img/off-the-shelf.png)

Wij zijn natuurlijk techneuten en maken graag de dingen zelf. Vandaar dat wij moeten kiezen om een device **Manually** toe te voegen.

Er zullen een aantal gegevens gevraagd worden:

* **Frequency plan**: de frequentieband waarop de LoRaWAN chip werkt. Voor Europa kan je kiezen voor `Europe 863-870 MHz (SF9 for RX2 - recommended)`
* **LoRaWAN version**: de versie van LoRaWAN die door de chip (hier de Microchip RN2483) wordt ondersteund. Voor de RN2483 is dit `MAC V1.0.1`.
* **Activation mode**: de manier waarop het device met het netwerk verbind.
  * ABP (activation-by-personalization) is de minder veilige optie omdat hier de encryptie sleutels in het device worden opgeslagen.
  * OTAA (Over-the-air-activation) is de meest veilige optie omdat er hier een join-procedure plaatsvind die resulteert in encryption keys die worden gegenereerd op het device en op de network server. Niet alle devices ondersteunen dit echter. De RN2483 en bijhorende bibliotheek gelukkig wel.

Vervolgens zal je ook onderstaande parameters dienen te genereren door op het :twisted_rightwards_arrows: icoontje te klikken:

* **DevEUI**: een unieke identificatie voor je device.
* **AppEUI** (also called *JoinEUI*): een unieke identificatie voor de join server. Dit wordt aangeboden door de verkoper van het device of in ons geval mag je dit allemaal `0` maken.
* **AppKey**: een geheime sleutel die wordt gebruikt om de `AppSKey` en `NwkSKey` sessie sleutels te genereren die beiden worden gebruikt om het LoRaWAN bericht te versleutelen.

::: tip `AppSKey` en `NwkSKey`

De `AppSKey` of de applicatie sessie key is een key die gebruikt wordt om de berichten te versleutelen tussen je device en de applicatie server. De `NwkSKey` of de de network sessie key is een key die gebruikt wordt om de berichten te versleutelen tussen je device en de network server. Wanneer je geen OTAA maar ABP gebruikt zal je deze geheime sleutels zowel in je device als op de Things Network moeten voorzien. Bij OTAA worden die automatisch gegenereerd op basis van de `AppKey` en wat andere informatie.
:::

Het **End device ID** wordt automatisch gegenereerd voor jou op basis van je `DevEUI`.

![Register Device](./img/register-device.png)

Klik op **Register end device** om te eindigen. Je zal doorverwezen worden naar de overzichtspagina van de nieuwe sensor. Daar kan je de nodige gegevens (`DevEUI`, `AppEUI` en `AppKey`) vinden die we straks in de code zullen moeten gebruiken.

## SODAQ LoRaWAN voorbeeld

`Hello world` voorbeelden zijn bij programmeren de meest eenvoudige voorbeelden om iets aan te tonen. Dit voorbeeld geeft het meest eenvoudige programma om de temperatuur van de ingebouwde sensor te verzenden via LoRaWAN.

::: tip
In de code staat hier en daar wat commentaar met de tekst `TODO:`. Deze tekst wordt door programmeurs gebruikt om zich er aan te herinneren dat er nog iets gedaan moet worden. Kijk dus uit naar `TODO:` tekst, je zal daar optioneel of verplicht nog iets moeten aanpassen.
:::

```cpp
#include <Sodaq_RN2483.h>

#define debugSerial SerialUSB
#define loraSerial Serial2

//**********************************************************
// TODO: verander de waarden van DevEUI, AppEUI en APPkey
//**********************************************************
static const uint8_t DevEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t AppEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t AppKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

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
bool sendLoraMessage = false;

//**********************************************************
// WARNING:   Niet aanpassen. Staat van event gebaseerde
//            sensor
//**********************************************************
int previousState = 0;
int currentState = 0;

//**********************************************************
// TODO: De setup van Arduino, wordt in het begin van je
//       sketch 1x uitgevoerd.
//       Als je sensor moet initialiseren, doe je dit hier
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

    // Configuratie button op SODAQ ExpLoRer
    pinMode(BUTTON, INPUT);        // Digitale pin als ingang
    previousState = digitalRead(BUTTON);    // Lezen van start staat
    currentState = previousState;           // Starten met deze staat

    // Configuratie van LoRaWAN
    loraSerial.begin(LoRaBee.getDefaultBaudRate());
    LoRaBee.init(loraSerial, LORA_RESET);
    setupLoRa();
}

//**********************************************************
// TODO: De loop van Arduino, deze blijft telkens herhalen
//       Hier kies je een type sensor:
//           - periodiek uitgelezen (met delay erin)
//           - event gebaseerde sensoren (zonder delay erin)
//**********************************************************
void loop()
{
    // Periodiek sensor uitlezen
    samplePeriodicSensor();

    // OF

    // Event gebaseerde sensor
    // checkForEvent();

    // Verzenden met LoRa als er bericht klaar staat
    if (sendLoraMessage) {
      SerialUSB.println("Starten met verzenden van LoRaWAN message");
      sendWithLoRa();
      sendLoraMessage = false;
    }

    // Delay verwijderen bij event gebaseerde sensoren
    delay(10000);     // Tijd om te wachten (milliseconden)
}

//**********************************************************
// TODO: Uitlezen van een periodieke sensor en vullen van buffer.
//       Dit moet worden aangepast naargelang de sensor
//**********************************************************
void samplePeriodicSensor()
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

    // Geef aan dat er een bericht klaar is om te verzenden
    sendLoraMessage = true;
}

//**********************************************************
// TODO: Detecteer een verandering voor een event gebaseerde
//       sensor.
//**********************************************************
void checkForEvent()
{
  currentState = digitalRead(BUTTON);

  if (currentState != previousState) {
    SerialUSB.println("De staat van BUTTON is gewijzigd");

    // Wat is de huidige staat?
    if (currentState == LOW) {
      SerialUSB.println("De knop werd ingedrukt");

      // Dit gaan we verzenden met LoRaWAN
      buffer[0] = HIGH;
      numberOfDataBytes = 1;
      sendLoraMessage = true;

    } else {
      SerialUSB.println("De knop werd los gelaten");
    }

    // Set the current state as the previous state
    previousState = currentState;
    delay(10);      // Do some debouncing
  }
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
  } else {
    debugSerial.println("Network connection failed!");
  }
  LoRaBee.setSpreadingFactor(7);
}

void sendWithLoRa()
{
  switch (LoRaBee.send(LORAWAN_PORT, buffer, numberOfDataBytes)) {
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
      debugSerial.println("Oh No! This should not happen. Something is really wrong! The program will reset the RN module.");
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

<!-- TODO: Plaats iets over de tijd van zenden + airtime! -->

### DevEUI, AppEUI en AppKey

Elke LoRaWAN toepassing heeft een aantal instellingen die in de code juist ingesteld moeten worden.

* **DevEUI**: Unieke identificatie van de sensor.
* **AppEUI**: Identificatie van de `App` waartoe de sensor behoort.
* **AppKey**: Encryptiesleutel voor de `App` zodat niemand jouw gegevens kan zien.

Zonder de juiste gegevens komen jouw sensorwaarden niet aan bij de juist applicatie. Vergeet deze dus zeker niet aan te passen in je code. De exacte waarden kan je terug vinden in de console van de Things Network.

Door op de bekjes `<>` te klikken kan je de keys omzetten naar een komma gescheiden formaat dat je rechtstreeks in je code kan plakken.

### Bibliotheken

Vooraleer we nu de firmware kunnen compileren en flashen dienen we nog twee bibliotheken te installeren. Dit doen we in de Arduino IDE. Navigeer hiervoor naar `Tools => Manage Libraries...`.

Zoek eerst naar `Sodaq_RN2483` en installeer de laatste versie van de bibliotheek door op `Install` te klikken.

![Sodaq_RN2483](./img/Sodaq_RN2483.png)

Vervolgens dien je ook de `Sodaq_wdt` bibliotheek te zoeken en te installeren.

![Sodaq_wdt](./img/Sodaq_wdt.png)

### Flashen

Nu de sensor geconfigureerd is kunnen we deze ook gaan programmeren.

Zorg er voor dat het juiste board geselecteerd is onder `Tools => Board`, namelijk `SODAQ ExpLoRer`.

### Data op The Things Network

Navigeer nu terug naar jouw applicatie op [The Things Network console](https://eu1.cloud.thethings.network/console/applications). Als alles goed gaat zou je onder `Live data` jouw gegevens moeten zien binnen komen.

![Live Data](./img/ttn-live-data.png)

Voorlopig zijn dit nog ruwe bytes, maar als er data binnen komt zit je goed.

Komt er geen data binnen, kijk dan eens naar de seriele monitor of er geen errors worden gegeven. Controleer ook nog eens of je de keys wel correct hebt ingegeven.

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
