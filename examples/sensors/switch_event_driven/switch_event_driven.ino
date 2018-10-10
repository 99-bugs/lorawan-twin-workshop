const int switchPin = 15;   // Pin van Switch

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while ((!SerialUSB) && (millis() < 5000));
  SerialUSB.println("Starten van switch demo");
  pinMode(switchPin, INPUT);        // Digitale pin als ingang
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Lees de huidige stand van de schakelaar
  int previousState = digitalRead(switchPin);
  int state = previousState;

  SerialUSB.println("Wachten voor event");

  // Wachten op verandering van de staat van de schakelaar.
  while (state == previousState) {
    previousState = state;          // Nieuwe staat opslaan in oude staat
    state = digitalRead(switchPin);    // Nieuwe staat inlezen
    delay(10);    // Even wachten voor ontdendering
  }

  SerialUSB.println("Event is gebeurt");

  SerialUSB.println("De schakelaar is ");
  SerialUSB.println(state);
  
}
