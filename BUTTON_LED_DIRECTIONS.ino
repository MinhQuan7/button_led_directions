#define ERA_DEBUG
#define DEFAULT_MQTT_HOST "mqtt1.eoh.io"
// You should get Auth Token in the ERa App or ERa Dashboard
#define ERA_AUTH_TOKEN "8bc40d34-5480-4b8c-b31d-1f339f239dbb"

#include <Arduino.h>
#include <ERa.hpp>
#include <ERa/ERaTimer.hpp>

const char ssid[] = "SH-31";
const char pass[] = "KhongBiet";

#define led1 13
#define button1 12 //D1

boolean bt1_state = HIGH;
ERaTimer timer;

/* This function print uptime every second */


void setup() {
    /* Setup debug console */
    Serial.begin(115200);
    ERa.begin(ssid, pass);
    /* Setup timer called function every second */
    pinMode(led1,OUTPUT);
    pinMode(button1,INPUT);
    digitalWrite(led1,LOW);
}
ERA_WRITE(V0) 
{
  int p = param.getInt(); //LẤY GIÁ TRỊ CỦA CHÂN ẢO ĐÓ TÁC ĐỘNG VÔ PHẦN CỨNG
  digitalWrite(led1,p);
  ERa.virtualWrite(V1,p); // ĐỒNG BỘ TRẠNG THÁI BUTTON VÀ CHÂN ẢO TRÊN ERA

}
void loop() {
    ERa.run();
    check_button();
}
void check_button(){
  if(digitalRead(button1)== 1 ){ //Khi nut nhan duoc nhan xuong - kiem tra o phan cung
    if(bt1_state==HIGH){
      digitalWrite(led1,!digitalRead(led1));//Dao trang thai led - giữ trạng thái của led 
      ERa.virtualWrite(V0,digitalRead(led1));
       //khi button ON thi led cung on 
       //led va button cung trang thai nen gan trang thai button voi led
      ERa.virtualWrite(V1,digitalRead(led1));
      // Khi button phần cứng nhấn thì dẫn đến giá trị led phần cứng thay đổi và ta đọc giá trị khi tác dụng button phần cứng
      bt1_state=LOW;
      delay(200);
    }
  }else{
    bt1_state=HIGH; //Đảm bảo là bình thường chưa nhấn nút thì luôn ở mức cao 
  }

}


