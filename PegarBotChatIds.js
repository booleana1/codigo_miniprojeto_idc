const chatId = msg.payload.chatId;

// Recupera a lista atual de chat_ids do contexto global
let lista = global.get("chat_ids") || [];

// Se o chatId ainda não estiver salvo, adiciona
if (!lista.includes(chatId)) {
    lista.push(chatId);
    global.set("chat_ids", lista);
    node.warn("Novo chat_id salvo: " + chatId);
}

// Prepara resposta de confirmação
msg.payload = {
    chatId: chatId,
    type: 'message',
    content: '✅ Você foi registrado para receber alertas!'
};

return msg;