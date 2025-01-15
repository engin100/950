---
layout: spec
latex: true
---

# Resources

A collection of useful cheat-sheets and diagrams you may find yourself referring back to over the course of the semester.

## Contents

- [Resources](#resources)
  - [Contents](#contents)
  - [Arduino Debugging Checklist](#arduino-debugging-checklist)
  - [Arduino Nano Pinout](#arduino-nano-pinout)
  - [Updating FTDI FT232 Drivers](#updating-ftdi-ft232-drivers)
  - [Arduino Nano Tech-Specs](#arduino-nano-tech-specs)
  - [Voltage Divider](#voltage-divider)
  - [LED Anode vs Cathode](#led-anode-vs-cathode)
  - [Basic Circuitry Formulas](#basic-circuitry-formulas)
  - [Resistor Color Codes](#resistor-color-codes)
  - [TMP36 Wiring](#tmp36-wiring)

## Arduino Debugging Checklist

- [ ] Make sure you have the correct board selected (Arduino Nano)
- [ ] Make sure your code compiles correctly, you can just compile without uploading.
- [ ] Check Ports: Tools->Ports, make sure the port selected is a serial port, if it is bluetooth there is an issue there.
- [ ] Check Bootloader: Tools->Bootloader, try switching the bootloader from new 32 to old 32 or vice versa.
- [ ] Reset the Arduino by holding down the button on it for a few seconds.
- [ ] Unplug the Arduino then plug it back in.
- [ ] Exit out of the Arduino software and reopen it (make sure to close ALL open software windows).  
- [ ] Try a different Arduino or Cord.
- [ ] Restart your computer.
- [ ] Update your FT232 drivers.

If your Arduino is still not functioning after trying all of these steps, call an instructor over for help!

## Arduino Nano Pinout

![Arduino Nano pinout](https://docs.arduino.cc/static/aea75b21cea87290ef2ed4e783b336ef/A000005-pinout.png)

## Arduino Nano Tech-Specs

- Built-in LED Pin #: 13
- Digital Pins: 14
- Analog Pins: 8
- PWM Pins: 6
- Voltage: 5V
- Input-Voltage: 7-12V
- Current per Pin: 20mA

For more detailed specs, see [the Arduino Nano website](https://docs.arduino.cc/hardware/nano)

*[PWM]: Pulse Width Modulation

## Updating FTDI FT232 Drivers

On some occasions, your computer may not detect the Arduino, no matter what you do[^1]. In this case, you likely need to update some drivers for the Arduino's onboard USB-Serial converter. This is pretty straightforward, fortunately. 

1. Go to the [FTDI VCP Drivers website](https://ftdichip.com/drivers/vcp-drivers/). 
2. Scroll down and select the option for your computer's operating system. Clicking on the link should start the download.
3. Once downloaded, unzip the file. 

<div class="primer-spec-callout" markdown="1">
The process to unzip the file varies between macOS and Windows. 
On Windows, right click the .zip file, click "extract all", then click "extract". 
On macOS, just click the .zip file. Your computer will automatically unzip it!
</div>

4. After the file is unzipped, run the application inside the folder. This application will guide you through the rest of the installation process.

[^1]:In our experience, this is typically seen on Windows computers, but could also happen on a Mac.

## Voltage Divider

![Voltage divider schematic](media/voltage-divider.png)

## LED Anode vs Cathode

![LED pinout diagram](media/LED-pinout-anode-cathode.png)

## Basic Circuitry Formulas

Voltage (V in Volts) = Current (I in Amps) * Resistance (R in Ohms)

Power (Watts) = Voltage (Volts) * Current (Amps)

Similarly, Watt-hours = Volts * Amp-hours

## Resistor Color Codes

![Resistor color code chart](https://eepower.com/uploads/education/resistor_color_codes_chart.png)

## TMP36 Wiring

[![TMP36 Pinout](https://cdn-learn.adafruit.com/assets/assets/000/000/471/large1024/temperature_tmp36pinout.gif?1447975787)](https://learn.adafruit.com/tmp36-temperature-sensor/overview)
