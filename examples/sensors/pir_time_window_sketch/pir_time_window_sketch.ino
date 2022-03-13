//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int PIR_PIN = 15;             // Pin van de bewegingssensor

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }
  
  pinMode(PIR_PIN, INPUT);          // Digitale pin als ingang

  SerialUSB.println("Starten van starter sketch bewegingssensor met tijdsvenster.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
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
    SerialUSB.println("Geen beweging gedetecteerd in tijdsvenster");
  }
}
