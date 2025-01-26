---
layout: spec
latex: true
---

# Lab 3: Group A Portion

Powering the Arduino, measuring battery voltage, and adding the MicroSD Card Adapter Module.

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

- [Lab 3: Group A Portion](#lab-3-group-a-portion)
  - [Contents](#contents)
  - [Materials](#materials)
  - [Procedure](#procedure)
    - [1. Powering the Arduino](#1-powering-the-arduino)
    - [2. Measuring Battery Voltage](#2-measuring-battery-voltage)
    - [3. Adding the MicroSD Card Adapter Module](#3-adding-the-microsd-card-adapter-module)

## Materials

- [ ] 1 Arduino Nano
- [ ] 1 Breadboard
- [ ] 1 Programming Cable (and adapters if necessary)
- [ ] 1 MicroSD Card
- [ ] 1 Data Logger
- [ ] 1 MicroSD Card - USB Adapter
- [ ] A handful of jumper wires
- [ ] 2 1k$$\Omega$$ resistors
- [ ] 1 9V battery
- [ ] 1 9V battery connector
- [ ] A computer with the Arduino IDE [installed](/tutorials#arduino-ide-install) and [setup](/tutorials#arduino-library).
- [ ] ENGR100-950 Arduino Library

## Procedure

### 1. Powering the Arduino

To start, we want to power our Arduino with the 9V battery. Plug your Arduino into your breadboard, and plug the 9V into it's connection clip. It should only fit one way, since the terminals are different shapes.

Notice that one wire coming out of the battery is red, and one is black. Common practice says that red will be positive, in this case +9V, and the black will be what we connect to our Arduino's GND.

Take these wires and plug them into your Arduino via your breadboard. Red should go to the Arduino's Vin, and black should go to any GND pin.

Once you've plugged the 9V in, the Arduino should light up - even though it isn't plugged into your computer! If it does, congrats, your external power is working! If not, check your connections again.

As one last check that everything is working before we move on, upload the File → Examples → Basics → Blink code that the Arduino IDE comes with, to your Arduino. After it finishes uploading, unplug your computer and verify that the onboard LED on the Arduino continues to blink on only the 9V's power.

<div class="primer-spec-callout info" markdown="1">
In the next lab we will go over creating a more reliable power source using a separate power circuit. For now, this will do, just take note that sensor readings may fluctuate based on whether the Arduino is powered by a battery or by your computer, and whether or not all of the sensors are plugged in and drawing power. More on this later!
</div>

### 2. Measuring Battery Voltage

Most modern electronics, from your smartphone to even rockets, have some way of reporting back the charge of any internal batteries. While we don't use the battery for very long at any one time in this lab, other people are using the same batteries, and so we do want to verify they are charged.

To measure battery voltage, we can use the analog pins on the Arduino, similar to how we did in lab 1. The caveat of this, however, is that the analog pins can **only take up to 5V!!** So, before reading the battery in, we need to build a voltage divider to step the battery voltage down to 5V max.

Using our voltage divider [(see the resources page for more)](/resources), we can take 2 1k$$\Omega$$ resistors and step ~9V down to ~4.5V. Go ahead and build this voltage divider.

When you are done, your 9V battery should have the black wire going to GND, and the red wire going to **both** Vin on the Arduino **and** a voltage divider.

Now, let's test that the voltages look realistic. Go to File → Examples → Basics → AnalogReadSerial and change the `analogRead()` function called in `loop()` to be the pin you plugged your voltage divider into. Run this code and make note of the values it returns.

You know on the Arduino Nano this value will be between 0-1023, and that your max voltage, as reported by the Arduino, is 5V. Convert your raw value to the voltage by dividing it by 1023 and multiplying it by 5V. This is the voltage your Arduino recorded.

Your battery, however, has a higher voltage than that. We now need to undo the effects of the voltage divider to determine the battery's original voltage. Since we used the same resistance on either side of the voltage divider, the voltage is being cut in half. Therefore, we can simply multiply the Arduino's recorded voltage by 2 to get the 9V battery's voltage. It should be somewhere between 8 and 10V.

<div class="primer-spec-callout info" markdown="1">
Note that the values displayed in the serial monitor are rounded, and don't show us as accurate of voltages as we would like. This is because the value is stored as an "int", or integer. To obtain decimal places, change this to a float, and when applying any calculations (such as converting from raw values to voltages) put .0 at the end to let the code know you are trying to obtain decimal values. Ex. "float voltage = rawValue * (10.0 / 1023.0);"
</div>

### 3. Adding the MicroSD Card Adapter Module

Unlike the other sensors and modules we have used so far, the MicroSD module we are using uses the Arduino's digital pins. Luckily for us, there are libraries (that you should have installed when following the tutorial and initially setting up your Arduino IDE), that handle all the complicated digital interfacing for us. All we need to know is which pins to plug the adapter module into.

![MicroSD Adapter Module Wiring](../media/SD-Card-Wiring.png){: .invert-colors-in-dark-mode }

While your Arduino is powered off and disconnected from the 9V, plug your module in as shown above. The Arduino pins for this **DO** matter and cannot easily be changed, unlike the analog pins.

Plug your microSD card into your computer and ensure that it is empty. If there are files on the card, delete them and empty the trash. You should always clear the card, empty the trash while the card is still inserted, and properly eject it before removing the card from your computer.

While power is disconnected from the Arduino, go ahead and insert the microSD card into the adapter module. Plug in the Arduino (to USB), connect the 9V battery, and open the file at File → Examples → ENGR100-950 → Lab3-SDtester and upload/run it. This script will throw an error statement in the serial monitor if the SD logger is not working properly. Once this script runs and appears to have worked for a few moments, go ahead and disconnect power, remove the SD card, and open the contents on your computer. You should see a file titled `DATALOG.CSV` which should be a CSV file with sample headers (names of the sensors we are using) and rows of data that are numbered 0-7 for each column. If this appears correct, then congratulations, you have successfully connected your SD logger and you are ready to meet up with Group B once they have finished their part! Make sure to clear this SD card and empty the trash!

<div class="primer-spec-callout warning" markdown="1">
When Group B is ready to move on, take both of your breadboards and move all the jumpers running from their Arduino into the same pins on your Arduino, so that everything is wired into one microcontroller (you need not physically move the components, but rather just their jumpers, leaving two breadboards side by side. They can lock together!). Connecting these breadboards is best done by moving ONLY the analog/digital jumpers from Group B's Arduino to Group A's Arduino, and then connecting a jumper from the 5V rail of Group A to the 5V rail of Group B (do this for the 3.3V rail and the GND rails as well). Note that the numbering of the analog pins does NOT matter, but the digital pins MUST go into the same numbered ordered as before. As one last final check, Group B's original Arduino should have nothing plugged into it, so you can remove any jumpers remaining connecting it to power or GND. Once this is done, follow the link below to jump back into the normal lab manual together.
</div>

- [Groups A & B Lab Manual - Finishing Steps](/labs/lab-3#6-adding-the-microsd-card-adapter-module)