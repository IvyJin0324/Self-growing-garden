#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <DHT.h>
#include "home_secrets.h"

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char* ssid     = SECRET_SSID;
const char* pass = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char* broker = "mqtt.cetools.org";
int        port     = 1884;

const char topic1[]  = "student/CASA0016/Qian(Ashley)/illumination";
const char topic2[]  = "student/CASA0016/Qian(Ashley)/soil moisture";
const char topic3[]  = "student/CASA0016/Qian(Ashley)/temperature";
const char topic4[]  = "student/CASA0016/Qian(Ashley)/humidity";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

   mqttClient.setUsernamePassword(mqttuser, mqttpass);


  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1 and A2
    int lightValue = analogRead(A0);
    int moisture = analogRead(A2);
    float temp = dht.readTemperature(); 
    int hum = dht.readHumidity(); 

    Serial.print("Sending message to topic: ");
    Serial.println(topic1);
    Serial.println(lightValue);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2);
    Serial.println(moisture);

    Serial.print("Sending message to topic3: ");
    Serial.println(topic3);
    Serial.println(temp);

    Serial.print("Sending message to topic4: ");
    Serial.println(topic4);
    Serial.println(hum);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic1);
    mqttClient.print(lightValue);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print(String(moisture));
    mqttClient.endMessage();

    mqttClient.beginMessage(topic3);
    mqttClient.print(String(temp));
    mqttClient.endMessage();

    mqttClient.beginMessage(topic4);
    mqttClient.print(hum);
    mqttClient.endMessage();

    Serial.println();
  }
}
