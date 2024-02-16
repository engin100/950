---
layout: spec
latex: true
---

# Lab 6: Designing a PCB using Altium Designer

## Contents

- [Lab 6: Designing a PCB using Altium Designer](#lab-6-designing-a-pcb-using-altium-designer)
  - [Contents](#contents)
  - [Introduction](#introduction)
  - [Participation](#participation)
  - [Lab Timeline](#lab-timeline)
  - [Altium](#altium)
    - [Schematic](#schematic)
    - [PCB](#pcb)
    - [DRC](#drc)
  - [Procedure](#procedure-starting-your-design-and-creating-a-schematic)
    - [Designing the PCB](#designing-the-pcb)
  - [Peer Review](#peer-review)
  - [Final Deliverable](#final-deliverable)
  - [Submission](#peer-review-and-final-submission)

Some random notes:
- downloaded the e100_libraries folder
- uncompress
- In altium, new project. Choose a place in Documents (not public documents...)
  - name should make sense!  Include team number in name!
- drag and drop the 4 library files from a file folder into your project.
  - It will ask about extracting libraries.  Extract them.
- click back on "home"
- All of the libraries are dumped into the general space and not into your project.
  - drag and drop all 6 source documents individually into your project.
  - Should then be able to see everything in your project under Libraries.
- Make a schematic of your project
  - As you place sensors on your schematic, change the label on the top of the sensor.  Some have a label of '*', while others are 'Temperature*'.  Give them all unique names that make sense.
  - Ground all of your components using a "GND Power Port"
  - Connect 5V pins together with arduino 5V pin (this will power the Arduino)
  - Connect 3.3V
  


## Introduction

In this lab, you will be designing a PCB using Altium Designer, an industry-standard PCB design software. It's crucial to focus on creating a high-quality design, as changes cannot be made to a PCB after the design is sent off to be manufactured. There is no post-lab for this lab (besides turning in your final design), but you will be reviewing each other's PCBs. Focus on making sure your design is good, and everything about your board works. 

## Participation

Working at a computer often can become a one person deal. It is important to avoid this during the lab. Our goal is for all students in this course learn the basics of Altium. When you are working on your PCBs, have at least one person spotting the person at the computer. This will help you share the work that goes into creating the PCB and eliminate mistakes that can render your finished product useless. It is important that no team member works alone, even during office hours. 

## Lab Timeline

- **February 22nd, 2023, 3:00pm**: Initial PCB design submission.
- **February 22nd, 2023, 5:00pm**: Peer review submissions due.
- **February 23rd, 2023, 12:00 noon**: Final PCB design submission.

## Altium

You may want to revisit the complete Altium tutorial in the Lab 1 post lab.  You worked through the schematic in Lab 1.  It would be worthwhile to revist this and then try to make the PCB, since that is what you will be doing in this lab.  The walk through on turning the schematic into the PCB is in lab-6-prelab.md.

Altium as a software can be very complex, and as such, we have given you some tools to help simplify the process of constructing your PCB. The following pictures are taken from a free online tutorial provided by Altium: [From Idea to Manufacture](https://www.altium.com/documentation/altium-designer/tutorial-complete-design-walkthrough?version=22). You can learn more about this example there.

Broadly, the workflow in Altium is divided up into three steps: Schematic, PCB, and Design Rule Check. The Schematic step is where you lay out the electrical schematic of your board. Using all the components, you define how they connect to each other, ground, and power. The PCB step is where you make the physical layout of those components on the board. The electrical connections you set up in the schematic are shown for your reference, and you lay them down on your PCB physically as traces. That is, each trace you set corresponds to an electrical connection you outlined in your Schematic. The Design Rule Check step is when the software looks over your work and makes sure you aren't committing any errors or contradictions. This is inevitably the most frustrating part of using Altium, because you think you've done everything right, and the software is here to tell you that you haven't. It is important to note that design rule checks do not check whether you laid out your board the way you wanted, they will not notice if you accidentally connected your temperature sensor to your pressure sensor instead of the Arduino. You must double check this yourself. The design rule checks only check if your design rules are violating the physical and electrical laws associated with making a PCB.

## Schematic

### Background
You begin with an idea. A circuit or device that you'd like to realize in a PCB. The first thing you need to do is tell Altium the components you'll be using, and their relationships to one another. Consider the drawing of a 'self-running a stable multivibrator' below. 
![Multivibrator schematic](/labs/media/lab-7_figures/multivibratorSchematic.jpg)

_Figure 1: A drawing of a schematic, that pretty closely resembles a schematic you’d make in Altium._

Fig. 2 shows Fig. 1 as an Altium schematic. The schematic is defined in a document with the extension **.SchDoc.**
![Fig 1 schematic](/labs/media/lab-7_figures/fig1schematic.png)

_Figure 2: The schematic of an astable multivibrator as displayed through Altium._

For additional reference, here is the schematic you made following Lab 1:
![Lab 1 schematic](/labs/media/lab-7_figures/postlab1bSchDoc.jpg)

_Figure 3: The schematic completed in the Postlab 1 assignment_

Note that each component is defined with its own individual symbol. Capacitors, resistors, and transistors (Q1 and Q2), and some connectors (P1) are standardized and thus have pre-loaded symbols in the software, but for most of our components, that is not the case. We have additional libraries custom made by ENGR100 staff with our components pre-loaded, so as we will discuss in the procedure, you can simply drag and drop them into place.


### Your Schematic Contents

Obviously, the functionality we're trying to put on a PCB is the ability to record data from your sensor board, so starting your schematic off by adding your full Lab 3, 4, and 5 circuits is a good starting point.

Additionally, we decided that turning on and off your board would be nice, so add the SW-SPST switch included in the miscellaneous devices library between the positive terminal of the battery and the VIN pin on the Arduino.

LEDs are also useful when diagnosing software bugs without a computer, telling you if the board is on or off, and also making cool light patterns. Please wire pins D4-D9 to their own LED with a 1K resistor on each LED. This way, you have 6 LEDs to diagnose problems and play with.

In summary, your schematic (and the PCB) must have:
1. An Arduino Nano (voltage input should be through the 5V connector and nothing should be connected to the Vin pin)
2. Two TMP36s (internal and external)
3. Humidity sensor
4. Pressure sensor
5. Accelerometer
6. GPS
7. Level shifter
8. SD Card writer
9. LEDs with surface mount resistors from 3.3V, 5.0V, and battery voltage lines to ground
10. Your extra sensor
11. The power daughter board (which includes battery connection, RBF pin, LDOs, capacitors, and charging port)
12. Surface mount capacitors from the input voltage line on the GPS to ground, the SD card input voltage to ground, and the Arduino 5V pin to ground.

If your extra sensor uses I2C communication protocols, you must connect it to the analog pins pre-set for I2C communications. In the Arduino Nano, these are A4 (SDA pin) and A5 (SCL pin). See more on connecting I2C devices (google search "connecting I2C devices to an Arduino nano") Be sure you read through your extra sensor’s documentation and/or hookup guide to understand whether it is I2C and if you will need the A4 and A5 I2C hookup pins. You can google search for the extra sensor datasheet.

#### Procedure: Starting Your Design and Creating A Schematic

1. Download the resources provided in the Canvas Files section for the Altium lab. There should be a folder called 'Altium Libraries' for you to download.
2. Open Altium Designer on a CAEN computer. Navigate to File -> New -> Project...
3. Choose the PCB project type.
4. The "Folder" field allows you to choose where this folder is created. You can save it to your "Documents" folder (**not "Public Documents"!!!**) for it to sync across all CAEN instances or, you can navigate to "This PC" -> "U-M Google Drive (I:)" as shown in Fig. 5 and save it in a folder here so that you can share it with teammates. **Do not save the project in your Downloads folder or in the Public Documents folder. On CAEN machines, these locations can be wiped every 24 hours.**
    ![Fig. 4](/labs/media/lab-7_figures/fig5.jpg)
    
    _Figure 4: CAEN File Explorer_
5. Name your project with your team number and appropriate name (e.g., Team05_Project_PCB_V1.0), and click "OK". See Fig. 6 for an example Project Creation.
    ![Fig. 5](/labs/media/lab-7_figures/fig6createWiz.jpg)
    
    _Figure 5: Project Creation Wizard popup_
6. Now you should add two libraries we have given you. To do this, you can drag and drop the libraries into the project.  They may show up in "Free Documents".  If they do, then you will need to drag them up to the project and drop them in there.  Once they are added, save the project.
7. Look at the Projects Tab on the left side of the screen. Right click your project name in bold and click Add New to Project -> Schematic. A blank piece of paper should appear on the screen. This is where you are to lay out your schematic drawing. A few instructions for laying out a schematic:

    * Go to Place -> Part to place a component. Navigate to the library you would like to use with the dropdown menu. A keyboard shortcut is to simply press "P" twice in a row.  If you select on the drop down menu in the upper right of the screen after choosing to place a part, the libraries in the last step should show up here.  If they don't, verify that the libraries are in the project, and everything (including the schematic) is saved.

    * You can either connect everything together with wires or use "nets". Nets are a convenient way to connect two pins without explicitly drawing a wire between them. You can place a net using Place -> Net Label. This is a great way to make sure things don't get too messy. One issue with nets is that it may be hard to see what is connected to what. The most common net is ground - it is so common that there is a special button for it. You can click on the ground (GND) button and attach this to all of the ground pins on all of your components.  This tells Altium that they are all connected together to a ground pin.
    
    * You can also use wires to connect everything together. Wires can cross each other without connecting, but if they have a circle where they cross, they are connected. **Make sure only the things that are supposed to be connected are connected!**

    * To find the properties of a given component, double click its symbol on the schematic. A component-specific properties window will open up. Here you can adjust the part label, the value of the component (such as resistance or capacitance), and the **footprint** of the component. The footprint is a representation of how the component looks in real life - e.g. what actually will be on your board. You can add a footprint by clicking the corresponding Add button in the Component Properties window.

That's a lot to keep in mind! The path to success involves moving slowing and methodically through each component, writing out your schematic on paper beforehand, staying organized, and asking questions. If you're confused on what to do, please ask! When you've finished your schematic, **ask another team to take a look at your schematic**. They can offer advice as to what issues you may have. Then, ask an IA to check it off and verify that it is correct. Once they mark it off, you can move onto creating the PCB. It is in your best interest to have a clean and accurate schematic before moving forward. Even minor changes on the schematic can require substantial changes on your PCB to accommodate.

**It is a good idea to design your schematic and then save everything.  Make sure that you can quit out of Altium and read back in the schematic.  If, for some reason, you need to stop working on this, the end of the schematic creation is a good place to pause.** 

### PCB

#### Background

The PCB is designed as a separate document with the extension **.PcbDoc.** We can create a new PCB document and correlate it to our schematic. This will import all the components to the PCB document. Then, just as in the schematic document, we can manually place each footprint. As before, the footprints will be provided via a custom library we have prepared for you.

Note the white lines that connect each of the footprints in Figure 3. These represent what pins on each part that should be connected via traces. This should be done manually, similar to how wires were drawn in the schematic. One notable difference is that physical traces should never be drawn at right angles - instead, they should be at obtuse angles. This is to minimize field leakage and reflection at corners.  It is important to note: all 1 kOhm resistors must use a 1206 footprint. If your resistors do not use this footprint by default, switch the footprint to the 'C1206' footprint in the miscellaneous devices library using the properties window.

![Fig. 3](/labs/media/lab-7_figures/fig3.jpg)

_Figure 3: The PCB Layout in Altium_

#### Procedure: Designing the PCB

_Pressing 1 on your keyboard takes you to the board design view. Pressing 2 takes you to the component layout screen. Pressing 3 takes you to the cartoon mockup screen. You should do your layout work (e.g. most of the work) in mode 2._

1. To create a new PCB file, right click your project name under your Projects tab, click New -> Add New to Project -> PCB.
2. Import your schematic components. Go to Design -> Import Changes from Project name. Validate your changes, make sure you see only green check marks next to each change. Then execute them. By zooming in and out on your board (by pressing the mouse scroll button and moving around), you should see a big red box containing all of the components. You can drag and drop them onto the board, which is the black rectangle. If you want to rotate a component, click and hold on it and then press the spacebar. Another option is to click it  and press M, which will bring up a menu for moving components. One of these menu options is the 'rotate selection' feature. This is better if you want to rotate it a specific amount and not in increments of 90 degrees.
3. Now we should adjust the size of our board. To do this, press 1 on your keyboard. Navigate to Design -> Edit Board Shape. The board should be no bigger than 4 inches by 4 inches. You can toggle between Imperial and Metric units by pressing Q. [This shows you how to do that.](https://resources.altium.com/p/layout-guide-changing-board-sizes-altium-designer)
4. We will add some design rules. Press 2 on your keyboard to ensure that you are on the component layout screen. Navigate to Design -> Rules. A PCB rules window should pop up. Set the following design rules:
    * Electrical -> Clearance = 6 mil
    * Routing -> Width
        - Minimum Width = 6 mil
        - Preferred Width = 15 mil
        - Maximum Width = 30 mil
    * Manufacturing -> MinimumAnnularRing = 7 mil
    * Manufacturing -> HoleSize = 13 mil (min) and 125 mil (max)
5. Layout your components neatly on the board. Be sure to place your Arduino and Data Logger in such a way that you do not obstruct the port for the uploading cable or the SD Card opening.
6. To connect traces to your different components, navigate to Route -> Interactive Routing. When you are placing a trace press 3 to toggle between your min, preferred, and max trace width as set in the design rules. Recall from lecture that your board will contain two copper layers. These layers are referred to as the top and bottom layers, and are colored red and blue. Route all traces except the ground traces. We will route those later to our polygon pour ground plane, which we make last.
7. You can place labels on your PCB to help you remember things. Because LEDs are directional, you may want to indicate which sides are positive by adding a "+" label near the high voltage side. Labels are good.
8. When routing, all traces should default to 15mil if you implemented the Design Rules correctly. However, you should manually the trace from the +9V connection to the VIN pin on the Arduino thicker, to compensate for the increased current flow through it.
9. Pour a ground plane. Using the menu at the bottom of the PCB, select the bottom layer and cover it with a grounded polygon pour. You can now connect all your ground connections directly to this by using vias (no traces involved).


Finally, we have a completed board! Altium creates a cartoon (Figure 4) that we can view before moving on to the final stage: Design Rule Check.

![Fig. 4](/labs/media/lab-7_figures/Assembly.gif)

_Figure 4: Completed PCB_

### DRC

The DRC, or Design Rule Check is a way to check the validity of your PCB with respect to the Design Rules we create. More on this in the procedure.

#### Procedure: Design Rules Check

1. Recall that you created a set of Design Rules before creating your PCB. The Design Rule Check (DRC) assesses your design in light of these rules, and highlights any discrepancies between your layout and those rules. Your DRC must return ZERO errors before your PCB can be considered complete. Design Rule Check can be run by navigating to Tools -> Design Rule Check. Click Run Design Rule Check to run DRC. Generally, errors are highlighted in bright green.
2. Once you have passed all design rule checks, take a screenshot of your error-free DRC screen.

## Final Deliverable

Each team must upload a single zip file containing **all project files and a screenshot showing all DRCs passed** to this designated Google Drive folder [(click here)](https://drive.google.com/drive/folders/1dqrIZPnpz_5BiepUqeAE46O8Z0YM9a0D) by 11:59pm on October 17th, 2023. Make sure that your PCB passes all design rule checks before submitting it to the Google Drive folder. Each student will peer review three PCBs with rubrics provided on Canvas. 

The zip file must:
* Contain all information so that another person can unzip the file, open Altium, and see you schematic and PCB.
* Be named with the following template: team_xx_altium.zip, which xx is your team number expressed as two digits (e.g., 01, 02, 10, 11, etc.)


## Peer Review

After the lab, every student will be required to peer review the PCBs of three other teams. 

Peer reviews are due by 11:59pm on Tuesday, October 24th, 2023.  There is a canvas assignment as well as a google form that must be filled out for each review.


## Peer Review and Final Submission

- [ ] Submit your error-free DRC screenshot and all project files to the designated Google Drive folder by **October 17th, 2023, 11:59pm**.
- [ ] Peer review three other teams' PCBs using provided rubrics by **October 24th, 2023, 11:59pm**.

Remember, accuracy and collaboration are essential. Reach out to IAs, Professor Ridley, or the **#lab-help** channel on Slack for assistance if needed. Good luck with your PCB design!
