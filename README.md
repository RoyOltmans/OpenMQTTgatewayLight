# OpenMQTTgatewayLight

With great thanks to the whole dev. group of OpenMQTTgateway
  - 1technophile
  - crankyoldgit
  - glasruit
  - HannesDi
  - Landrash
  - larsenglund
  - ChiefZ
  - PatteWi
  - jumpalottahigh
  - zerinrc
  - philfifi
  - Spudtater
  - prahjister
  - rickybrent
  - petricaM
  - ekim from Home assistant forum
  - ronvl from Home assistant forum
  - Chris Broekema
  - Lars Englund
  - Fredrik Lindqvist
  - Philippe LUC
  - Patrick Wilhelm
  - Georgi Yanev
  - zerinrc
  - ChiefZ
  - 8666 

This is an fork of OpenMQTTgateway v0.8 creating a lightweight implementation tested on the following hardware:
- ESP8266 NodeMCU v2
- Receiver - RF SRX882 v1.3
- Transmitter - TX STX882 v1.1

I created this implementation because I coudn't get the openMQTTgateway v0.8 working on my setup.

- SRX882 connected on PIN D2
- STX882 connected on RX

Important the VIN and GND can be used to power the SRX and STX as single 5v powersupply.

Right now only receiving has been tested Transmission needs to be tested.

See the screenshot below for the schematics
![alt text](https://raw.githubusercontent.com/RoyOltmans/OpenMQTTgatewayLight/master/61424014eb53528911e75fa273ecbcad029114f9.JPG)
