# RFID 125kHz Reader


De Grove RFID 125kHz Reader is een module die kan worden gebruikt om RFID kaarten draadloos uit te lezen. Dit soort sensoren wordt typisch toegepast voor toegangscontrole, track-en-trace van materiaal, ... Deze lezer kan kaarten uitlezen tot een maximaal theoretische afstand van 7cm (circa 5cm in de praktijk).

![RFID 125kHz Reader](./img/Grove-125KHz_RFID_Reader.jpg)

## Specificaties

| Parameter | Waarde |
| --- | --- |
| Spanning | 4.75-5.25V |
| Werkfrequentie | 125kHz |
| TTL Output | 	9600 baudrate, 8 data bits, 1 stop bit, no verify bit |
| Wiegand output | 26 bits Wiegand format, 1 even verify bit, 24 data bits, and 1 odd verify bit |

> **Wiegand**
>
> Wiegand is een van de meest gebruikte communicatiemethode voor apparaten voor toegangscontrole. De term Wiegand in BioStar is een communicatieprotocol dat het Suprema-apparaat en het apparaat van derden verbindt om ID-gegevens te verzenden of om het Suprema-apparaat te verbinden met een RF-lezer om ID-gegevens te verzenden.

De output mode kan worden geselecteerd aan de hand van de jumper:

* links: TTL
* rechts: Wiegand

## Aansluiten

Het aansluiten van de RFID lezer kan niet rechtstreeks via de Grove connector omdat het SODAQ bord niet voorzien is van een Grove connector voor een seriele poort (RX en TX). Daarom gebruiken we een Grove Screw Terminal bordje zoals hieronder afgebeeld.

![Grove Screw Terminal bordje](./img/screw_terminal.jpg)

Verbind vervolgens de terminals als volgt:

| Terminal zijde | SODAQ |
| --- | --- |
| GND (zwart) | GND |
| VCC (rood) | 5V |
| RX (wit) | D1 / TX |
| TX (geeld) | D0 / RX |

Zorg er ook voor dat de jumper op de lezer in volgende positie staat (TTL configuratie).

![TTL mode](./img/ttl_mode.jpg)

Vervolgens kan je ook de antenne aansluiten aan de 2-polige connector.

## Starter Applicatie

Onderstaand vind je een demo sketch die het ID uitleest van de kaart die voor de antenne wordt gehouden. Het huidige ID van de kaart wordt dan vervolgens naar de terminal geschreven.

```c++
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
```

## Meer informatie

Meer informatie is beschikbaar op [http://wiki.seeedstudio.com/Grove-125KHz_RFID_Reader/](http://wiki.seeedstudio.com/Grove-125KHz_RFID_Reader/).


