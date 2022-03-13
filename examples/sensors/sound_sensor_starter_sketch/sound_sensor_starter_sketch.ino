//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int SOUND_PIN = A8;           // Pin van de geluidssensor
const int MAX_SOUND_LEVEL = 1023;   // Maximale waarde van de geluidssensor
const int AVERAGE_SAMPLES = 32;     // Aantal samples voor gemiddelde

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }
  
  pinMode(SOUND_PIN, INPUT);          // Analoge pin als ingang

  SerialUSB.println("Starten van starter sketch geluidssensor.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees het geluidsniveau uit van de sensor
  int soundLevel = get_sound_level();
  SerialUSB.print("Geluidsniveau: ");
  SerialUSB.println(soundLevel);

  // Omzetten naar een waarde tussen 0 en 255
  int byteValue = map(soundLevel, 0, MAX_SOUND_LEVEL, 0, 255);
  SerialUSB.print("=> Byte waarde: ");
  SerialUSB.println(byteValue);

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}

//**********************************************************
// Bepaal het geluidsniveau van de geluidssensor.
//**********************************************************
int get_sound_level() {
  long averageSoundLevel = 0;
  for (int i = 0; i < AVERAGE_SAMPLES; i++) {
    averageSoundLevel += analogRead(SOUND_PIN);
  }

  return (int)(1.0 * averageSoundLevel / AVERAGE_SAMPLES);
}
