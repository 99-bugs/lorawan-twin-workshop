#include <Sodaq_RN2483.h>

#define debugSerial SerialUSB
#define loraSerial Serial2


//**********************************************************
// TODO: verander de waarden van DevEUI, AppEUI en APPkey
//**********************************************************

static uint8_t DevEUI[8] = { 0x00, 0x04, 0xA3, 0x0B, 0x00, 0x23, 0xE2, 0x40 };
const uint8_t AppEUI[8] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x01, 0x25, 0x5C };
const uint8_t AppKey[16] = { 0xF9, 0x1E, 0x4C, 0xCA, 0x99, 0x9E, 0x61, 0x2A, 0x13, 0xBD, 0x94, 0x8E, 0xB5, 0xA7, 0x6A, 0xDC };

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
