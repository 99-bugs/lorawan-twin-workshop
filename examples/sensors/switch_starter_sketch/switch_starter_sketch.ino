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
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    SerialUSB.println("De schakelaar staat in de AAN stand");
  }
  else {
    SerialUSB.println("De schakelaar staat in de UIT stand");
  }

  // 100 milliseconden wachten, kan je verlagen
  delay(100);
}
