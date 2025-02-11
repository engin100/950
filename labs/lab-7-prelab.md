---
layout: spec
latex: true
---

# Lab 7 Prelab: Altium Schematic to PCB

## Contents 

- [Lab 6 Prelab: Altium Schematic to PCB](#lab-6-prelab-altium-schematic-to-pcb)
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

- [ ] A CAEN computer, or a computer running UofM VMWare to access Altium software.
- [ ] [Altium libraries .zip file](https://drive.google.com/file/d/1JMCNjsRCwUEqwYapCFaCCkwo2zHAycD3/view?usp=drive_link) (you will need to unzip before using)
- [ ] [Spreadsheet of Footprints](https://drive.google.com/file/d/1tsC8cM-wiYfIB25BBM7o7ymhQ4F3gtD8/view?usp=sharing)
- [ ] [Second Spreadsheet of Footprints](https://drive.google.com/file/d/1LVTbnMMa6W0KI2mwZwTfUbNu1QJWeqjq/view?usp=sharing)

## Procedure

This prelab begins where Postlab 1b ends, at the transition from schematic to PCB! If you have not already made the schematic, you need to do so before proceeding through PCB design as we will be using that schematic for this procedure.

### Onwards and Upwards (Upwards = to PCB Design)

- Save your PCB (it will ask you to rename the file)
- Go to your PCB document (.PcbDoc)
- Design -> Import Changes from (..)
- Under “Add Rooms”, untick the Add box
- Click Execute Changes
- Click Close
- Component footprints should appear on the screen
    - They will appear to the left of the board, you can drag across the screen by holding down on right click and moving your mouse
- Now the fun begins!

### PCB General View and Sizing

- Pressing 1 will show the board size and shape
    - Can use to adjust the dimensions of the board
    - Design -> Edit Board Shape
- Pressing 2 will show the board and components as a 2-D model
    - Ideal for actually building your PCB
- Pressing 3 will show the board and components as a 3-D model
    - Ideal for getting a visual idea of how your PCB will look
    - Not ideal for actually moving parts and traces
    - Can use a combination of Ctrl and Shift keys along with the mouse to investigate the board further

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
- A pour that is usually used is a GND or 5V over the entire top or bottom layer
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

- [ ] A screenshot of the PCB you made
- [ ] Screenshot(s) of the PCB passing all design rule checks

Export/Download this document as a PDF and upload it. **DO NOT SUBMIT A GOOGLE DOC FILE**.

<div class="primer-spec-callout danger" markdown="1">
Submitting anything other than a single PDF may result in your work not being graded or your scores being heavily delayed.
</div>