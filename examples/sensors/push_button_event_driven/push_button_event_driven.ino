//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int PUSH_BUTTON_PIN = 15;   // Pin van de drukknop

// Globale variabelen met de staat van de drukknop
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
  
  pinMode(PUSH_BUTTON_PIN, INPUT);          // Digitale pin als ingang

  // We lezen ook de "start staat" in
  previousState = digitalRead(PUSH_BUTTON_PIN);
  currentState = previousState;

  SerialUSB.println("Starten van starter sketch niet-blokkerende push button events.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  if (has_button_been_pressed()) {
    // Versturen, verwerken, ... van de drukknop event
    SerialUSB.println("Er werd op de knop gedrukt");
  }

  // Hier kunnen we pas iets anders doen ...

}

//**********************************************************
// Controleer of er op de knop PUSH_BUTTON_PIN werd gedrukt
//**********************************************************
bool has_button_been_pressed()
{
  currentState = digitalRead(PUSH_BUTTON_PIN);

  if (currentState != previousState) {
    // Nieuwe staat opslaan in oude staat
    previousState = currentState;
    delay(10);    // Even wachten voor ontdendering

    // We willen enkel het "loslaten" detecteren
    if (currentState == HIGH) {
      // Aangeven dat de knop werd ingedrukt
      return true;
    }
  }

  // Er vond geen verandering plaats
  return false;
}
