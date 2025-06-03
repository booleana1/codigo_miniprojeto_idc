msg.measurement = "enchente";
msg.tags = { local: "RioSimulado" };
msg.payload = {
    distanceCm: msg.payload.distanceCm,
    potValue: msg.payload.potValue,
    estado: msg.payload.estado,
    alerta: msg.payload.alert
};
return msg;