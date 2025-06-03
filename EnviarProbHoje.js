let previsao = global.get("previsao_precipitacao") || [];
msg.payload = previsao.length > 0 ? previsao[0].precipitacao : 0;
return msg;