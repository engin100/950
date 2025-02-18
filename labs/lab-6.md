---
layout: spec
latex: true
---

# Lab 6: Structures

## Contents 
- [Lab 6: Structures](#lab-6-structures)
  - [Contents](#contents)
  - [Materials](#materials)
  - [Temperature](#temperature)
  - [Accelerometer](#accelerometer)
  - [Submission](#submission)

## Materials

- [ ] 3 different types of insulation
- [ ] Finished Breadboard
- [ ] Battery Pack
- [ ] 1 Box

## Temperature

For the temperature trials we will use the cold chamber to simulate the temperatures that your PCB will endure in the upper-atmosphere. You will use three different materials as insulation for your preliminary structures. When you have sufficiently insulated your breadboard you will attach your battery and place it into the cold chamber. Make sure that you are writing data to the SD as fast as possible; you will take data for about 4 minutes and plot each trial on the same graph. 

Using 3 different insulations at your disposal (possibilities include hard foam, cotton balls, fluff, etc...) complete the following steps three times, once for each material.

- Insulate your box, ensuring the insulation covers all sides of the breadboard.

- Attach the battery to your breadboard and, using your previously written programs, record TMP36 data on your SD for 4 minutes.

- Plot the data and make sure the TMP36 reaches a constant temperature. If it doesn't, repeat the trial for a longer period of time.

<div class="primer-spec-callout info" markdown="1">
After you've completed 3 trials, you will plot all three data sets on the same graph, making sure to label each line appropriately (legends!). Add the plot to your post-lab questions doc at the end.
</div>

## Accelerometer

For the accelerometer trials you will be carefully dropping your payload from chest height. This will (somewhat) simulate the turbulence that your PCB will encounter throughout its flight. You will again complete 3 trials, once each for your different materials as padding. Make sure that your breadboard has sufficient padding on all sides, and that you are dropping it in a way that the wires are facing up when it hits the ground. Ensure you are writing data to the SD as fast as possible, and you will be recording data for the duration of the drop.

<div class="primer-spec-callout warning" markdown="1">
Writing data to the SD card as fast as possible is considerably more important for these trials involving the accelerometer. When we use the accelerometer in conjunction with the BME680, and our slew of other sensors, the sampling speed of our Arduino is significantly decreased. You may want to consider utilizing a simpler program for these trials focusing on writing accelerometer data to the SD card to get the fastest sample speed possible.
</div>

Repeat these steps once for each material:

- Add the padding to your box, ensuring you have coverage on all sides of the breadboard.

- Attach your battery to the breadboard and, using your previously written programs, record accelerometer data on your SD card for the duration of the drop.

- Plot the data on separate graphs, and add the plots into your post-lab questions doc at the end.

## Submission

On Canvas, you will submit ***ONE PDF*** that will include all of the following:

- [ ] Using your gathered data, what would you use to insulate/protect your payload (a combination of materials is allowed if their combination is functional and realistic)? Explain why!
- [ ] All three TMP36 trials for the three insulations plotted on 1 plot. Include labels for each axis, and label the three lines as each trial respectively. Make sure to include which trial is for which insulation in the caption/legend.
- [ ] 3 accelerometer plots, one for each trial. Make sure to include appropriate labels for each plot.

To put said content into a PDF, it is suggested you create a new Google Doc ([docs.new](https://docs.new)) and paste your images and write any text in the document. Export/Download this document as a PDF and upload it. **DO NOT SUBMIT A GOOGLE DOC FILE OR SPREADSHEET FILES.**

<div class="primer-spec-callout danger" markdown="1">
Submitting anything other than a single PDF may result in your work not being graded or your scores being heavily delayed.
</div>