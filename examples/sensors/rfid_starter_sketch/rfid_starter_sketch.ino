void setup() {
    Serial.begin(9600);         // Serial is verbonden met de RFID lezer
    SerialUSB.begin(115200);    // De terminal voor de user
}
 
void loop()
{
    // Kijk of er een kaart is en zoja lees het ID
    String id = try_to_read_card();
    if (id.length() > 0) {
      SerialUSB.print("Kaart gedetecteerd met ID = ");
      SerialUSB.println(id);
    }
}

void clear_buffer(char * buffer, int length) {
  for (int i = 0; i < length; i++) {
      buffer[i] = NULL;
  }
}

String  try_to_read_card() {
  static char buffer[64];       // Een buffer voor de gelezen data
  static int counter = 0;       // Een teller voor buffer
  String id = "";               // Het uiteindelijke ID

  while(Serial.available()) {
    char newChar = Serial.read();   // Lees karakter van Serial

    // ASCII 02: STX (Start of Text)
    // ASCII 03: ETX (End of Text)
    if (newChar != 2 && newChar != 3 && counter < 64) {
      buffer[counter++] = newChar;
    } else {
      if (newChar == 3) {
        id = String(buffer);
      }
      clear_buffer(buffer, 64);
      counter = 0;
    }
  }
 
  return id;
}
