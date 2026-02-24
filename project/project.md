---
layout: spec
toc: false
latex: true
---
# Project Guidelines

## Project Specification

The goal of this semester's project is to:

1. Build a sensor package that will ascend to approximately 100,000 ft altitude that will measure:
- outside temperature
- inside temperature
- outside humidity
- ambient atmospheric pressure
- acceleration of the package in 3 dimensions
- location of package
- speed of the package

2. The sensor package must work over the entire time of the flight (ascent and descent). 

3. The complete package attached to the payload train must be less than 1 lb in weight.

4. The sensor package must be able to be turned on without opening the payload.

5. The payload must indicate that it is working without opening the payload.

6. The team must prove that their payload will meet requirements.

7. Conduct analysis of all of their data.

## Preliminary Design Review

The preliminary design review should cover the following topics:

1. Team name with a logo

2. Science question or topic

3. Requirements that are levied because of science and class

4. Requirements flowdown chart

5. System-level block diagram - Very much like your schematic, but simplified and with connections (5V, 3.3V, analog, digital)

6. PCB design. This should have some sort of indication of the size of the PCB. Pull from Altium; photo of actual PCB.

7. Preliminary structure design with some list of materials that you will need.

8. How your design was shaped by the requirements.

9. A data budget - spreadsheet!

10. A power budget - spreadsheet!

11. A mass budget - spreadsheet!

12. Testing strategies that you have come up with.

13. Any test results that you have at this point.

## Go / No-Go Tests

In order to launch, your board needs to pass the following tests:

1. Power on test - demonstrate that you can turn on the payload without opening the box.

2. Data collection test - collect data continuously for 2+ hours.

3. GPS test (aka Blue Bus Test) - take package on a bus (car/bike); show that you can track payload for at least an hour; Google Map needs to show route.
   
4. Shock test - fling your package, and it needs to continue to operate through test. Must show high-resolution (total) accelerometer data vs time. Should upload new code to Arduino for this (and next) test.
  
5. Stair test - kick your package down the stairs - high-resolution accelerometer data vs time.

6. Cold test - your package has to run for 2 hours at -40C. Must show internal and external temperatures vs time.

7. Elevator test - Find building that is at least 10 floors.  Place payload on floor of elevator. ascend all 10 floors, stopping twice at different floors. Show pressure converted to altitude vs time + acceleration vs time.


## EXTRAS

15 points are mandatory, but you can do up to 30 points (where 15 points would then be extra credit).

1. Extra LEDs:
- GPS Fix (can be right off GPS) - 1 point
- SD Card Detect (can be off sd card writer) - 1 point
- GPS in balloon mode (digital pin) - 2 points 
- Data being taken (eg, in the loop turn LED on and off - digital pin)  - 2 points
2. Put (all) LEDs and TMP36 on PCB outside of payload: 5 points
3. Smaller PCB (points go up as PCB gets smaller): (16sqin - area)/2 points (5 max)
4. Mass of payload (points go up as mass goes down): (16oz - weight)/2 points (5 max)
5. Style points for design (class votes on each): 1-5 points
6. Better timing for taking data (not "just" 1s data): 1-5 points, depending on complexity
7. Above and beyond data analysis: 1-5 points, depending on complexity (e.g. Skew-T diagram, plots of GPS satellite locations, etc.) 
8. Individual / Team Video: 10 points for 2 minutes / person
