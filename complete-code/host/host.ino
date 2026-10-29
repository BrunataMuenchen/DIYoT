#include <WiFi.h>
#include <PicoMQTT.h>

const char *WIFI_SSID     = "brunataworkshop";
const char *WIFI_PASSWORD = "brunataworkshop";

const uint16_t MQTT_PORT = 1883;
const char *MQTT_TOPIC = "alarm/test";

IPAddress local_ip(10, 10, 5, 1);
IPAddress gateway(10, 10, 5, 1);
IPAddress subnet(255, 255, 255, 0);


// MQTT Server explizit auf Port 1883
WiFiServer mqttTcpServer(MQTT_PORT);
PicoMQTT::Server mqtt(mqttTcpServer);


void setup()
{
    Serial.begin(115200);

    // ESP32 nur als Access Point betreiben
    WiFi.mode(WIFI_AP);

    // IP des Access Points setzen
    if (!WiFi.softAPConfig(local_ip, gateway, subnet))
    {
        Serial.println("Fehler bei softAPConfig");
    }

    // Access Point starten
    if (!WiFi.softAP(WIFI_SSID, WIFI_PASSWORD))
    {
        Serial.println("Fehler beim Starten des Access Points");
        return;
    }

    Serial.println();
    Serial.println("Access Point gestartet");
    Serial.print("SSID: ");
    Serial.println(WIFI_SSID);

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    Serial.print("MQTT Port: ");
    Serial.println(MQTT_PORT);


    // Alle Nachrichten auf alarm/test anzeigen
    mqtt.subscribe(MQTT_TOPIC,
        [](const char *topic, const char *payload)
        {
            Serial.print("MQTT [");
            Serial.print(topic);
            Serial.print("]: ");
            Serial.println(payload);
        }
    );

    // MQTT Broker starten
    mqtt.begin();

    Serial.println("MQTT Broker gestartet");
}


void loop()
{
    mqtt.loop();
}
