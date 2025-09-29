import requests
import csv
import time

# Configuração do canal ThingSpeak
CHANNEL_ID = "3094585" 
READ_API_KEY = "7P7NWUV8UR7VLDCB"
URL = f"https://api.thingspeak.com/channels/{CHANNEL_ID}/feeds.json"

def fetch_data():
    """Busca os últimos dados do ThingSpeak"""
    params = {
        "api_key": READ_API_KEY,
        "results": 1  # pega só o último registro
    }
    response = requests.get(URL, params=params)
    if response.status_code == 200:
        data = response.json()
        feeds = data.get("feeds", [])
        if feeds:
            return feeds[0]  # retorna o último registro
    return None

def save_to_csv(data, filename="telemetria.csv"):
    """Salva os dados em CSV"""
    header = ["created_at", "device_id", "moto_id", "patio_id",
              "status_code", "latitude", "longitude", "bateria"]

    file_exists = False
    try:
        with open(filename, "r"):
            file_exists = True
    except FileNotFoundError:
        pass

    with open(filename, "a", newline="", encoding="utf-8") as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=header)

        # escreve cabeçalho só na primeira vez
        if not file_exists:
            writer.writeheader()

        writer.writerow({
            "created_at": data.get("created_at"),
            "device_id": data.get("field1"),
            "moto_id": data.get("field2"),
            "patio_id": data.get("field3"),
            "status_code": data.get("field4"),
            "latitude": data.get("field5"),
            "longitude": data.get("field6"),
            "bateria": data.get("field7")
        })

if __name__ == "__main__":
    print("⏳ Iniciando coleta de dados do ThingSpeak...")
    try:
        while True:
            registro = fetch_data()
            if registro:
                save_to_csv(registro)
                print("✅ Registro salvo:", registro)
            else:
                print("⚠️ Nenhum dado recebido")

            time.sleep(20)  # espera 20s antes de buscar novamente
    except KeyboardInterrupt:
        print("\n⏹️ Coleta encerrada pelo usuário")
