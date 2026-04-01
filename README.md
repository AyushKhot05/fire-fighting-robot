# 🔥 Fire Fighting Robot (Arduino)

An autonomous Arduino-based fire-fighting robot that detects fire using multiple flame sensors and extinguishes it using a water pump and servo-controlled mechanism.

---

## 📌 Overview

This project demonstrates a simple yet effective fire detection and suppression system using Arduino.  
The robot continuously monitors its surroundings using flame sensors and automatically moves toward the fire source to extinguish it.

---

## ⚙️ Features

- 🔥 Multi-directional fire detection (Left, Center, Right)
- 🚗 Autonomous movement towards fire
- 💧 Automatic water spraying system
- 🎯 Servo-based directional control for accurate targeting
- ⚡ Real-time response without human intervention

---

## 🛠️ Components Used

- Arduino Uno  
- Flame Sensors (3x)  
- L298N Motor Driver  
- BO Motors & Wheels  
- Relay Module  
- Water Pump  
- Servo Motor  
- Breadboard & Jumper Wires  
- Power Supply  

---

## 🧠 Working Principle

1. The flame sensors continuously detect infrared radiation from fire.
2. Based on sensor values, the robot determines the direction of fire.
3. Motors drive the robot toward the detected fire source.
4. Once close, the robot stops and activates the water pump.
5. The servo motor sweeps to spread water and extinguish the fire.

---

## 📂 Project Structure
fire-fighting-robot/
│── fire_robot.ino
│── README.md
│── images/
│── docs/

## 🖼️ Project Images
![Robot](images\Robot.png)
![Circuit Diagram](images\Circuit Diagram.jpg)

---

## 📄 Documentation

This project also includes a detailed study and analysis of the system.

👉 Research Paper:  
[View PDF](docs\fire-fighting-robot-research-paper.pdf)

---

## 🚀 Future Improvements

- Add obstacle avoidance system  
- Integrate wireless control (Bluetooth/WiFi)  
- Improve fire detection accuracy  
- Add temperature and gas sensors  

---

## 👨‍💻 Author

**Ayush Khot**

---

## ⭐ If you like this project

Give it a ⭐ on GitHub and feel free to explore or improve it!