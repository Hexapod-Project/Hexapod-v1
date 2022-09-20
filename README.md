# Hexapod Robot

The source code of a hexapod robot created with Arduino based libraries on a Esp32 Microcontroller. 

It can be controlled using the app created with the <a href="https://github.com/edw-lee/HexapodControllerApp">Hexapod Controller App</a>.

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

* To Be Added.
