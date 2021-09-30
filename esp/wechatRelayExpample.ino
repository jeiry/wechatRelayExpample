#include <ESP8266WiFi.h>
const char* ssid = "xxx";
const char* password = "xxx";
//mqtt
#include <PubSubClient.h>
const char* mqtt_server = "t.xxx.fun";
const char* mqtt_username = "xxx";
const char* mqtt_password = "xxx";
String pubTopic = "";
String subTopic = "";
WiFiClient espClient;
PubSubClient client(espClient);

String unionid = "";

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uint64_t chipid =ESP.getChipId();
  unionid = String((uint32_t)chipid);
  Serial.print("union:");
  Serial.println(unionid);
  pubTopic = "/xxx/p/wechatexpample/"+unionid;
  subTopic = "/xxx/s/wechatexpample/"+unionid;
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(D7, OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
