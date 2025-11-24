# Boids 🐦🐦🐦
This project was created as homework for MP01: *The Language of C++*.  
A simple interactive implementation of the Boids algorithm, written in C++ and developed with Visual Studio.  
It simulates flocking behavior and allows user interaction such as adding birds and moving the nest.

---

## 📌 Contents
- [Usage](#usage)
- [Boids Rules](#boids-rules)
  - [Separation](#separation)
  - [Alignment](#alignment)
  - [Cohesion](#cohesion)
  - [Home Seeking](#home-seeking)
- [Configuration](#configuration)

---

## Usage

### 🐧 Add new birds
Left-click anywhere in the window to add new boids.
<div align="center">
  <img src="./add.gif" alt="add_bird_demo" width="50%">
</div>


---

### 🏠 Drag the nest
Click and drag the nest to move its location.  
Boids will adjust their behavior and gradually move toward the new target.
<div align="center">
  <img src="./drag.gif" alt="drag_bird_demo" width="50%">
</div>

---

## Boids Rules

The Boids algorithm (Craig Reynolds, 1987) models flocking behavior using three simple local rules.  
Each boid adjusts its velocity based on nearby neighbors.

---

### **Separation**
Avoid crowding and collisions by steering away from neighbors that are too close.

$$
a_{\text{separation}}[B \leftarrow B'] = k_s (B.\text{position} - B'.\text{position})
$$

---

### **Alignment**
Steer toward the **average heading and velocity** of nearby boids.

$$
v = \frac{1}{N} \left( B_1' \text{ speed} + \ldots + B_N' \text{ speed} \right)
$$
$$
a_{\text{alignment}} = k_a (v - B.\text{speed})
$$

---

### **Cohesion**
Move toward the **center of mass** of neighbors.

$$
c = \frac{1}{N} \left( B_1' \text{ position} + \ldots + B_N' \text{ position} \right)
$$

$$
a_{\text{cohesion}} = k_c (c - B_1' \text{ position})
$$

---

### **Home Seeking**
Boids are gently attracted toward a special point called the **nest**.

$$
\vec{v}_{\text{target}} = k_t \frac{(T.\text{position} - B.\text{position})}{\||T.\text{position} - B.\text{position}\||}
$$

---


### ⚙️ Configuration
Modify simulation parameters in `configs.h`:

- Separation / Alignment / Cohesion weights
- Maximum velocity
- Have a Home or not
- Home-seeking strength  
- Initial number of boids  
...
