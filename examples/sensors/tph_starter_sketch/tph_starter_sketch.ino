#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// De TPH sensor
Adafruit_BME280 bme;

void setup() {
    // put your setup code here, to run once:
    SerialUSB.begin(115200);
    while ((!SerialUSB) && (millis() < 5000));
    SerialUSB.println("Starten van TPH demo");
    bme.begin();      // Init de TPH sensor
}

void loop() {
    SerialUSB.print("Temperature = ");
    SerialUSB.print(bme.readTemperature());
    SerialUSB.println(" *C");

    SerialUSB.print("Pressure = ");
    SerialUSB.print(bme.readPressure() / 100.0F);
    SerialUSB.println(" hPa");

    SerialUSB.print("Humidity = ");
    SerialUSB.print(bme.readHumidity());
    SerialUSB.println(" %");

    SerialUSB.println();
    delay(2000);
}
