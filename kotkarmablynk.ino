/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  NOTE: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL47Fcuv9eW"//id templatki
#define BLYNK_TEMPLATE_NAME "CatFeeder"//nazwa 
#define BLYNK_AUTH_TOKEN ""//token 

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>


char ssid[] = "Redmi Note 12 Pro"; //nazwa wifi
char pass[] = ""; //hasło do sieci
const long utcOffsetInSeconds = 3600; // offset wzgeledem utc+0

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

Servo myservo;
const int trigPin = 12;
const int echoPin = 14;

int startTime1;
int startTime2;
int startTime3;
int startTime4;
int catFeed = 0;
float duration, distance;

int  hh, mm, ss, server_time;

void setup()
{
   myservo.attach(2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); 
 WiFi.begin(ssid, pass);
 Serial.print(ssid); Serial.println(" ...");
    myservo.write(0);
 int i = 0;
 while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.print(++i); Serial.print(' ');
 }
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timeClient.begin();
}

BLYNK_WRITE(V0)
{
    int value = param.asInt();
    if(value == 1&&catFeed==0)
      catFeed=1;
}
BLYNK_WRITE(V1)
{
    startTime1 = param.asInt();
}
BLYNK_WRITE(V2)
{
    startTime2 = param.asInt();
}
BLYNK_WRITE(V3)
{
    startTime3 = param.asInt();
}
BLYNK_WRITE(V4)
{
    startTime4 = param.asInt();
}


void loop()
{
  timeClient.update();
 hh = timeClient.getHours();
 mm = timeClient.getMinutes();
 ss = timeClient.getSeconds();
 server_time = 3600*hh + 60*mm + ss;
   if(startTime1 == server_time){
    catFeed=1;
   }
   if(startTime2 == server_time){
    catFeed=1;
   }
  if(startTime3 == server_time){
    catFeed=1;
   }
   if(startTime4 == server_time){
    catFeed=1;
   }
  if(catFeed==1)
  {
    feed();
    catFeed=0;
    level();
  }
  Blynk.run();
}

void feed()
{
    myservo.write(120);
    delay(1000);
    myservo.write(0);
}

void level(){
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  
  Blynk.virtualWrite(V5, 21 - distance);
}