#include <WiFi.h>
#include <PubSubClient.h>

// Anpassen
const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";
const char *MQTT_HOST = "";
const uint16_t MQTT_PORT = ;

const char *MQTT_TOPIC = "";

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
    // TODO generate unique clientId

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

  // TODO configure WIFI and MQTT

  connectWifi();
  connectMqtt();
}

void loop() {
  // TODO (re)connect to WIFI and MQTT, call MQTT main loop
}
