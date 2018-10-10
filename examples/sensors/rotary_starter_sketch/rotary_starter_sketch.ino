const int ROTARY_PIN = 8;      // Pin van de POT
const double POT_VCC = 5;      // Voedingsspanning van de POT (VCC)
const int POT_MAX_ANGLE = 300; // Maximale angle van de POT

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while ((!SerialUSB) && (millis() < 5000));
  SerialUSB.println("Starten van push button demo");
  pinMode(ROTARY_PIN, INPUT);
}

void loop()
{
  // Lees de waarde van de POT uit (tussen 0 en 255)
  int potValue = get_rotary_value();
  SerialUSB.print("Waarde van POT = ");
  SerialUSB.println(potValue);

  // 100 milliseconden wachten, kan je verhogen of verlagen
  delay(100);
}

int get_rotary_value() {
    int sensor_value = analogRead(ROTARY_PIN);
    float voltage = (float)sensor_value*POT_VCC/1023;
    float degrees = (voltage*POT_MAX_ANGLE)/POT_VCC;
    int byteValue = map(degrees, 0, POT_MAX_ANGLE, 0, 255);

    return byteValue;
}
