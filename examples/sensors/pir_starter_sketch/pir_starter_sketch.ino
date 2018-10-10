const int PIR_PIN = 15;   // Pin van de PIR sensor

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while ((!SerialUSB) && (millis() < 5000));
  SerialUSB.println("Starten van PIR sensor demo");
  pinMode(PIR_PIN, INPUT);          // Digitale pin als ingang
}

void loop()
{
  // Lees de huidige stand van de PIR sensor in
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    SerialUSB.println("Beweging gedetecteerd");
  }
  else {
    SerialUSB.println("Geen beweging");
  }

  // 500 milliseconden wachten, kan je verhogen of verlagen
  delay(500);
}
