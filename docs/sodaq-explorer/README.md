# SODAQ ExpLoRer

![Sodaq ExpLoRer](./img/explorer6b.png)

## Features

| Feature | Value |
| ------ | ----- |
| Microcontroller	| ATSAMD21J18, 32-Bit ARM Cortex M0+ |
| Compatibility	| Arduino M0 Compatible |
| Size |	93 x 55 mm |
| Operating | Voltage	3.3V |
| I/O Pins |	20 |
| Analog Output Pin |	10-bit DAC |
| External Interrupts |	Available on all pins |
| DC Current per I/O pin |	7 mA |
| Flash Memory |	256 KB and  4MB (external flash) |
| SRAM |	32KB |
| EEPROM |	Up to 16KB by emulation |
| Clock Speed |	48 MHz |
| Power |	5V USB power and/or 3.7 LiPo battery |
| Charging |	Solar charge controller, up to 500mA charge current |
| LED |	RGB LED, Blue LED |
| LoRa |	Microchip RN2483 Module |
| Bluetooth |	Microchip RN4871 Module |
| Cyptochip |	ATECC508A |
| Temperature sensor |	MCP9700AT |
| USB |	MicroUSB Port |

## Getting started

Download the latest Arduino IDE
[https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software)

To use the board in the Arduino IDE you need to load a custom board file for the SODAQ SAMD boards.
`http://downloads.sodaq.net/package_sodaq_samd_index.json`

File→Preferences

![](./img/sodaq_samd_boards_url.png)

Install the latest version of the SODAQ SAMD boards

Tools→Boards→Boards Manager…

![](./img/boards.png)

## Bluetooth

![](./img/bluetooth-4-logo.jpg)

To use the RN4871 Bluetooth module (BLE) please download the Arduino library here:

[Microchip_RN487x](http://support.sodaq.com/wp-content/uploads/2016/11/Microchip_RN487x.zip)

## Pinout

![](./img/explorer-pinout.png)

### Handy pin definitions!

Now that you’re using the SODAQ ExpLoRer board files, you’ll be able to use our handy pin definitions.
Our pin definitions allow you to address by name instead of pin number.

Here are all the pin definitions for the SODAQ ExpLoRer:

| Pin description |	Pin number |	Definition |
| --- | --- | --- |
| RGB Red  | |LED		LED_RED |
| RGB Green LED | |		LED_GREEN |
| RGB Blue LED | |		LED_BLUE |
| Blue LED |	D13 |	LED_BUILTIN |
| Bluetooth Wake | |		BLUETOOTH_WAKE |
| Bluetooth Reset* | |		BT_RESET |
| Push Button* | |		BUTTON |
| LoRa Reset* | |		LORA_RESET |
| Temperature Sensor |	A6 |	TEMP_SENSOR |

*Rev5 and higher

## Schematics

Click here for the latest schema:

[explorer_schematic_rev6c_868](http://support.sodaq.com/wp-content/uploads/2018/02/explorer_schematic_rev6c_868.pdf)

[explorer_schematic_rev6c_915](http://support.sodaq.com/wp-content/uploads/2018/02/explorer_schematic_rev6c_915.pdf)

[explorer_schematic_rev5b](http://support.sodaq.com/wp-content/uploads/2016/11/Explorer_schematic_rev5b.pdf)

[explorer_schematic_rev3-3](http://support.sodaq.com/wp-content/uploads/2016/11/Explorer_schematic_rev3-3.pdf)

## Hardware Serials

The SODAQ ExpLoRer has 4 hardware serials:
* **SerialUSB** – This is for when you are debugging over the USB Cable.
* **Serial** – Serial is attached to pin D1/TX and D0/RX.
* **Serial1** – Is connected to the Bluetooth Module.
* **Serial2** – Is connected to the RN2483 LoRaWAN Module.

```cpp
void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(57600);
  Serial.begin(57600);
  Serial1.begin(57600);
  Serial2.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
```

### SerialUSB

The sketch starts direct after uploading new code or when connected to a power source.
After opening a Serial Monitor the code will not reset, add the following code to your sketch if you want your sketch to wait for a Serial Monitor.

```cpp
  while ((!SerialUSB) && (millis() < 30000)) {
    // Wait for SerialUSB or start after 30 seconds
  }
```

## Battery management

The ExpLoRer can run on a battery. By default the ExpLoRer is delivered with a coincell battery.
To charge the battery you need to connect an usb and/or solar panel.

The ExpLoRer can only run on one battery at the same time, move the jumper to connect the internal (coincell) or external battery. It will only charge the battery connected with this jumper.

Connect any 3.3v – 5.2v power to the solar connector, this source will charge to battery.

## Bootloader mode

To safe power it is possible to disable the usb connection.
If the **reset button** is **pressed twice within a second** the current sketch will not start and the board will go into bootloader mode and is expecting a new sketch. On your computer you will see a different com port.