---
layout: spec
latex: true
---

# Lab 7 Prelab: KiCAD Schematic to PCB

## Contents 

- [Lab 7 Prelab: Altium Schematic to PCB](#lab-7-prelab-altium-schematic-to-pcb)
  - [Contents](#contents)
  - [Resources](#resources)
  - [Procedure](#procedure)
    - [Onwards and Upwards (Upwards = to PCB Design)](#onwards-and-upwards-upwards--to-pcb-design)
    - [PCB General View and Sizing](#pcb-general-view-and-sizing)
    - [Editing Part Placement on PCB](#editing-part-placement-on-pcb)
    - [Traces](#traces)
    - [Layers to Worry About](#layers-to-worry-about)
    - [Polygon Pour](#polygon-pour)
    - [Design Rule Check](#design-rule-check)
    - [Trace Width Guidelines](#trace-width-guidelines)
    - [Design Rules](#design-rules)
  - [Submission](#submission)

## Resources

- [ ] A computer running latest version of KiCAD
- [ ] [KiCAD Power Board libraries .zip file](https://umich.instructure.com/courses/819667/files/folder/Power%20Board%20Library) (you will need to unzip before using)
- [ ] [Youtube Tutorial](https://www.youtube.com/watch?v=NHHwZCHNMq8)
<!--
 Spreadsheet of Footprints - https://drive.google.com/file/d/1tsC8cM-wiYfIB25BBM7o7ymhQ4F3gtD8/view?usp=sharing
 Second Spreadsheet of Footprints - https://drive.google.com/file/d/1LVTbnMMa6W0KI2mwZwTfUbNu1QJWeqjq/view?usp=sharing
note these are outdated footprints which do not have the BME sensor.
-->

## Procedure

This is the second part of the introduction to KiCAD. In this assignment, you will draw a schematic for a power board and then turn that schematic into a PCB. There has been a video created that walks through all of the steps of making the schematic and then making a PCB. It is a relatively long process (the video is about one hour and fifteen minutes), but it really shows you all of the steps of going through the process. [The video is here.](https://www.youtube.com/watch?v=NHHwZCHNMq8)

### Onwards and Upwards (Upwards = to PCB Design)

- Save your schematic document
- Go to PCB editor
- Tools -> Update PCB from schematic
- Now the fun begins!

### PCB General View and Sizing

- Pressing option + 3 will show the 3D viewer of the board
    - Good to see your board in 3D and see components/traces on the top/bottom
    - Rotating in 3D viewer using your Left Mouse Button
- Use the tool shown here to view and select different layers
- <img width="262" height="173" alt="image" src="https://github.com/user-attachments/assets/5c0098a8-7e3f-4db0-b0b6-25ed41e1a063" />


### Editing Part Placement on PCB

- Click on part to drag it
- You can rotate the part by pressing the spacebar while clicking/dragging the component
- You can switch the component between top and bottom layers by toggling the L key while selecting the component
- HIGHLY HIGHLY suggest placing all the parts before you start connecting them
- Don’t worry if the gray lines are intersecting; traces can be drawn around them if needed
- You can move parts around after you start connecting them if needed, just have a general idea of where they will all be on the board

### Traces

- Route -> Interactive Routing to place the trace
- Make sure you know which layer of the board you are on
    - We are using a two layer so the only two layers traces should be on are “Top Layer” and “Bottom Layer”
- Can adjust layer of trace after placing on board by double clicking on the trace -> Layer -> Select Layer
- Once you see a larger circle around your pointer you know you’ve established an electrical connection
- Trace Guidelines are provided at end of presentation

### Layers To Worry About

- Top Layer - Top of the board electrical connections
- Bottom Layer - Bottom of the board for electrical connections
- Top Overlay - Your silkscreen for the top layer, can edit labels and add any text
- Bottom Overlay - Your silkscreen for the bottom layer, can edit labels and add any text
- You will use Mechanical 1, Keep Out and a couple of other layers later, but don’t worry about them right now

### Polygon Pour

- Can be used to remove the need for too many traces all over the board
- A pour that is usually used is a GND over the entire bottom layer
- For example, if you add a Polygon pour for the GND net for the entire bottom layer, then all components that have GND pins in the bottom layer will all be connected and you do not need traces to connect them
- Place -> Polygon pour
- Under Net Options, select the net you’d like to connect to
    - The net should have been defined in your schematic
- Under Properties, select the layer you’d like this pour to be on
- Click okay, and click around until you are satisfied with the shape, then click “Esc” to have your pour
    - You can adjust dimensions of the pour later if need be.

### Design Rule Check

- Ensure you are achieving mechanical specs set by the manufacturer based on the fidelity of their equipment
- To edit a Design Rule, click Design -> Rules
- On the left bar, search the different sections till you find the specific rule you need to change (most rules are under Manufacturing)
    - Can double click to edit
- Enter the value (and units) that is specified and click “Apply” followed by “OK”
    - Values to edit are above the diagram in blue
- Once you have all rules edited per the guidelines, click on Tools -> Design Rule Check to run the DRC
    - Click on Run Design Rule Check on bottom left
- You need ZERO errors before you can manufacture the design, we will require it as part of your final submission

### Trace Width Guidelines

- Power lines to the input of the LDO’s = 30 mil
- Output of LDO’s to electrolytic capacitors and Status LED’s = 25 mil
- All other traces = 15 mil
- NOTE: The other traces can be thinner if needed, but keep the power lines as thick as possible to ensure excessive current doesn’t burn them off.

### Design Rules

- All below are minimum values
- 6 mil trace clearance (minimum solder mask sliver)
- 6 mil trace width
    - Under Routing
- 13 mil drill size (hole size)
- 7 mil annular ring
    - You might need to create a New Rule for this one

## Submission

On Canvas, you will submit ***ONE PDF*** that will include all of the following:

- [ ] A screenshot of the schematic you made
- [ ] A screenshot of the PCB you made (**Both sides**)
- [ ] Screenshot(s) of the PCB passing all design rule checks

Export/Download this document as a PDF and upload it. **DO NOT SUBMIT A GOOGLE DOC FILE**.

<div class="primer-spec-callout danger" markdown="1">
Submitting anything other than a single PDF may result in your work not being graded or your scores being heavily delayed.
</div>
