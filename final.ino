#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID Pins
#define SS_PIN 10
#define RST_PIN 9

// GSM Pins
#define GSM_RX 2
#define GSM_TX 3

// Initialize RFID and LCD
MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns, 2 rows

// Initialize GSM
SoftwareSerial ec200u(GSM_RX, GSM_TX);

// Student Data
String studentUIDs[10] = {
  "1317cfa", "d3a8b3e0", "231c3f1c", "6331b3e1", "f3bad3e0",
  "b3cbc0e1", "6313d0e1", "938a55e0", "93c5bee1", "83fb44e0"
};

String studentNames[10] = {
  "Pavan", "Nilesh", "Prathmesh", "Nejkar", "Babar",
  "Mahesh", "Pratibha", "Pratik", "Pranit", "Karan"
};

String studentAddresses[10] = {
  "218001", "218002", "218003", "218004", "218005",
  "218006", "218007", "218008", "218009", "218010"
};

// Phone number to send SMS
String phoneNumber = "+919960979677";

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Scan your card...");

  // Initialize GSM
  ec200u.begin(115200);
  delay(1000);

  // Set GSM to SMS text mode
  sendATCommand("AT+CMGF=1\r\n", "OK", 2000);
}

void loop() {
  // Check for RFID card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Read card ID
  String cardID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    cardID += String(rfid.uid.uidByte[i], HEX);
  }

  Serial.print("Detected Card ID: ");
  Serial.println(cardID);

  // Check if card ID matches any student
  bool cardMatched = false;
  int studentIndex = -1;

  for (int i = 0; i < 10; i++) {
    if (cardID == studentUIDs[i]) {
      cardMatched = true;
      studentIndex = i;
      break;
    }
  }

  // Display on LCD and send SMS
  lcd.clear();

  if (cardMatched) {
    // Display student name and address on LCD
    lcd.setCursor(0, 0);
    lcd.print(studentNames[studentIndex]);
    lcd.setCursor(0, 1);
    lcd.print(studentAddresses[studentIndex]);

    // Send SMS with student name and address
    String smsMessage = "Student: " + studentNames[studentIndex] + ", Address: " + studentAddresses[studentIndex];
    sendSMS(phoneNumber, smsMessage);
  } else {
    // Display "Unknown Card" on LCD
    lcd.setCursor(0, 0);
    lcd.print("Unknown Card");
    lcd.setCursor(0, 1);
    lcd.print("Access Denied");
  }

  // Halt RFID and wait before next scan
  rfid.PICC_HaltA();
  delay(2000);
}

// Function to send AT commands to GSM module
void sendATCommand(String command, String response, int timeout) {
  String receivedData;
  ec200u.println(command); // Send the AT command
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (ec200u.available()) {
      char c = ec200u.read(); // Read the response
      receivedData += c;
    }
  }
  if (receivedData.indexOf(response) != -1) {
    Serial.println("Received: " + receivedData); // If the response is as expected
  } else {
    Serial.println("Error");
  }
}

// Function to send SMS
void sendSMS(String number, String text) {
  sendATCommand("AT+CMGS=\"" + number + "\"\r\n", ">", 2000); // Command to send SMS
  ec200u.print(text); // Text of the message
  delay(100);
  ec200u.write(26); // CTRL+Z to send the message
}