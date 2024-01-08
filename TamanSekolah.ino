#define BLYNK_TEMPLATE_ID "TMPL65Jyk6OAs"
#define BLYNK_TEMPLATE_NAME "test1"
#define BLYNK_AUTH_TOKEN "b8O8w5X3atVWjRX52B0SX1xKUXqUj0TH"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "qqqqqqq"; // ganti ssid wifinya
char pass[] = "sintya07"; // ganti pass wifinya

// Sesuaikan pin GPIO dengan pin yang Anda gunakan di Wemos D1 Mini
int relayPin1 = D4; // Ganti dengan pin yang digunakan untuk relay 1
int relayPin2 = D3; // Ganti dengan pin yang digunakan untuk relay 2

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(relayPin1, OUTPUT); // Set pin sebagai output
  pinMode(relayPin2, OUTPUT); // Set pin sebagai output
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V1) {
  int relayState = param.asInt();

  if (relayState == HIGH) {
    digitalWrite(relayPin1, HIGH); // Matikan relay 1
    Serial.println("Relay 1 turned OFF");
  } else {
    digitalWrite(relayPin1, LOW); // Nyalakan relay 1
    Serial.println("Relay 1 turned ON");
  }
}

BLYNK_WRITE(V0) {
  int relayState1 = param.asInt();

  if (relayState1 == HIGH) {
    digitalWrite(relayPin2, LOW); // Matikan relay 2
    Serial.println("Relay 2 turned OFF");
  } else {
    digitalWrite(relayPin2, HIGH); // Nyalakan relay 2
    Serial.println("Relay 2 turned ON");
  }
}
