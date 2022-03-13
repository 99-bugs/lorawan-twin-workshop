//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int ROTARY_PIN = A8;      // Pin van de POT
const double POT_VCC = 5;       // Voedingsspanning van de POT (VCC)
const int POT_MAX_ANGLE = 300;  // Maximale angle van de POT

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }
  
  pinMode(ROTARY_PIN, INPUT);          // Analoge pin als ingang

  SerialUSB.println("Starten van starter sketch potentiometer.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees de hoek uit van de potentiometer
  int potAngle = get_rotary_angle();
  SerialUSB.print("Hoek van de POT: ");
  SerialUSB.print(potAngle);
  SerialUSB.println("°");

  // Omzetten naar een waarde tussen 0 en 255
  int byteValue = map(potAngle, 0, POT_MAX_ANGLE, 0, 255);
  SerialUSB.print("=> Byte waarde: ");
  SerialUSB.println(byteValue);

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}

//**********************************************************
// Bepaal de hoek waarin de potentiometer staat gedraaid
//**********************************************************
double get_rotary_angle() {
  int sensor_value = analogRead(ROTARY_PIN);
  double voltage = (double)sensor_value*POT_VCC/1023;
  double degrees = (voltage*POT_MAX_ANGLE)/POT_VCC;

  return degrees;
}
