/*
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/

  
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

// Add slave tabs
#include "slaveMAC.h"  //MAC addresses of slaves
#include "LEDOn.h"


bool LEDState = false;
unsigned long lastTime = 0;  
unsigned long timerDelay = 1000;  // send readings timer

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
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(ESP01n2, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LEDState);
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    
    //LEDState = !LEDState;
    myData.LedOn = !myData.LedOn;
    digitalWrite(LED_BUILTIN, myData.LedOn);
   Serial.print("LED State : ");
  Serial.println(myData.LedOn);
 // Serial.print("LED State : ");
 // Serial.println(LEDState);

    // Send message via ESP-NOW
    esp_now_send(ESP01n5, (uint8_t *) &myData, sizeof(myData));
    lastTime = millis();
    
  }
  
}
