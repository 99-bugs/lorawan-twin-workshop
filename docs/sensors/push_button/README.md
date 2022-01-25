# Een Push Button

De Grove Push Button is een drukknop die ideaal is om dingen aan of uit te zetten. In tegenstelling tot een schakelaar blijft een drukknop niet in zijn positie staan. Dit betekent dus dat de knop zichzelf herstelt nadat deze is losgelaten.

Ondertussen bestaan er een aantal versies van deze module. Maar deze verschillen hoofdzakelijk in het uitzicht van de drukknop.

![De Push Button](./img/push_button.jpg)

## Aansluiten

Om de drukknop te verbinden met het SODAQ bord dien je eerst en vooral een **4-pins connector** aan te sluiten op de PCB. Vervolgens sluit je de andere zijde van de connector aan op het SODAQ bord. Opgelet, je dient hier wel de connectie te maken met de correcte header op het SODAQ bord, namelijk deze **met de digitale/analoge pins**, niet de I2C header. In volgende afbeelding wordt dit nog eens weergegeven.

![Drukknop op het SODAQ bord aansluiten](./img/connecting_button_to_sodaq.png)

Als je de markeringen op de PCB van de drukknop bekijkt en vergelijkt met deze op het SODAQ bord (achterzijde), zal je zien dat de output van de drukknop (aangeduid met `SIG`) is aangesloten op `D15`. `NC` staat voor *Not Connected* of niet aangesloten.

## Starter Applicatie

Onderstaand vind je een demo sketch die de stand van de drukknop om de 100 milliseconden uitleest. De huidige stand van de drukknop wordt vervolgens weergegeven in de console.

De vertraging kan worden verkleind of vergroot naargelang de toepassing.

```cpp
const int PUSH_PIN = 15;   // Pin of Push Button

// Put your setup code here, to run once:
void setup() {
  SerialUSB.begin(115200);

  // Configure push pin as digital input
  pinMode(PUSH_PIN, INPUT);

  // Wait for SerialUSB or start after 10 seconds
  while ((!SerialUSB) && (millis() < 10000)) {}

  SerialUSB.println("Starting Push Button demo ...");
}

// Put your main code here, to run repeatedly:
void loop() {
  // Read out the current state of the push button
  int pushState = digitalRead(PUSH_PIN);

  if (pushState == HIGH) {
    SerialUSB.println("The push button is pressed.");
  } else {
    SerialUSB.println("The push button is not pressed.");
  }

  // Wait 100 milliseconds between each read.
  // You can lower or raise this
  delay(100);
}
```

Als je de knop een aantal keer indrukt zou je een dergelijke output in de seriele monitor moeten krijgen.

![Output](./img/output.png)

## Event gebaseerd

De starter applicatie is goed om aan te tonen hoe de drukknop werkt, maar meestal zijn we niet geinterreseerd in de huidige staat op bepaalde momenten maar eerder in verandering. Met andere woorden, onze applicatie zou moeten detecteren wanneer er iemand de knop indrukt of los laat. Dit noemen we event gebaseerd.

Er zijn in principe twee manieren om dit te realiseren:

* met interrupts, waarbij de microcontroller hardwarematig de verandering detecteert. Dit moet echter worden ondersteund voor de pin waarop de drukknop is aangesloten.
* met een state machine, waarbij we software-matig kijken of de staat van de drukknop verandert is ten opzichte van de vorige check.

De tweede optie is hier voor ons de meest toepasselijke omdat dit ook later het best zal werken in samenwerking met LoRaWAN.

```cpp
const int PUSH_PIN = 15;   // Pin of Push Button

// Previous state of Push Button
int previousState = 0;
int currentState = 0;

// Put your setup code here, to run once:
void setup() {
  SerialUSB.begin(115200);

  // Configure push pin as digital input
  pinMode(PUSH_PIN, INPUT);
  previousState = digitalRead(PUSH_PIN);    // Read start state
  currentState = previousState;             // Starting with this state

  // Wait for SerialUSB or start after 10 seconds
  while ((!SerialUSB) && (millis() < 10000)) {}

  SerialUSB.println("Starting Push Button Event demo ...");
}

// Put your main code here, to run repeatedly:
void loop() {
  currentState = digitalRead(PUSH_PIN);

  if (currentState != previousState) {
    SerialUSB.println("Detected state change of push button");

    // What is the current state?
    if (currentState == LOW) {
      SerialUSB.println("Push button was PRESSED");
    } else {
      SerialUSB.println("Push button was RELEASED");
    }

    // Set the current state as the previous state
    previousState = currentState;
    delay(10);      // Do some debouncing
  }
}
```

Dit zou de volgende output moeten geven als je een aantal keer de knop indrukt en terug los laat.

![Output of Event Based Demo](./img/event_output.png)

Merk op dat je op deze manier nu kan kiezen op welke verandering je reageert. Op het drukken, het los laten of zelfs beiden.

## Meer informatie

Meer informatie kan je terugvinden op de website van Seeed Studio: [https://wiki.seeedstudio.com/Grove-Button](https://wiki.seeedstudio.com/Grove-Button).
