#include "deneyap.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#define ssid "ssid"
#define password "parola"

WiFiServer server(80);

int role_pini = D1;

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

  pinMode (role_pini, OUTPUT);
  
  Serial.begin(115200);
  initWiFi();
  Serial.print("WiFi cekim gucu: ");
  Serial.println(WiFi.RSSI());

  server.begin(); 
}

void loop() {
  
  WiFiClient client = server.available();     
  if (client)
  {
    boolean currentLineIsBlank = true;
    String buffer = "";  
    while (client.connected())
    {
      if (client.available())                    
      {
        char c = client.read(); 
        buffer+=c;                              
        if (c == '\n' && currentLineIsBlank)     
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();    
          client.print("<HTML><title>Deneyap Kart IoT Akilli Anahtar</title>");
          client.print("<body><h1> Deneyap Kart IoT Akilli Anahtar </h1>");
          client.print("<p>Relay Control</p>");
          client.print("<a href=\"/?relayon\"\"><button>Ac</button></a>");
          client.print("<a href=\"/?relayoff\"\"><button>Kapat</button></a>");
          client.print("</body></HTML>");
          break;        
        }
        if (c == '\n') { 
          currentLineIsBlank = true;
          buffer="";       
        } 
        else 
          if (c == '\r') {     
          if(buffer.indexOf("GET /?relayon")>=0)
            digitalWrite(role_pini, HIGH);
          if(buffer.indexOf("GET /?relayoff")>=0)
            digitalWrite(role_pini, LOW);   
        }
        else {
          currentLineIsBlank = false;
        }  
      }
    }
    client.stop();
  }
}
