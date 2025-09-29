# MottuBracelet 🏍️🔊📡

**Solução IoT desenvolvida pela equipe Amplexus Technology para auxiliar na localização de motos nos pátios da empresa Mottu, utilizando tecnologias como MQTT, HTTP e dashboards integrados.**

---

## 🔧 Tecnologias Utilizadas

- ESP32
- Arduino IDE
- [Wokwi](https://wokwi.com/) (simulador de circuitos)
- [HiveMQ](https://www.hivemq.com/) (Broker MQTT gratuito)
- [ThingSpeak](https://thingspeak.com/) (dashboard para IoT)

---

## 🧠 Visão Geral do Projeto

O MottuBracelet simula um dispositivo que é acoplado a motos estacionadas em pátios da Mottu. Ele pode ser:

- Acionado remotamente por MQTT (para localização com buzzer e LED);
- Monitorado em uma dashboard via HTTP (para visualização de status, pátio e dados da moto).

---

## 📁 Estrutura do Repositório

```text
├── mqtt-localizacao/
│ ├── sketch.ino       # Código para acionar LED e buzzer via MQTT
│ ├── diagram.json     # Diagrama do circuito no Wokwi
│ ├── libraries.txt    # Bibliotecas instaladas
│
├── http-dashboard/
│ ├── sketch.ino       # Código para envio de dados ao ThingSpeak
│ ├── diagram.json     # Diagrama correspondente
│
└── README.md          # Instruções e informações do projeto
```

---

## 🔌 Projeto 1 – Localização via MQTT (HiveMQ)

**Descrição:** Ao publicar a mensagem `localizar` no tópico MQTT, o bracelete é acionado (buzzer emite som + LED acende), facilitando a localização da moto no pátio.

### ✅ Teste a simulação:
🔗 [Simulação no Wokwi - MQTT](https://wokwi.com/projects/431504374736820225)

### ⚙️ Parâmetros MQTT:
- **Broker**: [broker.hivemq.com](https://www.hivemq.com/demos/websocket-client/)
  Fazer conexão com Host `broker.hivemq.com`, Port `8000` e ClientID `testeMottu123`
- **Tópico**: `mottu/moto123`
- **Mensagem**: `localizar`

### 💡 Comportamento:
- Ao receber "localizar", o sistema emite 3 bipes sonoros e acende o LED.
- O sistema pode ser acionado e desativado quantas vezes for necessário.

---

## 🌐 Projeto 2 – Envio de Dados ao ThingSpeak

**Descrição:** Ao iniciar o sistema, ele envia os dados de cadastro do bracelete (ID, pátio, moto e status) para um canal do ThingSpeak.

### ✅ Teste a simulação:
🔗 [Simulação no Wokwi - HTTP/ThingSpeak](https://wokwi.com/projects/431512695946249217)

### 🧾 Campos no ThingSpeak:
- **Field 1** – ID do Dispositivo (bracelete)
- **Field 2** – ID da Moto
- **Field 3** – ID do Pátio
- **Field 4** – Status Dispositivo (código da avaria)
- 
### 🛠️ Configure seu canal:
- Crie um canal no [ThingSpeak](https://thingspeak.mathworks.com/).
- Copie a **Write API Key** (em API Keys).
- Edite o código para incluir sua chave e número do canal nas variáveis:
```cpp
const char* apiKey = "SUA_API_KEY";
const char* server = "api.thingspeak.com";
```

---

## Resultados obtidos

- Simulação validada com sucesso.
- Comunicação funcional entre dispositivos MQTT e dashboard HTTP.
- Solução escalável e adaptável a diferentes plantas de pátios da Mottu.
