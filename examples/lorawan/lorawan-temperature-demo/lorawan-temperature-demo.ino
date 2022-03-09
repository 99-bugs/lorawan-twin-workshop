
#include <Sodaq_RN2483.h>

#define loraSerial Serial2

//**********************************************************
// TODO: Verander de waarden van DevEUI, AppEUI en APPkey
//       volgens deze aangegeven op de console van
//       The Things Network.
//**********************************************************
static const uint8_t DevEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t AppEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t AppKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//**********************************************************
// Niet aanpassen. Maakt de buffer voor data.
//**********************************************************
const int SIZE_OF_BUFFER = 32;
uint8_t buffer[SIZE_OF_BUFFER];   // Buffer voor bericht
uint8_t numberOfDataBytes = 1;    // Aantal te versturen bytes

// Aangeven of LoRaWAN bericht klaar is om te versturen
bool sendLoraMessage = false;     

//**********************************************************
// Staat van event gebaseerde sensoren
//**********************************************************
int previousState = 0;
int currentState = 0;

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  pinMode(LED_BLUE, OUTPUT);         // Blauwe LED als uitgang
  pinMode(LED_RED, OUTPUT);          // Rode LED als uitgang
  pinMode(LED_GREEN, OUTPUT);        // Groene LED als uitgang

  status_connecting();
    
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }

  SerialUSB.println("Starten van LoRaWAN temperatuur demo.");

  // Configuratie digitale pin als ingang
  pinMode(BUTTON, INPUT);

  // We lezen ook de "start staat" in
  previousState = digitalRead(BUTTON);
  currentState = previousState;

  // Configuratie van LoRaWAN
  loraSerial.begin(LoRaBee.getDefaultBaudRate());
  LoRaBee.init(loraSerial, LORA_RESET);
  setup_lora();
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//
//    Hier kies je een type sensor:
//       - periodiek uitgelezen (met delay erin)
//       - event gebaseerde sensoren (zonder delay erin)
//**********************************************************
void loop() {
    // Periodiek sensor uitlezen
    sample_periodic_sensor();

    // OF

    // Event gebaseerde sensor
    // check_sensor_for_event();

    // Verzenden met LoRaWAN als er bericht klaar staat
    if (sendLoraMessage) {
      SerialUSB.println("Starten met verzenden van LoRaWAN message");
      send_message_with_lora();
      sendLoraMessage = false;
    }

    // Delay verwijderen bij event gebaseerde sensoren
    delay(10000);     // Tijd om te wachten (milliseconden)
}

//**********************************************************
// TODO: Uitlezen van een periodieke sensor en vullen van buffer.
//       Dit moet worden aangepast naargelang de sensor
//**********************************************************
void sample_periodic_sensor() {
  //10mV per C, 0C is 500mV
  float mVolts = (float)analogRead(TEMP_SENSOR) * 3300.0 / 1023.0;
  float temperature = (mVolts - 500.0) / 10.0;

  // Uitschrijven naar seriele monitor
  SerialUSB.print("Temperatuur = ");
  SerialUSB.print(temperature);
  SerialUSB.println("°C");

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
void check_sensor_for_event() {
  currentState = digitalRead(BUTTON);

  if (currentState != previousState) {
    // Nieuwe staat opslaan in oude staat
    previousState = currentState;
    delay(10);    // Even wachten voor ontdendering

    // We willen enkel het "loslaten" detecteren
    if (currentState == HIGH) {
      SerialUSB.println("De knop werd ingedrukt");

      // Dit gaan we verzenden met LoRaWAN
      buffer[0] = HIGH;
      numberOfDataBytes = 1;
      sendLoraMessage = true;
    }
  }
}

//**********************************************************
// Niet aanpassen. Dit zijn de functies die de LoRa data verzenden.
//**********************************************************
void setup_lora() {
  if (LoRaBee.initOTA(loraSerial, DevEUI, AppEUI, AppKey, true)) {
    SerialUSB.println("LoRaWAN - Network connectie OK");
    status_ok();
  } else {
    SerialUSB.println("LoRaWAN - Network connectie gefaald!");
    status_error();
  }
  LoRaBee.setSpreadingFactor(7);
}

void send_message_with_lora(unsigned int port = 1) {
  status_sending();
  int status = LoRaBee.send(port, buffer, numberOfDataBytes);

  switch (status) {
    case NoError:
      SerialUSB.println("LoRaWAN - Bericht verstuurd.");
      status_ok();
      break;
    case NoResponse:
      SerialUSB.println("LoRaWAN - De RN2483 chip reageert niet meer.");
      status_warning();
      break;
    case Timeout:
      SerialUSB.println("LoRaWAN - Connectie time-out. 20 seconden wachten ...");
      status_warning();
      delay(20000);
      break;
    case PayloadSizeError:
      SerialUSB.println("LoRaWAN - Transmissie gefaald. Het bericht was te groot.");
      status_warning();
      break;
    case InternalError:
      SerialUSB.println("LoRaWAN - Interne fout. Resetting RN2483 ...");
      status_error();
      setup_lora();
      break;
    case Busy:
      SerialUSB.println("LoRaWAN - RN2483 is bezet. 10 seconden wachten ...");
      status_error();
      delay(10000);
      break;
    case NetworkFatalError:
      SerialUSB.println("LoRaWAN - Er was een network fout. Resetting RN2483 ...");
      status_error();
      setup_lora();
      break;
    case NotConnected:
      SerialUSB.println("LoRaWAN - Connectie verloren. Resetting RN2483 ...");
      status_error();
      setup_lora();
      break;
    case NoAcknowledgment:
      SerialUSB.println("LoRaWAN - Er werd geen bevestiging ontvangen.");
      status_warning();
      break;
    default:
      break;
  }
}

//**********************************************************
// Niet aanpassen. Status RGB led
//**********************************************************
void status_connecting() {
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
}

void status_ok() {
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
}

void status_sending() {
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
}

void status_warning() {
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
}

void status_error() {
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
}