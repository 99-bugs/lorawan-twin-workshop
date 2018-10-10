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
  // Lees de huidige stand van de drukknop in
  int pushState = digitalRead(pushPin);

  if (pushState == HIGH) {
    SerialUSB.println("De drukknop is ingedrukt");
  }
  else {
    SerialUSB.println("De drukknop is niet ingedrukt");
  }

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}
