/*  
  OpenMQTTGateway Light - ESP8266 NodeMCU v2

   Act as a wifi or ethernet gateway between your 433mhz/infrared IR signal  and a MQTT broker 
   Send and receiving command by MQTT
 
  This program enables to:
 - receive MQTT data from a topic and send RF 433Mhz signal corresponding to the received MQTT data
 - publish MQTT data to a different topic related to received 433Mhz signal
  
    Copyright: (c)Florian ROBERT
  
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

/*-------------------VERSION----------------------*/
#define OMG_VERSION "0.8L"

/*-------------------Main Configuration----------------------*/
#define TRACE false

/*-------------------WIFI Settings----------------*/
const char* ssid = "ACCESS POINT SSID";
const char* password = "ACCESS POINT PASSWORD";

/*-------------------PIN Settings----------------*/
#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO 
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)

/*-------------------MQTT Settings-------------------*/
char mqtt_user[20] = "your_username"; // not compulsory only if your broker needs authentication
char mqtt_pass[20] = "your_password"; // not compulsory only if your broker needs authentication
char mqtt_server[40] = "server-01.local.int";
long mqtt_port = strtol("1883",NULL,10);


/*-------------------Gateway MQTT Base Topic-------------------*/
#define Gateway_Name "OpenMQTTGateway"
#define Base_Topic "home/"
#define version_Topic  Base_Topic Gateway_Name "/version"

/*-------------------Gateway MQTT configuration-------------------*/
#define will_Topic  Base_Topic Gateway_Name "/LWT"
#define will_QoS 0
#define will_Retain true
#define will_Message "Offline"
#define Gateway_AnnouncementMsg "Online"

/*-------------------RF2 MQTT configuration-------------------*/
#define RF2codeKey "CODE_" // code will be defined if a subject contains RF2codeKey followed by a value of 7 digits
#define RF2periodKey "PERIOD_" // period  will be defined if a subject contains RF2periodKey followed by a value of 3 digits
#define RF2unitKey "UNIT_"  // number of your unit value  will be defined if a subject contains RF2unitKey followed by a value of 1-2 digits
#define RF2groupKey "GROUP_"  // number of your group value  will be defined if a subject contains RF2groupKey followed by a value of 1 digit
#define RF2dimKey "DIM"  // number of your dim value will be defined if a subject contains RF2dimKey and the payload contains the dim value as digits

/*-------------------MQTT Publish and Subscribe Topic-------------------*/
#define subjectMQTTtoRF2  Base_Topic Gateway_Name "/commands/MQTTtoRF2"
#define subjectRF2toMQTT  Base_Topic Gateway_Name "/RF2toMQTT"
