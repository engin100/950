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

### Key Features:

- Digital BME680 Temperature, Pressure, Humidity, and VOC Sensor (via Software SPI).
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
#include <SPI.h>
#include <SD.h>
#include <Adafruit_BME680.h>

#define BME_SCK   6
#define BME_MISO  7
#define BME_MOSI  8
#define BME_CS    9
#define SD_CS     10

Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
```

#### Description:

- **Libraries**: Includes SPI, SD, and Adafruit BME680 libraries.
- **Software SPI Pins**: Defines custom SPI pins for the BME680 sensor.
- **Hardware SPI Pins**: Uses the standard hardware SPI pins for the SD card.

#### Modifiable Components:

- Replace `#define` values for pins with those specific to your wiring configuration. For use with an Arduino Nano in conjunction with the microSD logger, it is recommended to use these default pins.

---

### Pin Assignments and Constants

```cpp
const int vDivPin           = A?; // Voltage divider pin
const int tmpPin            = A?; // TMP36 pin
const int xAccelPin         = A?; // x-axis accelerometer pin
const int yAccelPin         = A?; // y-axis accelerometer pin
const int zAccelPin         = A?; // z-axis accelerometer pin

const float R1              = ???; // Ohms, resistance between Vin and Vout
const float R2              = ???; // Ohms, resistance between Vout and GND

const float tmpSlope        = ?;   // TMP36 slope (from calibration curve)
const float tmpIntercept    = ?;   // TMP36 intercept (from calibration curve)

const float xAccelSlope     = ?;   // X-axis accelerometer slope
const float xAccelIntercept = ?;   // X-axis accelerometer intercept
const float yAccelSlope     = ?;   // Y-axis accelerometer slope
const float yAccelIntercept = ?;   // Y-axis accelerometer intercept
const float zAccelSlope     = ?;   // Z-axis accelerometer slope
const float zAccelIntercept = ?;   // Z-axis accelerometer intercept

bool SerialPrint            = ???; // Set to true for serial monitor output, false to disable
```

#### Description:

- Takes in user defined values for use with slope-intercept calibrations and pin declarations.

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
  if (SerialPrint) {
    Serial.begin(9600);
    while (!Serial) {}
  }

  pinMode(SD_CS, OUTPUT);
  if (!SD.begin(SD_CS)) {
    if (SerialPrint) {
      Serial.println(F("SD initialization failed!"));
    }
    while (true) {}
  }

  int fileIndex = 1;
  while (true) {
    snprintf(dataFileName, sizeof(dataFileName), "datalog%d.csv", fileIndex);
    if (!SD.exists(dataFileName)) {
      break;
    }
    fileIndex++;
  }

  File dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(F("Time (ms),Voltage (V),TMP36 (C),BME Temp (C),Pressure (Pa),Humidity (%),xAccel (g),yAccel (g),zAccel(g)"));
    dataFile.close();
  }

  if (!bme.begin()) {
    if (SerialPrint) {
      Serial.println(F("BME680 initialization failed!"));
    }
    while (true) {}
  }

  bme.setTemperatureOversampling(BME680_OS_2X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_1);
  bme.setGasHeater(0, 0);
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

  File dataFile = SD.open(dataFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }

  if (SerialPrint) {
    Serial.println(dataString);
  }

  unsigned long elapsed = millis() - currentTime;
  unsigned long delayTime = 1000 - elapsed % 1000;
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