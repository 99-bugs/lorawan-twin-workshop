#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// De TPH sensor
Adafruit_BME280 bme;

// Met een byte buffer zoals bij LoRaWAN
const int SIZE_OF_BUFFER = 6;
uint8_t buffer[SIZE_OF_BUFFER];

void setup() {
    // put your setup code here, to run once:
    SerialUSB.begin(115200);
    while ((!SerialUSB) && (millis() < 5000));
    SerialUSB.println("Starten van TPH demo");
    bme.begin();      // Init de TPH sensor
}

void loop() {
    read_tph_sensor_to_buffer();
    SerialUSB.println();
    delay(2000);
}

void read_tph_sensor_to_buffer()
{
    float temperature = bme.readTemperature();
    buffer[0] = ((int)(temperature * 100) >> 8) & 0xFF;
    buffer[1] = ((int)(temperature * 100) >> 0) & 0xFF;
    SerialUSB.print("Temperature = ");
    SerialUSB.print(temperature);
    SerialUSB.println(" *C");

    int pressure = bme.readPressure();
    buffer[2] = (pressure >> 16) & 0xFF;
    buffer[3] = (pressure >> 8) & 0xFF;
    buffer[4] = (pressure >> 0) & 0xFF;
    SerialUSB.print("Pressure = ");
    SerialUSB.print(pressure / 100.0F);
    SerialUSB.println(" hPa");

    buffer[5] = bme.readHumidity();
    SerialUSB.print("Humidity = ");
    SerialUSB.print(buffer[5]);
    SerialUSB.println(" %");
}
