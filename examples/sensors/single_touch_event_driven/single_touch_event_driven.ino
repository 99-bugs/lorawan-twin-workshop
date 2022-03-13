//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int TOUCH_PIN = 15;   // Pin van de touch sensor

// Globale variabelen met de staat van de touch sensor
int previousState = 0;
int currentState = 0;

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

  // We lezen ook de "start staat" in
  previousState = digitalRead(TOUCH_PIN);
  currentState = previousState;

  SerialUSB.println("Starten van starter sketch niet-blokkerende touch sensor events.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  if (has_pad_been_touched()) {
    // Versturen, verwerken, ... van de touch event
    SerialUSB.println("De touch pad werd aangeraakt");
  }

  // Hier kunnen we pas iets anders doen ...

}

//**********************************************************
// Controleer of iemand de touch heeft aangeraakt
//**********************************************************
bool has_pad_been_touched() {
  currentState = digitalRead(TOUCH_PIN);

  if (currentState != previousState) {
    // Nieuwe staat opslaan in oude staat
    previousState = currentState;

    // We willen enkel het "loslaten" detecteren
    if (currentState == HIGH) {
      // Aangeven dat de pad werd aangeraakt
      return true;
    }
  }

  // Er vond geen verandering plaats
  return false;
}
