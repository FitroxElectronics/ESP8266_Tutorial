#include <ESP8266WiFi.h>

// ไม่กำหนด SSID และ PASSWORD เพราะตัวนี้จะสร้างเครือข่าย ไม่ได้ไปเชื่อมต่อเครือข่ายใดๆ 

// กำหนด IP, Gateway, Subnet Address
IPAddress local_IP (192,168,1,11);
IPAddress gateway (192,168,1,9);
IPAddress subnet (255,255,255,0);

void setup(){
Serial.begin(115200);
// ตั้งค่า IP, Gateway และ Subnet ตามที่กำหนดไว้ แล้วแสดงสถานะว่าตั้งค่าสำเร็จหรือไม่
Serial.print("Soft AP Config.........");
Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready !!" : "Failed !");

// เริ่มการทำงานในโหมด Soft AP แล้วแสดงสถานะว่าสำเร็จหรือไม่
Serial.print("Soft AP Setting.........");
Serial.println(WiFi.softAP("ESP8266_AP01") ? "Ready !!" : "Failed !");

// เมื่อสำเร็จแล้วให้แสดงค่า IP Address ของตัว Soft AP
Serial.print("Soft AP IP Address : ");
Serial.print(WiFi.softAPIP());
}

void loop(){
 // do nothing ไม่ทำอะไรใน loop
}
