#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

String apiKey = "BSGGIJ4L1GGUPF77"; // Sua API KEY
const char* server = "https://api.thingspeak.com/update"; // HTTPS obrigatório

// Definição dos códigos (nomes consistentes)
#define DEVICE_ID 1        // Dispositivo Id
#define MOTO_ID 1001       // Código para MOTO-001 
#define PATIO_ID 5         // Código para Pátio
#define STATUS_CODE 2      // Código para status

void setup() {
  Serial.begin(115200);
  connectToWiFi();
}

void connectToWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Conectado!");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }
  
  delay(15000); // Intervalo de 15s entre envios

  HTTPClient http;
  http.begin(server);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String postData = "api_key=" + apiKey +
                   "&field1=" + String(DEVICE_ID) +
                   "&field2=" + String(MOTO_ID) +
                   "&field3=" + String(PATIO_ID) +
                   "&field4=" + String(STATUS_CODE); // Corrigido STATUS_CODE

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.println("✅ Dados enviados com sucesso para o ThingSpeak:");
    Serial.println(postData);
  } else {
    Serial.print("❌ Erro ao enviar: ");
    Serial.println(httpResponseCode);
    Serial.println("Resposta: " + http.getString()); // Mostra resposta do servidor
  }

  http.end();
}