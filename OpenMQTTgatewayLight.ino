/*
  OpenMQTTGateway Light  - ESP8266 NodeMCU V2

  This program enables to:
 - receive MQTT data from a topic and send RF 433Mhz signal corresponding to the received MQTT data
 - publish MQTT data to a different topic related to received 433Mhz signal

  Note when the ESP8266 is flashed restart it to reset and receive signals

  Date 14-oktober-2018

  Main Contributors openMQTTgateway:
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
  Branche Contributor openMQTTgatewayLight
  - Roy Oltmans    

  This file is part of OpenMQTTGateway.

  OpenMQTTGateway is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenMQTTGateway is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NewRemoteReceiver.h>
#include <NewRemoteTransmitter.h>
#include "User_config.h"

WiFiClient espClient;
PubSubClient client(espClient);

/*-------------------Var preperation----------------*/
char msg[50];
int value = 0;
String MQTTRF2string;
String MQTTswitchType;
struct RF2rxd
{
  unsigned int period;
  unsigned long address;
  unsigned long groupBit;
  unsigned long unit;
  unsigned long switchType;
  bool hasNewData;
};

/*-------------------Loading libraries and tools----------------*/
#include "ToolLib.h"
#include "MQTT.h"

void setup() {
  Serial.begin(115200);
  
  // See the interrupt-parameter of attachInterrupt for possible values (and pins)
  // to connect the receiver.
  // if you don't see codes try to reset your board after upload
  NewRemoteReceiver::init(D2, 2, catchRF2toMQTT);
  Serial.println("Receiver initialized");
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  Serial.println("");
  Serial.print("openMQTTGateway ver");
  Serial.print(OMG_VERSION);    
  Serial.println(" Started");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

// Callback function is called only when a valid code is received.
void catchRF2toMQTT(unsigned int period, unsigned long address, unsigned long groupBit, unsigned long unit, unsigned long switchType) {
  //Print the received code.
  trc("Code: ");
  trc(address);
  trc(" Period: ");
  trc(period);
  trc(" unit: ");
  trc(unit);
  trc(" groupBit: ");
  trc(groupBit);
  trc(" switchType: ");
  trc(switchType);
  MQTTRF2string = subjectRF2toMQTT+String("/")+RF2codeKey+String(address)+String("/")+RF2unitKey+String(unit)+String("/")+RF2groupKey+String(groupBit)+String("/")+RF2periodKey+String(period);
  MQTTswitchType = String(switchType);
  client.publish((char *)MQTTRF2string.c_str(),(char *)MQTTswitchType.c_str(), will_Retain);
}
