
#include <ESP8266WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
WiFiClient  client;
char ssid[] = "VM5774222"; //WiFi Name:  
char password[] = "b3rVddgtbvmp"; //WiFi Pass Code:   
unsigned long WriteChannelNumber = 1341661; //Write Channel Number and API Key:
const char * WriteAPIKey = "GPF7FSACWMHFYY4M";
#include <BME280I2C.h> //0x76-BME280 Temperature, Humidity & Pressure:
#include <Wire.h>
BME280I2C bme; //0x76 BME280 Temperature, Pressure & Himidity:
int DL = 1300; //Delay Period:

void setup() 
{
Serial.begin(9600);  //Initialize Serial:
Serial.println("In Setup");
ThingSpeak.begin(client);  //Initialize ThingSpeak:
Wire.begin();
bme.begin(); 
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
 Serial.println("14/11/21 Created.");
 Serial.println("Send data via ESP8266 to thingSpeak Channel Inc BME280 Temperature, Humidity, Pressure.");
 Serial.println("Folder  Summer_House_Temp_Hum_Pres_BME280_Multi.");
 Serial.println("08-06-23 Now Using ThingSpeak Library, Program Name Changed.");
 Serial.println("setField(3, pres / 100 + 10) changed to send mBar to Thingspeak.");
Serial.println("Completed Setup");
 Serial.println("Code 080620231807");
 delay(DL * 4);
 }

void loop() 
 {
float temp(NAN), hum(NAN), pres(NAN);
 BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);
    Serial.println();
   Serial.println("Summer House BME280");
  Serial.print("Temberature "); Serial.print(temp);             Serial.println("°C");
 Serial.print("Humidity ");    Serial.print(hum);              Serial.println("%");
Serial.print("Pressure ");    Serial.print(pres / 100 + 10);  Serial.println("mbar");
       
       ThingSpeak.setField(1, temp); //Field 1 Write:
       ThingSpeak.setField(2, hum); //Field 2 Write:
       ThingSpeak.setField(3, pres / 100 + 10); //Field 2 Write:
      ThingSpeak.writeFields(WriteChannelNumber, WriteAPIKey); //Write Fields 1,2,2, as Multiple:
     int statusCode = ThingSpeak.getLastReadStatus();
if(statusCode == 200)
 {
 Serial.print("Status Code "); Serial.print(statusCode); Serial.println(" ThingSpeak Multiple Write Completed\n");
 } 
 delay(DL);
}
