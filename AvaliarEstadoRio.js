let nivel = msg.payload.distanceCm;
let chuvaAtual = msg.payload.potValue;

let estado = "";
let alert = 0;

// Obtem previsão de chuva do contexto global
let previsao = global.get("previsao_precipitacao") || [];
let chanceChuvaHoje = previsao.length > 0 ? parseInt(previsao[0].precipitacao) : 0;

// Critérios combinados
if (nivel > 300) {
    estado = "Abaixo do nível";
} else if (nivel > 150) {
    estado = "Normal";
} else if (nivel > 80) {
    estado = "Alerta";
    if (chanceChuvaHoje >= 50) alert = 1;  // chuva aumenta risco
} else {
    estado = "Crítico";
    alert = 1;
}

msg.payload = {
    distanceCm: nivel,
    potValue: chuvaAtual,
    estado: estado,
    alert: alert,
    timestamp: new Date().toISOString()
};

return msg;