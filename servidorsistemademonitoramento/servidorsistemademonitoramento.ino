#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include "ACS712.h"

ACS712 sensor(ACS712_05B, 34);


const char* ssid = "seunomederedewifi";
const char* password = "senhadoseuwifi";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

int contador = 0;
float corrente = 0.00;
float voltagem = 0.00;

unsigned long ultimoTempo = 0;
const unsigned long intervalo = 1000;  // Intervalo de atualização em milissegundos (1 segundo)

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Cliente desconectado!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Cliente conectado do IP %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] Recebido: %s\n", num, payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.println("Aguarde. Calibrando..."); 
  sensor.calibrate();
  Serial.println("Fim da calibração");


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conexão WiFi estabelecida");

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  // Iniciar contador
  contador = 0;
  ultimoTempo = millis();


  // Configurar a página web
  server.on("/", HTTP_GET, []() {
    String mensagem = String(contador);
    // Adicionar dados ao JSON
    StaticJsonDocument<200> doc;

      float V = 127;
  float I = sensor.getCurrentAC(60);
  float P = V * I;
    

    // Adicionar dados ao JSON
    doc["nome"] = "Esp32";
    doc["corrente"] = I;
    doc["voltagem"] = P;

    // Serializar o JSON para uma string
    String jsonString;
    serializeJson(doc, jsonString);

    server.send(200, "text/plain", jsonString);
  });

  server.begin();
}

void loop() {
  webSocket.loop();
  StaticJsonDocument<200> doc;

  // Atualizar o contador a cada intervalo de tempo
  unsigned long agora = millis();
  if (agora - ultimoTempo >= intervalo) {
    corrente++;
    voltagem++;
    ultimoTempo = agora;

  float V = 127;
  float I = sensor.getCurrentAC(60);
  float P = V * I;   

    // Adicionar dados ao JSON
    doc["nome"] = "Esp32";
    doc["corrente"] = I;
    doc["voltagem"] = P;


    // Serializar o JSON para uma string
    String jsonString;
    serializeJson(doc, jsonString);
    webSocket.broadcastTXT(jsonString);
  }

  // Lidar com as solicitações do cliente
  server.handleClient();
}
