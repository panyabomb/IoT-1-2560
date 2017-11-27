#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "FITM WiFi";
const char* password = "";
const char* mqtt_server = "m11.cloudmqtt.com";
#define mqtt_port 11915
#define mqtt_user "upnkpelr"
#define mqtt_password "GHZ0Xc72wZx-"

float oldTemp = 0.0;
char msg[50]; // message for reciever

WiFiClient espClient;
PubSubClient client(espClient);
void setup(){
  Serial.begin(115200);
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); //port ใน mqtt
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("pir", mqtt_user, mqtt_password)) { // topic,username,password
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  int value= digitalRead(D1);
  if (!client.connected()) {
  reconnect();
  }
  client.loop();
  delay(1000);
  if (value == HIGH)
   {
     client.publish("/checkPIR", "1");
     Serial.println("yes");
   }
   else
   {
     client.publish("/checkPIR", "0");
     Serial.println("no");
   }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  String to = "";
  int i = 0;
  while (i < length) msg += (char)payload[i++];
  to = topic;
  if (to == "/checkPIR") {
    Serial.println(msg);
    if (msg.toFloat() == 1) {
      digitalWrite(D2, HIGH);
    } else {
      digitalWrite(D2, LOW);
    }
  }
}

