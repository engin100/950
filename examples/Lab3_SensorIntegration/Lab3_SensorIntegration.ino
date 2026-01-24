/*
  Sensor Integration

  Written by: Benjamen Miller & Ismael Enriquez, University of Michigan
  Included in UMICH ENGR 100.950 "Electronics for Atmospheric and Space Measurements" Public Library

  This code integrates the following components:
  Digital BME680 Temperature, Pressure, Humidity, VOCs sensor (Hardware SPI)
  Digital MicroSD Card Logger (Hardware SPI)
  Analog ADXL335 Accelerometer
  Analog TMP36 Temperature Sensor

  Code includes commands for Hardware SPI and analog communications.
  Take note of the values in the section "BME680 Configuration" for data filtering and oversampling
*/

// These are the pins your MicroSD Card Adapter and BME680 will be connected to.
// These pins are specific and should not change. You do not need to worry
// about why these are the pins, just connect them as listed.
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// ************************************************** NEEDS EDITING **************************************************
// This is the CS pin that the SD Logger is connected to
const int SDLoggerChipSelect = ??;

// This is the CS pin that the BME680 is connected to
const int BMEchipSelect = ??;

// These are the pins your accelerometer lines are connected to
const int xAccelPin = A?;
const int yAccelPin = A?;
const int zAccelPin = A?;

// This is the pin your TMP36 is connected to 
const int tmpPin = A?;

// This is the pin your voltage divider is connected to
const int vDivPin = A?;

// Ohms, R1 = sum of all resistances between Vin and Vout
const float R1 = ???;

// Ohms, R2 = sum of all resistances between Vout and GND
const float R2 = ???;

const float tmpSlope        = ?;
const float tmpIntercept    = ?;

const float xAccelSlope     = ?;
const float xAccelIntercept = ?;
const float yAccelSlope     = ?;
const float yAccelIntercept = ?;
const float zAccelSlope     = ?;
const float zAccelIntercept = ?;

// true to print, false for no serial monitor
bool serialPrint = ???;
// ************************************************** END EDITING **************************************************

// This is the string that goes at the top of your csv file. It is the column headers for your spreadsheet.
// You can change this as needed.
const String header = "Time(ms),Voltage(V),TMP36(C),BME_Temp(C),Pressure(Pa),Humidity(%),xAccel(g),yAccel(g),zAccel(g)";

//This instantiates the BME sensor in your code
Adafruit_BME680 bme(BMEchipSelect, &SPI);

// Filename placeholder
char dataFileName[16];

void setup() {
  if (serialPrint) {
    Serial.begin(9600);
    while (!Serial) { /* wait for Serial */ }
  }

  if(serialPrint)
    Serial.print(F("Initializing SD card..."));

  // See if the card is present and can be initialized:
  if (!SD.begin(SDLoggerChipSelect)) {
    if(serialPrint)
      Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  if(serialPrint)
    Serial.println("SD card initialized!");

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

  // Now, before we actually start reading data, we need to write the header to the file.
  // Open the file. Note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
      dataFile.println(header);
      dataFile.close();
      if (serialPrint) {
        Serial.print(F("Created file: "));
        Serial.println(dataFileName);
      }
  } 
  else {
      if (serialPrint) {
        Serial.print(F("Error1: Can't open "));
        Serial.println(dataFileName);
      }
  }

  // Initialize the BME and check if it's connected
  if (!bme.begin()) {
      if(serialPrint)
        Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
      while (1);
  }
  if(serialPrint)
    Serial.println(F("BME680 initialization OK!"));

  // *************** BME680 CONFIGURATION ***************
  bme.setTemperatureOversampling(BME680_OS_2X); // 2 samples for temperature oversampling
  bme.setHumidityOversampling(BME680_OS_2X);    // 2 samples for humidity oversampling
  bme.setPressureOversampling(BME680_OS_4X);    // 4 samples for pressure oversampling
  bme.setIIRFilterSize(BME680_FILTER_SIZE_1);   // Filter size for pressure & temperature, set to 0 for OFF

  // If you want to utilize the gas heater, a common setting is 320 C, 150 ms (320, 150)
  bme.setGasHeater(0, 0); // Gas heater settings: 0 C, 0 ms, DISABLED
  // *************** END OF BME680 CONFIGURATION ***************
  if(serialPrint)
    Serial.println(F("Setup complete!"));
}

void loop() {
  unsigned long currentTime = millis();
  bool bmeOk = bme.performReading();

  // Placeholder values for BME680
  float bme_temperature = NAN;
  float humidity        = NAN;
  float pressure        = NAN;

  if (!bmeOk) {
    if (serialPrint)
      Serial.println(F("**BME680 Read Failed**"));
    delay(10);
  } else {
    // Gather BME680 values
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

  // Now let's make a nice string to write to the file.
  // This is a comma-separated values (CSV) file, so we need to separate each value with a comma.
  String dataString = "";
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
  } 
  else {
    if (serialPrint) {
      Serial.print(F("Error2: Can't open "));
      Serial.println(dataFileName);
    }
  }
  if (serialPrint)
    Serial.println(dataString);

  unsigned long elapsed = millis() - currentTime;
  unsigned long delayTime = (1000 - (elapsed % 1000)) % 1000;
  delay(delayTime);
}