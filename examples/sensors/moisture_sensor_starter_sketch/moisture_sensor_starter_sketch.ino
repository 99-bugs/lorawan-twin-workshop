//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int MOISTURE_PIN = A8;           // Pin van de vochtsensor
const int MAX_MOISTURE_LEVEL = 1023;   // Maximale waarde van de analoge spanning

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }
  
  pinMode(MOISTURE_PIN, INPUT);          // Analoge pin als ingang

  SerialUSB.println("Starten van starter sketch vochtsensor.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees de spanning uit van de sensor
  int moistureVoltage = analogRead(MOISTURE_PIN);
  SerialUSB.print("Vochtgehalte: ");
  SerialUSB.println(moistureVoltage);

  // Omzetten naar een waarde tussen 0 en 255
  int byteValue = map(moistureVoltage, 0, MAX_MOISTURE_LEVEL, 0, 255);
  SerialUSB.print("=> Byte waarde: ");
  SerialUSB.println(byteValue);

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}
