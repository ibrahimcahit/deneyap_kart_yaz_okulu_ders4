#include "deneyap.h"
#include "WiFi.h"

#define ssid "ssid"
#define password "parola"

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
  Serial.begin(115200);
  initWiFi();
  Serial.print("WiFi cekim gucu: ");
  Serial.println(WiFi.RSSI());
}

void loop() {
  Serial.print("WiFi cekim gucu: ");
  Serial.println(WiFi.RSSI());
  delay(3000);
}
