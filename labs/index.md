---
layout: spec
toc: false
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

# Labs

As we publish labs, they will become available here.

## Lab 1: Arduino 101

Learning how to program and wire an Arduino micro-controller to control LEDs on a breadboard.

[Link to lab 1](/labs/lab-1)

### Lab 1b: Creating an Altium Schematic

Learning how to produce a PCB schematic in Altium.

[Link to lab 1b](/labs/lab-1b)

## Lab 2: Temperature Sensing

Using our Arduino and circuitry knowledge to read data from a temperature sensor and plot it in real-time.

[Link to lab 2](/labs/lab-2)

## Lab 3: Creating a Standalone Circuit and Adding Sensors

Saving Arduino sensor data to a microSD card so that we can use it later, and powering an Arduino with a battery. Additionally, adding more sensors such as pressure, acceleration, and humidity sensors.

:warning: This *may* come in handy when launching our weather balloons...

- [Link to lab 3 - START HERE](/labs/lab-3)
- [Link to lab 3 - Group A](/labs/lab-3GroupA)
- [Link to lab 3 - Group B](/labs/lab-3GroupB)

## Lab 4: Power and Calibrations

Creating a voltage regulating circuit to handle the power from the battery, and calibrating our complete circuit with known values.

[Link to lab 4](/labs/lab-4)

## Lab 5: Adding GPS

Adding a digital GPS component to our Arduino breadboard circuit.

[Link to lab 5](/labs/lab-5)

## Lab 6: Structures

Design and testing of your custom payload structures.

[Link to lab 6](/labs/lab-6)

### Lab 7 Prelab: Altium Schematic to PCB

Finishing up postlab 1b to turn the schematic into a finished PCB.


[Link to Lab 7 Prelab](/labs/lab-7-prelab)


## Lab 7: Altium

Moving away from the breadboards and creating a custom PCB (Printed Circuit Board) using Altium software.


[Link to lab 7](/labs/lab-7)

## Project
[Powerboard assembly guide](/project/power-board)