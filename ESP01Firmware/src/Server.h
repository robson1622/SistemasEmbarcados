#ifndef SERVER_H_
#define SERVER_H_

#include <ESP8266WiFi.h>
#include "Display.h"
#include "InfoType.h" // Importante incluir para reconhecer InfoPacket

class Server {
private:
    WiFiServer tcpServer;
    WiFiClient currentClient;
    uint16_t port;

public:
    Server(uint16_t port);
    void setup();
    // Agora retorna true se um pacote completo foi recebido
    bool receivePacket(InfoPacket &packet);
    bool hasClient();
    void commandHandler(InfoPacket &packet);
};

#endif