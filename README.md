# Deneyap Kart Yaz Okulu 4. Ders İçeriği

Deneyap Kart Yaz Okulu 4. Ders İçeriği

## Gereklilikler

Deneyap Kart kütüphanesini indirmeniz gerekmektedir:

* [Deneyap Kart kurulumu](https://docs.deneyapkart.org/) 

Blynk kütüphanesini indirmeniz gerekmektedir:

* [Blynk Kütüphanesi](https://github.com/ibrahimcahit/deneyap_kart_yaz_okulu_ders4/blob/main/blynk-library.zip)

## Bağlantı Şeması

![image](https://raw.githubusercontent.com/ibrahimcahit/deneyap_kart_yaz_okulu_ders4/main/dk_4.jpg)

## Ders ve Kod Sırası

* [Birinci Uygulama - Wi-Fi Bağlantısı](https://github.com/ibrahimcahit/deneyap_kart_yaz_okulu_ders4/blob/main/kod_1.ino)

* [İkinci Uygulama - IoT Termometre](https://github.com/ibrahimcahit/deneyap_kart_yaz_okulu_ders4/blob/main/kod_2.ino)

* [Üçüncü Uygulama - Akıllı Anahtar](https://github.com/ibrahimcahit/deneyap_kart_yaz_okulu_ders4/blob/main/kod_3.ino)

* [Dördüncü Uygulama - Blynk Entegrasyonu](https://github.com/ibrahimcahit/deneyap_kart_yaz_okulu_ders4/blob/main/kod_4.ino)

## Nasıl Çalışıyor?

Bu bölümde kodların açıklamalarını bulabilirsiniz

## Birinci Ders

Gerekli kütüphaneleri import ediyoruz

    #include "deneyap.h"
    #include "WiFi.h"
    
Sonrasında Wi-Fi ağ adımızı ve parolamızı giriyoruz. 

    #define ssid "ssid"
    #define password "parola"

`initWiFi` fonkiyonu içinde, Wi-Fi ağına bağlanma kodumuz olacak. Bu fonksiyonu, `Setup()` içinde çağıracağız. 

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

`Setup` fonksiyonu içinde, önce `initWiFi` fonksiyonumuzu çağırıyoruz. Sonrasında, ekrana Wi-Fi gücünü yazdırıyoruz. 

    void setup() {
      Serial.begin(115200);
      initWiFi();
      Serial.print("WiFi cekim gucu: ");
      Serial.println(WiFi.RSSI());
    }

`Loop` fonksiyonu içinde, 3 saniye aralıklarla çekimm gücünü yazdırmaya devam ediyoruz. 

    void loop() {
      Serial.print("WiFi cekim gucu: ");
      Serial.println(WiFi.RSSI());
      delay(3000);
    }


## İkinci Ders

Gerekli kütüphaneleri import ediyoruz

    #include "deneyap.h"
    #include "lsm6dsm.h"
    #include <WiFi.h>
    #include <WiFiClient.h>
    #include <WebServer.h>

Bir bekleme süresi belirliyoruz. Aynı zamanda sıcaklık sensörümüzü başlatıyoruz

    #define delayms 700
    LSM6DSM IMU;

Sonrasında Wi-Fi ağ adımızı ve parolamızı giriyoruz. 

    #define ssid "ssid"
    #define password "parola"
    
Web sunucumuzu başlatıyoruz

  WebServer server(80);

integer bir Temperature değişkeni tanımlıyoruz

  int Temperature;

Setup kısmında Wi-Fi ağına bağlanıyor, sıcaklık sensörümüzü başlatıyoruz

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

Kodun kalan kısmı, Deneyap Kart üzerinde açılan sunucuda, HTML kullanarak bir Web sayfası çiziyor ve sensörden alınan sıcaklık değerini bu Web sayfasına basıyor

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

## Üçüncü Ders

Gerekli kütüphaneleri import edelim

        #include "deneyap.h"
        #include <WiFi.h>
        #include <WiFiClient.h>
        #include <WebServer.h>

Sonrasında Wi-Fi ağ adımızı ve parolamızı giriyoruz. 

    #define ssid "ssid"
    #define password "parola"

Sweb sunucumuzu başlatalım. Ayrıca Röle pinimizi D1 olarak atayalım

        WiFiServer server(80);
        int role_pini = D0;
        
Wi-Fi ağına bağlanacağımız initWiFi fonksiyonumuzu tanımlayalım

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

Setup fonksiyonunda, röle pinimizi çıkış olarak ayarlayalım

        void setup() {

          pinMode (role_pini, OUTPUT);

          Serial.begin(115200);
          initWiFi();
          Serial.print("WiFi cekim gucu: ");
          Serial.println(WiFi.RSSI());

          server.begin(); 
        }

Loop fonksiyonunda ise Web sayfamızı HTML kullanarak çiziyoruz

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





































































