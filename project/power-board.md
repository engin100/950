---
layout: spec
latex: true
---

# Powerboard Assembly Guide

<div class="primer-spec-callout danger" markdown="1">
While you could grab all components at once then get to soldering, it is best to grab the components ONE at a time, so that things don't get lost or mixed up.
</div>

## Procedure
1. Take your PCB and solder on your 3v3 LDO.

   <div class="primer-spec-callout danger" markdown="1">
   Double and triple check that you 3v3 LDO is in the correct spot and is not in the 5v LDO spot. Have an instructor check after you finish this step.
   </div>

![Step 1](/media/powerboard-guide-figures/power-board-3v3.jpeg)

2. Next, solder on your 5v LDO.
![Step 2](/media/powerboard-guide-figures/power-board-5v.jpeg)

3. Now, solder the two 1uF capacitors. **Note that they go on the left of the LDOs**
![Step 3](/media/powerboard-guide-figures/power-board-1uf.jpeg)

4. Solder the two 4.7uF capacitors on the other side of the LDOs:
![Step 4](/media/powerboard-guide-figures/power-board-47uf.jpeg)

Now, you can choose whether to add the surface mount LED or through hole LED. Since they
both indicate battery power, there is no need to have both on the board. You can also
choose to have the SMD installed on the board and then run wires from the through hole out
to an LED visible from the outside of your payload.

5. If you chose to install the surface mount LED, solder both the surface mount LED and resistor.
![Step 5](/media/powerboard-guide-figures/power-board-smd-led.jpeg)

6. If you chose to install the through hole LED, solder both the through hole LED and
   resistor. **Note that this photo has the power connector installed, ignore this until
   the step that asks you to install it.**
![Step 6](/media/powerboard-guide-figures/power-board-tht-led.jpeg)

7. Next, solder the diode. Be careful bending the leads on the diode since they're thick
   and potentially easy to break.
![Step 7](/media/powerboard-guide-figures/power-board-diode.jpeg)

8. Solder the RBF jack:
![Step 8](/media/powerboard-guide-figures/power-board-rbf.jpeg)

9. Finally, solder the power connector, insert your RBF plug, and you have a functioning
   power board!
![Step 9](/media/powerboard-guide-figures/power-board-complete.jpeg)

<div class="primer-spec-callout danger" markdown="1">
Have an instructor check your board and test it before moving on.
</div>

The final step before you can use your power board to supply your payload PCB is to solder
the 4-pin header. How this is done will depend on how you designed your PCB to fit the
power board, so it is recommended to wait until your main PCB is soldered to test fit and
solder the pin header.