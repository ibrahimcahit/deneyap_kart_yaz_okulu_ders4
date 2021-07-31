#include "deneyap.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include "lsm6dsm.h"
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

#define ssid "ssid"
#define password "parola"

LSM6DSM IMU;

char auth[] = "auth-code";

int role_pin = D1;
int pinValue;
int Temperature;

BLYNK_READ(V0) 
{
  Temperature = IMU.readTempC();
  Blynk.virtualWrite(V0, Temperature); 
}

BLYNK_WRITE(V1)   
{
  pinValue = param.asInt();
}

void initWiFi() {

  WiFi.begin(ssid, password);
  Serial.print("WiFi Agina Baglaniliyor..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println('.');
    delay(500);
  }
  Serial.println();
  Serial.println("Kablosuz aga baglanildi!");
  Serial.print("IP adresi: "); Serial.println(WiFi.localIP());
}

void setup() {
  pinMode(role_pin, OUTPUT);

  Serial.begin(115200);
  initWiFi();
  Serial.print("WiFi cekim gucu: ");
  Serial.println(WiFi.RSSI());

  Blynk.begin(auth, ssid, password);
}

void loop() {

  Blynk.run();
  digitalWrite(role_pin, pinValue);
}
