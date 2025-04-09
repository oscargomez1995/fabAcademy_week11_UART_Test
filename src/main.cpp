#include "Arduino.h"
uint8_t tries=0; // Initialize tries variable
uint8_t Id=0; // Initialize Id variable

uint8_t RX_pin=8; // RX pin for Serial2
uint8_t TX_pin=7; // TX pin for Serial2

void setup() {
  Serial.begin(115200); // Initialize Serial Monitor at 115200 baud rate
  Serial2.begin(115200,SERIAL_8N1,RX_pin,TX_pin); // Initialize Serial
  delay(1000); // Wait for 1 second
}

void loop() {
  if (Serial2.available()&&Id!=0){ // Check if data is available to read
    uint8_t received = Serial2.readStringUntil('\n').toInt(); // Read the data until newline and convert to integer
    if(received==255){ // Check if received data is greater than or equal to 255
      received=1; // Reset to 0
    }else{
      received++; // Increment
    }
    delay(1000); // Wait for 1 second
    Serial2.println(received); // Send the data as a character to the Serial Monitor
    Serial2.readStringUntil('\n'); // Read the data until newline
    delay(500);
    Serial.println(received); // Print the data to the Serial Monitor
  }else{
    if(tries<5){ // Check if tries is less than 5
      delay(1000); // Wait for 1 second
      Serial2.println(Id); // Print message if no data is available
      Serial2.readStringUntil('\n'); // Read the data until newline
      delay(500);
      Serial.println(Id);
      tries++; // Increment tries
      Id=1;
    }
  }
}