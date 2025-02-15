/*
  Sensor Integration

  Written by: Benjamen Miller, University of Michigan
  Included in UMich ENGR 100.950 "Electronics for Atmospheric and Space Measurements" Public Library

  This code integrates the following components:
  Digital BME680 Temperature, Pressure, Humidity, VOCs sensor (Software SPI)
  Digital MicroSD Card Logger (Hardware SPI)
  Analog ADXL335 Accelerometer
  Analog TMP36 Temperature Sensor

  Code includes commands for Software SPI, Hardware SPI, and analog communications.
  Take note of the values in the section "BME680 Configuration" for data filtering and oversampling
*/

#include <SPI.h>
#include <SD.h>
#include <Adafruit_BME680.h>

// --- Software SPI pins for BME680 ---
#define BME_SCK   6
#define BME_MISO  7
#define BME_MOSI  8
#define BME_CS    9

// --- Hardware SPI pin for SD Card ---
#define SD_CS     10

// BME680 object constructor
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

// ************************************************** NEEDS EDITING **************************************************
const int vDivPin           = A?; // Voltage divider pin
const int tmpPin            = A?; // TMP36 pin
const int xAccelPin         = A?; // x-axis accelerometer pin
const int yAccelPin         = A?; // y-axis accelerometer pin
const int zAccelPin         = A?; // z-axis accelerometer pin

const float R1              = ???; // Ohms, R1 = sum of all resistances between Vin and Vout
const float R2              = ???; // Ohms, R2 = sum of all resistances between Vout and GND

const float tmpSlope        = ?;
const float tmpIntercept    = ?;

const float xAccelSlope     = ?;
const float xAccelIntercept = ?;
const float yAccelSlope     = ?;
const float yAccelIntercept = ?;
const float zAccelSlope     = ?;
const float zAccelIntercept = ?;

bool SerialPrint            = ???; // True to print, false for no serial monitor
// ************************************************** END EDITING **************************************************

// Filename placeholder
char dataFileName[16];

void setup() {
  if (SerialPrint) {
    Serial.begin(9600);
    while (!Serial) { /* wait for Serial */ }
  }

  // --- Initialize SD Card on hardware SPI ---
  pinMode(SD_CS, OUTPUT);
  if (!SD.begin(SD_CS)) {
    if (SerialPrint) {
      Serial.println(F("SD initialization failed!"));
    }
    while (true) {}
  }
  if (SerialPrint) {
    Serial.println(F("SD initialization OK."));
  }

  // --- Find next available file name, like "datalog1.csv", "datalog2.csv" ---
  int fileIndex = 1;
  while (true) {
    // Format candidate
    snprintf(dataFileName, sizeof(dataFileName), "datalog%d.csv", fileIndex);
    
    // Use this filename if it doesn't exist
    if (!SD.exists(dataFileName)) {
      break;  // Filename chosen
    }
    fileIndex++;  // Increment and try the next number
  }

  // Create chosen file and write header
  File dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(F("Time (ms),Voltage (V),TMP36 (C),BME Temp (C),Pressure (Pa),Humidity (%),xAccel (g),yAccel (g),zAccel(g)"));
    dataFile.close();

    if (SerialPrint) {
      Serial.print(F("Created file: "));
      Serial.println(dataFileName);
    }
  } else {
    if (SerialPrint) {
      Serial.print(F("Error1: Can't open "));
      Serial.println(dataFileName);
    }
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
    bme_temperature  = bme.temperature; // °C
    humidity         = bme.humidity;    // %
    pressure         = bme.pressure;    // Pa
  }

  float vDivVal      = analogRead(vDivPin);
  float vDivVoltage  = (vDivVal * 5.0 / 1023.0) * ((R1 + R2) / R2);

  float tmpV         = analogRead(tmpPin) * 5.0 / 1023.0;
  float tmp          = (tmpSlope * tmpV) + tmpIntercept;

  float xAccelV      = analogRead(xAccelPin) * 5.0 / 1023.0;
  float xAccel       = (xAccelSlope * xAccelV) + xAccelIntercept;

  float yAccelV      = analogRead(yAccelPin) * 5.0 / 1023.0;
  float yAccel       = (yAccelSlope * yAccelV) + yAccelIntercept;

  float zAccelV      = analogRead(zAccelPin) * 5.0 / 1023.0;
  float zAccel       = (zAccelSlope * zAccelV) + zAccelIntercept;

  // Build the CSV line with a string
  String dataString;
  dataString += String(millis());       
  dataString += ",";
  dataString += String(vDivVoltage);    
  dataString += ",";
  dataString += String(tmp);            
  dataString += ",";
  dataString += String(bme_temperature);
  dataString += ",";
  dataString += String(pressure);       
  dataString += ",";
  dataString += String(humidity);       
  dataString += ",";
  dataString += String(xAccel);         
  dataString += ",";
  dataString += String(yAccel);         
  dataString += ",";
  dataString += String(zAccel);         

  // Write to SD card using unique filename
  File dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  } else {
    if (SerialPrint) {
      Serial.print(F("Error2: Can't open "));
      Serial.println(dataFileName);
    }
  }

  // Print string to serial monitor
  if (SerialPrint) {
    Serial.println(dataString);
  }

  unsigned long elapsed = millis() - currentTime;
  unsigned long delayTime = 1000 - elapsed % 1000;
  delay(delayTime);
}
