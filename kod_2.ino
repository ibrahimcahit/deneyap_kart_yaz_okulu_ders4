#include "deneyap.h"
#include "lsm6dsm.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#define delayms 700

LSM6DSM IMU;

#define ssid "ssid"
#define password "parola"

WebServer server(80);

int Temperature;

void setup() {
  Serial.begin(115200);
  delay(100);

  IMU.begin();

  Serial.println("Bu aga baglaniliyor: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Kablosuz baglanti basarili");
  Serial.print("Web sayfasi IP adresi: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP sunucusu başlatıldı");

}
void loop() {

  server.handleClient();

}

void handle_OnConnect() {

  Temperature = IMU.readTempC();
  Serial.println(IMU.readTempC());
  server.send(200, "text/html", SendHTML(Temperature));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Sayfa bulunamadı");
}

String SendHTML(float Temperaturestat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Deneyap Kart IoT Termometre</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Deneyap Kart IoT Termometre</h1>\n";

  ptr += "<p>Ortam Sicakligi: ";
  ptr += (int)Temperaturestat;
  ptr += " C</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
