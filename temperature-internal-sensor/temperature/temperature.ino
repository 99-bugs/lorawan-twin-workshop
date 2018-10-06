#include <Sodaq_RN2483.h>

#define debugSerial SerialUSB
#define loraSerial Serial2

static uint8_t DevEUI[8]
{ 0x00, 0x04, 0xA3, 0x0B, 0x00, 0x23, 0xE2, 0x40 };

const uint8_t AppEUI[8] =
{ 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x01, 0x25, 0x5C };

const uint8_t AppKey[16] =
{ 0xC3, 0xD1, 0x6B, 0xFC, 0xAD, 0x52, 0xBC, 0xA1, 0xD6, 0xFB, 0xE6, 0xFA, 0x1F, 0xD2, 0xD2, 0x17 };

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
   float reading = getTemperature();
   debugSerial.println(reading);

   uint8_t buffer[2];
   buffer[0] = ((int)(reading * 100) >> 8) & 0xFF;
   buffer[1] = ((int)(reading * 100) >> 0) & 0xFF;

    switch (LoRaBee.send(1, buffer, 2))
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
    // Delay between readings
    // 60 000 = 1 minute
    delay(10000); 
}

float getTemperature()
{
  //10mV per C, 0C is 500mV
  float mVolts = (float)analogRead(TEMP_SENSOR) * 3300.0 / 1023.0;
  float temp = (mVolts - 500.0) / 10.0;
  
  return temp;
}

