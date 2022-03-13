//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int LIGHT_PIN = A8;         // Pin van de Light sensor
const int LIGHT_MAX_VALUE = 800;  // Maximum waarde bij veel licht

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }
  
  pinMode(LIGHT_PIN, INPUT);          // Analoge pin als ingang

  SerialUSB.println("Starten van starter sketch licht sensor.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees de waarde van de licht sensor uit
  int lightVoltage = analogRead(LIGHT_PIN);
  SerialUSB.print("Spanning licht sensor: ");
  SerialUSB.println(lightVoltage);

  // Omzetten naar een waarde tussen 0 en 255
  int byteValue = map(lightVoltage, 0, LIGHT_MAX_VALUE, 0, 255);
  SerialUSB.print("Byte waarde licht sensor: ");
  SerialUSB.println(byteValue);

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}
