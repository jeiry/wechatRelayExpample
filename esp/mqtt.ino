unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String str;
  for (int i = 0; i < length; i++) {
    str += String((char)payload[i]);
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.print(str);
  if (str == "on") {
    digitalWrite(D7, 1);
  } else if (str == "off") {
    digitalWrite(D7, 0);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP826601Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...

      // ... and resubscribe
      client.subscribe(subTopic.c_str());
      char message[256];
      sprintf(message, "{\"action\":\"login\",\"deviceid\":\"%s\"}", unionid.c_str());
      client.publish(pubTopic.c_str(),message);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
