#include <WiFi.h>
#include <PicoMQTT.h>

const char *WIFI_SSID     = "brunataworkshop";
const char *WIFI_PASSWORD = "brunataworkshop";

const uint16_t MQTT_PORT = 1883;
const char *MQTT_TOPIC = "alarm/test";

IPAddress local_ip(10, 10, 5, 1);
IPAddress gateway(10, 10, 5, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer mqttTcpServer(MQTT_PORT);
PicoMQTT::Server mqtt(mqttTcpServer);

void setup()
{
    Serial.begin(115200);

    // TODO configure WiFi in access point mode, set ip and start message

    // TODO subscribe to topic to debug sent data 

    // TODO start MQTT broker

    Serial.println("MQTT Broker gestartet");
}


void loop()
{
  // TODO call mqtt loop function
}
