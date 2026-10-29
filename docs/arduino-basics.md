# Grundlagen der Arduino-Programmierung

Ein Arduino-Programm heißt **Sketch** und wird meist in einer Datei mit der Endung `.ino` geschrieben. Die verwendete Programmiersprache basiert auf **C++** und ergänzt es um Funktionen für Mikrocontroller, zum Beispiel `pinMode()`, `digitalWrite()` und `delay()`. Welche Funktionen und insbesondere Pins konkret verfügbar sind, hängt dabei vom konkreten Mikrocontroller ab.

## Kurzeinführung in "Arduino"

| Thema | Arduino |
| --- | --- |
| Anweisungen | `int counter = 0;` enden mit `;`. |
| Blöcke | `{ ... }` begrenzen Funktionen und Kontrollstrukturen. |
| Typen | `int`, `bool`, `float` oder `String` werden explizit angegeben. |
| Funktionen | `void setup() { ... }` definiert eine Funktion ohne Rückgabewert. |
| Bibliotheken | `#include <WiFi.h>` bindet eine Headerdatei ein. |

Arduino-Sketches werden auf deinem Computer lokal **kompiliert** und anschließend auf den Mikrocontroller "hochgeladen". Anders als ein Skript in Python oder JavaScript laufen sie danach auf dem Board selbst weiter – auch wenn der Computer nicht mehr angeschlossen ist, solange das Board Strom bekommt.

## Der Aufbau eines Sketches

```cpp
// Bibliotheken bei Bedarf hier einbinden, z. B. #include <WiFi.h>

int counter = 0;  // Globale Variable: bleibt zwischen loop()-Aufrufen erhalten.

void setup() {
  Serial.begin(115200);  // Serielle Ausgabe einmal vorbereiten.
}

void loop() {
  Serial.println(counter);
  counter++;
  delay(1000);           // Eine Sekunde warten (1000 Millisekunden).
}
```

`setup()` wird **einmal** beim Start des Boards oder nach einem Reset ausgeführt. Hier wird das Board für die geplante Verwendung initialisiert, etwa mit `Serial.begin(...)`, dem Einrichten von Pins oder das Starten einer Netzwerkverbindung.

`loop()` wird danach **immer wieder** aufgerufen. Hier steht, was das Gerät fortlaufend tun soll. Das könnte dann das Abfragen von Sensoren oder das Verarbeiten von Nachrichten beinhalten.

Globale Variablen (wie `counter` im Beispiel oben) behält ihren Wert zwischen den Durchläufen; eine innerhalb von `loop()` deklarierte lokale Variable wird dagegen bei jedem Aufruf neu angelegt.

## Serielle Ausgabe beobachten

Verbinde das Board per USB. Mit der Arduino CLI kannst du zuerst den Anschluss ermitteln und dann den seriellen Monitor mit derselben Baudrate öffnen, die im Sketch bei `Serial.begin(115200)` steht:

```sh
arduino-cli board list
arduino-cli monitor -p <PORT> -c baudrate=115200
```

Ersetze `<PORT>` durch den angezeigten Anschluss, z. B. `/dev/ttyACM0` unter Linux oder `COM3` unter Windows. Den Monitor beendest du mit **Strg+C**.

In der **Arduino IDE** wählst du zuerst das Board und seinen Port aus und öffnest dann **Werkzeuge → Serieller Monitor** (oder das Symbol „Serieller Monitor“). Stelle dort ebenfalls **115200 Baud** ein, damit die Ausgabe des Beispiels lesbar ist.

---

Weiterführend: [Arduino-Sprachreferenz](https://docs.arduino.cc/language-reference/), [Sketch-Spezifikation](https://docs.arduino.cc/arduino-cli/sketch-specification/) und [Arduino CLI/ESP32-C6 einrichten](arduino-cli.md).
