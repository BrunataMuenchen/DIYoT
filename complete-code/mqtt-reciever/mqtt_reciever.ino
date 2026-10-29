#include <WiFi.h>
#include <PubSubClient.h>

// Anpassen
const char *WIFI_SSID = "brunataworkshop";
const char *WIFI_PASSWORD = "brunataworkshop";
const char *MQTT_HOST = "10.10.5.1";
const uint16_t MQTT_PORT = 1883;

const char *MQTT_TOPIC = "alarm/test";

constexpr uint8_t LED_PIN = 8;
constexpr bool LED_ACTIVE_LOW = true;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

void setLed(bool on) {
    if (on) {
        rgbLedWrite(LED_PIN, 50, 0, 0);
    } else {
        rgbLedWrite(LED_PIN, 0, 0, 0);
    }
}

void blinkAlarm() {
  for (int i = 0; i < 3; ++i) {
    setLed(true);
    delay(180);
    setLed(false);
    delay(180);
  }
}

void onMqttMessage(char *topic, byte *payload, unsigned int length) {
  Serial.print("MQTT Nachricht auf ");
  Serial.print(topic);
  Serial.print(": ");
  for (unsigned int i = 0; i < length; ++i) Serial.print((char)payload[i]);
  Serial.println(" °C");
  Serial.println();

  blinkAlarm();
}

void connectWifi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("WLAN verbinden");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print('.');
  }
  Serial.println(" verbunden");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void connectMqtt() {
  while (!mqtt.connected()) {
    Serial.print("MQTT verbinden ... ");

    char clientId[32];
    snprintf(clientId, sizeof(clientId), "alarm-led-%08lx",
             (unsigned long)(ESP.getEfuseMac() & 0xffffffff));

    if (mqtt.connect(clientId)) {
      Serial.println("verbunden");
      mqtt.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("Fehler rc=");
      Serial.println(mqtt.state());
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  setLed(false);

  WiFi.mode(WIFI_STA);
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setCallback(onMqttMessage);

  connectWifi();
  connectMqtt();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWifi();
  if (!mqtt.connected()) connectMqtt();
  mqtt.loop();
}
