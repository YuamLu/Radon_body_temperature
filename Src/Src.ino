#define eJumpTime 30
#define B1IO 0
#define B2IO 35

#include <TFT_eSPI.h>
#include <Button2.h>


TFT_eSPI tft = TFT_eSPI();
Button2 B1_ = Button2(B1IO);
Button2 B2_ = Button2(B2IO); 


int tagTime = 0;
int radonTemperatureSeptum = 500;
int T1_ = 0;
int T2_ = 0;
bool standerButtonState;
bool B1state = true;


void setup()
{
  Serial.begin(115200);

  pinMode(B1IO, INPUT_PULLUP);
  pinMode(B2IO, INPUT_PULLUP);
  standerButtonState = true;
  
  tft.begin();               // 初始化LCD
  tft.setRotation(1);  
  tft.fillScreen(TFT_BLACK); // 用全黑清除螢幕

  B1_.setPressedHandler(press);   //建立A按鍵按下Pressed的事件
  B2_.setPressedHandler(press);   //建立B按鍵按下Pressed的事件
  
}


void loop()
{ 
  
  radonTemperature();
  B1_.loop();  //重複按鍵的觸發設定
  B2_.loop();
  
}


void radonTemperature(){
  while(millis() - tagTime >= radonTemperatureSeptum){
  //tft.fillScreen(TFT_BLACK);
  /*產生亂數(體溫)*/
  float temp = 35.9 + random(15) * 0.1;
  String T = String(temp);
  String R = String(radonTemperatureSeptum);
  String t1_ = String(T1_);
  String t2_ = String(T2_);
  tft.setRotation(0);        // 螢幕正立(TTGO基準)
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FreeSerifBold12pt7b);
  tft.setCursor(10, 120);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  //tft.fillScreen(TFT_BLACK);
  tft.printf(T.c_str());

  /*調整速率版
  tft.setCursor(50,220);
  tft.setTextSize(1);
  tft.printf(R.c_str());
  tagTime = millis();
  Serial.println(R.c_str());
  tagTime = millis();*/

  tft.setCursor(0,20);
  tft.setTextSize(1);
  tft.printf(t1_.c_str());
  
  tft.setCursor(0,220);
  tft.setTextSize(1);
  tft.printf(t2_.c_str());
  


  
  tagTime = millis();
  }
}
void press(Button2& btn) {
    if (btn == B1_) {   //按下A按鍵
      T1_ ++;
    } else if (btn == B2_) {  //按下B按鍵
      T2_ ++;
    }
}
/*//調整速率版
void press(Button2& btn) {
    if (btn == B1_) {   //按下A按鍵
      if(radonTemperatureSeptum >50){
      radonTemperatureSeptum -= 50;
      }
    } else if (btn == B2_) {  //按下B按鍵
      radonTemperatureSeptum += 50;
    }else{
      radonTemperatureSeptum += 500;
    }
}
*/
