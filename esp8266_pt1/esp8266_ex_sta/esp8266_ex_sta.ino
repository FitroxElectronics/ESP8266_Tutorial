#include <ESP8266WiFi.h>

// กำหนด SSID และ PASSWORD ให้เปลี่ยน xxxxx เป็น SSID(ชื่อ WiFi) และ PASSWORD เข้าใช้งานของตัวท่านเอง
const char* ssid = "xxxxxxxxx";
const char* password = "xxxxxxxxx";

// กำหนด IP, Gateway, Subnet Address
IPAddress staticIP(192,168,1,11);
IPAddress gateway(192,168,1,9);
IPAddress subnet(255,255,255,0);

void setup(){
Serial.begin(115200);
Serial.printf("Connecting to %s\n", ssid);
WiFi.begin(ssid, password);          // เริ่มเชื่อมต่อเครือข่าย wifi โดยใช้ ssid และ password ที่กำหนดไว้
WiFi.config(staticIP, gateway, subnet);     // ตั้งค่า IP โดยใช้ค่าที่กำหนดไว้

// รอจนกว่าจะเชื่อมต่อสำเร็จโดยคำสั่ง หากยังเชื่อมต่อเครือข่ายไม่ได้ให้รอครึ่งวินาทีแล้วลองใหม่
while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }

// หากเชื่อมต่อสำเร็จ ให้แสดงข้อความและ Local IP (คือ IP Address ที่ Router แจกมาให้)
Serial.println();
Serial.print("Successful Connected ! , IP Address : ");
Serial.println(WiFi.localIP());
}

void loop(){
 // do nothing ไม่ทำอะไรใน loop
}
