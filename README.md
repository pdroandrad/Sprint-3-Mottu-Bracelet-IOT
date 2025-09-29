# MottuBracelet 🏍️🔊📡

**Solução IoT desenvolvida pela equipe Amplexus Technology para auxiliar na localização e monitoramento de motos nos pátios da empresa Mottu, utilizando tecnologias como MQTT, HTTP, dashboards integrados e persistência de dados.**

---

## 👨‍💻 Integrantes

- Pedro Abrantes Andrade | RM558186
- Ricardo Tavares de Oliveira Filho | RM556092
- Victor Alves Carmona | RM555726

---

## 🔧 Tecnologias Utilizadas

- ESP32
- Arduino IDE / VS Code + PlatformIO
- [Wokwi](https://wokwi.com/) (simulador de circuitos)
- [HiveMQ](https://www.hivemq.com/) (Broker MQTT gratuito)
- [ThingSpeak](https://thingspeak.com/) (dashboard para IoT)
- Python 3 + Requests (para coleta de dados e persistência em CSV)

---

## 🧠 Visão Geral do Projeto

O **MottuBracelet** simula um dispositivo que é acoplado a motos estacionadas em pátios da Mottu. Ele pode ser:

- **Acionado remotamente via MQTT** (para localização com buzzer e LED);
- **Monitorado em uma dashboard via HTTP/ThingSpeak** (telemetria com GPS simulado e nível de bateria);
- **Registrado localmente em CSV** (persistência de dados para análise histórica).

---

## 📁 Estrutura do Repositório

```text
├── mqtt-localizacao/
│   ├── sketch.ino       # Código para acionar LED e buzzer via MQTT
│   ├── diagram.json     # Diagrama do circuito no Wokwi
│   ├── libraries.txt    # Bibliotecas instaladas
│
├── http-dashboard/
│   ├── sketch.ino       # Código para envio de dados de telemetria ao ThingSpeak
│   ├── diagram.json     # Diagrama correspondente
│
├── data-logger/
│   └── logger.py        # Script Python para coletar dados do ThingSpeak e salvar em CSV
│
└── README.md            # Instruções e informações do projeto
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

## 🌐 Projeto 2 – Envio de Telemetria ao ThingSpeak

**Descrição:** A cada 20 segundos, o dispositivo envia ao canal do ThingSpeak informações simuladas de telemetria.

### ✅ Teste a simulação:
🔗 [Simulação no Wokwi - HTTP/ThingSpeak](https://wokwi.com/projects/443436161135181825)

### 🧾 Campos no ThingSpeak:
- **Field 1** – ID do Dispositivo (bracelete)
- **Field 2** – ID da Moto
- **Field 3** – ID do Pátio
- **Field 4** – Status Dispositivo (código da avaria)
- **Field 5** – Latitude
- **Field 6** – Longitude
- **Field 7** – Bateria (%)
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

## 🗂 Projeto 3 – Persistência em CSV

**Descrição:** O script logger.py coleta periodicamente os dados do ThingSpeak e salva em um arquivo CSV chamado telemetria.csv.

### ✅ Como executar:
```cpp
cd data-logger
pip install requests
python logger.py
```

### Saída: Um arquivo telemetria.csv contendo os registros históricos de latitude, longitude, nível da bateria e timestamp.

## 📌 Casos de Uso Demonstrados

1. **Moto desaparecida no pátio**  
   - Supervisor publica `localizar` no tópico MQTT.  
   - Bracelete responde com buzzer + LED piscando.  

2. **Moto em pátio incorreto**  
   - GPS simulado envia coordenadas divergentes.  
   - Dashboard do ThingSpeak mostra discrepância.  

3. **Bateria baixa**  
   - Bracelete envia percentual de bateria ao ThingSpeak.  
   - Persistência no CSV permite análise posterior.

## Resultados obtidos

- Simulação validada com sucesso no Wokwi.
- Comunicação funcional entre dispositivos via MQTT e HTTP.
- Dashboard do ThingSpeak atualizado em tempo real.
- Persistência de dados local em CSV implementada.
- Solução escalável e adaptável a diferentes plantas de pátios da Mottu.
