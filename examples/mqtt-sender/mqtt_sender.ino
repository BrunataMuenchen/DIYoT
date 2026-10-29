#include <WiFi.h>
#include <PubSubClient.h>

// TODO customize
const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";
const char *MQTT_HOST = "";
const uint16_t MQTT_PORT = 0;

const char *MQTT_TOPIC = "";

constexpr uint8_t BUTTON_PIN = 0;
constexpr unsigned long DEBOUNCE_MS = 50;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

bool lastButton = HIGH;
unsigned long lastChange = 0;

void connectWifi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("WLAN verbinden");
  // TODO connect to WIFI
}

void connectMqtt() {
  while (!mqtt.connected()) {
    Serial.print("MQTT verbinden ... ");

    char clientId[32];
    // TODO generate unique clientId
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
  // TODO configure button pin as an input
 
  // TODO Configure WIFI and MQTT

  connectWifi();
  connectMqtt();
}

void loop() {
  // TODO (re)connect to WIFI and MQTT, call MQTT loop
  mqtt.loop();

  // TODO read the button state and
  bool button = digitalRead(BUTTON_PIN);

  // TODO if the state changed, and it has been more time than the configured debounce since the last change, send message
  if () {
    // TODO send message, log message for debug
  }
}
