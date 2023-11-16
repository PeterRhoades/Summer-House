
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "Adafruit_SHT31.h" //0x44-SHT31 Temperature & Humidity:
#include <BME280I2C.h> //0x76-BME280 Temperature, Humidity & Pressure:
#include "ThingSpeak.h" // Always include thingspeak header file after other header files and custom macros
WiFiClient  client;
char ssid[] = "VM5774222"; //WiFi Name:  
char password[] = "b3rVddgtbvmp"; //WiFi Pass Code:   
unsigned long WriteChannelNumberBME = 1341661; //Write Channel Number and API Key:
const char * WriteAPIKeyBME = "GPF7FSACWMHFYY4M";
unsigned long WriteChannelNumberSHT = 2253593;
const char * WriteAPIKeySHT = "NV5R8RZ8B7TE3JNI";//I
BME280I2C bme; //0x76 BME280 Temperature, Pressure & Himidity:
Adafruit_SHT31 sht31 = Adafruit_SHT31();
int DL = 1500; //Delay Period:

void setup() 
{
Serial.begin(9600);  //Initialize Serial:
Serial.println("In Setup");
 Serial.println("SHT31 test");
    if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
    }
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
 Serial.println("Send data via ESP8266 to thingSpeak Channel Inc BME280 & SHT31.");
 Serial.println("Folder  Summer_BME280_SHT3X_Multi.");
 Serial.println("08-06-23 Now Using ThingSpeak Library, Program Name Changed.");
 Serial.println("setField(3, pres / 100 + 10) changed to send mBar to Thingspeak.");
 Serial.println("04-09-23 enableHeater disabled.");
 Serial.println("05-10-23 setField(3,(int)****) added to Print int and float [int d = (int)tempSHT].");
 Serial.println("Completed Setup\n");
 Serial.println("Code 1249280823\n\n\n");
 delay(DL * 2);
 }

void loop() 
 {
float temp(NAN), hum(NAN), pres(NAN);
 BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);
   float tempSHT = sht31.readTemperature();
 float humSHT = sht31.readHumidity();
  Serial.println("Summer House BME280");
  Serial.print("Temberature "); Serial.print(temp);             Serial.println("°C");
  Serial.print("Humidity ");    Serial.print(hum);              Serial.println("%");
  Serial.print("Pressure ");    Serial.print(pres / 100 + 10);  Serial.println("mbar");
Serial.print("Temperature int "); Serial.print((int)temp); Serial.println("°C");
Serial.print("Humidity int ");    Serial.print((int)hum); Serial.println("%");
Serial.print("Pressure int ");    Serial.print((int)pres /100 + 10); Serial.println("mbar\n");
  Serial.println("Summer House SHT31");
   Serial.print("Temperature  "); Serial.print(tempSHT); Serial.println("°C");
    Serial.print("Humidity  "); Serial.print(humSHT); Serial.println("%");
Serial.print("Temperature int "); Serial.print((int)tempSHT); Serial.println("°C");
Serial.print("Humidity int ");    Serial.print((int)humSHT); Serial.println("%");

 ThingSpeak.setField(1, temp); //Field 1 Write:
  ThingSpeak.setField(2, hum); //Field 2 Write:
   ThingSpeak.setField(3, pres / 100 + 10); //Field 3 Write:
  ThingSpeak.setField(4, (int)temp); //Field 1 Write:
 ThingSpeak.setField(5, (int)hum); //Field 2 Write:
ThingSpeak.setField(6, (int)pres / 100 + 10); //Field 3 Write:
    ThingSpeak.writeFields(WriteChannelNumberBME, WriteAPIKeyBME); //Write Fields 1,2,3 as Multiple:
     int statusCodeBMP = ThingSpeak.getLastReadStatus();
 ThingSpeak.setField(1, tempSHT);
  ThingSpeak.setField(2, humSHT);
  ThingSpeak.setField(3, (int)tempSHT);
  ThingSpeak.setField(4, (int)humSHT);
   ThingSpeak.writeFields(WriteChannelNumberSHT, WriteAPIKeySHT); //Write Fields 1,2 as Multiple:
    int statusCodeSHT = ThingSpeak.getLastReadStatus();
if(statusCodeBMP == 200 && statusCodeSHT == 200)
 {
 Serial.print("Status Code SHT31  "); Serial.println(statusCodeSHT);
 Serial.println("                      ThingSpeak Multiple Write Completed");
 Serial.print("Status Code BMP280 "); Serial.println(statusCodeBMP); 
 Serial.println("                      ThingSpeak Multiple Write Completed\n");
 } 
 delay(DL);
 }
