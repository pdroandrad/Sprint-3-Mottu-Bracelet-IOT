#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

const int BUZZER_PIN = 13;
const int LED_PIN = 12;

bool localizarAtivo = false;
unsigned long tempoAnterior = 0;
int bipAtual = 0;
bool buzzerLigado = false;

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)message[i];
  }

  if (msg == "localizar") {
    localizarAtivo = !localizarAtivo;
    if (!localizarAtivo) {
      noTone(BUZZER_PIN);
      digitalWrite(LED_PIN, LOW);
      bipAtual = 0;
      buzzerLigado = false;
    } else {
      digitalWrite(LED_PIN, HIGH);
      tempoAnterior = millis();
      bipAtual = 0;
      buzzerLigado = false;
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("MottuBraceletClient")) {
      client.subscribe("mottu/moto123");
    } else {
      delay(1000);
    }
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (localizarAtivo) {
    unsigned long agora = millis();
    unsigned long tempoDecorrido = agora - tempoAnterior;

    if (bipAtual < 3) {
      // Ciclo de bip (200ms ligado, 300ms desligado)
      if (!buzzerLigado && tempoDecorrido >= (500 * bipAtual)) {
        tone(BUZZER_PIN, 2000); // Bip agudo (2000Hz)
        buzzerLigado = true;
        tempoAnterior = agora;
        Serial.println("Bip ON");
      } else if (buzzerLigado && tempoDecorrido >= 200) {
        noTone(BUZZER_PIN);
        buzzerLigado = false;
        bipAtual++;
        tempoAnterior = agora;
        Serial.println("Bip OFF");
      }
    } else {
      // Pausa de 1s após 3 bips
      if (tempoDecorrido >= 1000) {
        bipAtual = 0;
        tempoAnterior = agora;
        Serial.println("Reiniciando ciclo");
      }
    }
  }
}