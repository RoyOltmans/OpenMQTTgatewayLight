void callback(char* topic, byte* payload, unsigned int length) {
  trc("Message arrived [");
  trc(topic);
  trc("] ");
  for (int i = 0; i < length; i++) {
    trc((char)payload[i]);
  }
  trc("");
}

void reconnect() {
  int failure_number = 0;
  // Loop until we're reconnected
  while (!client.connected()) {
    trc("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(Gateway_Name, mqtt_user, mqtt_pass, will_Topic, will_QoS, will_Retain, will_Message)) {
      trc("connected");
      failure_number = 0;
      // Once connected, publish an announcement...
      client.publish(will_Topic,Gateway_AnnouncementMsg,will_Retain);
      // publish version
      client.publish(version_Topic,OMG_VERSION,will_Retain);
      //Subscribing to topic
      // ... and resubscribe
      client.subscribe(subjectMQTTtoRF2);
      trc("MQTT Topic subscribed");
    } else {
      trc("failed, rc=");
      trc(client.state());
      trc(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTTtoRF2(char * topicOri, char * datacallback) {

  // RF DATA ANALYSIS
  //We look into the subject to see if a special RF protocol is defined 
  String topic = topicOri;
  bool boolSWITCHTYPE;
  boolSWITCHTYPE = to_bool(datacallback);
  bool isDimCommand = false;
  
  long valueCODE  = 0;
  int valueUNIT = -1;
  int valuePERIOD = 0;
  int valueGROUP  = 0;
  int valueDIM  = -1;
  
  int pos = topic.lastIndexOf(RF2codeKey);       
  if (pos != -1){
    pos = pos + +strlen(RF2codeKey);
    valueCODE = (topic.substring(pos,pos + 8)).toInt();
    trc("RF2 code:");
    trc(valueCODE);
  }
  int pos2 = topic.lastIndexOf(RF2periodKey);
  if (pos2 != -1) {
    pos2 = pos2 + strlen(RF2periodKey);
    valuePERIOD = (topic.substring(pos2,pos2 + 3)).toInt();
    trc("RF2 Period:");
    trc(valuePERIOD);
  }
  int pos3 = topic.lastIndexOf(RF2unitKey);       
  if (pos3 != -1){
    pos3 = pos3 + strlen(RF2unitKey);
    valueUNIT = (topic.substring(pos3, topic.indexOf("/", pos3))).toInt();
    trc("Unit:");
    trc(valueUNIT);
  }
  int pos4 = topic.lastIndexOf(RF2groupKey);
  if (pos4 != -1) {
    pos4 = pos4 + strlen(RF2groupKey);
    valueGROUP = (topic.substring(pos4,pos4 + 1)).toInt();
    trc("RF2 Group:");
    trc(valueGROUP);
  }
  int pos5 = topic.lastIndexOf(RF2dimKey);
  if (pos5 != -1) {
    isDimCommand = true;
    valueDIM = atoi(datacallback);
    trc("RF2 Dim:");
    trc(valueDIM);
  }
  
  if ((topic == subjectMQTTtoRF2) || (valueCODE != 0) || (valueUNIT  != -1)|| (valuePERIOD  != 0)){
    trc("MQTTtoRF2");
    if (valueCODE == 0) valueCODE = 8233378;
    if (valueUNIT == -1) valueUNIT = 0;
    if (valuePERIOD == 0) valuePERIOD = 272;
    trc(valueCODE);
    trc(valueUNIT);
    trc(valuePERIOD);
    trc(valueGROUP);
    trc(boolSWITCHTYPE);
    trc(valueDIM);
    NewRemoteReceiver::disable();
    trc("Creating transmitter");
    NewRemoteTransmitter transmitter(valueCODE, D9, valuePERIOD);
    trc("Sending data");
    if (valueGROUP) {
      if (isDimCommand) {
        transmitter.sendGroupDim(valueDIM); 
      }
      else {
        transmitter.sendGroup(boolSWITCHTYPE); 
      }
    }
    else {
      if (isDimCommand) {
        transmitter.sendDim(valueUNIT, valueDIM); 
      }
      else {    
        transmitter.sendUnit(valueUNIT, boolSWITCHTYPE); 
      }
    }
    trc("Data sent");
    NewRemoteReceiver::enable();

    // Publish state change back to MQTT
    String MQTTAddress;
    String MQTTperiod;
    String MQTTunit;
    String MQTTgroupBit;
    String MQTTswitchType;
    String MQTTdimLevel;

    MQTTAddress = String(valueCODE);
    MQTTperiod = String(valuePERIOD);
    MQTTunit = String(valueUNIT);
    MQTTgroupBit = String("0");
    MQTTswitchType = String(boolSWITCHTYPE);
    MQTTdimLevel = String(valueDIM);
    String MQTTRF2string;
    trc("Adv data MQTTtoRF2 push state via RF2toMQTT");
    if (isDimCommand) {
      MQTTRF2string = subjectRF2toMQTT+String("/")+RF2codeKey+MQTTAddress+String("/")+RF2unitKey+MQTTunit+String("/")+RF2groupKey+MQTTgroupBit+String("/")+RF2dimKey+String("/")+RF2periodKey+MQTTperiod;
      client.publish((char *)MQTTRF2string.c_str(),(char *)MQTTdimLevel.c_str());  
    }
    else {
      MQTTRF2string = subjectRF2toMQTT+String("/")+RF2codeKey+MQTTAddress+String("/")+RF2unitKey+MQTTunit+String("/")+RF2groupKey+MQTTgroupBit+String("/")+RF2periodKey+MQTTperiod;
      client.publish((char *)MQTTRF2string.c_str(),(char *)MQTTswitchType.c_str());  
    }
  }
}
