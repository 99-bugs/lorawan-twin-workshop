# Dashboard met AllThingsTalk


<!-- http://docs.allthingstalk.com/networks/use-the-things-network/#send-data-from-ttn-console-and-receive-it-in-maker -->

<!-- 
```php
#include <Sodaq_RN2483.h>
#include <stdio.h>

#define debugSerial SerialUSB
#define loraSerial Serial2

#define NIBBLE_TO_HEX_CHAR(i) ((i <= 9) ? ('0' + i) : ('A' - 10 + i))
#define HIGH_NIBBLE(i) ((i >> 4) & 0x0F)
#define LOW_NIBBLE(i) (i & 0x0F)

const uint8_t devAddr[4] =
{ 0x26, 0x01, 0x14, 0x43 };

// USE YOUR OWN KEYS!
const uint8_t appSKey[16] =
{ 0x23, 0x9B, 0xA2, 0xB9, 0x19, 0x9C, 0x28, 0xD4, 0xB6, 0xE4, 0x09, 0x62, 0xC2, 0xBC, 0x20, 0xB9 };

// USE YOUR OWN KEYS!
const uint8_t nwkSKey[16] =
{ 0xE3, 0x58, 0x1F, 0x7E, 0x46, 0x52, 0xC1, 0x72, 0x32, 0xB7, 0x7F, 0x29, 0x70, 0xD9, 0xD4, 0xA4 };

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
  if (LoRaBee.initABP(loraSerial, devAddr, appSKey, nwkSKey, true))
  {
    debugSerial.println("Communication to LoRaBEE successful.");
  }
  else
  {
    debugSerial.println("Communication to LoRaBEE failed!");
  }
  LoRaBee.setSpreadingFactor(7);
}

void loop()
{
   float reading = getTemperature();
   debugSerial.println(reading);

   uint8_t buffer[2];
   buffer[0] = (((int) (reading * 100)) >> 8) & 0xFF;
   buffer[1] = (((int) (reading * 100)) >> 0) & 0xFF;
   

    switch (LoRaBee.send(1, (uint8_t*)buffer ,2))
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

``` -->