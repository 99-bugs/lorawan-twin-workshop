#include <Sodaq_RN2483.h>
#include <Wire.h>
#include <Seeed_QTouch.h>

// Vorige staat van de touch pads (geen aangeraakt)
int previousKey = -1;

#define debugSerial SerialUSB
#define loraSerial Serial2

//**********************************************************
// TODO: verander de waarden van DevEUI, AppEUI en APPkey
//**********************************************************

static uint8_t DevEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t AppEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t AppKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//**********************************************************
// TODO: De port waarop de data wordt verzonden
//       Anders per soort sensor
//**********************************************************
const int port = 2;

// Buffer die data kan bevatten
uint8_t buffer[16];

void setup()
{
    delay(1000);
    SerialUSB.begin(115200);
    while ((!SerialUSB) && (millis() < 30000));
    debugSerial.println("Starting LoRaWAN");

    // Configuratie van LoRaWAN
    loraSerial.begin(LoRaBee.getDefaultBaudRate());
    LoRaBee.init(loraSerial, LORA_RESET);
    setupLoRa();

    // Touch sensor
    Wire.begin();      //Sommige borden hebben dit nodig (ook SODAQ)
}

void loop()
{
    // put your main code here, to run repeatedly:
    int key = QTouch.touchNum();

    if (key != previousKey) {
      if (key == 0) {
        SerialUSB.println("Key 0 is touched");
      } else if (key == 1) {
        SerialUSB.println("Key 1 is touched");
      } else if (key == 2) {
        SerialUSB.println("Key 2 is touched");
      } else {
        SerialUSB.println("Key released");
        buffer[0] = (previousKey & 0xFF);    // Buffer vullen met onze data (touch pad)
        sendWithLoRa(1);    // buffer verzenden met LoRa
      }
      previousKey = key;
    }
}

void setupLoRa()
{
    if (LoRaBee.initOTA(loraSerial, DevEUI, AppEUI, AppKey, true)) {
        debugSerial.println("Network connection successful.");
    }
    else {
        debugSerial.println("Network connection failed!");
    }
    LoRaBee.setSpreadingFactor(6);
}

void sendWithLoRa(int numberOfBytes) {
    switch (LoRaBee.send(port, buffer, numberOfBytes))
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
