//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int SOUND_PIN = A8;           // Pin van de geluidssensor
const int AVERAGE_SAMPLES = 32;     // Aantal samples voor gemiddelde
const int NOISY_LEVEL = 500;        // Wat zien we als "veel lawaai"

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

  SerialUSB.println("Starten van detector sketch geluidssensor.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  bool noiseDetected = false;
  
  for (int i = 0; i < (1000 / (AVERAGE_SAMPLES / 10)); i++) {
    // Lees het gemiddelde geluidsniveau in
    int soundLevel = get_sound_level();

    // Als er ook maar 1x veel lawaai is, dan gaan we dit detecteren
    if (soundLevel >= NOISY_LEVEL) {
      noiseDetected = true;
    }

    delay(10);    // 10ms * (1000 / (AVERAGE_SAMPLES / 10))
                  //    = tijdsvenster van circa 10 seconden
  }

  // Rapportering
  if (noiseDetected) {
    SerialUSB.println("Teveel lawaai gedetecteerd in tijdsvenster");
  } else {
    SerialUSB.println("Geen lawaai in tijdsvenster");
  }
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
