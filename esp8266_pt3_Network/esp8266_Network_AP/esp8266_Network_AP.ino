#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "ESP_NETWORK";
const char *pass = "12345"; 

unsigned int localPort = 2000;        // กำหนดพอร์ตสำหรับ UDP packets

IPAddress ServerIP(192,168,4,1);      // IP Address ของ AP
IPAddress ClientIP_1(192,168,4,2);    // IP Address ของ Client ตัวที่ 1
IPAddress ClientIP_2(192,168,4,3);    // IP Address ของ Client ตัวที่ 2

// ปุ่มกดที่ GPIO0 GPIO1 GPIO2 GPIO3
int btn_1 = 0;
int btn_2 = 1;
int btn_3 = 2;
int btn_4 = 3;

WiFiUDP udp;

char packetBuffer[9];   // UDP data

void setup()
{
    Serial.begin(9600);

    WiFi.softAP(ssid, pass);    // เริ่มการทำงานโหมด AP

// เริ่ม UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());

// Pin Setting
    pinMode(btn_1, INPUT);
    pinMode(btn_2, INPUT); 
    pinMode(btn_3, INPUT); 
    pinMode(btn_4, INPUT); 
}


void loop()
{
    int cb = udp.parsePacket();
    if (!cb){
      // ปุ่มที่ 1
        if (digitalRead(btn_1) == HIGH){
          udp.beginPacket(ClientIP_1, 2000);    // เริ่มส่งข้อมูลไปที่ Client 1 พอร์ต 2000 
          udp.write("a", 1);                       // ส่งข้อมูล 'a' ออกไป มีขนาด 1 byte
          udp.endPacket();                      // จบการส่งข้อมูล
        }
      // ปุ่มที่ 2
        if (digitalRead(btn_2) == HIGH){
          udp.beginPacket(ClientIP_1, 2000);    // เริ่มส่งข้อมูลไปที่ Client 1 พอร์ต 2000 
          udp.write("b", 1);                       // ส่งข้อมูล 'b' ออกไป มีขนาด 1 byte
          udp.endPacket();                      // จบการส่งข้อมูล
        }
      // ปุ่มที่ 3
        if (digitalRead(btn_3) == HIGH){
          udp.beginPacket(ClientIP_2, 2000);    // เริ่มส่งข้อมูลไปที่ Client 2 พอร์ต 2000 
          udp.write("a", 1);                       // ส่งข้อมูล 'a' ออกไป มีขนาด 1 byte
          udp.endPacket();                      // จบการส่งข้อมูล
        }
      // ปุ่มที่ 4
        if (digitalRead(btn_4) == HIGH){
          udp.beginPacket(ClientIP_2, 2000);    // เริ่มส่งข้อมูลไปที่ Client 2 พอร์ต 2000 
          udp.write("b", 1);                       // ส่งข้อมูล 'b' ออกไป มีขนาด 1 byte
          udp.endPacket();                      // จบการส่งข้อมูล
        }
    }
}
