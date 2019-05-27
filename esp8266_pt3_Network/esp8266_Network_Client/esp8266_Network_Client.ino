#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
const char *ssid = "ESP_NETWORK";
const char *pass = "12345"; 
 
unsigned int localPort = 2000;        // กำหนดพอร์ตสำหรับ UDP packets
 
IPAddress ServerIP(192,168,4,1);      // IP ของ AP
IPAddress ClientIP_1(192,168,4,2);    // หากตัวที่ 2 อย่าลืมเปลี่ยน 1 เป็น 2 IP = 192.168.4.3
 
// Pin ของ LED ที่ GPIO0 และ GPIO2
int led_1 = 0;
int led_2 = 2;

WiFiUDP udp;
 
char packetBuffer[9];                 // UDP data

void setup()
{
    Serial.begin(9600);
 
    WiFi.begin(ssid, pass);         // เชื่อมต่อกับ AP
  
 
// รอจนเชื่อมต่อสำเร็จ
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
//เริ่มใช้งาน UDP
    udp.begin(localPort);

    pinMode(led_1, OUTPUT);
    pinMode(led_2, OUTPUT);
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
}

void loop()
{
    int cb = udp.parsePacket();
// ถ้ามีข้อมูลส่งเข้ามา
    if (!cb){
      udp.read(packetBuffer, 1);    // อ่านข้อมูลที่ส่งมา กำหนดขนาด 1 byte
      char* pack = packetBuffer;    // เก็บข้อมูลที่เข้ามาในตัวแปร pack
      if (pack == "a"){
        digitalWrite(led_1, !digitalRead(led_1));
      }
      if (pack == "b"){
        digitalWrite(led_2, !digitalRead(led_2));
      }
    }
}
