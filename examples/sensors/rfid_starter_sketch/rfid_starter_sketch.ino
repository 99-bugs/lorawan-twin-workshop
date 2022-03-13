//**********************************************************
// Hier gaan we globale variabelen declareren.
// Deze zijn beschikbaar doorheen de volledige sketch.
//**********************************************************
const int SIZE_OF_BUFFER = 32;
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
  
  Serial.begin(9600);         // Serial is verbonden met de RFID lezer

  SerialUSB.println("Starten van starter sketch RFID lezer.");
}

//**********************************************************
// De main loop van Arduino, deze blijft telkens herhalen.
//**********************************************************
void loop() {
  // Lees het id van een RFID kaart
  read_rfid_card();   // Blokkeert tot een ID is gedetecteerd
  
  SerialUSB.print("Kaart gedetecteerd met ID = ");
  SerialUSB.println(buffer);   // buffer bevat ID

  // Welke tag werd gedetecteerd?
  if (!strcmp(buffer, "0A0069138AFA")) {
    SerialUSB.println("Rode tag gedetecteerd");
  } else if (!strcmp(buffer, "380067B6739A")) {
    SerialUSB.println("Blauwe tag gedetecteerd");
  } else if (!strcmp(buffer, "080066377821")) {
    SerialUSB.println("Gele tag gedetecteerd");
  } else {
    SerialUSB.println("Onbekende tag gedetecteerd");
  }
}

int read_rfid_card() {
  static int counter = 0;       // Een teller voor buffer
  int sizeOfId = 0;

  while (sizeOfId != 12) {
    while(Serial.available()) {
      char newChar = Serial.read();   // Lees karakter van Serial
      // ASCII 02: STX (Start of Text)
      // ASCII 03: ETX (End of Text)
      if (newChar != 2 && newChar != 3 && counter < SIZE_OF_BUFFER) {
        buffer[counter++] = newChar;
        buffer[counter] = '\0';
        sizeOfId = counter;
      } else {
        counter = 0;
      }
    }
  }
 
  return sizeOfId;
}
