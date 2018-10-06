# LoRaWAN 'hello world' voorbeeld

`Hello world` voorbeelden zijn bij programmeren de meest eenvoudige voorbeelden om iets aan te tonen. Dit voorbeeld geeft het meest eenvoudige programma om vaste waarde, in dit geval de tekst `Hello world!` te verzenden via LoRaWAN.

::: tip
In de code staat hier en daar wat commentaar met de tekst `TODO:`. Deze tekst wordt door programmeurs gebruikt om zich er aan te herinneren dat er nog iets gedaan moet worden. Kijk dus uit naar `TODO:` tekst, je zal daar optioneel of verplicht nog iets moeten aanpassen.
:::

## DevEUI, AppEUI en AppKey

Elke LoRaWAN toepassing heeft een aantal instellingen die in de code juist ingesteld moeten worden. 

* **DevEUI**: Unieke identificatie van de sensor.
* **AppEUI**: Identificatie van de `App` waartoe de sensor behoort.
* **AppKey**: Encryptiesleutel voor de `App` zodat niemand jouw gegevens kan zien.

Zonder de jusite gegevens komen Vergeet deze dus zeker niet aan te passen in je code. De exacte waarden kan je terug vinden in de console van de Things Network. 

## De `getValue()` functie

Onderaan het programma vind je de `getValue()` functie. Wanneer deze functie aangeroepen wordt in het hoofdprogramma, dan zal deze functie een `String` of tekstwaarde teruggeven. Deze teruggeven waarde - die je dus krijgt bij het aanroepen van de functie - zal de waarde zijn die via LoRaWAN verzonden wordt.

Pas deze tekst gerust eens aan, en kijk of je deze waarde kunt verzenden. Let wel op, LoRaWAN kan maar een beperkt aantal tekens verzenden. Hou je bericht dus korter dan 50 tekens. Meer tekens kunnen onder bepaalde omstandigheden verzonden worden.

## Voorbeeld code

<!-- <<< @/docs/examples/lorawan/hello-world.md  -->

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


void setup()
{
  delay(1000);
  
  while ((!debugSerial) && (millis() < 10000)){
    // Wait 10 seconds for debugSerial to open
  }

  debugSerial.println("Start");

  // Start streams
  debugSerial.begin(57600);
  loraSerial.begin(LoRaBee.getDefaultBaudRate());

  LoRaBee.setDiag(debugSerial); // to use debug remove //DEBUG inside library
  LoRaBee.init(loraSerial, LORA_RESET);
  
  setupLoRa();
}

void setupLoRa(){
  if (LoRaBee.initOTA(loraSerial, DevEUI, AppEUI, AppKey, true))
  {
    debugSerial.println("Network connection successful.");
  }
  else
  {
    debugSerial.println("Network connection failed!");
  }

  LoRaBee.setSpreadingFactor(7);
}


void loop()
{
   String value = getValue();
   debugSerial.println(value);

    switch (LoRaBee.send(1, (uint8_t*)value.c_str(), value.length()))
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
      debugSerial.println("Oh No! This shouldn't happen. Something is really wrong! The program will reset the RN module.");
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
    // Delay between transmissions (in milliseconds)
    // 60 000 = 1 minute
    delay(10000); 
}

//**********************************************************
// TODO: De waarde van 'value' zal de data zijn die
//       verzonden wordt via LoRaWAN. Je kan deze
//       dus aanpassen afhankelijk van je toepassing.
//**********************************************************

String getValue()
{
  String value = "Hello world!";
  return value;
}
```