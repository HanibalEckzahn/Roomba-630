# Roomba-ESP8266

ESP8266 MQTT Roomba Controller (Useful to connect old Roombas to the Smart Home)

## Parts:
* [ESP12E](http://www.ebay.com/itm/121951859776) ESP8266 Wifi microcontroller ($3-4) Though any ESP module will probably work
* [Small 3.3V switching step-down regulator](https://www.amazon.com/gp/product/B01MQGMOKI) ($1-2)
* 5kOhm & 10kOhm resistor for 5V->3.3V voltage divider (any two resistors above a few kOhm with a 1:2 ratio should work)
* Some ~10kOhm pullup/pulldown resistors to get the ESP12E in the right modes for programming (probably anything 2k-20kOhm will work fine)
* 3.3V FTDI cable for initial programming
* Some wire you can jam into the Roomba's Mini Din connector, or a proper Mini Din connector



### Connections

* ESP GPIO15 -> 10kOhm Resistor -> GND
* ESP GPIO0 -> 10kOhm Resistor -> 3.3V

* ESP GPIO14 -> Roomba BRC (Pin5 on Roomba)

* Voltage regulator Vin -> Roomba Vpwr (Pin 1 or 2 on Roomba)
* Voltage regulator GND -> Roomba GND (Pin 6 or 7 on Roomba)

* Roomba TX  -> 5kOhm -> ESP RX -> 10kOhm -> GND
* Roomba RX  -> 5kOhm -> ESP TX -> 10kOhm -> GND

* ESP 3.3V -> Voltage regulator 3.3V
* ESP GND -> Voltage regulator GND



Use at your own risk!!

![alt tag](https://github.com/incmve/roomba-eps8266/blob/master/Images/roombot-interface.jpg)


