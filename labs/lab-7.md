---
layout: spec
latex: true
---

# Lab 7: Designing a PCB using KiCad Designer

## Contents

- [Lab 7: Designing a PCB using KiCad Designer](#lab-7-designing-a-pcb-using-kicad-designer)
  - [Contents](#contents)
  - [Introduction](#introduction)
  - [Participation](#participation)
  - [Lab Timeline](#lab-timeline)
  - [KiCad](#kicad)
    - [Schematic](#schematic)
    - [PCB](#pcb)
    - [DRC](#drc)
  - [Procedure](#procedure-starting-your-design-and-creating-a-schematic)
    - [Designing the PCB](#designing-the-pcb)
  - [Peer Review](#peer-review)
  - [Final Deliverable](#final-deliverable)
  - [Submission](#peer-review-and-final-submission)


## Introduction

In this lab, you will be designing a PCB using KiCad Designer, an industry-standard PCB design software. It's crucial to focus on creating a high-quality design, as changes cannot be made to a PCB after the design is sent off to be manufactured. There is no post-lab for this lab (besides turning in your final design), but you will be reviewing each other's PCBs. Focus on making sure your design is good, and everything about your board works. 

## Participation

Working at a computer often can become a one person deal. It is important to avoid this during the lab. Our goal is for all students in this course learn the basics of KiCad. When you are working on your PCBs, have at least one person spotting the person at the computer. This will help you share the work that goes into creating the PCB and eliminate mistakes that can render your finished product useless. It is important that no team member works alone, even during office hours. 

## Lab Timeline

- **February 26th, 2026, 3:00pm**: Initial PCB design submission.
- **February 26th, 2026, 5:00pm**: Peer review submissions due.
- **February 27th, 2026, 12:00 noon**: Final PCB design submission.

## KiCad

The walk through on creating a schematic and turning the schematic into the PCB is in [lab-7-prelab](/labs/lab-7-prelab). Make sure you do this before starting the KiCad project!

Broadly, the workflow in KiCad is divided up into three steps: Schematic, PCB, and Design Rule Check. The Schematic step is where you lay out the electrical schematic of your board. Using all the components, you define how they connect to each other, ground, and power. The PCB step is where you make the physical layout of those components on the board. The electrical connections you set up in the schematic are shown for your reference, and you lay them down on your PCB physically as traces. That is, each trace you set corresponds to an electrical connection you outlined in your Schematic. The Design Rule Check step is when the software looks over your work and makes sure you aren't committing any errors or contradictions. This is inevitably the most frustrating part of using KiCad, because you think you've done everything right, and the software is here to tell you that you haven't. It is important to note that design rule checks do not check whether you laid out your board the way you wanted, they will not notice if you accidentally connected your temperature sensor to your pressure sensor instead of the Arduino (if that is what you did in your schematic). You must double check this yourself. The design rule checks only check if your design rules are violating the physical and electrical laws associated with making a PCB.

To get started:
- Downloaded the new e100_libraries zip file. [Here is the library.](https://drive.google.com/drive/folders/1hEMXx6rBtbnSW5AzhhSkubN2ptC8kDTD?usp=drive_link)
- Uncompress it.
- In KiCad, select new project. Choose a folder to save the project. The name should make sense!  Include team number in the name!
- 
- Click back on "home"
- All of the libraries may be dumped into the general space and not into your project.  If they are, drag and drop all of the source documents individually into your project.  You should then be able to see everything in your project under Libraries.
- Make a schematic of your project

## Schematic

### Background
You begin with an idea. A circuit or device that you'd like to realize in a PCB. The first thing you need to do is tell KiCad the components you'll be using, and their relationships to one another. Consider the drawing of a 'self-running a stable multivibrator' below. 
![Multivibrator schematic](/labs/media/lab-7_figures/multivibratorSchematic.jpg)

_Figure 1: A drawing of a schematic, that pretty closely resembles a schematic you’d make in KiCad._

Fig. 2 shows Fig. 1 as an KiCad schematic. The schematic is defined in a document with the extension **.SchDoc.**
![Fig 1 schematic](/labs/media/lab-7_figures/fig1schematic.png)

_Figure 2: The schematic of an astable multivibrator as displayed through KiCad._

For additional reference, here is the schematic you made following Lab 1:
![Lab 1 schematic](/labs/media/lab-7_figures/postlab1bSchDoc.jpg)

_Figure 3: The schematic completed in the Postlab 1 assignment_

Note that each component is defined with its own individual symbol. Capacitors, resistors, and transistors (Q1 and Q2), and some connectors (P1) are standardized and thus have pre-loaded symbols in the software, but for most of our components, that is not the case. We have additional libraries custom made by ENGR100 staff with our components pre-loaded, so as we will discuss in the procedure, you can simply drag and drop them into place.  See link above.


### Your Schematic Contents

Obviously, the functionality we're trying to put on a PCB is the ability to record data from your sensor board, so starting your schematic off by adding your full Lab 3, 4, and 5 circuits is a good starting point.

We have made a power board that provides you the LDOs and battery connector.  This is included in the provided ENGR100 library.

LEDs are also useful when diagnosing software bugs without a computer, telling you if the board is on or off, and also making cool light patterns.

You will also use resistors and capacitors.

Please wire the 5V, 3.3V and battery line to their own LEDs with a 1K resistor on each LED. You are free to add LEDs in other places on your board if you would like!

Footprints of LEDs, resistors and capacitors:
- Capacitors have to be 1206 SMD (surface mount only)
- LEDs have to be LED_THT:LED_D5.0mm  (thru-hole)
- Resistors can be 1206 SMD (surface mount) **or** Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal (thru-hole)

Some notes:
- **As you place sensors on your schematic, change the label on the top of the sensor.  Some have a label of '*', while others are 'Temperature*'.  Give them all unique names that make sense (like TMP36 or Datalog).**
- Ground all of your components using a "GND Power Port"
- Connect 5V pins together from the power board with arduino 5V pin (this will power the Arduino) and all other 5V power connections on the 5V powered devices. There should be **NO connection to the Vin pin of the Arduino!**  You could make a 5V Net to make things cleaner.

In summary, your schematic (and the PCB) must have:
- [ ] An Arduino Nano Every (voltage input should be through the 5V connector and nothing should be connected to the Vin pin)
- [ ] TMP36 or thermister (external temperature) - if using thermister, talk to teaching staff
- [ ] BME sensor (humidity, pressure, and temperature)
- [ ] Accelerometer
- [ ] GPS
- [ ] Level shifter
- [ ] SD Card writer
- [ ] LEDs with resistors from 3.3V, 5.0V, and battery voltage lines to ground
- [ ] Any extra sensors you choose to use
- [ ] The power daughter board (which includes battery connection, RBF pin, LDOs, and capacitors)
- [ ] 0.1 micro-F capacitors from the input voltage line on the GPS to ground, the SD card input voltage to ground, and the Arduino 5V pin to ground (3 capacitors).
- [ ] 0.1 micro-F capacitors from input line to ground close to TMP36, BME680, and accelerometer (3 more capacitors).

If your extra sensor uses I2C communication protocols, you must connect it to the analog pins pre-set for I2C communications. In the Arduino Nano, these are A4 (SDA pin) and A5 (SCL pin). See more on connecting I2C devices (google search "connecting I2C devices to an Arduino nano") Be sure you read through your extra sensor’s documentation and/or hookup guide to understand whether it is I2C and if you will need the A4 and A5 I2C hookup pins. You can google search for the extra sensor datasheet.

If you choose to use the GUVA sensor, use the Humidity sensor in the ENGR100 library, and relabel the pins (and labels) to be the appropriate type (you need to swap the GND and 5V pins).

If you choose to use a heater, we will use a generic MOSFET, using the [wiring diagram here.](https://adam-meyer.com/arduino/images/2012/03/rfp30n06le-arduino-solenoid.png)  In this diagram, the MOSFET has pins 1 - G; 2 - D; 3 - S.  You can use a generic resistor to represent the heater, since it will just be soldered into place.

![Heater with MOSFET Schematic](/media/Heater_wiring.png)

- If you use the **photo-cells** or a **thermister**, you can use generic resistors, since these will be soldered with wires, so the connection type doesn't really matter much.  Both a photo-cell and a thermister act as resistors, so you will be creating a voltage divider circuit, with a resistor in series with the photo-cell / thermister, with the analog line coming off the wire in-between the resistor and photo-cell /thermister.

![Photo-cells with MUX Schematic](/media/Light_sensor_mux.png)

#### Procedure: Starting Your Design and Creating A Schematic

1. Download KiCad Libraries, which have been made [available here](https://drive.google.com/drive/folders/1as9BSRX3MIbJ2zoFcvnK2wEEbZvzaijp).

2. Open KiCad Designer on your computer. Navigate to File -> New -> Project...

3. Choose the PCB project type.

4. The "Folder" field allows you to choose where this folder is created. You are going to zip this folder and share it with others.  The folder should have your team number in it.

5. Name your project with your team number and appropriate name (e.g., Team05_Project_PCB_V1.0), and click "OK". 

6. Now you should add the libraries we have given you. You will need to add both schematics and footprints. Once they are added, save the project.

7. You should be able to click on the "Schematic Editor" and start making your schematic. Some notes:

    * Watch the [youtube video](https://www.youtube.com/watch?v=NHHwZCHNMq8) to figure some things out.
    
    * You may manually have to link a footprint to the schematic for a component. To do that, use the "Tools -> Assign Footprints" menu.  Make sure that you have added the footprint libraries!
    
    * Change the labels on things to make sense and so you can recognize them when they are dropped into the PCB.  For example, if you have an LED and a resistor on the 5V line, call the LED "LED5V" and the resistor "R5V". This should help in making the PCB a lot.

    * Use nets for power (+5V, +3.3V, GND), but use wires for all other connections.  This will make it much easier to find issues with the schematic.
    
That's a lot to keep in mind! The path to success involves moving slowing and methodically through each component, writing out your schematic on paper beforehand, staying organized, and asking questions. If you're confused on what to do, please ask! When you've finished your schematic, **ask another team to take a look at your schematic**. They can offer advice as to what issues you may have. Then, ask an IA to check it off and verify that it is correct. Once they mark it off, you can move onto creating the PCB. It is in your best interest to have a clean and accurate schematic before moving forward. Even minor changes on the schematic can require substantial changes on your PCB to accommodate.

**It is a good idea to design your schematic and then save everything.  Make sure that you can quit out of KiCad and read back in the schematic.  If, for some reason, you need to stop working on this, the end of the schematic creation is a good place to pause.** 

### PCB

#### Background

The PCB is designed as a separate document with the extension **.PcbDoc.** We can create a new PCB document and correlate it to our schematic. This will import all the components to the PCB document. Then, just as in the schematic document, we can manually place each footprint. As before, the footprints will be provided via a custom library we have prepared for you.

Note the white lines that connect each of the footprints in Figure 3. These represent what pins on each part that should be connected via traces. This should be done manually, similar to how wires were drawn in the schematic. One notable difference is that physical traces should never be drawn at right angles - instead, they should be at obtuse angles. This is to minimize field leakage and reflection at corners.  

![Fig. 3](/labs/media/lab-7_figures/fig3.jpg)

_Figure 3: The PCB Layout in KiCad_

#### Procedure: Designing the PCB

_Pressing 1 on your keyboard takes you to the board design view. Pressing 2 takes you to the component layout screen. Pressing 3 takes you to the cartoon mockup screen. You should do your layout work (e.g. most of the work) in mode 2._

1. To create a new PCB file, right click your project name under your Projects tab, click New -> Add New to Project -> PCB.

2. Import your schematic components. Go to Design -> Import Changes from Project name (or Design -> Update PCB Document). Validate your changes, make sure you see only green check marks next to each change. Then execute them.

3. By zooming in and out on your board (by pressing the mouse scroll button and moving around), you should see a big red box containing all of the components. You can drag and drop them onto the board, which is the black rectangle. If you want to rotate a component, click and hold on it and then press the spacebar. Another option is to click it and press M, which will bring up a menu for moving components. One of these menu options is the 'rotate selection' feature. This is better if you want to rotate it a specific amount and not in increments of 90 degrees.

4. Now we should adjust the size of our board.
- Edit -> Origin -> Set, then select the lower left corner of your board.
- Press "1" to go into board planning mode
- Navigate to Design -> Edit Board Shape.
- The board should be no bigger than 4 inches by 4 inches. You can toggle between Imperial and Metric units by pressing Q. [This shows you how to do that.](https://resources.altium.com/p/layout-guide-changing-board-sizes-altium-designer)

5. Make sure to press "2" to get back into the mode where you can move stuff around.

6. We will add some design rules. Press 2 on your keyboard to ensure that you are on the component layout screen. Navigate to Design -> Rules. A PCB rules window should pop up. Set the following design rules:
    * Electrical -> Clearance = 10 mil
    * Routing -> Width
        - Minimum Width = 6 mil
        - Preferred Width = 15 mil
        - Maximum Width = 30 mil
    * Manufacturing -> Hole Size = 13 mil (min) and 125 mil (max)
    * Manufacturing -> Minimum Annular Ring = 7 mil

7. Layout your components neatly on the board. Be sure to place your Arduino and Data Logger in such a way that you do not obstruct the port for the uploading cable or the SD Card opening.

8. To connect traces to your different components, choose Place -> Trace. When you are placing a trace press 3 to toggle between your min, preferred, and max trace width as set in the design rules (the vast majority should be your preferred, so you don't have to change this very often).

9. When routing, all traces should default to 15mil if you implemented the Design Rules correctly. However, you should manually thicken the traces from the power connections to the GPS, Arduino, and SD Card reader to 20mil in order to compensate for the increased current flow through them. For the heater, use 30mil traces!

10. Recall from lecture that your board contains two copper layers. These layers are referred to as the top and bottom layers, and are colored red and blue. You can route traces on either side of the board.  You need to escape out of placing traces, then switch layers (by clicking on the layer that you want), the go back to placing traces.

11. Route all traces except the ground traces. We will route those later to our polygon pour ground plane, which we make last.

12. When routing, you may notice obvious conflicts (lots of traces need to cross).  You can play with the design by rotating components, moving components, or rearranging your components to ease these conflicts.  You may have to do this a few times, so when you place a trace the first time, don't think of it as the final time - think of this as a sketch that you are refining as you go.  **It is ok (and expected!) to delete traces, move things and retrace!** Use both layers of the board to trace! Remember that through hole components are connected on both sides of the board, so you can trace on either side!

13. You can use Vias to have a trace go from the top layer to the bottom layer or bottom to the top layer.  You can use this technique when you have to cross another trace.  Most trace crossings can be avoided with some thinking about placement of components, orientation of the different components, or tracing using different routes.  Routes should not be too long, though! **Don't have super long traces to avoid crossing.** 

14. When placing a Via, you have to assign it to a "Net".  For example, if you want to ground a surface mount pad, create a Via (place -> Via), double click on it (to get to Properties, and then select the net "GND".  Now, KiCad knows that it should be grounded.

15. You can place labels (technically, you Place -> String) on your PCB to help you remember things. Because LEDs are directional, you may want to indicate which sides are positive by adding a "+" label near the high voltage side. Labels are good.  **You MUST label your board with your team number and name** as well as the date and your names if you would like.

16. Pour a ground plane. Using the menu at the bottom of the PCB, select the bottom layer and cover it with a polygon pour. Once you put the polygon pour, open the properties, change the Net to "GND" and click on the "Repour". All of your grounded vias will be connected to the ground plane! **If you add new items to your PCB, you will need to repour your polygon pour.**  You may have to do this multiple times if you end up changing things over and over.

Finally, we have a completed board! KiCad creates a cartoon (Figure 4) that we can view before moving on to the final stage: Design Rule Check.

![Fig. 4](/labs/media/lab-7_figures/Assembly.gif)

_Figure 4: Completed PCB_

### DRC

The DRC, or Design Rule Check is a way to check the validity of your PCB with respect to the Design Rules we create. More on this in the procedure.

#### Procedure: Design Rules Check

1. Recall that you created a set of Design Rules before creating your PCB. The Design Rule Check (DRC) assesses your design in light of these rules, and highlights any discrepancies between your layout and those rules. Your DRC must return ZERO errors before your PCB can be considered complete. Design Rule Check can be run by navigating to Tools -> Design Rule Check. Click Run Design Rule Check to run DRC. Generally, errors are highlighted in bright green.

2. Once you have passed all design rule checks, take a screenshot of your error-free DRC screen.

## Final Deliverable

Each team must upload a single zip file containing **all project files and a screenshot showing all DRCs passed** to this designated Google Drive folder (linked in the Canvas assignment) by the date and time specified on the Canvas assignment.

Each student will peer review three PCBs with rubrics provided on Canvas. 

The zip file must:
* Contain all information so that another person can unzip the file, open KiCad, and see you schematic and PCB.
* Be named with the following template: team_xx_altium.zip, which xx is your team number expressed as two digits (e.g., 01, 02, 10, 11, etc.)


## Peer Review

After the lab, every student will be required to peer review the PCBs of three other teams. 

There is a canvas assignment as well as a google form that must be filled out for each review.


## Peer Review and Final Submission

- [ ] Submit your error-free DRC screenshot and all project files to the designated Google Drive folder by the assignment deadline discussed in class and posted on the Canvas assignment.
- [ ] Peer review three other teams' PCBs using provided rubrics by the date and time stated in the Canvas assignment.

Remember, accuracy and collaboration are essential. Reach out to IAs, Professor Ridley, or the **#lab-help** channel on Slack for assistance if needed. Good luck with your PCB design!
