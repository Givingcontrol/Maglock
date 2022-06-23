/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

const int relayPin = 0;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  bool LedOn;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

   //int g = myData.LedOn;
   if ( myData.LedOn == true) 
      { digitalWrite(LED_BUILTIN, HIGH); 
        digitalWrite(relayPin, HIGH);// turn the LED on (HIGH is the voltage level)
      }
   if ( myData.LedOn == false)  
      {digitalWrite(LED_BUILTIN, LOW);
       digitalWrite(relayPin, LOW);
      }
  
  Serial.print("LED State : ");
  Serial.println(myData.LedOn);
  
   Serial.println();

 
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

pinMode(LED_BUILTIN, OUTPUT);
 pinMode(relayPin, OUTPUT);  
}

void loop() {

}
