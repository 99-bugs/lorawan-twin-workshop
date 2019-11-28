#include <Wire.h>
#include <Seeed_QTouch.h>

void setup()
{
    // put your setup code here, to run once:
    SerialUSB.begin(115200);
    while ((!SerialUSB) && (millis() < 5000));
    SerialUSB.println("Starten van Q Touch demo");
    Wire.begin();      //Sommige borden hebben dit nodig (ook SODAQ)
}

void loop()
{
  // Lees de huidige stand van de pads in
  int previousState = QTouch.touchNum();
  int state = previousState;

  SerialUSB.println("Wachten voor event");

  // Wachten op verandering van de staat van de touchpads.
  // We wachten ook zolang de pad aangeraakt blijft (state == -1)
  //    (loslaten negeren we dus, enkel indrukken)
  while (state == previousState || state  == -1) {
    previousState = state;          // Nieuwe staat opslaan in oude staat
    state = QTouch.touchNum();      // Nieuwe staat inlezen
    delay(100);    // Even wachten voor ontdendering
  }

  SerialUSB.println("Event is gebeurd");
  SerialUSB.print("Toets aangeraakt met id = ");
  SerialUSB.println(state);
}
