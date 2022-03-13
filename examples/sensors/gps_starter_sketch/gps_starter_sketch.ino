//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int SIZE_OF_BUFFER = 128;
char buffer[SIZE_OF_BUFFER] = {};

//**********************************************************
// De setup van Arduino, wordt in het begin van je sketch
// eenmalig uitgevoerd.
// Als je sensor moet initialiseren, dan doe je dit hier
//**********************************************************
void setup() {
  SerialUSB.begin(115200);

  // 10 seconden wachten op SerialUSB. 
  while ((!SerialUSB) && (millis() < 10000)) { }
  
  Serial.begin(9600);         // Serial is verbonden met de GPS sensor

  SerialUSB.println("Starten van starter sketch GPS sensor.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees data lijn van de GPS
  read_gps_data_line();   // Blokkeert tot GPS beschikbaar is
  
  // SerialUSB.println("GPS data:");
  // SerialUSB.println(buffer);   // buffer bevat GPS data

  String line(buffer);
  if (line.startsWith("$GPGGA")) {
    SerialUSB.print("GPS data: ");
    SerialUSB.println(line);   // buffer bevat GPS data
  }
}

int read_gps_data_line() {
  int counter = 0;      // Teller voor de buffer
  bool startDetected = false;
  bool done = false;

  do {
    if (Serial.available()) {
      // Lees karakter van Serial
      char newChar = Serial.read();
            
      // Kijk of dit het begin is van een lijn (start met dollar)
      if (newChar == '$') {
        clear_buffer();
        startDetected = true;
      }

      // We negeren alle data tenzij start werd gedetecteerd
      if (startDetected) {
        buffer[counter++] = newChar;

        // Look for the end of the datagram
        if (newChar == '\n') {
          startDetected = false;
          buffer[counter] = '\0';   // Afsluiten van buffer met null-character
          return true;      // Aangeven dat de buffer klaar is

        } else if (counter >= SIZE_OF_BUFFER) {    // buffer overflow
          clear_buffer();
        }
      }
    }
  } while (!done);
}

void clear_buffer() {
  for (int i = 0; i < SIZE_OF_BUFFER; i++) {
    buffer[i] = 0;
  }
}

