# 🛰️ Aerial Tower Assistance System

This project is a smart embedded system designed to **assist in monitoring and managing aerial towers** (such as communication or transmission towers) using **ESP32**, **GPS**, and **LoRa** technology. It provides remote location tracking and data communication between field units and the control center, improving safety, reliability, and maintenance efficiency.

---

## 🔧 Features

- 📡 **Real-time GPS Location Tracking** of field personnel near towers  
- 📶 **Wireless Communication via LoRa (RYLR998)** for long-range data transmission  
- 🔋 Low power consumption — ideal for remote deployments  
- 🖥️ PC interface via USB for monitoring received data  
- 📱 Android app integration for GPS data push

---

## 📦 Hardware Used

- **ESP32-WROOM Module** – Main controller  
- **Reyax RYLR998 LoRa Module** – Wireless data transmission  
- **GPS Module (e.g., NEO-6M)** – Real-time coordinate acquisition  
- **Android Smartphone** – Sends GPS to ESP32 via TCP  
- **TTL-to-USB Converter** – For connecting receiving LoRa module to PC  
- **Laptop or PC** – Runs Arduino IDE for monitoring serial data

---

## 🔁 System Workflow

1. The Android app collects the phone’s GPS coordinates.
2. It connects to ESP32 via Wi-Fi and sends the data over a TCP socket.
3. ESP32 receives the GPS data and transmits it via LoRa.
4. Another RYLR998 LoRa module (connected to PC) receives the data.
5. The data is displayed in real-time on the **Serial Monitor** using the Arduino IDE.

---

## 📱 Android App Functionality

- Enables **Wi-Fi & GPS** on launch
- Scans for and connects to ESP32
- Sends current GPS coordinates via TCP
- Sends data **only once per connection** to conserve resources

---

## 💾 Folder Structure

