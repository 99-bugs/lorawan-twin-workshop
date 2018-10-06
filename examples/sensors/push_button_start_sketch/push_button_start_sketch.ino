const int pushPin = 15;   // Pin van de drukknop

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while ((!SerialUSB) && (millis() < 30000));
  SerialUSB.println("Starten van push button demo");
  pinMode(pushPin, INPUT);          // Digitale pin als ingang
  pinMode(LED_BLUE, OUTPUT);        // Blauwe LED als uitgang
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Lees de huidige stand van de drukknop in
  int pushState = digitalRead(pushPin);

  if (pushState == HIGH) {
    // LED aan
    digitalWrite(LED_BLUE, LOW);    // Geinverteerd
    SerialUSB.println("De drukknop is ingedrukt");
  }
  else {
    // LED uit
    digitalWrite(LED_BLUE, HIGH);    // Geinverteerd
    SerialUSB.println("De drukknop is niet ingedrukt");
  }

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}
