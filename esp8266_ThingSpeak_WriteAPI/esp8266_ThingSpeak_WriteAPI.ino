#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  

// ค่าต่างๆของ DHT11
#define DHTPIN D2  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

// ตั้งค่า WiFi ให้แทนด้วย SSID และ Password ของท่านเอง
const char* ssid = "xxxxxxxxx";  
const char* password = "xxxxxxxxx";
  
WiFiClient client;  

// ให้แทนด้วย Channel และ API ของตัวเอง
unsigned long ChNumber = 793717;             // Channel ID
const char * WriteKey = "R6QXQGYWJGA8NMWI";    // Write API

// กำหนดตัวแปร
uint8_t temp, humi;


void setup()  
{  
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  

// เชื่อมต่อกับ WiFi
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
// รอจนกว่าจะเชื่อมต่อสำเร็จ
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }
// แสดงสถานะเมื่อเชื่อมต่อสำเร็จ
  Serial.println("");  
  Serial.println("WiFi connected");  
// แสดง IP Address
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}


void loop(){
// อ่านข้อมูลจาก DHT11 และแสดงทาง Serial Monitor
  static boolean data_state = false;  
  temp = dht.readTemperature();  
  humi = dht.readHumidity();  
  Serial.print("Temperature is :");  
  Serial.print(temp);  
  Serial.println("C");  
  Serial.print("Humidity is :");  
  Serial.print(humi);  
  Serial.println("%"); 
  
// ส่งข้อมูลที่ 1 (ในที่นี้คืออุณหภูมิ) ไปยัง Channel ของเราใน Field ที่ 1  
  if( data_state )  
  {  
   ThingSpeak.writeField(ChNumber, 1, temp, WriteKey);  
   data_state = false;  
  }
// ส่งข้อมูลที่ 2 (ในที่นี้คือความชื้น) ไปยัง Channel ของเราใน Field ที่ 2  
  else  
  {  
   ThingSpeak.writeField(ChNumber, 2, humi, WriteKey);  
   data_state = true;  
  }

// แสดงข้อความเมื่อส่งข้อมูลเสร็จ
  Serial.println("Successful Update Data to ThingSpeak"); 

// หน่วงเวลา 30 วินาที (แพ็คเกจฟรีของ ThingSpeak จะอัพเดทได้ทุกๆ 15 วินาที)
  delay(30000);
} 
