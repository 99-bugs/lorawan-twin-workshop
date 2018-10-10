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
  bool motionDetected = false;
  
  for (int i = 0; i < 1000; i++) {
      // Lees de huidige stand van de PIR sensor in
      int pirState = digitalRead(PIR_PIN);

      // Als er ook maar 1x beweging is, dan gaan we dit detecteren
      if (pirState == HIGH) {
        motionDetected = true;
      }

      delay(10);    // 10ms * 1000 = tijdsvenster van 10 seconden
  }

  // Rapportering
  if (motionDetected) {
    SerialUSB.println("Beweging gedetecteerd in tijdsvenster");
  } else {
    SerialUSB.println("Geen beweging in tijdsvenster");
  }
}
