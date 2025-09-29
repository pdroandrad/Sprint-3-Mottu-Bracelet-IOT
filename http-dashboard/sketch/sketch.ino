#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

String apiKey = "2W2TJDWNT0XVG0CI"; // Substitua pela sua chave
const char* server = "https://api.thingspeak.com/update";

// Dados fixos de identificação
#define DEVICE_ID 1
#define MOTO_ID 1001
#define PATIO_ID 5
#define STATUS_CODE 2

// Variáveis para simular GPS e bateria
float latitude = -23.5505;   // Ponto inicial (São Paulo)
float longitude = -46.6333;
int bateria = 100;           // Começa cheia

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

  // Simulação: gera pequenas variações no GPS
  latitude += ((random(-5, 6)) / 10000.0);  
  longitude += ((random(-5, 6)) / 10000.0);

  // Simulação: consumo de bateria
  bateria -= random(0, 3); // cai 0 a 2% por ciclo
  if (bateria < 10) bateria = 100; // reinicia simulação

  delay(15000); // Intervalo de envio

  HTTPClient http;
  http.begin(server);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String postData = "api_key=" + apiKey +
                    "&field1=" + String(DEVICE_ID) +
                    "&field2=" + String(MOTO_ID) +
                    "&field3=" + String(PATIO_ID) +
                    "&field4=" + String(STATUS_CODE) +
                    "&field5=" + String(latitude, 6) +
                    "&field6=" + String(longitude, 6) +
                    "&field7=" + String(bateria);

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.println("✅ Dados enviados com sucesso:");
    Serial.println(postData);
  } else {
    Serial.print("❌ Erro ao enviar: ");
    Serial.println(httpResponseCode);
    Serial.println("Resposta: " + http.getString());
  }

  http.end();
}
