#include <Wire.h>
#include <Seeed_QTouch.h>

// Vorige staat van de touch pads (geen aangeraakt)
int previousKey = -1;

void setup()
{
    // put your setup code here, to run once:
    SerialUSB.begin(115200);
    while ((!SerialUSB) && (millis() < 30000));
    SerialUSB.println("Starten van Q Touch demo");
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
      }
      previousKey = key;
    }
}
