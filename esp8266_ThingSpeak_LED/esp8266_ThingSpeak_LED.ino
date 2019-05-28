#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

// กำหนดขา LED Output
#define LED D1

// เปลี่ยนเป็น WiFi ของตัวเอง
char* ssid = "xxxxxxxxx"; 
char* pass = "xxxxxxxxx";


int status = WL_IDLE_STATUS;
WiFiClient  client;

int readValue;                            // ตัวแปรเก็บข้อมูลที่อ่านได้จาก channel field
    
unsigned long myChannelNumber = xxxxxx;   // xxxxxx ให้แทนด้วย Channel ID ของตัวเอง
const char * myReadAPIKey = "xxxxxx";     // xxxxxx ให้แทนด้วย Read API Keys ของตัวเอง

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  ThingSpeak.begin(client);               // เริ่มใช้ ThingSpeak
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
// รอรับค่าจาก ThingSpeak
   readValue = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey);
// แสดงผลออกทาง Serial
  Serial.print("readValue = ");
  Serial.println(readValue);

  if ( readValue == 1){
    digitalWrite(LED, HIGH);        // ถ้าค่าที่ส่งมา = 1 ขา LED ให้ HIGH ทำให้ LED ติด
  }
  else{
    digitalWrite(LED, LOW);         // ถ้าเป็นค่าอื่นๆขา LED ให้ LOW ทำให้ LED ดับ
  }
// กรณีนำไปควบคุมรีเลย์หรืออื่นๆ ให้ปรับค่าตามความต้องการได้ (ดูเรื่อง Active HIGH, Active LOW ให้ถูก)
}
