#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>

#define WIFI_SSID "MyWifiAp"
#define WIFI_PASSWORD "MyPassword"

#define MQTT_ADDRESS IPAddress(192, 168, 2, 59)
#define MQTT_PORT 1883

#define MQTT_TOPIC_TEMPERATURE "home/masterbedroom/temperature"
#define MQTT_TOPIC_HUMIDITY "home/masterbedroom/humidity"

#define ONE_MINUTE 60000

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_ADDRESS, MQTT_PORT);

  connectToWifi();
}

void loop() {
  char payload[10];

  getTemperature(payload);
  mqttClient.publish(MQTT_TOPIC_TEMPERATURE, 0, true, payload);
  
  getHumidity(payload);
  mqttClient.publish(MQTT_TOPIC_HUMIDITY, 0, true, payload);
  
  delay(ONE_MINUTE);
}
