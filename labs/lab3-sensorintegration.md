---
layout: spec
latex: true
---

# Sensor Integration Code Manual

Code manual for `Lab3_SensorIntegration.ino`, published in the University of Michigan ENGR100-950 Electronics for Atmospheric and Space Measurements' public Arduino example library.

## Contents

- [Introduction](#introduction)
  - [Key Features](#key-features)
- [Code Breakdown](#code-breakdown)
  - [Global Configuration and Libraries](#global-configuration-and-libraries)
    - [Description](#description)
    - [Modifiable Components](#modifiable-components)
  - [Pin Assignments and Constants](#pin-assignments-and-constants)
    - [Description](#description-1)
    - [Modifiable Components](#modifiable-components-1)
  - [Setup Function](#setup-function)
    - [Description](#description-2)
    - [Modifiable Components](#modifiable-components-2)
  - [Loop Function](#loop-function)
    - [Description](#description-3)
    - [Modifiable Components](#modifiable-components-3)
- [Additional Tips](#additional-tips)

---

## Introduction

`Lab3_SensorIntegration.ino` is a comprehensive Arduino program designed for ENGR100-950. This code integrates both digital and analog sensors to gather environmental and motion data in real-time. The primary use case is for high-altitude weather balloon projects, where sensor accuracy, data redundancy, and proper integration are critical.

<div class="primer-spec-callout info" markdown="1">
In order to run this code, make sure you install the "Adafruit BME680 Library" by Adafruit in the Arduino IDE Library.
</div>

### Key Features:

- Digital BME680 Temperature, Pressure, Humidity, VOCs sensor (via Hardware SPI).
- Digital MicroSD Card Logger (via Hardware SPI).
- Analog ADXL335 Accelerometer.
- Analog TMP36 Temperature Sensor.

This manual provides a detailed breakdown of each code section, explaining its functionality, purpose, modifiable components, and usage examples. It also includes guidance on configuring placeholders (`?`) in the code with values specific for your setup.

<div class="primer-spec-callout danger" markdown="1">
**Important:** Ensure all `?` placeholders in the code are replaced with specific values relevant to your setup. These include pin numbers, calibration constants, and resistor values.
</div>

---

## Code Breakdown

### Global Configuration and Libraries

This section includes the necessary libraries, pin assignments, and initialization of key components. It ensures the program can interface with the sensors and peripherals.

```cpp
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

```

#### Description:

- **Libraries**: Includes SPI, SD, Adafruit_Sensor, and Adafruit BME680 libraries.


---

### Pin Assignments and Constants

```cpp
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

```

#### Description:
- **Chip Select (CS) Pins**: User-defined CS pins for the SD logger and BME680 on the shared hardware SPI bus.
- **Analog Pins**: User-defined analog pins for the voltage divider, TMP36, and ADXL335 accelerometer axes.
- **Constants**: Defines calibration values for analog sensors and voltage divider resistances in the form of slopes and intercepts (or Ohms for voltage dividers) to be used in the adjustment of voltages to real-world values.

#### Modifiable Components:

- **Pin Assignments**: User defined pin assignments for the battery voltage (voltage divider), TMP36, and ADXL335 Accelerometer.
- **Constants**: Defines calibration values for analog sensors and voltage divider resistances in the form of slopes and intercepts (or Ohms for voltage dividers) to be used in the adjustment of voltages to real-world values.

<div class="primer-spec-callout info" markdown="1">
To determine the values for `tmpSlope` and `tmpIntercept`, perform a linear calibration of the TMP36 sensor against known temperature references. Similarly, calibrate each axis of the accelerometer by recording output values for -1g and 1g.
</div>

---

### Setup Function

```cpp
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
```

#### Description

- Prepares the serial monitor for reporting values and sets the baud rate to 9600.
- Configures the microSD logger and opens the next iteration of a `datalog.csv` file to prepare for data logging.
- Writes a header for the csv file, and notifies the user of any issues with component initialization.
- Configures the BME680 for the specific needs of the user through oversampling and filter adjustments, and turning on/off IIR Filtering.

#### Modifiable Components:

- Change `setTemperatureOversampling`, `setHumidityOversampling`, and `setPressureOversampling` to suit your needs. For example:
  - `BME680_OS_1X`: Faster but less precise. Samples once and reports the value.
  - `BME680_OS_16X`: Slower but more precise. Samples 16 times and reports the average.
- Adjust `setGasHeater(temperature, duration)` if VOC measurements are needed. Temperature is in Celsius and duration is in milliseconds. If VOC measurements are not needed it is recommended to set this to `setGasHeater(0,0)` in order to prevent the heater from causing slight discrepencies in temperature values.
- Adjust the csv file's header for use with your specific components and application.

<div class="primer-spec-callout warning" markdown="1">
If the BME680 fails to initialize, double-check your wiring and power supply connections.
</div>

---

### Loop Function

```cpp
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
```

#### Description:

- Records starting time for the current iteration.
- Checks BME680 for temperature, humidity, and pressure, and returns error if reading fails.
- Stores values for the voltage divider, TMP36, and ADXL335 accelerometer based on user defined slope-intercept equations.
- Stores sensor values in a string, and if the microSD logger is cooperating writes that string to the csv file.
- Delays the program such that the next iteration occurs exactly one second after the previous one started.

#### Modifiable Components:

- Customize the delay time to adjust the sampling rate. For example, use `delay(500);` for ~2Hz sampling. Note that this is highly dependent upon the time it takes each sensor to perform a sample, so whatever delay is added here is in addition to the time it takes each sensor to report its values. The default shown here is used to delay the loop iteration such that each iteration is exactly 1 second apart.

---

### Additional Tips

- Test each sensor individually to confirm proper functionality before integrating them into the final setup.
- Review the Adafruit BME680 library documentation for advanced features and troubleshooting guidance.