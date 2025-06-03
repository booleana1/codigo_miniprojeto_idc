#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define POT_PIN 1
#define LED_PIN 4
#define BUZZER_PIN 5

const char* mqtt_server = "broker.emqx.io";
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* pubTopic = "IPB/IoT/Lab/TurnoB/Projeto/Enchente/EnvironmentInfo";
const char* subTopic = "IPB/IoT/Lab/TurnoB/Projeto/Enchente/AlertInfo";

WiFiClient espClient;
PubSubClient client(espClient);

long lastTime = 0;
char msg[100];

void setup_wifi() {
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password, 6); // canal 6 para Wokwi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  String strPayload = "";
  for (unsigned int i = 0; i < length; i++) {
    strPayload += (char)payload[i];
  }
  Serial.print("Payload: ");
  Serial.println(strPayload);

  StaticJsonDocument<100> doc;
  DeserializationError error = deserializeJson(doc, strPayload);

  if (error) {
    Serial.print("Erro ao parsear JSON: ");
    Serial.println(error.f_str());
    return;
  }

  if (String(topic) == subTopic) {
    int alert = doc["alert"];
    digitalWrite(LED_PIN, alert);
    digitalWrite(BUZZER_PIN, alert);
    Serial.print("Alerta: ");
    Serial.println(alert ? "LIGADO" : "DESLIGADO");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado!");
      client.subscribe(subTopic);
    } else {
      Serial.print("Falha. Código: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s");
      delay(5000);
    }
  }
}

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration / 3.6825;  // fator empírico para Wokwi
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  long now = millis();
  if (now - lastTime > 2000) {
    lastTime = now;

    float distanceCm = readDistance();
    int potValue = analogRead(POT_PIN);

    StaticJsonDocument<100> doc;
    doc["distanceCm"] = distanceCm;
    doc["potValue"] = potValue;
    serializeJson(doc, msg);

    Serial.print("Publicando: ");
    Serial.println(msg);
    client.publish(pubTopic, msg);
  }
}
