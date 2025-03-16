# Circuit Diagram

INTRODUCTION:
This project demonstrates the integration of RFID technology, GSM communication, and LCD display to create a smart student attendance system. The system identifies students using RFID cards, displays their details on an LCD, and sends real-time SMS notifications to a predefined phone number. It is designed for use in schools, colleges, or offices to automate attendance tracking and provide instant notifications.

WORKING:
The system operates in the following steps:

RFID Card Scanning:
A student scans their RFID card using the MFRC522 RFID module.
The system reads the unique identifier (UID) of the card and compares it with a predefined list of student UIDs stored in the Arduino.
Student Identification:
If the UID matches a student in the database, the system retrieves the student’s name and address.
The student’s name and address are displayed on the I2C LCD screen.
SMS Notification:
The system sends an SMS to a predefined phone number using the Quectel EC200U-CN GSM module.
The SMS contains the student’s name and address for quick identification.
Access Control:
If the UID does not match any student, the system denies access.
The LCD displays "Unknown Card - Access Denied".

Equipment Used :
Arduino Uno
MFRC522 RFID Module
Quectel EC200U-CN GSM Module and Antenna
I2C LCD Display (16x2)
RFID Cards
Jumper Wires

![rfid_rc522_lcd](https://github.com/user-attachments/assets/96a42e0b-5474-4718-83ea-577f20608999)

![GSM](https://github.com/user-attachments/assets/88db434a-2825-44f9-afb8-824d1ff978fa)
![SMS](https://github.com/user-attachments/assets/21af0887-94e4-4353-aeb1-3dbc92465c25)
![Block Diagram](https://github.com/user-attachments/assets/e9d737a5-3676-45f6-88b3-c0256156e4af)
