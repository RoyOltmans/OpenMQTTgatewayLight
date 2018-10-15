//trace
void trc(String msg){
  if (TRACE) {
  Serial.println(msg);
  }
}

void trc(int msg){
  if (TRACE) {
  Serial.println(msg);
  }
}

void trc(unsigned int msg){
  if (TRACE) {
  Serial.println(msg);
  }
}

void trc(long msg){
  if (TRACE) {
  Serial.println(msg);
  }
}

void trc(unsigned long msg){
  if (TRACE) {
  Serial.println(msg);
  }
}

void trc(double msg){
  if (TRACE) {
  Serial.println(msg);
  }
}

void trc(float msg){
  if (TRACE) {
  Serial.println(msg);
  }
}

bool to_bool(String const& s) { // thanks Chris Jester-Young from stackoverflow
     return s != "0";
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println("");
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
