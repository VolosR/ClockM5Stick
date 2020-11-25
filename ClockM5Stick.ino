#include <M5StickC.h>
#include "AXP192.h"
#include "7seg20.h"

#include "ani.h"


#define grey 0x65DB

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;
int bright[4]={8,9,10,12};
void setup() {
 pinMode(39,INPUT_PULLUP);
  pinMode(37,INPUT_PULLUP);
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setSwapBytes(true);
  M5.Lcd.setTextSize(1);

M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
  //M5.Lcd.setTextColor(grey,TFT_BLACK);
 
  //M5.Lcd.fillRect(112,12,40,40,TFT_RED);  
// M5.Lcd.pushImage(112,12,40,40,ani[frame]);
 M5.Axp.EnableCoulombcounter(); 
 M5.Axp.ScreenBreath(bright[0]);

  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = 10;
  TimeStruct.Minutes = 16;
  TimeStruct.Seconds = 00;
 // M5.Rtc.SetTime(&TimeStruct); set your time here uncomment
  RTC_DateTypeDef DateStruct;
  DateStruct.WeekDay = 2;
  DateStruct.Month = 11;
  DateStruct.Date = 24;
  DateStruct.Year = 2020;
 // M5.Rtc.SetData(&DateStruct); .....set your date here, uncomment
}

int H=0;
int M=0;

String ho="";
String mi="";
String se="";

String days[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

int c=0;
int pres=0;
bool spavanje=0;
bool inv=0;

int frame=0;
void loop() {
  
  spavanje=0;
  if(digitalRead(37)==0)
  {
    if(pres==0)
        {
          pres=1;
          c++;
          if(c>3)
          c=0;
           M5.Axp.ScreenBreath(bright[c]);
           M5.Lcd.fillRect(146,55,8,30,TFT_BLACK);
          }
    
    }else{pres=0;}

  
  M5.Rtc.GetTime(&RTC_TimeStruct);
  M5.Rtc.GetData(&RTC_DateStruct);
  M5.Lcd.setCursor(0, 15);
  M5.Lcd.setTextFont(0);

 M5.Lcd.drawString(String( M5.Axp.GetBatVoltage())+" V  ",114,3); 
 M5.Lcd.setFreeFont(&DSEG7_Classic_Bold_30);
 
 if(H!=int(RTC_TimeStruct.Hours) || M!=int(RTC_TimeStruct.Minutes)){
 ho=String(RTC_TimeStruct.Hours);
 if(ho.length()<2)
 ho="0"+ho;

  mi=String(RTC_TimeStruct.Minutes);
 if(mi.length()<2)
 mi="0"+mi;
 M5.Lcd.drawString(ho+":"+mi,2,46);
 H=int(RTC_TimeStruct.Hours);
 M=int(RTC_TimeStruct.Minutes);
 }
 
 // M5.Lcd.printf("Week: %d\n",RTC_DateStruct.WeekDay);
      se=String(RTC_TimeStruct.Seconds);
   if(se.length()<2)
      se="0"+se;
  M5.Lcd.drawString(se,112,57,4);
  
M5.Lcd.drawString(days[RTC_DateStruct.WeekDay-1]+"    ",4,0,2);
  M5.Lcd.setTextColor(grey,TFT_BLACK);
  
   M5.Lcd.drawString(String(RTC_DateStruct.Date)+"/"+String(RTC_DateStruct.Month),4,20,4);
   M5.Lcd.drawString(String(RTC_DateStruct.Year),70,28,2);
  M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);

  
 for(int i=0;i<c+1;i++)
 M5.Lcd.fillRect(146,73-(i*5),8,3,grey); 

 if(digitalRead(39)==LOW){
 while(digitalRead(39)==LOW);
 M5.Lcd.invertDisplay(inv);
 inv=!inv;
 }

M5.Lcd.pushImage(112,12,40,40,ani[frame]);
frame++;
if(frame==132)
frame=0;

  delay(12);
}
