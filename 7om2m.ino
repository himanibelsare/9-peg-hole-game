#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include "ThingSpeak.h"
 
const char* apiKey = "CMLH804A9YFKMN9A";     //  Enter your Write API key from ThingSpeak
const char* apiKey2 = "DKPQCTHR4PVQ1ZAF";
 
const char *ssid =  "n";     // replace with your wifi ssid and wpa2 key
const char *pass =  "nanini1234";
const char* server = "api.thingspeak.com";
const char* channelID = "1921666";
int channelNo = 3;
const char* channel2ID = "1958263";
int channel2No = 4;

// onem2m
#include <HTTPClient.h>
#define CSE_IP "esw-onem2m.iiit.ac.in"
#define CSE_PORT 443
#define OM2M_ORGIN "H36rb1:1Y7XRf"
#define OM2M_MN "/~/in-cse/in-name/"
#define OM2M_AE "Team-3"
#define OM2M_DATA_CONT "Node-1/Data"
#define INTERVAL 15000L

const char * ntpServer = "pool.ntp.org";

long int prev_millis = 0;
unsigned long epochTime;

HTTPClient http;

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime( & timeinfo)) {
    //Serial.println("Failed to obtain time");
    return (0);
  }
  time( & now);
  return now;
}




int sensorValue = 0;
int gsr_average = 0;
long int start_time = millis();
long int curr_time;
int tsecs;
int tmins;

int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int led5 = 0;
int led6 = 0;
int led7 = 0;
int led8 = 0;
int led9 = 0;

#define EMGPIN 16
#define GSR 5
#define LED1 23
#define LED2 33
#define LED3 32
#define LED4 34
#define LED5 35
#define LED6 22
#define LED7 21
#define LED8 19
#define LED9 18

WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);

       WiFi.mode(WIFI_STA);
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

      ThingSpeak.begin(client);

      pinMode(LED1, INPUT);
      pinMode(LED2, INPUT);
      pinMode(LED3, INPUT);
      pinMode(LED4, INPUT);
      pinMode(LED5, INPUT);
      pinMode(LED6, INPUT);
      pinMode(LED7, INPUT);
      pinMode(LED8, INPUT);
      pinMode(LED9, INPUT);
}
 
void loop() {

  //EMG
  int emg_sensor_value = analogRead(EMGPIN);
  float emg_voltage = emg_sensor_value * (5.0 / 1023.0);
  Serial.print("EMG Reading: ");
  Serial.println(emg_sensor_value);

  int x = ThingSpeak.writeField(channelNo, 1, emg_sensor_value, apiKey);
//  if(x == 200){
//    Serial.println("Channel update successful.");
//  }


  //GSR
  int sum;
  for(int i=0;i<10;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(5);
      }
   gsr_average = sum/10;
   Serial.println(gsr_average);

  x = ThingSpeak.writeField(channelNo, 2, gsr_average, apiKey);
//  if(x == 200){
//    Serial.println("Channel update successful.");
//  }

  //LEDs
  //LED 1
  if (digitalRead(LED1) == HIGH) {
      if (led1 == 0) {
        Serial.println("Pin 1 in");
        x = ThingSpeak.writeField(channel2No, 1, 1, apiKey2);
      }
      led1 = 1;
    }
    else if (digitalRead(LED1) == LOW) {
      if (led1 == 1) {
        Serial.println("Pin 1 out");
        x = ThingSpeak.writeField(channel2No, 1, 0, apiKey2);
      }
      led1 = 0;
    }

   //LED 2
   if (digitalRead(LED2) == HIGH) {
      if (led2 == 0) {
        Serial.println("Pin 2 in");
        x = ThingSpeak.writeField(channel2No, 2, 1, apiKey2);
      }
      led2 = 1;
    }
    else if (digitalRead(LED2) == LOW) {
      if (led2 == 1) {
        Serial.println("Pin 2 out");
        x = ThingSpeak.writeField(channel2No, 2, 0, apiKey2);
      }
      led2 = 0;
    }

    //LED 3
   if (digitalRead(LED3) == HIGH) {
      if (led3 == 0) {
        Serial.println("Pin 3 in");
        x = ThingSpeak.writeField(channel2No, 3, 1, apiKey2);
      }
      led3 = 1;
    }
    else if (digitalRead(LED3) == LOW) {
      if (led3 == 1) {
        Serial.println("Pin 3 out");
        x = ThingSpeak.writeField(channel2No, 3, 0, apiKey2);
      }
      led3 = 0;
    }

    //LED 4
   if (digitalRead(LED4) == HIGH) {
      if (led4 == 0) {
        Serial.println("Pin 4 in");
        x = ThingSpeak.writeField(channel2No, 4, 1, apiKey2);
      }
      led4 = 1;
    }
    else if (digitalRead(LED4) == LOW) {
      if (led4 == 1) {
        Serial.println("Pin 4 out");
        x = ThingSpeak.writeField(channel2No, 4, 0, apiKey2);
      }
      led4 = 0;
    }

    //LED 5
   if (digitalRead(LED5) == HIGH) {
      if (led5 == 0) {
        Serial.println("Pin 5 in");
        x = ThingSpeak.writeField(channel2No, 5, 1, apiKey2);
      }
      led5 = 1;
    }
    else if (digitalRead(LED5) == LOW) {
      if (led5 == 1) {
        Serial.println("Pin 5 out");
        x = ThingSpeak.writeField(channel2No, 5, 0, apiKey2);
      }
      led5 = 0;
    }

    //LED 6
   if (digitalRead(LED6) == HIGH) {
      if (led6 == 0) {
        Serial.println("Pin 6 in");
        x = ThingSpeak.writeField(channel2No, 6, 1, apiKey2);
      }
      led6 = 1;
    }
    else if (digitalRead(LED6) == LOW) {
      if (led6 == 1) {
        Serial.println("Pin 6 out");
        x = ThingSpeak.writeField(channel2No, 6, 0, apiKey2);
      }
      led6 = 0;
    }

    //LED 7
   if (digitalRead(LED7) == HIGH) {
      if (led7 == 0) {
        Serial.println("Pin 7 in");
        x = ThingSpeak.writeField(channel2No, 7, 1, apiKey2);
      }
      led7 = 1;
    }
    else if (digitalRead(LED7) == LOW) {
      if (led7 == 1) {
        Serial.println("Pin 7 out");
        x = ThingSpeak.writeField(channel2No, 7, 0, apiKey2);
      }
      led7 = 0;
    }

    //LED 8
   if (digitalRead(LED8) == HIGH) {
      if (led8 == 0) {
        Serial.println("Pin 8 in");
        x = ThingSpeak.writeField(channel2No, 8, 1, apiKey2);
      }
      led8 = 1;
    }
    else if (digitalRead(LED8) == LOW) {
      if (led8 == 1) {
        Serial.println("Pin 8 out");
        x = ThingSpeak.writeField(channel2No, 8, 0, apiKey2);
      }
      led8 = 0;
    }

    //LED 9
   if (digitalRead(LED9) == HIGH) {
      if (led9 == 0) {
        Serial.println("Pin 9 in");
        x = ThingSpeak.writeField(channelNo, 8, 1, apiKey);
      }
      led9 = 1;
    }
    else if (digitalRead(LED9) == LOW) {
      if (led9 == 1) {
        Serial.println("Pin 9 out");
        x = ThingSpeak.writeField(channelNo, 8, 0, apiKey);
      }
      led9 = 0;
    }

  // onem2m
  if (millis() - prev_millis >= INTERVAL) {
    epochTime = getTime();
    String data;
    String server = "https://" + String() + CSE_IP + ":" + String() + CSE_PORT + String() + OM2M_MN;

    http.begin(server + String() + OM2M_AE + "/" + OM2M_DATA_CONT + "/");

    http.addHeader("X-M2M-Origin", OM2M_ORGIN);
    http.addHeader("Content-Type", "application/json;ty=4");
    http.addHeader("Content-Length", "100");

    data = "[" + String(emg_sensor_value) + ", " + String(gsr_average) + ", " + String(led1) + ", " + String(led2) + ", " + String(led3) + ", " + String(led4) +", " + String(led5) +", " + String(led6) +", " + String(led7) +", " + String(led8) +", " + String(led9) +  + "]";
    String req_data = String() + "{\"m2m:cin\": {"

                      +
                      "\"con\": \"" + data + "\","

                      +
                      "\"lbl\": \"" + "V1.0.0" + "\","

                      //+ "\"rn\": \"" + "cin_"+String(i++) + "\","

                      +
                      "\"cnf\": \"text\""

                      +
                      "}}";
    int code = http.POST(req_data);
    http.end();
    Serial.println(code);
    prev_millis = millis();
  }

  delay(1000);
}
