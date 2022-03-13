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

  SerialUSB.println("Starten van starter sketch bewegingssensor.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees de huidige stand van de PIR sensor in
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    SerialUSB.println("Beweging gedetecteerd");
  }
  else {
    SerialUSB.println("Geen beweging gedetecteerd");
  }

  // 500 milliseconden wachten, kan je verhogen of verlagen
  delay(500);
}
