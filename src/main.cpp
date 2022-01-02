#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include "EspMQTTClient.h"
#include <PubSubClient.h> 
#include <Roomba.h>
#include <config.h>
#include <TimeLib.h>

SoftwareSerial mySerial(SERIAL_RX, SERIAL_TX); // (RX, TX. inverted, buffer)


String ClientIP;

// Div
File UploadFile;
String fileName;
String  BSlocal = "0";
int FSTotal;
int FSUsed;


// webserver
ESP8266WebServer server(80);
MDNSResponder   mdns;
WiFiClient client;




void setup() {

  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(SERIAL_RX, INPUT);
  pinMode(SERIAL_TX, OUTPUT);
  pinMode(Wake_Pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(Wake_Pin,LOW);
  WiFi.begin("Alice im WLAN",PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
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

//HTML
String header       =  "<html lang='de'><head><title>Roombot control panel</title><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><link rel='stylesheet' href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js'></script><script src='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js'></script></head><body>";
String navbar       =  "<nav class='navbar navbar-default'><div class='container-fluid'><div class='navbar-header'><a class='navbar-brand' href='/'>Roombot control panel</a></div><div><ul class='nav navbar-nav'><li><a href='/'><span class='glyphicon glyphicon-info-sign'></span> Status</a></li><li class='dropdown'><a class='dropdown-toggle' data-toggle='dropdown' href='#'><span class='glyphicon glyphicon-cog'></span> Tools<span class='caret'></span></a><ul class='dropdown-menu'><li><a href='/updatefwm'><span class='glyphicon glyphicon-upload'></span> Firmware</a></li><li><a href='/filemanager.html'><span class='glyphicon glyphicon-file'></span> File manager</a></li><li><a href='/fupload'> File upload</a></li></ul></li><li><a href='https://github.com/incmve/roomba-eps8266/wiki' target='_blank'><span class='glyphicon glyphicon-question-sign'></span> Help</a></li></ul></div></div></nav>";
String containerStart   =  "<div class='container'><div class='row'>";
String containerEnd     =  "<div class='clearfix visible-lg'></div></div></div>";
String siteEnd        =  "</body></html>";

String panelHeaderName    =  "<div class='col-md-4'><div class='page-header'><h1>";
String panelHeaderEnd   =  "</h1></div>";
String panelEnd       =  "</div>";

String panelBodySymbol    =  "<div class='panel panel-default'><div class='panel-body'><span class='glyphicon glyphicon-";
String panelBodyName    =  "'></span> ";
String panelBodyValue   =  "<span class='pull-right'>";
String panelcenter   =  "<div class='row'><div class='span6' style='text-align:center'>";
String panelBodyEnd     =  "</span></div></div>";

String inputBodyStart   =  "<form action='' method='POST'><div class='panel panel-default'><div class='panel-body'>";
String inputBodyName    =  "<div class='form-group'><div class='input-group'><span class='input-group-addon' id='basic-addon1'>";
String inputBodyPOST    =  "</span><input type='text' name='";
String inputBodyClose   =  "' class='form-control' aria-describedby='basic-addon1'></div></div>";
String roombacontrol     =  "<a href='/roombastart'<button type='button' class='btn btn-default'><span class='glyphicon glyphicon-play' aria-hidden='true'></span> Start</button></a><a href='/roombamax'<button type='button' class='btn btn-default'><span class='glyphicon glyphicon-play' aria-hidden='true'></span> Max Clean</button></a><a href='/roombastop'<button type='button' class='btn btn-default'><span class='glyphicon glyphicon-stop' aria-hidden='true'></span> Stop</button></a><a href='/roombaspot'<button type='button' class='btn btn-default'><span class='glyphicon glyphicon-cleaning' aria-hidden='true'></span> Spot</button></a><a href='/roombadock'<button type='button' class='btn btn-default'><span class='glyphicon glyphicon-home' aria-hidden='true'></span> Dock</button></a></div>";




//API 
//TODO API completieren

  //server.on ( "/format", handleFormat );
  //server.on("/", handle_root);
  //server.on("/", handle_fupload_html);
  //server.on("/api", handle_api);
  //server.on("/updatefwm", handle_updatefwm_html);
  //server.on("/fupload", handle_fupload_html);
  //server.on("/filemanager_ajax", handle_filemanager_ajax);
  //server.on("/delete", handleFileDelete);
  //server.on("/roombastart", handle_roomba_start);
  //server.on("/roombamax", handle_roomba_max);
  //server.on("/roombastop", handle_roomba_stop);
  //server.on("/roombaspot", handle_roomba_spot);
  //server.on("/roombadock", handle_roomba_dock);
  //server.on("/restart", handle_esp_restart);



// ROOT page
void handle_root()
{

  // get IP
  IPAddress ip = WiFi.localIP();
  ClientIP = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  delay(500);

  String title1     = panelHeaderName + String("Roombot Settings") + panelHeaderEnd;
  String IPAddClient    = panelBodySymbol + String("globe") + panelBodyName + String("IP Address") + panelBodyValue + ClientIP + panelBodyEnd;
  String ClientName   = panelBodySymbol + String("tag") + panelBodyName + String("Client Name") + panelBodyValue + panelBodyEnd;
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