#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#include "configuration.h"

/*========= WIFI SETUP ========*/
void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void setup_ota() {
  ArduinoOTA.setPasswordHash(OTA_PASSWORD_HASH);

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    Serial.println("Starting OTA update " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA Update Completed");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Authentication Error");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("OTA Begin Error");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("OTA Connect Error");
    } else if (error == OTA_END_ERROR) {
      Serial.println("OTA End Error");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("OTA Receive Error");
    }
  });

  ArduinoOTA.begin();
}

/*=== MAIN =================*/

void setup() { 
  Serial.begin(115200);

  //setup client
  setup_wifi();
  setup_ota();
}

void loop() { 
  ArduinoOTA.handle();

}