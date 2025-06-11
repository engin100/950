---
layout: null
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

# Course Staff

Below you can meet the instructors and instructional aides who run ENGR 100-950.

<style>
.staff-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
  gap: 20px;
}
.staff-member {
  text-align: center;
  padding: 1em;
  border: 1px solid #ddd;
  border-radius: 4px;
}
.staff-member img {
  width: 150px;
  height: 150px;
  object-fit: cover;
  border-radius: 50%;
  background: #f0f0f0;
  margin-bottom: 10px;
}
</style>

<div class="staff-grid">
  <div class="staff-member">
    <img src="{{ '/media/ridley.png' | relative_url }}" alt="Prof. Aaron Ridley portrait">
    <h3>Prof. Aaron Ridley</h3>
    <p>Technical lead</p>
    <p><a href="mailto:ridley@umich.edu">ridley@umich.edu</a></p>
    <p>Office: 1416 CSRB</p>
  </div>
  <div class="staff-member">
    <img src="{{ '/media/alanhogg.png' | relative_url }}" alt="Dr. Alan Hogg portrait">
    <h3>Dr. Alan Hogg</h3>
    <p>Communication Instructor - lead</p>
    <p><a href="mailto:alanhogg@umich.edu">alanhogg@umich.edu</a></p>
    <p>Office: GFL</p>
  </div>
  <div class="staff-member">
    <img src="{{ '/media/davidgrs.png' | relative_url }}" alt="Dr. David Greenspan portrait">
    <h3>Dr. David Greenspan</h3>
    <p>Communication Instructor - lead</p>
    <p><a href="mailto:davidgrs@umich.edu">davidgrs@umich.edu</a></p>
    <p>Office: GFL</p>
  </div>
  <div class="staff-member">
    <img src="{{ '/media/hbarnard.png' | relative_url }}" alt="Hannah Barnard portrait">
    <h3>Hannah Barnard</h3>
    <p>Instructional Aide</p>
    <p><a href="mailto:hbarnard@umich.edu">hbarnard@umich.edu</a></p>
    <p>Office: 1210 CSRB</p>
  </div>
  <div class="staff-member">
    <img src="{{ '/media/zianren.png' | relative_url }}" alt="Zian (Sam) Ren portrait">
    <h3>Zian (Sam) Ren</h3>
    <p>Instructional Aide</p>
    <p><a href="mailto:zianren@umich.edu">zianren@umich.edu</a></p>
    <p>Office: 1210 CSRB</p>
  </div>
  <div class="staff-member">
    <img src="{{ '/media/jfwoods.png' | relative_url }}" alt="Jack Woods portrait">
    <h3>Jack Woods</h3>
    <p>Instructional Aide</p>
    <p><a href="mailto:jfwoods@umich.edu">jfwoods@umich.edu</a></p>
    <p>Office: 1210 CSRB</p>
  </div>
  <div class="staff-member">
    <img src="{{ '/media/benjamen.png' | relative_url }}" alt="Ben Miller portrait">
    <h3>Ben Miller</h3>
    <p>Instructional Aide</p>
    <p><a href="mailto:benjamen@umich.edu">benjamen@umich.edu</a></p>
    <p>Office: 1210 CSRB</p>
  </div>
</div>
