# Smart Home
&emsp;&emsp;&emsp;&emsp;โครงงานนี้เป็นส่วนหนึ่งของวิชา Computer programming จัดทำขึ้นโดยมีวัตถุประสงค์เพื่อนำความรู้ที่ได้รับจากศึกษาการเขียน
โปรแกรมภาษา C และต่อบอร์ด Arduino ทั้งในห้องเรียนและจากการศึกษาด้วยตัวเอง ซึ่งในปัจจุบัน IoT หรือ Internet of Things 
ได้เข้ามามีบทบาทอย่างมากในชีวิตประจำวัน คณะผู้จัดทำจึงได้นำความรู้มาประยุกต์ใช้ให้เข้ากับการดำเนินชีวิตในแต่ละวันเพื่อเพิ่ม
ความสะดวกสบายให้กับผู้ใช้งานมากขึ้นอาทิ เช่น การเปิด-ปิดไฟ ที่สามารถเปิด-ปิด ผ่านสวิตซ์ (blynk) หรือ การพูดผ่าน
(google assistance),ไฟเปิดอัตโนมัติในเวลากลางคืน,ตรวจจับฝน,ตรวจจับผู้บุกรุก โดยจะส่งข้อความเตือนผ่าน line เพื่อแจ้งเหตุ
การณ์ต่างๆ คณะผู้จัดทำหวังเป็นอย่างยิ่งว่าโครงงานนี้จะสามารถสร้างประโยชน์และเป็นแนวทางในการพัฒนาเทคโนโลยีที่เกี่ยวข้องกับ
IoT ต่อไปในอนาคตเป็นอย่างมาก
# Poster
[![Poster][poster]](https://github.com/rujrawee11/compro/blob/main/image/Poster.jpg)
# YouTube สาธิตการทำงาน
link: https://www.youtube.com/embed/JpotUoLt1cI
# เว็บไซต์
[https://github.com/rujrawee11/compro](https://laughing-gates-57a1de.netlify.app)
# จุดประสงค์
1.	เพื่อให้สะดวกต่อการเปิดปิดไฟในบ้านมากขึ้นและช่วยลดค่าใช้จ่าย (ลืมปิดไฟน้อยลง)
2.	เพื่อให้ลดการวิตกกังวล เวลาที่ออกไปข้างนอกแล้วตากผ้าไว้ ให้แบบจำลองนี้ส่งสัญญาณไปแจ้งเตือน
3.	เพื่อให้มีการระวังตัวเองมากขึ้นเมื่อมีสัญญาณเตือนว่ามีคนมาบุกรุก ให้ดูกล้องวงจรปิด หรือไปแอบดูว่าใครมา
# อุปกรณ์
1. บอร์ดทดลองวงจร (Photoboard) 
2. Node MCU V2 ESP8266
3. LED
4. ตัวต้านทาง 220 โอห์ม
5. Jumper M2M, Jumper M2F
6. LDR photoresistor sensor วัดความสว่างความเข้มแสง
7. Raindrop sensor วัดปริมาณน้ำฝน
8. IR infrared obstacle avoidance sensor ตรวจจับวัตถุสิ่งกีดขวาง
# หลักการทำงาน
[![รวม][all]](https://github.com/rujrawee11/compro/blob/main/image/รวม.jpg)
ตามแบบจำลองวงจรภายในบ้าน โดยให้ LED จำลองเป็นหลอดไฟภายในบ้าน 2 หลอดและมีไฟเตือนด้วย 2 หลอด 

1. การเปิด-ปิดไฟ โดยการกดปุ่มในแอปพลิเคชัน Blynk จะต้องไปทำการสร้างปุ่มใน Blynk  และทำการเชื่อมกับ code ก่อนถึง
จะทำการควบคุมการเปิดปิดได้ หรือสามารถใช้การสั่งงานด้วยเสียง(google assistant)
2. การเปิด-ปิดไฟแบบอัตโนมัติด้วยการวัดปริมาณตามความเข้มแสง ถ้ามีแสง จะทำให้หลอดไฟดับ ถ้าไม่มีแสงจะทำให้หลอดไฟจะติด 
3. เมื่อมีน้ำที่ raindrop จะมีไฟแจ้งเตือนที่ LED ว่าฝนตกแล้วจะส่งแจ้งเตือนไปทางไลน์ว่า ฝนตกแล้ว 	
4. เมื่อมีสิ่งกีดขวางที่หน้า IR จะทำการแจ้งเตือนที่ LED และส่งแจ้งเตือนไปทางไลน์
# Library
- #include <TridentTD_LineNotify.h>
- #include <ESP8266WiFi.h>
- #include <BlynkSimpleEsp8266.h>
# Source Code
- เชื่อม Blynk
  char auth[] = "รหัส TOKEN";   //รหัส Token Blynk

  char ssid[] = "ชื่อ WIFI"; // 2.4G only ชื่อ Wi-Fi

  char pass[] = "Password"; //รหัสผ่าน

- LED เปิด-ปิดไฟโดยใช้แอป >><br />
  "BLYNK_WRITE(D0)//เป็นฟังก์ชันในการสั่งการทำงานเมื่อกดปุ่ม D0 ใน Blynk Application ซึ่งในที่นี้คือ การเปิดปิดไฟแบบปุ่ม<br />
{ <br />
  //ค่าที่ได้จาก Widget_Button จะเป็น 0 และ 1 ถ้ามีการปดปุ่ม<br />
  &emsp;if (param.asInt() == 1) {<br />
    &emsp;//เรียกใช้เปิดไฟ LED<br />
    &emsp;&emsp;digitalWrite(LED_PIN_1, HIGH); <br />
  &emsp;}<br />
  &emsp;else {<br />
    &emsp;//เรียกใช้ปิดไฟ LED<br />
    &emsp;&emsp;digitalWrite(LED_PIN_1, LOW);<br />
  &emsp;}<br />
}"<br />

- LED เปิด-ปิดไฟแบบ Auto ตามคววามเข้มแสง โดยจะอยู่ในเงื่อนไขของ void loop >><br />
  &emsp;if (val < 900 or val == 900 or val > 900) { // ค่า 900 สามารถกำหนดปรับได้ตามค่าแสงในห้องต่างๆ การเปิด-ปิดไฟแบบ auto<br />
    &emsp;&emsp;if (val < 900){<br />
      &emsp;&emsp;&emsp;digitalWrite(LED_PIN_2, LOW);} // สั่งให้ LED ติดสว่าง<br />
   &emsp; &emsp;else{<br />
      &emsp;&emsp;&emsp;digitalWrite(LED_PIN_2, HIGH); // สั่งให้ LED ดับ}<br />
  }<br />

- Raindrop sensor ตรวจจับปริมาณน้ำฝน ถ้าฝนตก LED ติดและมีการแจ้งเตือนไปทางไลน์ >><br />
  &emsp;if (rainDigitalVal == 0 or rainDigitalVal == 1) { // สามารถกำหนดปรับค่าได้ตามสถานที่ต่างๆ sensor ตรวจจับน้ำฝน<br />
    &emsp;&emsp;if (rainDigitalVal == 0){<br />
      &emsp;&emsp;&emsp;digitalWrite(LED_PIN_3, HIGH);} // สั่งให้ LED ติดสว่าง<br />
      &emsp;&emsp;&emsp;LINE.notify("ฝนตกแล้ว เก็บผ้าเร็ว!"); //แจ้งเตือนพร้อมมีไฟ LED บอก<br />
    &emsp;&emsp;else{<br />
      &emsp;&emsp;&emsp;digitalWrite(LED_PIN_3, LOW); // สั่งให้ LED ดับ}<br />
  }<br />

- IR Infared sensor ตรวจจับสิ่งกีดขวาง สัญญาณกันขโมย ถ้ามีคนมาไฟจะติด และส่งแจ้งเตือนไปาทางไลน์ >><br />
  &emsp;if (val3 == 0 or val3 != 0) { // สามารถกำหนดปรับค่าได้ตามสถานที่ต่างๆ sensor ตรวจจับสิ่งกีดขวาง<br />
    &emsp;&emsp;if (val3 == 0){<br />
      &emsp;&emsp;&emsp;digitalWrite(LED_PIN_4, HIGH);} // สั่งให้ LED ติดสว่าง<br />
      &emsp;&emsp;&emsp;LINE.notify("มีคนมา!"); //แจ้งเตือนพร้อมมีไฟ LED บอก<br />
    &emsp;&emsp;else{<br />
      &emsp;&emsp;&emsp;digitalWrite(LED_PIN_4, LOW); // สั่งให้ LED ดับ}
  }
# ประโยชน์ที่คาดว่าจะได้รับ
1.	แบบจำลองการต่อวงจรนี้สามารถนำไปประยุกต์ใช้ได้จริงและมีประโยชน์ต่อผู้ใช้งาน
2.	แบบจำลองการต่อวงจรนี้สามารถนำไปต่อยอดในอนาคตได้
3.	ฝึกทักษาการเขียนโปรแกรมด้วยภาษา C และสามารถนำมาประยุกต์ใช้กับการต่อบอร์ด Arduino ได้
4.	ฝึกการทำงานเป็นกลุ่ม
# Member
1.	นายพีรพัฒน์ กิจพร้อมผล 63070125
2.	นางสาวรัชนีย์ ขันธิวงค์ 63070149
3.	นางสาวรุจรวี มีลา 63070151
4.	นางสาวอาภัสรา โมรัษเฐียร 63070188<br />
&emsp;รายงานนี้ป็นส่วนหนึ่งของวิชา Computer Programming สาขาวิชาเทคโนโลยีสารสนเทศ ภาคเรียนที่ 2 ปีการศึกษา 2563<br />
คณะเทคโนโลยีสารสนเทศ สถาบันเทคโนโลยีพระจอมเกล้าเจ้าคุณทหารลาดกระบัง

[poster]:https://github.com/rujrawee11/compro/blob/main/image/Poster.jpg
[all]:https://github.com/rujrawee11/compro/blob/main/image/รวม.jpg
