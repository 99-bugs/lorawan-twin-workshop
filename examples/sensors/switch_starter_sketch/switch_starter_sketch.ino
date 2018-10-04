const int switchPin = 15;   // Pin van Switch

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while ((!SerialUSB) && (millis() < 30000));
  SerialUSB.println("Starten van switch demo");
  pinMode(switchPin, INPUT);        // Digitale pin als ingang
  pinMode(LED_BLUE, OUTPUT);        // Blauwe LED als uitgang
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Lees de huidige stand van de schakelaar
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    // LED aan
    digitalWrite(LED_BLUE, LOW);    // Geinverteerd
    SerialUSB.println("De schakelaar staat in de AAN stand");
  }
  else {
    // LED uit
    digitalWrite(LED_BLUE, HIGH);    // Geinverteerd
    SerialUSB.println("De schakelaar staat in de UIT stand");
  }

  // 100 milliseconden wachten, kan je verlagen
  delay(100);
}
