//Version
String roombotVersion = "0.1.3";
String WMode = "1";

//WIFI Settings

#define HOSTNAME "Roomba"
// #define SSID "Your SSID HERE"
#define PASSWORD "string"

EspMQTTClient client(
  "SSID",
  "PASSWORD",
  "192.168.1.100",
  "MQTTUsername",
  "MQTTPassword",
  "TestClient1"
);

// WIFI AP 
const char *APssid = "Roombot";
const char *APpassword = "momo2021";



//MQTT Settings

#define MQTT_Server "192.168.x.x"
#define MQTT_PORT "1888"
#define MQTT_User "xxxx"
#define MQTT_Password "password"

// Pimatic settings
String host   = "192.168.1.25";
const int httpPort    = 1099;
String Username     = "iot";
String Password     = "broker";
String chargevar = "chargestatus";
String distancevar = "distance";
char authVal[40];
char authValEncoded[40];




//ESP Settings
#define SERIAL_RX     D5  // pin for SoftwareSerial RX
#define SERIAL_TX     D6  // pin for SoftwareSerial TX
#define Wake_Pin      D1


