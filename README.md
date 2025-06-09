# Car-Black-Box
# 🚗 Car Black Box Project using PIC18F4580

This project implements a prototype of a **Car Black Box** using the **PIC18F4580** microcontroller. Much like an airplane's black box, this device records critical data such as speed, impact, and GPS location, which can be used for post-accident analysis and diagnostics.

## 📦 Features

- ⚠️ Impact detection using accelerometer
- 🕒 Real-time clock for timestamping (via I2C RTC module)
- 💾 Data logging to EEPROM
- 📊 CLCD display for status
- 🔌 UART interface for data retrieval

## 🧰 Hardware Requirements

- PIC18F4580 microcontroller
- Potentiometer(TO access the speed using ADC)
- RTC module (DS1307) 
- EEPROM
- CLCD display
- Power supply

## 🧑‍💻 Software Requirements

- MPLAB X IDE
- XC8 Compiler
- Teraterm

## ⚙️ Functionality Overview

| Component      | Function                          |
|----------------|-----------------------------------|     
| Potentioometer | Detects Speed                     |
| RTC Module     | Provides timestamps               |
| EEPROM         | Stores events                     |
| CLCD Display   | Shows current status              |
| Switches       | To Select options                 |

1) **```DASHBOARD```**
**```CLCD DISPLAY```**

|```Event```| ```Speed```| ```Time```|
|-----------|------------|-----------|
|   O       |    20      |  1.15     |
|   GR      |     -      |    -      |
|   GN      |     -      |    -      |
|   G1      |     -      |    -      |
|   G2      |     -      |    -      |
|   G3      |     -      |    -      |
|   G4      |     -      |    -      |
| Collision |     -      |    -      |

2)**```Enter Password```**

3)**```Menu```**
 |           |               |
 |-----------|---------------|
 | ```3.1``` | -> View Log   |
 | ```3.2``` | Download Log  |
 | ```3.3``` | Clear Log     |
 | ```3.4``` |  Set Time     |
 | ```3.5``` |Change Password|
 | ```3.6``` |  Clear Log    |
  
**```Storing Events```**
Steps:

1)Storing Speed
* we are accessing the speed from the potentiometer by using ADC.
* We are receiving the analog value from potentiometer.
* 
2)Time
* To get the time we are using RTC.
* To read the time from the RTC, we are using protocol I2C.

3)EEPROM
* Whenever the change in the gear or change in the collision we are stroing the event,speed,time inEEPROM.
* For 1 log we are storing event,time,speed.
* Here we are stroing 10logs in EEPROM,if new event occurs just overwriting the old event becauuse limited space in EEPROM.

  
## 🗂️ Project Structure
1. Open the project in **MPLAB X**.
2. Compile using **XC8 compiler**.
3. Flash the hex to your **PIC18F4580** using a programmer.
4. Connect modules as per the schematic
5. Power up the system and monitor CLCD for live status.

