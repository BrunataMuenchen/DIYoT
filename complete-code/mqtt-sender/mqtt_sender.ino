#include <WiFi.h>
#include <PubSubClient.h>

// Anpassen
const char *WIFI_SSID = "brunataworkshop";
const char *WIFI_PASSWORD = "brunataworkshop";
const char *MQTT_HOST = "10.10.5.1";
const uint16_t MQTT_PORT = 1883;

const char *MQTT_TOPIC = "alarm/test";

// ESP32-C3 Super Mini: BOOT-Taster liegt bei den ueblichen Boards an GPIO 9.
constexpr uint8_t BUTTON_PIN = 9;
constexpr unsigned long DEBOUNCE_MS = 50;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

bool lastButton = HIGH;
unsigned long lastChange = 0;

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
    snprintf(clientId, sizeof(clientId), "alarm-button-%08lx",
             (unsigned long)(ESP.getEfuseMac() & 0xffffffff));

    if (mqtt.connect(clientId)) {
      Serial.println("verbunden");
    } else {
      Serial.print("Fehler rc=");
      Serial.println(mqtt.state());
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  mqtt.setServer(MQTT_HOST, MQTT_PORT);

  connectWifi();
  connectMqtt();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWifi();
  if (!mqtt.connected()) connectMqtt();
  mqtt.loop();

  bool button = digitalRead(BUTTON_PIN);

  if (button != lastButton && millis() - lastChange >= DEBOUNCE_MS) {
    lastChange = millis();
    lastButton = button;

    if (button == LOW) {
            float temp = temperatureRead();

      char payload[16];
      snprintf(payload, sizeof(payload), "%.1f", temp);

      Serial.print("Temperatur: ");
      Serial.print(temp);
      Serial.println(" °C");

      Serial.println("Taster gedrueckt, sende Alarm");
      if (!mqtt.publish(MQTT_TOPIC, payload, false)) {
        Serial.println("MQTT Publish fehlgeschlagen");
      }
    }
  }
}
