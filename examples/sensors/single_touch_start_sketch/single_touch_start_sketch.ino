//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int TOUCH_PIN = 15;   // Pin van de touch sensor

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }
  
  pinMode(TOUCH_PIN, INPUT);          // Digitale pin als ingang

  SerialUSB.println("Starten van starter sketch touch sensor.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees de huidige stand van de touch sensor in
  int touchState = digitalRead(TOUCH_PIN);

  if (touchState == HIGH) {
    SerialUSB.println("De touch knop wordt aangeraakt");
  }
  else {
    SerialUSB.println("De touch knop is niet aangeraakt");
  }

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}
