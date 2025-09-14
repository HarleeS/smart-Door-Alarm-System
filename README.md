# Smart-Door-Alarm-System


## Project purpose
This project demonstrates a simple IoT-enabled door alarm system using an Arduino Uno, PIR sensor, reed module, an LED alarm indicator, and an ESP-01S Wi-Fi module acting as a cloud client. The design follows an **Edge Logic with API Integration** approach: the Arduino performs local sensor processing and immediate alarm control, and the ESP-01S handles cloud notifications (IFTTT or MQTT).


## Features
- Local alarm (LED) with low latency
- Event-triggered cloud notification (IFTTT webhook) via ESP-01S (AT mode)
- Simulation mode for demonstrations without physical Wi-Fi hardware
- Clear wiring diagram and setup guide for future hardware testing

## Files
- `DoorAlarm.ino` — Main Arduino sketch (well-commented). *Contains a SIMULATE_ESP flag for demonstrations.*
- `circuit/` — Circuit images/diagrams (Fritzing or screenshots).
- `docs/` — Architecture diagram and supporting material.
- `README.md` — This file.

## Hardware (prototype)
- Arduino Uno
- ESP-01S Wi-Fi module (optional for simulation)
- External 3.3V regulator (AMS1117 or LDO) capable of ≥500mA
- PIR motion sensor
- Reed module (magnetic door sensor)
- LED + 220Ω resistor
- Breadboard and jumper wires
- Optional: USB-TTL 3.3V adapter for testing ESP AT commands

## Wiring (summary)
- ESP-01S `VCC`, `CH_PD` → 3.3V regulator output (do NOT use Arduino 3.3V pin)
- ESP-01S `GND` → common GND with Arduino and regulator
- ESP-01S `TX` → Arduino D2 (SoftwareSerial RX)
- ESP-01S `RX` ← Arduino D3 (SoftwareSerial TX) **via level shifter or resistor divider**
- PIR `VCC` → Arduino 5V; PIR `DO` → Arduino D7
- Reed `VCC` → Arduino 5V; Reed `DO` → Arduino D6
- LED → Arduino D13 through 220Ω resistor to GND

## Software setup (development & testing)
1. Install the **Arduino IDE**.
2. Open `DoorAlarm.ino` and configure:
   - `SIMULATE_ESP = true` for Tinkercad/Wokwi or if ESP hardware is unavailable.
   - If using a real ESP, set `SIMULATE_ESP = false` and fill `ssid`, `password`, `apiKey`, and `eventName`.
3. Upload to Arduino Uno.
4. For simulation: run your circuit in Tinkercad/Wokwi and observe Serial Monitor output for simulated notifications.
5. For real hardware:
   - Power the ESP from an external 3.3V regulator (common GND).
   - Ensure Arduino TX → ESP RX has voltage level shifting.
   - If SoftwareSerial has baud issues, change ESP AT baud to 9600 using a USB-TTL adapter and `AT+UART_DEF` (recommended).

## How to show the Wi-Fi limitation in the report
Include a note: *Physical ESP/regulator connection was not completed due to hardware constraints. The code contains simulation mode and a Tinkercad project link to demonstrate functional behavior.*

## Creating an IFTTT webhook (brief)
1. Create an IFTTT account and add the Webhooks service.
2. Create a new Applet: `If Webhooks receive an event named <eventName> -> Then send a notification/email/...`
3. Get your key from `https://maker.ifttt.com/use/<your_key>` and place it in `DoorAlarm.ino`.



