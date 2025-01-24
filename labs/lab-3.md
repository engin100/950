---
layout: spec
latex: true
---

# Lab 3: Creating a Standalone Arduino and Adding Sensors

<div class="primer-spec-callout danger" markdown="1">
This is the first lab completed as a team! As such, the amount of work needed to complete it is slightly higher than previous labs. The completion of this lab will be made MUCH easier if you carefully read through this manual and complete it in steps.
</div>

## Contents 

- [Lab 3: Creating a Standalone Arduino and Adding Sensors](#lab-3-creating-a-standalone-arduino-and-adding-sensors)
  - [Contents](#contents)
  - [Introduction](#introduction)
    - [Arduino Power Requirements](#arduino-power-requirements)
    - [Data Logging](#data-logging)
  - [Procedure](#procedure)
    - [Materials](#materials)
    - [1. Powering the Arduino](#1-powering-the-arduino)
    - [2. Measuring Battery Voltage](#2-measuring-battery-voltage)
    - [3. Adding the Temperature Sensor](#3-adding-the-temperature-sensor)
    - [4. Adding the Accelerometer](#4-adding-the-accelerometer)
    - [5. Adding the BME680 Temperature, Pressure, Humidity, VOC Sensor](#5-adding-the-bme680-temperature-pressure-humidity-voc-sensor)
    - [6. Adding the MicroSD Card Adapter Module](#6-adding-the-microsd-card-adapter-module)
    - [7. Collecting Data](#7-collecting-data)
    - [8. Analyzing the Data in MATLAB](#8-analyzing-the-data-in-matlab)
  - [Submission](#submission)

## Introduction

So far, every time we have used our Arduino to log data, we have read the data through Arduino's Serial monitor, and have powered the Arduino via our computer's USB port. While this has worked so far, our end goal is to send these Arduinos on weather ballons! We cannot use a computer for power and data logging for that!

This lab can be broken down into two main sections, one in which we learn to power the board via a battery and estimate the battery's capacity or charge, and one where we record Arduino sensor data onto a microSD card. At the end of this lab, you should have all the knowledge you need to make a fully portable temperature, pressure, humidity, and acceleration logger.

### Arduino Power Requirements

The Arduino Nanos that we use in this class operate at 5V logic. This means the pins coming off of it, like the digital pins, are all at 5Vs. The Arduino, however, has circuitry inside it that lets it take a range of voltages as input. This is called the Vin pin, and takes a voltage between 7-12V. The Arduino then internally converts that down to a safer 5V level for its own operations. For this lab, we will be powering our Arduino Nano with a 9V battery.

### Data Logging

Our Arduino has some memory on it, but reading and writing to this memory is a rather complicated procedure, which is why we need the Arduino IDE to handle writing the code to the Arduino's memory for us. Writing variables to the Arduino's memory is not user-friendly and is difficult to read back. Therefore, we elect to instead use a microSD card, which has a far higher data capacity and allows us to easily read data on our computer. This lab will use a pre-built data logging module to write data to the microSD card in a similar way you write data out to the Arduino's Serial Monitor.

## Procedure

<div class="primer-spec-callout danger" markdown="1">
Due to the length of this lab, we are giving you the option to split into two groups within your team. This is not required, and if you would like to work all together, simply continue on with the lab manual. If you would like to pursue this option, split into two groups, and assign one group to be Group A, and one group to be Group B, then follow the links below to modified lab manuals.
</div>

- [Link to Group A Lab Manual](/labs/lab-3GroupA)
- [Link to Group B Lab Manual](/labs/lab-3GroupB)

### Materials

- [ ] 1 Arduino Nano
- [ ] 1 Breadboard
- [ ] 1 Programming Cable (and adapters if necessary)
- [ ] 1 TMP36 Temperature Sensor
- [ ] 1 BME680 Temperature, Pressure, Humidity, VOC Sensor
- [ ] 1 Accelerometer
- [ ] 1 MicroSD Card
- [ ] 1 Data Logger
- [ ] 1 MicroSD Card - USB Adapter
- [ ] 2 1k$$\Omega$$ resistors
- [ ] A handful of jumper wires
- [ ] 1 9V battery
- [ ] 1 9V battery connector
- [ ] A computer with the Arduino IDE [installed](/tutorials#arduino-ide-install) and [setup](/tutorials#arduino-library).
- [ ] ENGR100-950 Arduino Library

### 1. Powering the Arduino

To start, we want to power our Arduino with the 9V battery. Plug your Arduino into your breadboard, and plug the 9V into it's connection clip. It should only fit on one way, as the 9V's two terminals are different shapes.

Notice that one wire coming out of the battery is red, and one is black. Common practice says that red will be positive, in this case +9V, and the black will be what we connect to our Arduino's GND.

<div class="primer-spec-callout danger" markdown="1">
Oftentimes we will refer to "Common Practice", meaning the circuit will work if you don't follow this convention, but it may be harder to understand for an outsider, or in certain "edge cases" it might function differently than expected. A common practice we are requiring you to follow is color coding your jumper wires, as this makes debugging a complex circuit much easier. Additionally, please supply 5v to one red power rail on the breadboard, 3.3v to the other red rail, and GND the remaining two blue rails. Then you can connect any sensors to those rails without tracing wires over and over back to the Arduino pins.

- **Red (or orange):** Power lines(5v, 3.3v, etc.)
- **Black:** Ground
- **Blue:** Analog (Pins labeled with an A, and most likely used for analogRead or sensor data)
- **Yellow:** Digital (Pins labeled with a D, most likely used to control things or for more complicated sensors)
- **Left Red Rail:** 5v
- **Right Red Rail:** 3.3v
</div>

Take these wires and plug them into your Arduino via your breadboard. Red should go to the Arduino's Vin, and black should go to any GND pin.

Once you've plugged the 9V in, the Arduino should light up - even though it isn't plugged into your computer! If it does, congrats, your external power is working! If not, check your connections again.

As one last check that everything is working before we move on, upload the File → Examples → Basics → Blink code that the Arduino IDE comes with to your Arduino. After it finishes uploading, unplug your computer and verify that the onboard LED on the Arduino continues to blink on only the 9V's power.

<div class="primer-spec-callout info" markdown="1">
In the next lab we will go over creating a more reliable power source using a separate power circuit. For now, this will do, just take note that sensor readings may fluctuate based on whether the Arduino is powered by a battery or by your computer, and whether or not all of the sensors are plugged in and drawing power. More on this later!
</div>

### 2. Measuring Battery Voltage

Most modern electronics, from your smartphone to even rockets, have some way of reporting back the charge of any internal batteries. While we don't use the battery for very long at any one time in this lab, other people are using the same batteries, and so we do want to verify they are charged.

To measure battery voltage, we can use the analog pins on the Arduino, similar to how we did in lab 1. The caveat of this is, however, that the analog pins can **only take up to 5V!!** So, before reading the battery in, we need to build a voltage divider to step the battery voltage down to 5V max.

Using our voltage divider [(see the resources page for more)](/resources), we can take 2 1k$$\Omega$$ resistors and step 9V down to 4.5V max. Go ahead and build this voltage divider.

When you are done, your 9V battery should have the black wire going to GND, and the red wire going to **both** Vin on the Arduino **and** a voltage divider.

Now, let's test that the voltages look about right. Go to File → Examples → Basics → AnalogReadSerial and change the `analogRead()` function called in `loop()` to be the pin you plugged your voltage divider into. Run this code and make note of the values it returns.

You know on the Arduino Nano this value will be between 0-1024, and that your max voltage, as reported by the Arduino, is 5V. Convert your raw value to the voltage by dividing it by 1023 and multiplying it by 5V. This is the voltage your Arduino recorded.

Your battery, however, has a higher voltage than that. We now need to undo the effects of the voltage divider to determine the battery's original voltage. Since we used the same resistance on either side of the voltage divider, the voltage is being cut in half. Therefore, we can simply multiply the Arduino's recorded voltage by 2 to get the 9V battery's voltage. It should be somewhere between 8 and 10V.

<div class="primer-spec-callout info" markdown="1">
Note that the values displayed in the serial monitor are rounded, and don't show us as accurate of voltages as we would like. This is because the value is stored as an "int", or integer. To obtain decimal places, change this to a float, and when applying any calculations (such as converting from raw values to voltages) put .0 at the end to let the code know you are trying to obtain decimal values. Ex. "value * (10.0 / 1023.0);"
</div>

### 3. Adding the Temperature Sensor

<div class="primer-spec-callout danger" markdown="1">
Whenever you perform a calibration curve, or want to read accurate values to the SD card, you should do so with the battery connected and computer disconnected. Because of the differences in voltage applied by a computer through USB and the 9V batteries we are using, there is some variation in the voltage values read by the Arduino from each sensor. For this lab, since you don't have an SD logger connected (yet!) just calibrate using the serial monitor through USB. Keep this in mind for future labs though!
</div>

- [Link to TMP36 Spec Sheet](https://drive.google.com/file/d/10Lu2-s9MYqh0s0O6Nkxy8E_LDwDpnZ7T/view?usp=sharing)

Just like we did in the last lab, we now need to plug in the TMP36 to an analog pin on the Arduino, and read it using `analogRead()` and `Serial.println()`. Add this to the code used for measuring the battery voltage with comma-separated values. (Hint: You can use `Serial.print()` to print values without a newline character between them, which may help you print csv integers to the serial monitor for testing. Then you can just use `Serial.print(",");` to add a comma between the values. The last line you print, which will be the last sensor column of your csv matrix, should use `Serial.println()` in order to make a new line for the next data read). Convert these raw values to voltages using the equations used in previous labs, then print the voltages in the aforementioned format.

Here is the wiring diagram again for your reference:

[![TMP36 Pinout](https://cdn-learn.adafruit.com/assets/assets/000/000/471/large1024/temperature_tmp36pinout.gif?1447975787)](https://learn.adafruit.com/tmp36-temperature-sensor/overview)

<div class="primer-spec-callout warning" markdown="1">
This temperature sensor will be used to measure the external temperature of your payload. In the next step you'll add a digital sensor that measures temperature, pressure, humidity, and Volatile Organic Compounds (VOCs). This sensor will be used for the interior temperature of your payload.
</div>

Once you have your temperature sensor connected, it's time to make a calibration curve. You can do this in the same manner as in the last lab using the cold chamber or going outside. Enter these calibration curves into your Arduino code by modifying the temperature variables with a slope-intercept equation, and verify that the serial monitor is producing realistic temperature values. Save these calibration curves (slope and intercept values) somewhere for later use! **It may be less annoying to calibrate all of the sensors at the end once you have all the sensors connected but before you have the data logger plugged in. This is up to you! In whatever case, make sure to clearly record your slope and intercept values from the curves.**

### 4. Adding the Accelerometer

- [Link to ADXL335 Spec Sheet](https://drive.google.com/file/d/1nYnJopSdXv7brn2TT8iLgIH01D7TD_NQ/view?usp=sharing)

<div class="primer-spec-callout danger" markdown="1">
The accelerometer we are using connects to 3.3v ONLY. DO NOT CONNECT TO 5V.
</div>

Begin by skimming over the provided spec sheet and become familiar with the pin layout. Connect the sensor to the Arduino, based on the pin-out provided and using the **3.3V pin** as the power supply. Each of the axes (x, y, and z) will be connected to its own analog pin. You will not have anything connected to the ST pin.

Add code to the program you've been working with to read voltage values from each of the three axes. Then perform a two-point calibration for each axis individually, and update the code to print the new calibrated values in the same comma-delimited format as before. **Save these calibration curves (slope and intercept values)! Take a screenshot of the serial monitor printing out a string of data from all of the sensors in the same line, every half second (or whatever the time delay is set to within the code).**

<div class="primer-spec-callout info" markdown="1">
To perform a calibration curve of the accelerometer, take note of the axes as labeled on the top of the sensor. Holding the sensor so that only one axis is experiencing acceleration due to gravity, record the output value as -1g (g being acceleration due to gravity). Then flip it over 180 degrees so that it is experiencing 1g, and record this value as your second point. Apply these calibration curves to the code from before in csv format.
</div>

### 5. Adding the BME680 Temperature, Pressure, Humidity, VOC Sensor

<div class="primer-spec-callout info" markdown="1">
BME680 is the name of a specific sensor/component, produced by Bosch, that can measure temperature, pressure, humidity, and VOCs. In order to make the use of a BME680 much simpler, companies like Adafruit produce a BME680 breakout board. These are custom PCBs (Printed Circuit Boards) with the BME680 sensor attached, along with a slew of other power-handling or signal processing components. Linked below are the spec sheets for both variations. The sensor spec sheet is likely more useful for finding the operating ranges of the sensor, sensitivity levels, and other sensor operating details. The breakout spec sheet is likely more useful for finding wiring instructions and/or example code. The breakout spec sheet also lists the required input power range since this is determined by the circuitry of the breakout board.
</div>

- [Link to BME680 Adafruit breakout Spec Sheet](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas.pdf)
- [Link to BME680 sensor Spec Sheet](https://cdn-shop.adafruit.com/product-files/3660/BME680.pdf)

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

Navigate to and open the following example file: File -> Examples -> ENGR100-950 -> Lab3_SensorIntegration.

Read through the code carefully and modify all of the "?" to have accurate values relavent to your setup. This includes slope and intercept values from calibration curves, and pin numbering for your specific wiring. Run this code and ensure it's working as expected.

### 6. Adding the MicroSD Card Adapter Module

<div class="primer-spec-callout info" markdown="1">
For teams working in two separate groups (all others ignore this message): You should already have your SD logger wired in, so once you have all of your components running on one Arduino/computer, skip down to "Plug your microSD card into your computer..."
</div>

Unlike the other sensors and modules we have used so far, the MicroSD module we are using uses the Arduino's digital pins. Luckily for us, there are libraries (that you should have installed when following the tutorial and initially setting up your Arduino IDE), that handle all the complicated digital interfacing for us. All we need to know is which pins to plug the adapter module into.

![MicroSD Adapter Module Wiring](../media/SD-Card-Wiring.png){: .invert-colors-in-dark-mode }

While your Arduino is powered off and disconnected from the 9V, plug your module in as shown above. The Arduino pins for this **DO** matter and cannot easily be changed, unlike the analog pins.

Plug your microSD card into your computer and ensure that it is empty. If there are files on the card, delete them and empty the trash. You should always clear the card, empty the trash while the card is still inserted, and properly eject it before removing the card from your computer.

Once everything is wired up, put your microSD card into the adapter module and plug in your Arduino. At this point you should modify and upload the code found in File → Examples → ENGR100-950 → Lab3-SD.

Please read through the comments of this code file, as you will be adding additional sensors and modifying this file on your own. In this lab, you may also need to change the analog pins that are the defaults for all of your sensors.

There is a delay statement at the end of the loop.  Think about how many data points will be taken if you take data for 5 minutes.  Will you need data this often?  More often?  Less often?  Adjust the delay accordingly.

**Now that you have a completed circuit, take a picture of your setup and save this for your submission file. (Remember, wires and rails should follow "common practice" mentioned earlier.)**

### 7. Collecting Data

With everything plugged into the 9V and running, unplug the Arduino from your computer. Enjoy the portability of your new breadboard and walk around the building a little bit. Get the temperature to change dramatically by putting your sensor board into the cold chamber.  Wait for about 1-2 minutes to allow the temperature to adjust. Try rotating your circuit in different orientations so that each axis experiences some acceleration due to gravity, and walk outside to watch humidity change. This should provide plenty of data for all of your sensors!

Go back to the lab and unplug the 9V now (unplug the battery and leave the wires connected to your board). Carefully remove the microSD from the adapter module, and plug it into your computer. You should see a `DATALOG.CSV` file. If you do not, or the file seems corrupted or very small, delete the file, plug the microSD card back in, and watch what the Serial monitor on your computer says while running the code.

Once you have a sufficiently long test (2-3 minutes) and can see that there are clear changes in the data in the file created, you are done with the hardware portion of this lab!

Before returning all of your equipment, make sure you save your file on your computer!! Maybe even upload it and share it with team members so you have a backup!

Then, delete the .csv file and any other .txt files off of the microSD card (you can leave any folders) so that other teams in future labs have to actually do the lab themselves, and don't just steal your data!

### 8. Analyzing the Data in MATLAB

You should have a MATLAB script saved from an in-class exercise. Use this MATLAB script to process and analyze the data you collected earlier in the lab. You should create plots for battery voltage, two temperature sensors, a humidity sensor, a pressure sensor, and each axis from the accelerometer. These plots should be titled, axes labeled, and calibration curves applied so that they contain the proper units. Make sure to use legends if you have more than one line on a single graph (such as if you put the temperature sensors together). Again, to reiterate, your CSV file (from the code provided to you) will have voltages and your MATLAB script will apply the calibration curves to make the data useful. Consider using subplots to organize the data better!

<div class="primer-spec-callout warning" markdown="1">
Make sure you follow "common practice" Tech Comm rules, labelling all plots' axes and titles, and add legends where necessary.
</div>

## Submission

On Canvas, you will submit ***ONE PDF*** that will include all of the following:

- [ ] A picture of your complete circuit with proper color conventions.
- [ ] A screenshot of your serial **monitor** once all sensors are printing values in the same line (you may unplug the Arduino so the data pauses).
- [ ] Exported images of the finished plots from MATLAB (with labels and calibrations!).
- [ ] Screenshot of a schematic created in Altium of your entire completed circuit.

To put said content into a PDF, it is suggested you create a new Google Doc ([docs.new](https://docs.new)) and paste your images and write any text in the document. Export/Download this document as a PDF and upload it. **DO NOT SUBMIT A GOOGLE DOC FILE OR SPREADSHEET FILES.**

<div class="primer-spec-callout danger" markdown="1">
Submitting anything other than a single PDF may result in your work not being graded or your scores being heavily delayed.
</div>
