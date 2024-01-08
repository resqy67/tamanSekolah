#define BLYNK_TEMPLATE_ID "TMPL65Jyk6OAs"
#define BLYNK_TEMPLATE_NAME "test1"
#define BLYNK_AUTH_TOKEN "b8O8w5X3atVWjRX52B0SX1xKUXqUj0TH"
#include <WiFiManager.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char ssid[] = "SERVER 2";
char pass[] = "SKARLA01";
char auth[] = "b8O8w5X3atVWjRX52B0SX1xKUXqUj0TH";

int relayPin1 = D4;
int relayPin2 = D3;

// int led2 = D2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFiManager wifiManager;
  int attempt = 0;
  while (!wifiManager.autoConnect("AP-ESP8266")) {
    Serial.println("Gagal terhubung ke jaringan WiFi.");

    // Mencoba hingga 3 kali
    if (attempt >= 3) {
      Serial.println("Mencoba akses titik akses sementara.");
      startAccessPointMode();
      break;
    }

    delay(3000);
    attempt++;
  }
  
  // Jika berhasil terhubung ke jaringan WiFi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Terhubung ke jaringan WiFi!");
    Serial.print("Alamat IP: ");
    Serial.println(WiFi.localIP());

    // Menghubungkan ke server Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, WiFi.SSID().c_str(), WiFi.psk().c_str());
    // Blynk.begin(auth, ssid, pass);

  }
  // Blynk.begin(auth, ssid, pass);
  
}
  // pinMode(led1, OUTPUT);

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}

BLYNK_WRITE(V1) { // Fungsi ini akan dipanggil ketika ada perubahan nilai pada tombol di aplikasi Blynk (gunakan widget Button dengan pin V1)
  int relayState = param.asInt(); // Baca nilai tombol di aplikasi Blynk

  if (relayState == HIGH) {
    digitalWrite(relayPin1, LOW); // Nyalakan relay
    Serial.println("Relay turned OFF");
  } else {
    digitalWrite(relayPin1, HIGH); // Matikan relay
    Serial.println("Relay turned ON");
  }
}

BLYNK_WRITE(V0) {
  int relayState1 =  param.asInt();

  if (relayState1 == HIGH) {
    digitalWrite(relayPin2, LOW);
    Serial.println("Relay turned OFF");

  } else {
    digitalWrite(relayPin2, HIGH);
    Serial.println("Relay turned ON");

  }
}

void startAccessPointMode() {
  Serial.println("Memulai mode akses titik akses sementara.");
  Serial.println("Starting Ap Mode!");

  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);

  // Mengatur konfigurasi untuk mode akses titik akses
  if (!wifiManager.startConfigPortal("AP-ESP8266")) {
    Serial.println("Gagal memulai mode akses titik akses.");
    Serial.println("Failed to start AP Mode");
    Serial.println("Restarting ESP8266!!");
    ESP.restart();
  }

  Serial.println("Terhubung ke jaringan WiFi!");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  // Menghubungkan ke server Blynk
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
}

void configModeCallback(WiFiManager *wifiManager) {
  Serial.println("Config Portal");
  // lcd.print(WiFi.softAPIP());
}