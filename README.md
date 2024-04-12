# Hexapod Robot

The source code of a hexapod robot created with Arduino based libraries on a Esp32 Microcontroller. 

It can be controlled using the app created with the <a href="https://github.com/edw-lee/HexapodApp">Hexapod App</a>.

The movement algorithm is based on the <a href="https://github.com/edw-lee/HexapodSimulator">Hexapod Simulator</a> with some modifications.

### Libraries

* Arduino Esp32
* Adafruit_PWMServoDriver

### Hardwares

* Microcontroller: Esp32
* Servo controller: PCA9685 (2 boards, 3 legs (9 servos) per board)
* Legs: 6 (18 servos in total, 3 per leg (3DOF))
* Servo brand: TowerPro MG90s
* Battery: 7.4v 2600mah Li-Po
* Step-Down Converter: LM2596 (Set to 6v)


### Circuit Diagram

![Hexapod Circuit Diagram](/pictures/circuit.png)
* The pins to the servos' PWM input can be changed in the Hexapod class initLegs() function in the [Hexapod.cpp file](/src/Hexapod.cpp) .

### Build Diagrams

* No dimensions are provided in the diagrams as it might not be accurate for different hardwares used.
* These diagrams are for references only. Feel free to get creative with the design.
* My real build for this hexapod was recycled to reuse the parts for version 2. Hence, the lack of real pictures of the Hexapod.
* Material used: Plywood

<img src='/pictures/Leg-ExplodedView.png' width=800>

<img src='/pictures/Leg-Assembled.png' width=800>

<img src='/pictures/Body-ExplodedView.png' width=800>

<img src='/pictures/Body-Assembled.png' width=800>

<img src='/pictures/Hexapod-Full.png' width=800>
