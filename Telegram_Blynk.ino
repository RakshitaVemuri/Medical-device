#include <Blynk.h>


#define BLYNK_PRINT Serial

#include<String.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "CTBot.h"        //arduino json should be 5.13.2v
//#define  msg_sender_id 884359289    
//#define  msg_sender_id 868282279
#define  msg_sender_id 836767397

String readstring;
CTBot myBot;
String ssid = "OnePlus 8T";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "Fly2moon21!";
 // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
//String token = "1178269773:AAGFtUmQnDpFfkEsAuzI-ML2CZwr5eLWM_4";
String token = "1843467546:AAE_VAtn2BwiJnG-6zl_Hge-mATdfg3592w";

uint8_t led = D0;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)    
char Start_buff[70]; 
int i,z;             
char ch;
int str_len;
 char textmessage[20];
 int sw=D1;
TBMessage msg;
void MESSAGE_SEND();
void WAITING();
void SEND_SERVER();
void buffer_clear();
//char auth[] = "uZrnRrW5G1lHjez0OfrrHMz11SZljBO_";
char auth[] = "DIMKaQkuI-IjwglhdBnuS3qODEdVKLKy";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid1[] = "OnePlus 8T";
char pass1[] = "Fly2moon21!";
//WidgetLCD lcd(V0);
//char ch;

void setup()
{
 
  Serial.begin(9600);
 
  pinMode(sw,INPUT);
  Blynk.begin(auth, ssid1, pass1);
  delay(2000);
  // You can also specify server:   
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
   Serial.println("Starting TelegramBot...");

    // connect the ESP8266 to the desired access point
    myBot.wifiConnect(ssid, pass);

    // set the telegram bot token
    myBot.setTelegramToken(token);
   // myBot.setTelegramToken(token1);

    // check if all things are ok
    if (myBot.testConnection())
        Serial.println("\ntestConnection OK");
    else
        Serial.println("\ntestConnection NOK");
  Blynk.virtualWrite(V0,"OBD...");
   Blynk.virtualWrite(V0,"\r\n");
   TEST();
    //MESSAGE_SEND();
}
char Serial_read(void)
{
      char ch;
      while(Serial.available() == 0);
      ch = Serial.read(); 
      return ch;
}

void TEST()
{
String ssid = "OnePlus 8T";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "Fly2moon21!";
 // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "1843467546:AAE_VAtn2BwiJnG-6zl_Hge-mATdfg3592w";


char auth[] = "DIMKaQkuI-IjwglhdBnuS3qODEdVKLKy";
//char auth[] = "uZrnRrW5G1lHjez0OfrrHMz11SZljBO_";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid1[] = "OnePlus 8T";
char pass1[] = "Fly2moon21!";


uint8_t led = D0;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)                            

 TBMessage msg;


    // initialize the Serial
    Serial.begin(9600);
    Serial.println("Starting TelegramBot...");

    // connect the ESP8266 to the desired access point
    myBot.wifiConnect(ssid, pass);

    // set the telegram bot token
    myBot.setTelegramToken(token);

    // check if all things are ok
    if (myBot.testConnection())
        Serial.println("\ntestConnection OK");
    else
        Serial.println("\ntestConnection NOK");

    // set the pin connected to the LED to act as output pin
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH); // turn off the led (inverted logic!)
   //myBot.sendMessage(msg_sender_id, "WELCOME TO TECHNOFLY OPERATE THE DEVICES"); 
   //TEST();
MESSAGE_SEND();
  
while(1) {
    // a variable to store telegram message data

    // if there is an incoming message...
    if (myBot.getNewMessage(msg)) {

        if (msg.text.equalsIgnoreCase("START")) {              // if the received message is "LIGHT ON"...
            digitalWrite(led, HIGH);                               // turn on the LED (inverted logic!)
//            myBot.sendMessage(msg.sender.id, "OBD...");  // notify the sender
         myBot.sendMessage(msg.sender.id, "Door to Door Medicare...");
         Serial.println(msg.sender.id);
            WAITING();
//loop();
//Check();
           // Brake();
        }
         else {                                                    // otherwise...
            // generate the message for the sender
            String reply;
            reply = (String)"Welcome " + msg.sender.username + (String)". Try START";
            myBot.sendMessage(msg.sender.id, reply);             // and send it
            
        }
    }
    // wait 500 milliseconds
    delay(500);
}
 
  
}

void loop()
{

  //Blynk.run();
 //serialEvent();
//WAITING();
//SEND_SERVER();
//Brake();
Check();
}
void Brake()
{
  if(digitalRead(sw)==LOW)
  {
    int j;
    for(j=0;j<5;j++)
    {
    Serial.print("Brake Failure");
    Serial.print('B');
    myBot.sendMessage(msg_sender_id, "Brake Failure"); 
    buffer_clear();
    delay(2000);
//    break;
  }
  }
//  break;
}
void Check()
{
   while(1)
 {      
  buffer_clear();
  if(Serial.available()>0)
   {                  
          while(Serial_read()!='$');
          i=0;
          while((ch=Serial_read())!='#')
          {
            Start_buff[i] = ch;
             i++;
          }  
          Start_buff[i]='\0';
       } 
       Serial.print(Start_buff);
          
//                   readstring += c;
//                   if (readstring.length() > 0)
//                   { 
//                   Serial.print(readstring);
                   myBot.sendMessage(msg_sender_id, Start_buff); 
                   Brake();
//                   buffer_clear();
//                   delay(1000);
//                  if(readstring=="TEMP:")
//                  {
////                    Serial.print('B');
//              //Serial.print(ch);
//              myBot.sendMessage(msg_sender_id, readstring); 
//              buffer_clear();
//                   // delay(1000);
//                   // loop();
//                  }
//                   }

//  if((Start_buff[0]=='E'))
//    {
//       Brake();
//      //Blynk.virtualWrite(V0,Start_buff);
//      // Blynk.virtualWrite(V0,"\r\n");
//       //delay(2000);
//       myBot.sendMessage(msg_sender_id, Start_buff); 
//       Brake();
//    buffer_clear();
//    }
//    if((Start_buff[0]=='A'))
//    {
//       Brake();
//      //Blynk.virtualWrite(V0,Start_buff);
//      // Blynk.virtualWrite(V0,"\r\n");
//       //delay(2000);
//       myBot.sendMessage(msg_sender_id, Start_buff); 
//       Brake();
//    buffer_clear();
//    }
//    if((Start_buff[0]=='C'))
//    {
//       Brake();
//      //Blynk.virtualWrite(V0,Start_buff);
//      // Blynk.virtualWrite(V0,"\r\n");
//       //delay(2000);
//       myBot.sendMessage(msg_sender_id, Start_buff); 
//       Brake();
//    buffer_clear();
//    }
//    if(strcmp(Start_buff,Start_buff)==0)
//    {
////       Serial.println("3333");
////      Blynk.virtualWrite(V0,Start_buff);
////       Blynk.virtualWrite(V0,"\r\n");
////       delay(2000);
//Brake();
//       myBot.sendMessage(msg_sender_id, Start_buff); 
//    buffer_clear();
//    }
}
}
void MESSAGE_SEND()
{
   myBot.sendMessage(msg_sender_id, "SEND START TO CONTINUE"); 
  // myBot.sendMessage(msg_sender_id1, "WELCOME TO ATM"); 
  
}

void WAITING()
{
   Serial.println("WAITE");
  
  buffer_clear();
  msg.text[0]='\0';
        msg.text[1]='\0';
         msg.text[2]='\0' ;
         msg.text[3]='\0';
          msg.text[4]='\0';
           msg.text[5]='\0';
           
 while(1)
 {      buffer_clear();
    Blynk.run();
      if (Serial.available() > 0)
      {
         //Serial.println("halo");
        
          while(Serial_read()!='$');
          i=0;
          while((ch=Serial_read())!='#')
          {
            Start_buff[i] = ch;
             i++;
          }  
          Start_buff[i]='\0';
       }
     Serial.println(Start_buff);
     myBot.sendMessage(msg_sender_id, Start_buff); 
     delay(1000);
     Blynk.virtualWrite(V2,Start_buff);
       Blynk.virtualWrite(V2,"\r\n");
       delay(2000);
//     buffer_clear();
//     MESSAGE_RECEIVE_1();
    
//    if((Start_buff[0]=='E'))
//    {
//       Serial.println("111");
//      //Blynk.virtualWrite(V0,Start_buff);
//      // Blynk.virtualWrite(V0,"\r\n");
//       //delay(2000);
//       myBot.sendMessage(msg_sender_id, Start_buff); 
//       Brake();
//    buffer_clear();
//    }
    
   if(strcmp(Start_buff,"Manual")==0)
    {
       
      Blynk.virtualWrite(V2,"Door to Door Medicare");
       Blynk.virtualWrite(V2,"\r\n");
       delay(2000);
     //  myBot.sendMessage(msg_sender_id,"Door to Door Medicare"); 
    while(1)
    {
    buffer_clear();
    MESSAGE_RECEIVE_1();
    }
    }


    
}

}
void MESSAGE_RECEIVE_1()
{
    msg.text[0]='\0';
        msg.text[1]='\0';
         msg.text[2]='\0' ;
         msg.text[3]='\0';
          msg.text[4]='\0';
           msg.text[5]='\0';
           buffer1_clear();
           Serial.println("enter jjj");
    myBot.sendMessage(msg_sender_id, "OPERATE THE DEVICES....");        
   while(1)
   {
     if (myBot.getNewMessage(msg))
     { 
    
      String message = msg.text;
      String str = "C";
      String all = str + message;
      // Convert String to char array
      int str_len = message.length() + 1;
      char textmessage[str_len];
      message.toCharArray(textmessage,str_len);
          //delay(1000); 

      Serial.println(textmessage);
   
      if(strcmp(textmessage,"*RFID#")==0)
    {
       Serial.println("aaaa"); 

       Blynk.virtualWrite(V2,textmessage);
       Blynk.virtualWrite(V2,"\r\n");
           buffer1_clear();
            WAITING();
    } 
     if(strcmp(textmessage,"LIGHT OFF")==0)
    {
       Serial.println("bbbb"); 

//       Blynk.virtualWrite(V0,"BILL NOT PAID ");
//       Blynk.virtualWrite(V0,"\r\n");
           buffer1_clear();
            WAITING();
    } 
    
    }
 
    delay(500);
    //WAITING();
//    if(Serial_read()=='$')
//    {
//     if (Serial.available() > 0)
//      {
//         Serial.println("halo");
//        
//          while(Serial_read()!='$');
//          i=0;
//          while((ch=Serial_read())!='#')
//          {
//            Start_buff[i] = ch;
//             i++;
//          }  
//          Start_buff[i]='\0';
//       }
//       myBot.sendMessage(msg_sender_id,Start_buff);      
//   
//   }
   }
  
}

void buffer_clear()
{
  for(z=0;z<60;z++)
  {
    Start_buff[z]='\0';
//    textmessage[z]='\0';
    
  } 
}
void buffer1_clear()
{
  for(z=0;z<5;z++)
  {
   
   textmessage[z]='\0';
    
  } 

}
