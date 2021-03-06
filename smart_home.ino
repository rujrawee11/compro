#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "tcaW1TC2BDg5FTGlfd8Rk1z1VFp6N7pKd7ugcBsu2Jo"   // บรรทัดที่ 13 ใส่ รหัส TOKEN ที่ได้มาจากข้างบน

#include <TridentTD_LineNotify.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Ea5ZYzCi3ivGUl8ak6YhHpjwQElQ4jus";   //รหัส Token Blynk
char ssid[] = "NAVANITILAW_HOME_2.4GHz"; // 2.4G only ชื่อ Wi-Fi
char pass[] = "0813434814"; //รหัสผ่าน

#define LED_PIN_1 D0 //Led เปิด-ปิด แบบปุ่ม(เชื่อม Blynk)
#define LED_PIN_2 D2 //Led เปิด-ปิด แบบอัตโนมัติ
#define LED_PIN_3 D4 //Led Alarm sensor ตรวจจับน้ำฝน
#define LED_PIN_4 D1 //Led Alarm sensor ตรวจจับสิ่งกีดขวาง
#define rainDigital D5 //ขาของ Raindrop

int analogPin = A0; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่5 ของ ไฟเปิด-ปิด auto
int digitalPin = D3; //ประกาศตัวแปร ให้ digitalPin ของ sensor ตรวจจับสิ่งกีดขวาง
int val = 0; //แสดงค่าความสว่างของแสง เปิด-ปิดไฟ auto
int val3 = 0; //แสดงสถานะของ sensor ตรวจจับสิ่งกีดขวาง

BLYNK_WRITE(D0)//เป็นฟังก์ชันในการสั่งการทำงานเมื่อกดปุ่ม D0 ใน Blynk Application ซึ่งในที่นี้คือ การเปิดปิดไฟแบบปุ่ม
{ 
  //ค่าที่ได้จาก Widget_Button จะเป็น 0 และ 1 ถ้ามีการปดปุ่ม
  if (param.asInt() == 1) {
    //เรียกใช้เปิดไฟ LED
    digitalWrite(LED_PIN_1, HIGH); 
  }
  else {
    //เรียกใช้ปิดไฟ LED
    digitalWrite(LED_PIN_1, LOW);
  }
}

void setup() { 
  Serial.begin(9600);
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  LINE.notify("myarduino.net");
  Blynk.begin(auth, ssid, pass); //Token, ชื่อ Wi-Fi, รหัสผ่าน
  pinMode(LED_PIN_1, OUTPUT); //แสดงค่าทาง Led เปิด-ปิด แบบปุ่ม(เชื่อม Blynk)
  pinMode(LED_PIN_2, OUTPUT); //แสดงค่าทาง Led เปิด-ปิด แบบอัตโนมัติ
  pinMode(LED_PIN_3, OUTPUT); //แสดงค่าทาง Led Alarm sensor ตรวจจับน้ำฝน
  pinMode(LED_PIN_4, OUTPUT); //แสดงค่าทาง Led Alarm sensor ตรวจจับสิ่งกีดขวาง
  pinMode(digitalPin, INPUT); //รับจาก sensor ตรวจจับสิ่งกีดขวาง
  pinMode(rainDigital,INPUT); //รับจาก sensor ตรวจจับน้ำฝน
}
void loop() {
  Blynk.run();
  val = analogRead(analogPin); //อ่านค่า Analog จาก LDR sensor วัดความสว่าง
  int rainDigitalVal = digitalRead(rainDigital); //อ่านค่า Digital จาก sensor raindrop
  val3 = digitalRead(digitalPin); //อ่านค่า Digital จาก sensor infared ตรวจจับสิ่งกีดขวาง
  Serial.print("val_LDR = "); //แสดงค่าบรรทัดเดียวกัน
  Serial.println(val); // พิมพ์ค่าของตัวแปร val //แสดงค่าขึ้นบรรทัดใหม่
  Serial.println(rainDigitalVal);
  Serial.print("val_Object = ");
  Serial.println(val3); 
  if (val < 900 or val == 900 or val > 900) { // ค่า 900 สามารถกำหนดปรับได้ตามค่าแสงในห้องต่างๆ การเปิด-ปิดไฟแบบ auto
    if (val < 900){
      digitalWrite(LED_PIN_2, LOW);} // สั่งให้ LED ติดสว่าง
    else{
      digitalWrite(LED_PIN_2, HIGH); // สั่งให้ LED ดับ
    }
  }
  if (rainDigitalVal == 0 or rainDigitalVal == 1) { // สามารถกำหนดปรับค่าได้ตามสถานที่ต่างๆ sensor ตรวจจับน้ำฝน
    if (rainDigitalVal == 0){
      digitalWrite(LED_PIN_3, HIGH); // สั่งให้ LED ติดสว่าง
    String LineText;
    String string1 = "ฝนตกแล้ว";
    String string2 = "!";
    LineText = string1 + string2;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);}
      
    else{
      digitalWrite(LED_PIN_3, LOW); // สั่งให้ LED ดับ
    }
  }
  if (val3 == 0 or val3 != 0) { // สามารถกำหนดปรับค่าได้ตามสถานที่ต่างๆ sensor ตรวจจับสิ่งกีดขวาง
    if (val3 == 0){
      digitalWrite(LED_PIN_4, HIGH); // สั่งให้ LED ติดสว่าง
    String LineText;
    String string1 = "มีคนแปลกหน้า";
    String string2 = "!";
    LineText = string1 + string2;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);}
    else{
      digitalWrite(LED_PIN_4, LOW); // สั่งให้ LED ดับ
    }
  }
  delay(100);
}