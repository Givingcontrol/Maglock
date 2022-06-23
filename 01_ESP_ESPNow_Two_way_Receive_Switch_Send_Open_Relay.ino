/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp8266-nodemcu/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
#include "LEDOn.h"
#include "slaveMAC.h"

// REPLACE WITH THE MAC Address of your receiver 


// Define variables to store data to be sent
bool SwitchOn = false;
bool RelayOn = false;
bool LEDSwitchOn = false;


// Define variables to store incoming readings
bool incomingSwitch;
bool incomingRelay;
bool incomingLED;


// Updates  readings every 1 seconds
const long interval = 1000; 
unsigned long previousMillis = 0;    // will store last time DHT was updated 

// Variable to store if sending data was successful
String success;



// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingSwitch = receivedData.SwitchClosed;
  incomingRelay = receivedData.activateRelay;
  incomingLED = receivedData.LedOn;
}


void printIncomingReadings(){
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("LED: ");
  Serial.println(incomingLED);
  Serial.print("switch: ");
  Serial.println(incomingSwitch);
  Serial.print("relay: ");
  Serial.println(incomingRelay);
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

 
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(ESP01n4, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);

   //define input -outputs
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}
 
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
/*
    LEDSwitchOn =  true;
    sentData.LedOn = LEDSwitchOn;
    // Send message via ESP-NOW
    esp_now_send(ESP01n4, (uint8_t *) &sentData, sizeof(sentData));
*/
   
    if 
     ( incomingSwitch == true)
      {digitalWrite(LED_BUILTIN, LOW ); 
     delay(3000);
    //  LEDSwitchOn =  true;
     digitalWrite(LED_BUILTIN, HIGH);
     sentData.deactivateRelay = true;
    // Send message via ESP-NOW
    esp_now_send(ESP01n4, (uint8_t *) &sentData, sizeof(sentData));
     delay(3000);
     }
  if 
     ( incomingSwitch == false)
      {digitalWrite(LED_BUILTIN, HIGH);
      //wait and tell other unit to switch on LED
      
      }

    // Print incoming readings
    printIncomingReadings();
  }
}
