#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <Roomba.h>
#include <config.h>
#include <Roomba.h>
#include <TimeLib.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include "EspMQTTClient.h"
#include <PubSubClient.h> 

SoftwareSerial mySerial(SERIAL_RX, SERIAL_TX); // (RX, TX. inverted, buffer)



// Div
File UploadFile;
String fileName;
String  BSlocal = "0";
int FSTotal;
int FSUsed;


// webserver
ESP8266WebServer  server(80);
MDNSResponder   mdns;
WiFiClient client;


// Roomba setup
Roomba roomba(&Serial, Roomba::Baud115200);

EspMQTTClient client1(
  SSID,
  PASSWORD",
  "192.168.1.100",
  "MQTTUsername",
  "MQTTPassword",
  "TestClient1"
);

void setup() {

  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(SERIAL_RX, INPUT);
  pinMode(SERIAL_TX, OUTPUT);
  pinMode(Wake_Pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(Wake_Pin,LOW);
  WiFi.begin("Alice im WLAN",PASSWORD);
  //int i = 0;
  // put your setup code here, to run once:
}

void loop() {
  if (mySerial.available()) {
    Serial.print(mySerial.read());
  }
  server.handleClient();
  // put your main code here, to run repeatedly:
}



  server.on ( "/format", handleFormat );
  server.on("/", handle_root);
  server.on("/", handle_fupload_html);
  server.on("/api", handle_api);
  server.on("/updatefwm", handle_updatefwm_html);
  server.on("/fupload", handle_fupload_html);
  server.on("/filemanager_ajax", handle_filemanager_ajax);
  server.on("/delete", handleFileDelete);
  server.on("/roombastart", handle_roomba_start);
  server.on("/roombamax", handle_roomba_max);
  server.on("/roombastop", handle_roomba_stop);
  server.on("/roombaspot", handle_roomba_spot);
  server.on("/roombadock", handle_roomba_dock);
  server.on("/restart", handle_esp_restart);



// ROOT page
void handle_root()
{

  // get IP
  IPAddress ip = WiFi.localIP();
  ClientIP = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  delay(500);

  String title1     = panelHeaderName + String("Roombot Settings") + panelHeaderEnd;
  String IPAddClient    = panelBodySymbol + String("globe") + panelBodyName + String("IP Address") + panelBodyValue + ClientIP + panelBodyEnd;
  String ClientName   = panelBodySymbol + String("tag") + panelBodyName + String("Client Name") + panelBodyValue + espName + panelBodyEnd;
  String Version     = panelBodySymbol + String("info-sign") + panelBodyName + String("Roombot Version") + panelBodyValue + roombotVersion + panelBodyEnd;
  String Uptime     = panelBodySymbol + String("time") + panelBodyName + String("Uptime") + panelBodyValue + hour() + String(" h ") + minute() + String(" min ") + second() + String(" sec") + panelBodyEnd + panelEnd;


  String title2     = panelHeaderName + String("Pimatic server") + panelHeaderEnd;
  String IPAddServ    = panelBodySymbol + String("globe") + panelBodyName + String("IP Address") + panelBodyValue + host + panelBodyEnd;
  String User     = panelBodySymbol + String("user") + panelBodyName + String("Username") + panelBodyValue + Username + panelBodyEnd + panelEnd;


  String title3 = panelHeaderName + String("Commands") + panelHeaderEnd;
  String commands = panelBodySymbol + panelBodyName + panelcenter + roombacontrol + panelBodyEnd;


  server.send ( 200, "text/html", header + navbar + containerStart + title1 + IPAddClient + ClientName + Version + Uptime + title3 + commands + containerEnd + siteEnd);
}




// handles

void handle_api()
{
  // Get vars for all commands
  String action = server.arg("action");
  String value = server.arg("value");
  String api = server.arg("api");

  if (action == "clean" && value == "start")
  {
    handle_roomba_start();

  }

  if (action == "dock" && value == "home")
  {
    handle_roomba_dock();
  }
  if (action == "reset" && value == "true")
  {
    server.send ( 200, "text/html", "Reset ESP OK");
    delay(500);
    Serial.println("RESET");
    ESP.restart();
  }
}



void handle_esp_distance() {

  mySerial.write(142);
  delay(50);
  mySerial.write(19);
  delay(50);
  if (mySerial.available()) {
    Serial.println("..");
    Serial.print(Serial.read());
  }
  String data = String(Serial.read());
  Serial.println("Distance traveled");
 //handle_esp_pimatic(data, distancevar);
}

void handle_roomba_wake(){
   digitalWrite(Wake_Pin, HIGH);
   delay(100);
   digitalWrite(Wake_Pin, LOW);
   delay(500);
   digitalWrite(Wake_Pin, HIGH);
}

void handle_roomba_start()
{
  handle_roomba_wake();
  Serial.println("Starting");
  mySerial.write(128);
  delay(50);
  mySerial.write(131);
  delay(50);
  mySerial.write(135);
  Serial.println("I will clean master");
  handle_root();
}

void handle_roomba_max()
{
  handle_roomba_wake();
  Serial.println("Starting");
  mySerial.write(128);
  delay(50);
  mySerial.write(131);
  delay(50);
  mySerial.write(136);
  Serial.println("Maximum cleaning");
  handle_root();
}


void handle_roomba_spot()
{
  handle_roomba_wake();
  mySerial.write(128);
  delay(50);
  mySerial.write(131);
  delay(50);
  mySerial.write(134);
  Serial.println("Spot cleaning");
  handle_root();
}

void handle_roomba_stop()
{
  handle_roomba_wake();
  mySerial.write(128);
  delay(50);
  mySerial.write(131);
  delay(50);
  mySerial.write(133);
  Serial.println("STOP");
  handle_root();
}


void handle_roomba_dock(){
  handle_roomba_wake();
  mySerial.write(128);
  delay(50);
  mySerial.write(131);
  delay(50);
  mySerial.write(143);
  Serial.println("Thank you for letting me rest, going home master");
}

void handle_esp_restart(){
  ESP.restart();
}