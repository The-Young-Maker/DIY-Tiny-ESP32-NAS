
//WiFi library
#include <WiFi.h>
//SD cards library
#include <SPI.h>
#include <SD.h>
#include <FS.h>

//Web server library

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

//Discovery related library
#include <ESPmDNS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

/* Hardware Configurations */
#define CS_PIN 5 // 5, 2, 4

/* Software Global Variables */
AsyncWebServer server(80);
String adminUsername = "";
String adminPassword = "";
String mdnsName = "webstick";
String authSession = "";

/* Time Keeping */
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

/* Debug variables */

/* Function definations */
String loadWiFiInfoFromSD();


void setup() {
  // Setup Debug Serial Port
  Serial.begin(115200);
  
  //Try Initialize SD card (blocking)
  while (!SD.begin(CS_PIN,SPI,4000000U,"/sd",15U,false)){
    Serial.println("SD card initialization failed. Retrying in 3 seconds...");
    delay(3000);
  }
  Serial.println("SD card initialized");
  // Serial.println("\n\nStorage Info:");
  // Serial.println("----------------------");
  // getSDCardTotalSpace();
  // getSDCardUsedSpace();
  // Serial.println("----------------------");
  // Serial.println();

  //Connect to wifi based on settings (cfg/wifi.txt)
  initWiFiConn();

  //Load admin credentials from SD card (cfg/admin.txt)
  initAdminCredentials();
  
  //Start mDNS service
  initmDNSName();
  if (!MDNS.begin(mdnsName)){
      Serial.println("mDNS Error. Skipping.");
  }else{
      Serial.println("mDNS started. Connect to your webstick using http://" + mdnsName + ".local");
      MDNS.addService("http", "tcp", 80);
  }

  //Start NTP time client
  timeClient.begin();
  Serial.print("Requesting time from NTP (unix timestamp): ");
  timeClient.update();
  Serial.println(getTime());

  //Initialize database
  DBInit();

  //Resume login session if any
  initLoginSessionKey();
  
  // Start listening to HTTP Requests
  initWebServer();
}
  

void loop(){
  timeClient.update();
  delay(10);
}
