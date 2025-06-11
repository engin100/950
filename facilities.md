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

  .facilities {
    max-width: 1000px;
    margin: 60px auto;
    padding: 0 20px;
    color: #00274C;
  }
  .facility-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
    gap: 20px;
  }
  .facility-card {
    background-color: #f7f7f7;
    border-radius: 8px;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
    overflow: hidden;
    text-align: center;
  }
  .facility-card img {
    width: 100%;
    height: 180px;
    object-fit: cover;
  }
  .facility-card h3 {
    margin: 0.5em 0;
    color: #00274C;
  }
  .facility-card p {
    padding: 0 10px 20px;
  }

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

# Facilities

<section class="facilities">
  <p>Below is a brief overview of the laboratory spaces available for ENGR100-950.</p>
  <div class="facility-grid">
    <div class="facility-card">
      <img src="https://via.placeholder.com/400x300?text=Soldering+Lab" alt="Soldering Lab">
      <h3>Soldering Lab</h3>
      <p>Workstations equipped with soldering irons and fume extractors for building circuits.</p>
    </div>
    <div class="facility-card">
      <img src="https://via.placeholder.com/400x300?text=Computer+Lab" alt="Computer Lab">
      <h3>Computer Lab</h3>
      <p>High performance machines with the software you need for coding and PCB design.</p>
    </div>
    <div class="facility-card">
      <img src="https://via.placeholder.com/400x300?text=Research%2FDesign+Lab" alt="Research and Design Lab">
      <h3>Research/Design Lab</h3>
      <p>Space for prototyping and sensor testing as you iterate on your balloon payload.</p>
    </div>
    <div class="facility-card">
      <img src="https://via.placeholder.com/400x300?text=Construction+Lab" alt="Construction Lab">
      <h3>Construction Lab</h3>
      <p>Tools and materials for building and assembling the final flight hardware.</p>
    </div>
  </div>
</section>

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
