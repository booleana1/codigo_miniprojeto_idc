# Projeto IoT – Monitoramento de Enchentes (Node-RED + Wokwi)

Este repositório contém o projeto desenvolvido na disciplina de **Internet das Coisas**, com foco no monitoramento de variáveis ambientais através de sensores simulados no **Wokwi** e lógica de automação implementada no **Node-RED**.

## 📍 Descrição Geral

O sistema simula a leitura de dois sensores:
- **Sensor de chuva** (representado por um potenciômetro no Wokwi)
- **Sensor de profundidade** (representado por um sensor ultrassônico HC-SR04)

Esses sensores são simulados em tempo real no ambiente Wokwi, enviando dados para o Node-RED via protocolo **MQTT**. A lógica de controle, visualização e envio de alertas é toda feita no Node-RED, incluindo a notificação via **bot do Telegram**.

---

## 🧠 Tecnologias Utilizadas

- **Node-RED** (fluxo de automação, visualização e alertas)
- **Wokwi** (simulação dos sensores com ESP32)
- **MQTT** (comunicação entre ESP32 e Node-RED)
- **Bot do Telegram** (envio de alertas em tempo real)
- **Dashboard Node-RED** (visualização em tempo real dos sensores)

---

## 🚀 Funcionalidades

- Leitura contínua dos sensores de chuva e profundidade
- Exibição em painel interativo via Node-RED Dashboard
- Envio de alerta automático via **Telegram Bot** quando valores críticos são detectados
- Simulação precisa de condições ambientais para testes de automação
