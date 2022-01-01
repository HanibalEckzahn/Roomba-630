#include <Arduino.h>
#include <config.h>
#include <Roomba.h>
#include <TimeLib.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(SERIAL_RX, SERIAL_TX); // (RX, TX. inverted, buffer)



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
  // put your main code here, to run repeatedly:
}

