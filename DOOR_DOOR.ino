
#include <Wire.h>
#include<LiquidCrystal.h>
#include "MAX30100_PulseOximeter.h"
#include<SoftwareSerial.h>
SoftwareSerial RFID(10,11);
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
LiquidCrystal lcd(13,12,6,5,4,3);

int IN1=8;
int IN2=9;
int IN3=15;
int IN4=16;

int relay=7;

char Start_buff[70];
char ch;
String message="";
//char CARD_1[]="$0011913087";
char CARD_1[]="5500E8DDE787";

void onBeatDetected()
{
    //Serial.println("Beat!");
}
 
void setup()
{
  lcd.begin(16,2);
  RFID.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  pinMode(relay,OUTPUT);
  
    Serial.begin(9600);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Door To Door");
    lcd.setCursor(0,1);
    lcd.print("Medicare");
    delay(2000);
    //Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        //Serial.println("FAILED");
        lcd.clear();
        lcd.print("FAILED");
        for(;;);
    } else {
        //Serial.println("SUCCESS");
        lcd.clear();
        lcd.print("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);



}
 
void loop()
{
//    
//  //  delay(1000);
    //SENSOR_READING();
   // delay(5000);
   Manual();
    
}
int SENSOR_READING()
{
  
    int i=0;
    while(i<10000)
    {
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
    {
//        Serial.print("Heart rate:");
//        Serial.print(pox.getHeartRate());
//        Serial.print("bpm / SpO2:");
//        Serial.print(pox.getSpO2());
//        Serial.println("%");
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("HB:");
         lcd.setCursor(4,0);
         lcd.print(pox.getHeartRate());
         // lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("SPO2:");
         lcd.setCursor(7,1);
         lcd.print(pox.getSpO2());
//         //delay(1000);
        tsLastReport = millis();
      
        
    }
    if(i==9000)
      {
      Serial.print("$Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%#");  
      }
    i++;
    }
    Temp_Monitor();

  
}
void FORWARD()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("FORWARD....");
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  
} 
void REVERSE()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("REVERSE....");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
} 
void LEFT()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LEFT....");
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
} 
void RIGHT()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RIGHT....");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  
} 
void STOP()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("STOP....");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
//       lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("PLACE THE FINGER");
//  lcd.setCursor(0,1);
//  lcd.print("ON SENSOR.......");
//  delay(2000);
  
} 
void Temp_Monitor()
{
  float    vout=analogRead(A0);
    vout=(vout*500)/1023;
float    tempc=vout;
   
    Serial.print("$TEMP:");
    Serial.print(tempc);
    Serial.println("C#");
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Temp:");
         lcd.setCursor(6,0);
         lcd.print(tempc);
         lcd.print("C");
        delay(1000);
//return tempc;
//FORWARD();
//    delay(2000);
//    STOP();
//    delay(1000);
//setup();
//if (!pox.begin()) {
//        Serial.println("FAILED");
//        for(;;);
//    } else {
//        Serial.println("SUCCESS");
//    }
//     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
// 
//    // Register a callback for the beat detection
//    pox.setOnBeatDetectedCallback(onBeatDetected);
}
void Manual()
{
  Serial.println("$Manual#");
  while(1)
  {
if(Serial.available()>0)
   {     
    //Serial.print("$#");             
          while(Serial_read()!='*');
         int i=0;
          while((ch=Serial_read())!='#')
          {
            Start_buff[i] = ch;
             i++;
          }  
          Start_buff[i]='\0';
       } 
      // Serial.print(Start_buff);
       lcd.clear();
       lcd.print(Start_buff);
       if(!strcmp(Start_buff,"FORWARD"))
    {
      FORWARD();     
    }
     if(!strcmp(Start_buff,"STOP"))
    {
      STOP();     
    }
    if(!strcmp(Start_buff,"LEFT"))
    {
      LEFT();     
    }
    if(!strcmp(Start_buff,"RIGHT"))
    {
      RIGHT();     
    }
    if(!strcmp(Start_buff,"REVERSE"))
    {
      REVERSE();     
    }
     if(!strcmp(Start_buff,"RFID"))
    {
      RFID_CHECKING();     
    }
}
}
char Serial_read(void)
{
      char ch;
      while(Serial.available() == 0);
      ch = Serial.read(); 
      return ch;
}
void RFID_CHECKING()
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Scan the  ");
    lcd.setCursor(0,1);
    lcd.print("Card......   ");
    //Serial.print("Scan the Card...");
   
    delay(1000);
 while(1)
 {
    if(RFID.available()>0)
    {
     
      message=RFID.readString();
      int str_len = message.length() + 1;
      char textmessage[12];
      message.toCharArray(textmessage,str_len);
//      Serial.println(textmessage);
      textmessage[12]='\0';
      if(!strcmp(textmessage,"5500E8DDE787"))
      {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Name:XYZ ");
          lcd.setCursor(0,1);
          lcd.print("NO:123456789 ");
//          lcd.setCursor(0,1);
//          lcd.print("Ticket");
          Serial.println("$HOUSE NO1:XYZ");
          Serial.println("MOBILE NO:123456789#");
          delay(2000);  
        int i=0;
        while(i<2)
        {  
           if (!pox.begin()) {
//        Serial.println("FAILED");
lcd.clear();
lcd.print("FAILED");
        for(;;);
    } else {
//        Serial.println("SUCCESS");
lcd.clear();
lcd.print("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
     int a= SENSOR_READING();
      
//     if(i==4)
//     {
//      Serial.print("$");
//      Serial.print(a);
//      Serial.println("#");
//     }
    i++;
        }
        digitalWrite(relay,HIGH);
        delay(1000);
        digitalWrite(relay,LOW);
        loop();
        
}
if(!strcmp(textmessage,"5500E8DDE888"))
      {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Name:ABC ");
          lcd.setCursor(0,1);
          lcd.print("NO:987654321 ");
//          lcd.setCursor(0,1);
//          lcd.print("Ticket");
          Serial.println("$HOUSE NO2:ABC");
          Serial.println("MOBILE NO:987654321#");
          delay(2000);  
        int i=0;
        while(i<2)
        {  
           if (!pox.begin()) {
//        Serial.println("FAILED");
lcd.clear();
lcd.print("FAILED");
        for(;;);
    } else {
//        Serial.println("SUCCESS");
lcd.clear();
lcd.print("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
     int a= SENSOR_READING();
      
//     if(i==4)
//     {
//      Serial.print("$");
//      Serial.print(a);
//      Serial.println("#");
//     }
    i++;
        }
        digitalWrite(relay,HIGH);
        delay(1000);
        digitalWrite(relay,LOW);
        loop();
        
}
    }
    
 }
}
