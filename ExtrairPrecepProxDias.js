let dias = msg.payload.data;
let precipitacoes = dias.map(d => ({
    dia: d.forecastDate,
    precipitacao: d.precipitaProb
}));

msg.payload = precipitacoes;
return msg;