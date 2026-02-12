/*
  Sensor Integration GPS

  Written by: Benjamen Miller & Ismael Enriquez, University of Michigan
  Included in UMICH ENGR 100.950 "Electronics for Atmospheric and Space Measurements" Public Library

  This code integrates the following components:
  Digital BME680 Temperature, Pressure, Humidity, VOCs sensor (Hardware SPI)
  Digital MicroSD Card Logger (Hardware SPI)
  Analog ADXL335 Accelerometer
  Analog TMP36 Temperature Sensor
  Digital Adafruit Ultimate GPS Breakout

  Code includes commands for Hardware SPI and analog communications.
  Take note of the values in the section "BME680 Configuration" for data filtering and oversampling

  These are the pins your MicroSD Card Adapter and BME680 will be connected to.
  These pins are specific and should not change. You do not need to worry
  about why these are the pins, just connect them as listed.
  MOSI - pin 11
  MISO - pin 12
  CLK  - pin 13
*/

#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <SoftwareSerial.h>
SoftwareSerial gps(2, 3); // RX, TX

bool isVerbose = true;

const int nChars = 500;
char gps_string[nChars];

void clear_gps_string() {
  for (int i = 0; i < nChars ; i++) gps_string[i] = '\0';
}

void read_gps() {

  char t;

  // If we arrive in the middle of a gps_available
  // wait for that to go away:
  while (gps.available()) {
    t = gps.read(); // do nothing
    delay(1);
  }

  // ok, now wait until the gps is available again:
  while (!gps.available()) {
    delay(1); // do nothing
  }

  // now read in the GPS data:
  int iChar = 0;
  while (gps.available()) {
    gps_string[iChar] = gps.read();
    iChar++;
    delay(1);
  }

}

// ************************************************** NEEDS EDITING **************************************************
// This is the CS pin that the SD Logger is connected to
const int SDLoggerChipSelect = ??;

// This is the CS pin that the BME680 is connected to
const int BMEchipSelect = ??;

// These are the pins your accelerometer lines are connected to
const int xAccelPin = ??;
const int yAccelPin = ??;
const int zAccelPin = ??;

// This is the pin your TMP36 is connected to 
const int tmpPin = ??;

// This is the pin your voltage divider is connected to
const int vDivPin = ??;

// Ohms, R1 = sum of all resistances between Vin and Vout
const float R1 = ??;

// Ohms, R2 = sum of all resistances between Vout and GND
const float R2 = ??;

// ***** Enable the following boolean to print raw voltages to the serial monitor for calibration of analog sensors *****
bool calibration_setup      = ??; // True for calibration mode (slope = 1, intercept = 0), false for normal operation

// Note that you still need to fill in the slope and intercept values below to prevent an error from the question marks, this
// just overrides those values for calibrating so you don't have to switch all of the pin declarations values back and forth.

float tmpSlope              = ??; // Slope for TMP36 calibration curve
float tmpIntercept          = ??; // Intercept for TMP36 calibration curve

float xAccelSlope           = ??; // Slope for x-axis accelerometer calibration curve
float xAccelIntercept       = ??; // Intercept for x-axis accelerometer calibration curve
float yAccelSlope           = ??; // Slope for y-axis accelerometer calibration curve
float yAccelIntercept       = ??; // Intercept for y-axis accelerometer calibration curve
float zAccelSlope           = ??; // Slope for z-axis accelerometer calibration curve
float zAccelIntercept       = ??; // Intercept for z-axis accelerometer calibration curve

bool SerialPrint            = ??; // True to print, false for no serial monitor (defaults to true in calibration mode)
// ************************************************** END EDITING **************************************************

// Filename placeholder
char dataFileName[16];

// BME680 object constructor
Adafruit_BME680 bme(BMEchipSelect, &SPI);
void setup() {
  Serial.begin(9600);
    if (calibration_setup) {
      // Calibration mode
      SerialPrint = true;
      tmpSlope        = 1.0;
      tmpIntercept    = 0.0;
      
      xAccelSlope     = 1.0;
      xAccelIntercept = 0.0;
      yAccelSlope     = 1.0;
      yAccelIntercept = 0.0;
      zAccelSlope     = 1.0;
      zAccelIntercept = 0.0;

      if (SerialPrint) {
        Serial.println(F("Calibration mode enabled."));
      }
  } else {
      if (SerialPrint) {
        Serial.println(F("Calibration mode disabled."));
      }
  }

  if (SerialPrint) {
    if (isVerbose) {
      Serial.println(F("Serial communication initialized."));
    }
  }


  // --- Initialize SD Card on hardware SPI ---
  pinMode(SDLoggerChipSelect, OUTPUT);
  if (!SD.begin(SDLoggerChipSelect)) {
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
    dataFile.println("Time (ms),Voltage (V),TMP36 (C),BME Temp (C),Pressure (Pa),Humidity (%),xAccel (g),yAccel (g),zAccel(g)");
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

  gps.begin(9600);
  // set the gps port to listen:
  gps.listen();
  if (isVerbose) Serial.println("GPS is initialized!");  

  if (SerialPrint) {
    Serial.println(F("Setup complete."));
  }
}

void loop() {
  auto currentTime = millis();
  bool bmeOk = bme.performReading();
  clear_gps_string();
  read_gps();

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
    dataFile.println(gps_string);
    dataFile.close();
  } else {
    if (SerialPrint) {
      Serial.print(F("Error2: Can't open "));
      Serial.println(dataFileName);
    }
  }

  // Print string to serial monitor
  if (SerialPrint) {
    if (isVerbose) Serial.println(gps_string);
    Serial.println(dataString);
  }

  unsigned long elapsed = millis() - currentTime;
  unsigned long delayTime = (1000 - (elapsed % 1000)) % 1000;
  delay(delayTime);
}
