---
layout: spec
latex: true
---

# Lab 3: Group B Portion

Adding the temperature sensor, BME680 4-in-1 sensor, and accelerometer.

<div class="primer-spec-callout danger" markdown="1">
Oftentimes we will refer to "Common Practice", meaning the circuit will work if you don't follow this convention, but it may be harder to understand for an outsider, or in certain "edge cases" it might function differently than expected. A common practice we are requiring you to follow is color coding your jumper wires, as this makes debugging a complex circuit much easier. Additionally, please supply 5v to one red power rail on the breadboard, 3.3v to the other red rail, and GND the remaining two blue rails. Then you can connect any sensors to those rails without tracing wires over and over back to the Arduino pins.

- **Red (or orange):** Power lines (5v, 3.3v, etc.)
- **Black:** Ground
- **Blue:** Analog (Pins labeled with an A, and most likely used with analogRead or sensor data)
- **Yellow:** Digital (Pins labeled with a D, most likely used to control things or with more complicated sensors)
- **Left Red Rail:** 5v
- **Right Red Rail:** 3.3v
</div>

## Contents 

- [Lab 3: Group B Portion](#lab-3-group-b-portion)
  - [Contents](#contents)
  - [Materials](#materials)
  - [Procedure](#procedure)
    - [1. Adding the Temperature Sensor](#1-adding-the-temperature-sensor)
    - [2. Adding the Accelerometer](#2-adding-the-accelerometer)
    - [3. Adding the BME680 Temperature, Pressure, Humidity, VOC Sensor](#3-adding-the-bme680-temperature-pressure-humidity-voc-sensor)

## Materials

- [ ] 1 Arduino Nano
- [ ] 1 Breadboard
- [ ] 1 Programming Cable (and adapters if necessary)
- [ ] 1 TMP36 Temperature Sensors
- [ ] 1 BME680 Temperature, Pressure, Humidity, VOC Sensor
- [ ] 1 Accelerometer
- [ ] A handful of jumper wires
- [ ] A computer with the Arduino IDE [installed](/tutorials#arduino-ide-install) and [setup](/tutorials#arduino-library).
- [ ] ENGR100-950 Arduino Library

## Procedure

### 1. Adding the Temperature Sensor

<div class="primer-spec-callout danger" markdown="1">
Whenever you perform a calibration curve, or want to read accurate values to the SD card, you should do so with the battery connected and computer disconnected. Because of the differences in voltage applied by a computer through USB and the 9V batteries we are using, there is some variation in the voltage values read by the Arduino from each sensor. For this lab, since you don't have an SD logger connected (yet!) just calibrate using the serial monitor through USB. Keep this in mind for future labs though!
</div>

- [Link to TMP36 Spec Sheet](https://drive.google.com/file/d/10Lu2-s9MYqh0s0O6Nkxy8E_LDwDpnZ7T/view?usp=sharing)

Just like we did in the last lab, we now need to plug in the TMP36 to an analog pin on the Arduino, and read it using `analogRead()` and `Serial.println()`.

Here is the wiring diagram again for your reference:

[![TMP36 Pinout](https://cdn-learn.adafruit.com/assets/assets/000/000/471/large1024/temperature_tmp36pinout.gif?1447975787)](https://learn.adafruit.com/tmp36-temperature-sensor/overview)

Go to File → Examples → Basics → AnalogReadSerial and change the `analogRead()` function called in `loop()` to be the pin you plugged your TMP36 into. You know on the Arduino Nano this value will be between 0-1023, and that your max voltage, as reported by the Arduino, is 5V. Convert your raw value to the voltage outputted by the TMP36 by dividing it by 1023 and multiplying it by 5V. This is the voltage your Arduino recorded.

<div class="primer-spec-callout info" markdown="1">
Note that the values displayed in the serial monitor are rounded, and don't always show us as accurate of voltages as we would like. This is because the value is stored as an "int", or integer. To obtain decimal places, change this to a float, and when applying any calculations (such as converting from raw values to voltages) put .0 at the end to let the code know you are trying to obtain decimal values. Ex. "float voltage = rawValue * (10.0 / 1023.0);"
</div>

Once you have your temperature sensor connected, it's time to make a calibration curve. You can do this in the same manner as in the last lab using the cold chamber or going outside. Enter these calibration curves into your Arduino code by modifying the temperature variables with a slope-intercept equation, and verify that the serial monitor is producing realistic temperature values. Save these calibration curves (slope and intercept values) somewhere for later use! **It may be less annoying to calibrate all of the sensors at the end once you have all the sensors connected but before you have the data logger plugged in. This is up to you! In whatever case, make sure to clearly record your slope and intercept values from the curves.**

<div class="primer-spec-callout warning" markdown="1">
This temperature sensor will be used to measure the external temperature of your payload. In a later step you'll add a digital sensor that measures temperature, pressure, humidity, and Volatile Organic Compounds (VOCs). That sensor will be used for the interior temperature of your payload.
</div>

### 2. Adding the Accelerometer

- [Link to ADXL335 Spec Sheet](https://drive.google.com/file/d/1nYnJopSdXv7brn2TT8iLgIH01D7TD_NQ/view?usp=sharing)

<div class="primer-spec-callout danger" markdown="1">
The accelerometer we are using connects to 3.3v ONLY. DO NOT CONNECT TO 5V.
</div>

Begin by skimming over the provided spec sheet and become familiar with the pin layout. Connect the sensor to the Arduino, based on the pin-out provided and using the **3.3V pin** as the power supply. Each of the axes (x, y, and z) will be connected to its own analog pin. You will not have anything connected to the ST pin.

Add code to the file used for measuring the TMP36 to store the data with comma-separated values. (Hint: You can use `Serial.print()` to print values without a newline character between them, which may help you print csv integers to the serial monitor for testing. Then you can just use `Serial.print(",");` to add a comma between the values. The last line you print, which will be the last sensor column of your csv matrix, should use `Serial.println()` in order to make a new line for the next data sample). Convert these raw values to voltages using the equations used in previous labs, then print the sensor voltages in the aforementioned format. You'll need to add code for each of the three axes.

Perform a two-point calibration for each axis individually, and update the code to print the new calibrated values in the same comma-delimited format as before. **Save these calibration curves (slope and intercept values)!**

<div class="primer-spec-callout info" markdown="1">
To perform a calibration curve of the accelerometer, take note of the axes as labeled on the top of the sensor. Holding the sensor so that only one axis is experiencing acceleration due to gravity, record the output value as -1g (g being acceleration due to gravity). Then flip it over 180 degrees so that it is experiencing 1g, and record this value as your second point. Apply these calibration curves to the code from before in csv format.
</div>

### 3. Adding the BME680 Temperature, Pressure, Humidity, VOC Sensor

<div class="primer-spec-callout info" markdown="1">
BME680 is the name of a specific sensor/component, produced by Bosch, that can measure temperature, pressure, humidity, and VOCs. In order to make the use of a BME680 much simpler, companies like Adafruit produce a BME680 breakout board. These are custom PCBs (Printed Circuit Boards) with the BME680 sensor attached, along with a slew of other power-handling or signal processing components. Linked below are the spec sheets for both variations. The sensor spec sheet is likely more useful for finding the operating ranges of the sensor, sensitivity levels, and other sensor operating details. The breakout spec sheet is likely more useful for finding wiring instructions and/or example code. The breakout spec sheet also lists the required input power range since this is determined by the circuitry of the breakout board.
</div>

- [Link to BME680 Adafruit Breakout Spec Sheet](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas.pdf)
- [Link to BME680 Sensor Spec Sheet](https://cdn-shop.adafruit.com/product-files/3660/BME680.pdf)

<div class="primer-spec-callout info" markdown="1">
Pay attention to the required supply voltage for each of these components to prevent accidental damage. You can find these values in the provided spec sheets for each individual component. In the case of the BME680 Adafruit Breakout, it can handle 3.3v or 5v. For the case of this lab we will be using 5v.
</div>

Begin by skimming over the provided spec sheets and become familiar with the pin layout. Connect the sensor to the Arduino, based on the pin-out provided below.

| BME680 Adafruit Breakout Pin | Arduino Nano Pin  |
| ---------- | -------- |
| Vin (Voltage In) | 5 volt rail |
| 3Vo (3v Out) | NOT USED |
| GND (Ground) | Ground rail |
| SCK (Serial Clock) | D6 |
| SDO (Serial Data Out, aka MISO) | D7 |
| SDI (Serial Data In, aka MOSI) | D8 |
| CS (Chip Select) | D9 |

Navigate to and open the following example file: File -> Examples -> ENGR100-950 -> Lab3_BME680. This file is a standalone BME680 tester to ensure you have everything in working order before proceeding.

Check all of the outputs and ensure they are plausible before proceeding. If they seem extraordinarily different from expected values, ask an instructor for help.

<div class="primer-spec-callout warning" markdown="1">
When Group A is ready to move on, take both of your breadboards and move all the jumpers running from your Arduino into the same pins on their Arduino, so that everything is wired into one microcontroller (you need not physically move the components, but rather just their jumpers, leaving two breadboards side by side. They can lock together!). Connecting these breadboards is best done by moving ONLY the analog/digital jumpers from Group B's Arduino to Group A's Arduino, and then connecting a jumper from the 5V rail of Group A to the 5V rail of Group B (do this for the 3.3V rail and the GND rails as well). As one last final check, Group B's original Arduino should have nothing plugged into it, so you can remove any jumpers remaining for power or GND. Once this is done, follow the link below to jump back into the normal lab manual together.
</div>

- [Groups A & B Lab Manual - Finishing Steps](/labs/lab-3#6-adding-the-microsd-card-adapter-module)