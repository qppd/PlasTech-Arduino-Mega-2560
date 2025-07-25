
<h1 align="center">♻️ PlasTech RVM - Arduino Mega 2560</h1>

<p align="center">
  <b>Smart Reverse Vending Machine (RVM)</b><br>
  Built using <b>Arduino Mega 2560</b> to collect, detect, and sort recyclable bottles.<br>
  Designed by <a href="https://github.com/qppd">QPPD</a> for smart waste management in the Philippines.
</p>

<br>

<p align="center">
  <img src="https://img.shields.io/badge/platform-Arduino--Mega2560-blue?style=flat-square" alt="Platform">
  <img src="https://img.shields.io/badge/status-Active-brightgreen?style=flat-square" alt="Status">
  <img src="https://img.shields.io/github/license/qppd/PlasTech-Arduino-Mega-2560?style=flat-square" alt="License">
</p>

---

## 🔧 Features

- 🚮 **Detects plastic bottles** using IR sensors and capacitive proximity sensors.
- 📦 **Sorts items** with servo-controlled doors and compartments.
- 💡 **LED indicators** for feedback (Ready, Success, Error).
- 🧠 **Credit system** (expandable for point-based rewards).
- 🖥️ Designed for integration with an LCD or touchscreen for user interaction.

---

## 🧩 Hardware Components

| Component               | Description                           |
|------------------------|---------------------------------------|
| Arduino Mega 2560      | Main microcontroller                  |
| IR Sensor (TCRT5000)   | Bottle detection                      |
| Capacitive Sensor      | Plastic detection                     |
| Limit Switch           | Start trigger                         |
| MG996R Servo Motor     | Opens/closes compartment              |
| 2N2222 Transistors     | Drives high-current LEDs              |
| 2-Channel Relay Module | Powers servo & other peripherals      |
| LED Indicators         | Shows status (Red, Green)             |
| Push Button            | Manual override (optional)            |

---

## 🗂️ File Structure

```
PlasTech-Arduino-Mega-2560/
├── /PlasTech_RVM/        # Main Arduino sketch folder
│   ├── PlasTech_RVM.ino  # Main sketch file
│   └── modules/          # Modular code for cleaner structure
├── LICENSE
└── README.md
```

---

## 🚀 Getting Started

1. **Install the Arduino IDE**:  
   https://www.arduino.cc/en/software

2. **Clone this repository**:
   ```bash
   git clone https://github.com/qppd/PlasTech-Arduino-Mega-2560.git
   ```

3. **Connect your components** using the pin mappings in `PlasTech_RVM.ino`.

4. **Upload the sketch** to your Arduino Mega 2560.

5. **Power the system** and test the full bottle detection flow.

---

## 📸 System Overview

<p align="center">
  <img src="https://via.placeholder.com/700x400.png?text=PlasTech+RVM+Hardware+Overview" alt="System Diagram">
</p>

---

## 📌 Pin Assignments (Sample)

| Arduino Pin | Connected Component         |
|-------------|-----------------------------|
| D2          | IR Sensor Output            |
| D3          | Limit Switch (Start)        |
| D4          | RED LED (via 2N2222)        |
| D5          | GREEN LED (via 2N2222)      |
| D6          | Servo Signal (MG996R)       |
| D7          | Relay IN1 (Servo power)     |
| D22         | Capacitive Sensor Digital   |

---

## 🧠 Future Features

- Firebase integration for real-time data sync  
- LCD/touchscreen interface for better UX  
- GSM module for remote monitoring  
- Coin/point dispensing mechanism  

---

## 🤝 Contribution

We welcome pull requests and ideas from the community!  
Fork the repo → create a new branch → submit a PR.

---

## 📄 License

This project is licensed under the MIT License.  
See [`LICENSE`](./LICENSE) for more info.

---

<p align="center">
  Built with ❤️ by <a href="https://github.com/qppd">QPPD</a> | Quezon Province, Philippines
</p>
