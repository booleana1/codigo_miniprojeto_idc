let chatIds = global.get("chat_ids") || [];

let mensagens = chatIds.map(id => ({
    payload: {
        chatId: id,
        type: 'message',
        content: '🚨 Alerta de enchente! Dirija-se ao ponto de evacuação mais próximo.'
    }
}));

if (msg.payload.alert === 1) {
    return mensagens;
} else {
    return null;
}