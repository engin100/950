---
layout: spec
latex: true
---

# Lab 3: Group B Portion

Adding the BME680 4-in-1 sensor, temperature sensor, and accelerometer.

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
  - [1. Adding the BME680 Temperature, Pressure, Humidity, VOC Sensor](#1-adding-the-bme680-temperature-pressure-humidity-voc-sensor)
  - [2. Adding the TMP36](#2-adding-the-tmp36)
  - [3. Adding the Accelerometer](#3-adding-the-accelerometer)
  - [4. Calibrating the Accelerometer](#4-calibrating-the-accelerometer)

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

### 1. Adding the BME680 Temperature, Pressure, Humidity, VOC Sensor

<div class="primer-spec-callout info" markdown="1">
BME680 is the name of a specific sensor/component, produced by Bosch, that can measure temperature, pressure, humidity, and VOCs. In order to make the use of a BME680 much simpler, companies like Adafruit produce a BME680 breakout board. These are custom PCBs (Printed Circuit Boards) with the BME680 sensor attached, along with a slew of other power-handling or signal processing components. Linked below are the spec sheets for both variations. The sensor spec sheet is likely more useful for finding the operating ranges of the sensor, sensitivity levels, and other sensor operating details. The breakout spec sheet is likely more useful for finding wiring instructions and/or example code. The breakout spec sheet also lists the required input power range since this is determined by the circuitry of the breakout board.
</div>

- [Link to BME680 Adafruit Breakout Spec Sheet](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas.pdf)
- [Link to BME680 Sensor Spec Sheet](https://cdn-shop.adafruit.com/product-files/3660/BME680.pdf)

<div class="primer-spec-callout info" markdown="1">
Pay attention to the required supply voltage for each of these components to prevent accidental damage. You can find these values in the provided spec sheets for each individual component. In the case of the BME680 Adafruit Breakout, it can handle 3.3v or 5v. For the case of this lab we will be using 5v.
</div>

In Lab 2, you wired up the BME680. If you do not remember how to wire it up, open up the breakout spec sheet and look at the section tittled **SPI Wiring**.

To make sure that the BME680 is working you can again use the BME680_Example_Code by navigating to `File → Examples → ENGR100-950 → BME680_Example_Code`. Check all of the outputs and ensure they are plausible before proceeding. If they seem extraordinarily different from expected values, ask an instructor for help.

### 2. Adding the TMP36

<div class="primer-spec-callout danger" markdown="1">
Whenever you perform a calibration curve, or want to read accurate values to the SD card, you should do so with the battery connected and computer disconnected. Because of the differences in voltage applied by a computer through USB and the 9V batteries we are using, there is some variation in the voltage values read by the Arduino from each sensor. For this lab, since you don't have an SD logger connected (yet!) just calibrate using the serial monitor through USB. Keep this in mind for future labs though!
</div>

- [Link to TMP36 Spec Sheet](https://drive.google.com/file/d/10Lu2-s9MYqh0s0O6Nkxy8E_LDwDpnZ7T/view?usp=sharing)

Just like we did in the last lab, we now need to plug in the TMP36 to an analog pin on the Arduino, and read it using `analogRead()` and `Serial.println()`.

Here is the wiring diagram again for your reference:

[![TMP36 Pinout](https://cdn-learn.adafruit.com/assets/assets/000/000/471/large1024/temperature_tmp36pinout.gif?1447975787)](https://learn.adafruit.com/tmp36-temperature-sensor/overview)

Go to `File → Examples → Basics → AnalogReadSerial` and change the `analogRead()` function called in `loop()` to be the pin you plugged your TMP36 into. You know on the Arduino Nano this value will be between 0-1023, and that your max voltage, as reported by the Arduino, is 5V. Convert your raw value to the voltage outputted by the TMP36 by dividing it by 1023 and multiplying it by 5V. This is the voltage your Arduino recorded.

<div class="primer-spec-callout info" markdown="1">
Note that the values displayed in the serial monitor are rounded, and don't always show us as accurate of voltages as we would like. This is because the value is stored as an "int", or integer. To obtain decimal places, change this to a float, and when applying any calculations (such as converting from raw values to voltages) put .0 at the end to let the code know you are trying to obtain decimal values. Ex. "float voltage = rawValue * (10.0 / 1023.0);"
</div>

Once you have your TMP36 connected, it's time to make a calibration curve. You can do this in the same manner as in the last lab using the cold chamber or going outside. Enter these calibration curves into your Arduino code by modifying the temperature variables with a slope-intercept equation, and verify that the serial monitor is producing realistic temperature values. Save these calibration curves (slope and intercept values) somewhere for later use! **It may be less annoying to calibrate all of the sensors at the end once you have all the sensors connected but before you have the data logger plugged in. This is up to you! In whatever case, make sure to clearly record your slope and intercept values from the curves.**

<div class="primer-spec-callout danger" markdown="1">
Make sure to recalibrate your TMP36 as it is likely you did not get the same TMP36 as you did in lab 2, meaning that the calibration curve that you created will not work for this TMP36.
</div>

### 3. Adding the Accelerometer

- [Link to ADXL335 Spec Sheet](https://drive.google.com/file/d/1nYnJopSdXv7brn2TT8iLgIH01D7TD_NQ/view?usp=sharing)

<div class="primer-spec-callout danger" markdown="1">
The accelerometer we are using connects to 3.3v ONLY. **DO NOT CONNECT TO 5V.**
</div>

Begin by skimming over the provided spec sheet and become familiar with the pin layout. Connect the sensor to the Arduino, based on the pin-out provided and using the **3.3V pin** as the power supply. Each of the axes (x, y, and z) will be connected to its own analog pin. You will not have anything connected to the ST pin.

Add code to the file used for measuring the TMP36 to store the voltage values from each of the three axes in comma-separated values (CSV) format. 

(Hint: You can use `Serial.print()` to print values without a newline character between them, which may help you print CSV integers to the serial monitor for testing. Then you can just use `Serial.print(",");` to add a comma between the values. The last line you print, which will be the last sensor column of your CSV matrix, should use `Serial.println()` in order to make a new line for the next data sample). Convert these raw values to voltages using the equations used in previous labs, then print the voltages in the aforementioned format.

```cpp
// The "|" represents where you are after printing to the serial monitor
Serial.print("firstVal");
//firstVal|

Serial.print(",");
//firstVal,|

Serial.println("secondVal");
//firstVal,secondVal
//|

Serial.print("I am in a new line because of println");  
//firstVal,secondVal
//I am in a new line because of println|
```

### 4. Calibrating The Accelerometer

To calibrate your accelerometer, you will have to go through the same procedure that you did in lab 2, for all 3 axes of the accelerometer. This means that for each axis, you will need at least 2 known values of acceleration that you can subject the sensor to while reading the voltage.

In order to find 2 known values of acceleration, we must understand what exactly is it that the accelerometer measures. The name "accelerometer" is kind of misleading in this case, since it doesn't actually measure total acceleration. Internally, the sensor has a tiny object (usually silicon) that is connected to the rest of the sensor via a spring-like connection. This connection has electrical properties that change based on the tension that the connection experiences. This is a simplified explanation, but the actual sensors don't differ too much. 

If a force is applied to the outside of the sensor, the tension in the connection increases to keep the small internal object accelerating at the same rate as the sensor. This means that the sensor can only detect acceleration from forces that are applied **only** to the outside of the package, since if a force was applied equally to the internal object, the tension in the connection would not have to increase to keep the object accelerating with the rest of the sensor. Usually this isn't a problem, since most forces we're concerned with are fall into this category, however, there is one major force that doesn't: **gravity**. Recall from physics that gravity acts in a way that makes all objects accelerate at the same rate ($$9.8\,\frac{m}{s^2}$$). This is the exact type of force that accelerometers cannot measure, since the internal connection does not have to apply any force to the internal object to keep it accelerating with the sensor - in the absence of external forces, everything accelerates at $$9.8\,\frac{m}{s^2}$$.

Now let's try to figure out what the accelerometer would measure in 2 different situations: in free-fall, and sitting stationary on a lab table. Start by drawing a free-body diagram for each situation, and then remove the gravitational force. The acceleration from the remaining forces is what the sensor would measure. In the situation of free-fall, since gravity is the only force (in the absence of air resistance), the accelerometer measures nothing. In the situation of the sensor sitting stationary, the normal force opposes gravity and is exactly equal to the force from gravity. The accelerometer will only measure the acceleration from the normal force, and since the normal force is equal to gravity in this case, it will measure $$9.8\,\frac{m}{s^2}$$, or 1 G, upwards. You will use this fact to calibrate the accelerometer.

<div class="primer-spec-callout info" markdown="1">
Reminder to pay attention to the 3-axis figure printed on the sensor module. When the sensor is flat on the table, the Z-axis should be vertical, and the others will be parallel to the table/ground.
</div>

In this orientation, the Z-axis is straight up, and from our previous findings it should measure 1G. X and Y are both perpendicular to the force of gravity and would be recording 0Gs. If you turn your board upside down, the Z axis should read -1G. Rotate your sensor around as needed so that each axis has at least two data-points where it is (anti-)parallel to the force of gravity and make sure to take note of the voltage value for both points.

With this calibration process completed, each axis will have a calibration value of 1G and -1G. Record the voltage values in your spreadsheet, and calculate the calibration curve for each axis.

Now update the code to print the new calibrated values in the same CSV format as before. **Save these calibration curves (slope and intercept values)!**

<div class="primer-spec-callout warning" markdown="1">
When Group A is ready to move on, take both of your breadboards and move all the jumpers running from your Arduino into the same pins on their Arduino, so that everything is wired into one microcontroller (you need not physically move the components, but rather just their jumpers, leaving two breadboards side by side. They can lock together!). Connecting these breadboards is best done by moving ONLY the analog/digital jumpers from Group B's Arduino to Group A's Arduino, and then connecting a jumper from the 5V rail of Group A to the 5V rail of Group B (do this for the 3.3V rail and the GND rails as well). Note that the numbering of the analog pins does NOT matter, but the digital pins MUST go into the same numbered ordered as before. As one last final check, Group B's original Arduino should have nothing plugged into it, so you can remove any jumpers remaining connecting it to power or GND. Once this is done, follow the link below to jump back into the normal lab manual together.
</div>

- [Groups A & B Lab Manual - Finishing Steps](/labs/lab-3#6-adding-the-microsd-card-adapter-module)