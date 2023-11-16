/*Peter Rhoades©:
Sunday 14/11/21:
Folder Summer_House_Temp_Hum_DHT22_Multi:
Send data to thingSpeak Channel Inc SHT21 Temperature & Humidity®: 
Summer House Temperature DHT22 : 
%%channel_1654219_field_1%%°C 
Summer House Humidity DHT22: 
%%channel_1654219_field_2%%% 
*/
#include <ESP8266WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
WiFiClient  client;
#include "DHTesp.h"
DHTesp dht;
char ssid[] = "VM5774222"; //WiFi Name:  
char password[] = "b3rVddgtbvmp"; //WiFi Pass Code:   
unsigned long WriteChannelNumber = 1654219; //Write Channel Number and API Key:
const char * WriteAPIKey = "7D6AYJFNFFL31Q3K";
int DL = 1500;; //Delay Period 
 
void setup() 
{
Serial.begin(9600);
Serial.println("In Setup");
ThingSpeak.begin(client);  //Initialize ThingSpeak:
dht.setup(D4, DHTesp::DHT22); // Connect DHT sensor to D4
wificonnect();
}

void wificonnect()
 {
 WiFi.begin(ssid, password);
  Serial.println(".....Conneting to Home WiFi.....");
   while(WiFi.status() != WL_CONNECTED){
  Serial.print("...");
 delay(500);  
 }
 Serial.println();
  Serial.print("WiFi Name:"); Serial.print(WiFi.SSID());
   Serial.print("   IP Address:");
    Serial.print(WiFi.localIP());
     Serial.print("   RRSI:");
      Serial.println(WiFi.RSSI());
     Serial.println("");
  Serial.println("08-06-23 Now Using ThingSpeak Library.");
  Serial.println("Folder //Summer_House_Temp_Hum_DHT22_Multi.");
  Serial.println("08-06-23 Now Using ThingSpeak Library, Program Name Changed.");
  Serial.println("05-10-23 setField(3,(int)****) added to Print int and float.");
  Serial.println("Completed Setup");
  Serial.println("080620231834:\n\n\n");
 delay(DL * 2);
 }
    
void loop() 
    {        
  float hum = dht.getHumidity();
  float temp = dht.getTemperature();
  Serial.println();
  Serial.println("Summer House DHT22");
  Serial.print("Temperature "); Serial.print(temp, 2);  Serial.println("°C");
  Serial.print("Humidity ");    Serial.print(hum, 2);     Serial.println("%");
 Serial.print("Temperature int "); Serial.print((int)temp); Serial.println("°C");
 Serial.print("Humidity int ");    Serial.print((int)hum); Serial.println("%");
  ThingSpeak.setField(1, temp); //Field 1 Write:
  ThingSpeak.setField(2, hum); //Field 2 Write:
  ThingSpeak.setField(3,(int)temp); //Field 3 Write:
  ThingSpeak.setField(4,(int)hum); //Field 4 Write:
  ThingSpeak.writeFields(WriteChannelNumber, WriteAPIKey); //Write Fields 1,2,2, as Multiple:
  int statusCode = ThingSpeak.getLastReadStatus();
if(statusCode == 200)
 {
 Serial.print("Status Code "); Serial.print(statusCode); Serial.println(" ThingSpeak Multiple Write Completed\n");
 }
 delay(DL); 
 }
