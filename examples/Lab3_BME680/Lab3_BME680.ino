/*
  BME680

  Written by: Benjamen Miller, University of Michigan
  Included in UMich ENGR 100.950 "Electronics for Atmospheric and Space Measurements" Public Library

  This code tests the following component:
  Digital BME680 Temperature, Pressure, Humidity, VOCs sensor (Software SPI)

  Code includes commands for Software SPI
  Take note of the values in the section "BME680 Configuration" for data filtering and oversampling
*/

#include <SPI.h>
#include <Adafruit_BME680.h>

// --- Software SPI pins for BME680 ---
#define BME_SCK   6
#define BME_MISO  7
#define BME_MOSI  8
#define BME_CS    9

// BME680 object constructor
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

bool SerialPrint = true; // Boolean for serial printing ON/OFF function

void setup() {
  if (SerialPrint) {
    Serial.begin(9600);
    while (!Serial) { /* wait for Serial */ }
  }

  // --- Initialize BME680 on software SPI ---
  if (!bme.begin()) {
    if (SerialPrint) {
      Serial.println(F("BME680 initialization failed! Check wiring."));
    }
    while (true) {}
  }
  if (SerialPrint) {
    Serial.println(F("BME680 initialization OK."));
  }

  // *************** BME680 CONFIGURATION ***************
  bme.setTemperatureOversampling(BME680_OS_2X); // 2 samples for temperature oversampling
  bme.setHumidityOversampling(BME680_OS_2X);    // 2 samples for humidity oversampling
  bme.setPressureOversampling(BME680_OS_4X);    // 4 samples for pressure oversampling
  bme.setIIRFilterSize(BME680_FILTER_SIZE_1);   // Filter size for pressure & temperature, set to 0 for OFF

  // If you want to utilize the gas heater, a common setting is 320 C, 150 ms (320, 150)
  bme.setGasHeater(0, 0); // Gas heater settings: 0 C, 0 ms, DISABLED
  // *************** END OF BME680 CONFIGURATION ***************

  if (SerialPrint) {
    Serial.println(F("Setup complete."));
  }
}

void loop() {
  static unsigned long startTime = 0;
  unsigned long currentTime = millis();
  bool bmeOk = bme.performReading();

  // Placeholder values for BME680
  float bme_temperature = NAN;
  float humidity        = NAN;
  float pressure        = NAN;

  if (!bmeOk) {
    if (SerialPrint) {
      Serial.println(F("**BME680 Read Failed**"));
    }
    delay(10);
  } else {
    // Gather sensor values
    bme_temperature = bme.temperature; // °C
    humidity        = bme.humidity;    // %
    pressure        = bme.pressure;    // Pa
  }

  String dataString;
  dataString += String(millis());       
  dataString += ",";
  dataString += String(bme_temperature);
  dataString += ",";
  dataString += String(pressure);       
  dataString += ",";
  dataString += String(humidity);

  // (Optional) Print to Serial Monitor
  if (SerialPrint) {
    Serial.println(dataString);
  }

  unsigned long elapsed = millis() - currentTime;
  unsigned long delayTime = 1000 - elapsed % 1000;
  delay(delayTime);
}
