const int pushPin = 15;   // Pin van de drukknop

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while ((!SerialUSB) && (millis() < 5000));
  SerialUSB.println("Starten van push button demo");
  pinMode(pushPin, INPUT);          // Digitale pin als ingang
}

void loop()
{
  // Lees de huidige stand van de drukknop
  int previousState = digitalRead(pushPin);
  int state = previousState;

  SerialUSB.println("Wachten voor event");

  // Wachten op verandering van de staat van de knop.
  // We wachten ook zolang de knop ingedrukt is (state == LOW)
  //    (loslaten negeren we dus, enkel indrukken)
  while (state == previousState || state  == LOW) {
    previousState = state;          // Nieuwe staat opslaan in oude staat
    state = digitalRead(pushPin);    // Nieuwe staat inlezen
    delay(10);    // Even wachten voor ontdendering
  }

  SerialUSB.println("Event is gebeurt");
}
