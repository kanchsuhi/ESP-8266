#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include<WiFiClient.h>

const char* ssid = "kanchsuhi yalini";  
const char* password = "kanchu123";   

const int trigger = 2;
const int echo = 0;
long T;
float distanceCM;
WiFiClient  client;

unsigned long myChannelField =791309;  // Channel ID
const char * myWriteAPIKey = "WJ9AAJ8YIK3EA0WA"; // Your write API Key

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
 }  
   
void loop()
{
 
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
  ThingSpeak.writeField(myChannelField,1, distanceCM, myWriteAPIKey);
  delay(1000);
}
