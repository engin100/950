// These are the pins your MicroSD Card Adapter and BME680 will be connected to.
// These pins are specific and should not change. You do not need to worry
// about why these are the pins, just connect them as listed.
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13

// You will pick which digital pin to connect to the chip select pin of the BME
const int BMEchipSelect = ??;


//These are the libraries needed for the BME680 to work
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

//This instantiates the BME sensor in your code
Adafruit_BME680 bme(BMEchipSelect, &SPI);

void setup() {
    Serial.begin(9600);

    delay(100); // Arbitrary delay to let the serial monitor start up

    // Initialize the BME and check if it's connected
    if (!bme.begin()) {
        Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
        while (1);
    }

    // *************** BME680 CONFIGURATION ***************
    bme.setTemperatureOversampling(BME680_OS_2X); // 2 samples for temperature oversampling
    bme.setHumidityOversampling(BME680_OS_2X);    // 2 samples for humidity oversampling
    bme.setPressureOversampling(BME680_OS_4X);    // 4 samples for pressure oversampling
    bme.setIIRFilterSize(BME680_FILTER_SIZE_1);   // Filter size for pressure & temperature, set to 0 for OFF

    // If you want to utilize the gas heater, a common setting is 320 C, 150 ms (320, 150)
    bme.setGasHeater(0, 0); // Gas heater settings: 0 C, 0 ms, DISABLED
    // *************** END OF BME680 CONFIGURATION ***************
}

void loop() {
    bme.performReading(); // Take a reading from the BME680 - all sensor values get measured at once

    Serial.print(F("Temperature = "));
    Serial.print(bme.temperature); // Access the temperature from the latest reading
    Serial.println(F(" *C"));

    Serial.print(F("Pressure = "));
    Serial.print(bme.pressure); // Pressure
    Serial.println(F(" hPa"));

    Serial.print(F("Humidity = "));
    Serial.print(bme.humidity); // Humidity
    Serial.println(F(" %"));

    Serial.print(F("Gas = "));
    Serial.print(bme.gas_resistance / 1000.0); // Resistance of the VOC gas sensor. This value can be correlated with the VOC gas concentration
    Serial.println(F(" KOhms"));

    delay(1000);
}