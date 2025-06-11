---
layout: spec
latex: true
---

<style>
  body {
    margin: 0;
    font-family: Arial, sans-serif;
    padding-top: 70px;
  }
  .navbar {
    background-color: #00274C;
    overflow: hidden;
    position: fixed;
    top: 0;
    width: 100%;
    z-index: 1000;
    display: flex;
    align-items: center;
    padding: 10px 0;
    transition: padding 0.3s;
  }
  .navbar.shrink {
    padding: 4px 0;
  }
  .navbar img.logo {
    height: 50px;
    margin-left: 10px;
    transition: height 0.3s;
  }
  .navbar.shrink img.logo {
    height: 30px;
  }
  .navbar ul {
    margin: 0;
    padding: 0;
    list-style: none;
    display: flex;
    margin-left: auto;
    justify-content: flex-end;
  }
  .navbar li {
    position: relative;
  }
  .navbar a {
    display: block;
    color: #FFCB05;
    padding: 14px 20px;
    text-decoration: none;
    font-weight: bold;
  }
  .navbar li:hover > a {
    background-color: #001d38;
  }
  .dropdown-content {
    display: none;
    position: absolute;
    background-color: #00274C;
    min-width: 160px;
    z-index: 1;
  }
  .dropdown-content li { width: 100%; }
  .dropdown-content a { padding: 12px 16px; }
  .dropdown:hover .dropdown-content { display: block; }

  @media (max-width: 600px) {
    .navbar { flex-direction: row; align-items: center; }
    .navbar img.logo { display: none; }
    .nav-links { flex-direction: row; width: auto; display: flex; }
    .navbar li { width: auto; }
    .navbar a { padding: 10px; }
    .dropdown-content { display: none; }
  }
</style>

<nav class="navbar">
  <img class="logo" src="{{ '/media/umich-coe3.png' | relative_url }}" alt="University of Michigan, College of Engineering">
  <ul class="nav-links">
    <li class="dropdown"><a href="{{ '/syllabus' | relative_url }}">Syllabus</a>
      <ul class="dropdown-content">
        <li><a href="https://calendar.google.com/calendar/u/0?cid=dW1pY2guZWR1X3FranB0bnZjNGs5MXA0dDQ4dXExOGFoNWNzQGdyb3VwLmNhbGVuZGFyLmdvb2dsZS5jb20">Course Calendar</a></li>
      </ul>
    </li>
    <li class="dropdown"><a href="{{ '/labs/' | relative_url }}">Labs</a>
      <ul class="dropdown-content">
        <li><a href="{{ '/soldering/solder-challenge' | relative_url }}">Solder Challenge</a></li>
        <li><a href="{{ '/project/project' | relative_url }}">Project Spec</a></li>
      </ul>
    </li>
    <li><a href="{{ '/project/project' | relative_url }}">Project</a></li>
    <li><a href="{{ '/staff' | relative_url }}">Staff</a></li>
    <li><a href="{{ '/facilities' | relative_url }}">Facilities</a></li>
  </ul>
</nav>
<script>
window.addEventListener('scroll', function() {
  var navbar = document.querySelector('.navbar');
  if (window.scrollY > 50) {
    navbar.classList.add('shrink');
  } else {
    navbar.classList.remove('shrink');
  }
});
</script>

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

5. Your extra sensor and its characteristics

6. System-level block diagram - Very much like your schematic, but simplified and with connections (5V, 3.3V, analog, digital)

7. PCB design. This should have some sort of indication of the size of the PCB. Pull from Altium; photo of actual PCB.

8. Preliminary structure design with some list of materials that you will need.

9. How your design was shaped by the requirements.

10. A data budget - spreadsheet!

11. A power budget - spreadsheet!

12. A mass budget - spreadsheet!

13. Testing strategies that you have come up with.

14. Any test results that you have at this point.


## Go / No-Go Tests

In order to launch, your board needs to pass the following tests:

1. Power on test - demonstrate that you can turn on the payload without opening the box.

2. Data collection test - collect data continuously for 2+ hours.

3. GPS test (aka Blue Bus Test) - take package on a bus (car/bike); show that you can track payload for at least an hour; Google Map needs to show route.
   
4. Shock test - fling your package, and it needs to continue to operate through test. Must show high-resolution (total) accelerometer data vs time. Should upload new code to Arduino for this (and next) test.
  
5. Stair test - kick your package down the stairs - high-resolution accelerometer data vs time.

6. Cold test - your package has to run for 2 hours at -40C. Must show internal and external temperatures vs time.

7. Elevator test - Find building that is at least 10 floors.  Place payload on floor of elevator. ascend all 10 floors, stopping twice at different floors. Show pressure converted to altitude vs time + acceleration vs time.


