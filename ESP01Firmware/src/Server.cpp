#include "Server.h"
#include "wifiinfo.h"
#include "FanController.h"

Server::Server(uint16_t port) : tcpServer(port), port(port) {}

void Server::setup() {
    tcpServer.begin();
    tcpServer.setNoDelay(true);

    WiFi.begin(ssid, password);
    Display::setWifiConnected(false);
    Display::showNotification("Connexion au WiFi");
    unsigned long cont = 0;
    

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        cont++;
        if (cont > 10){
            Display::showNotification("Erreur Wi-Fi.");
            cont = 0;
        }
    }

    Display::setWifiConnected(true);
    Display::showNotification("WiFi connecté.");
}

bool Server::receivePacket(InfoPacket &packet) {
    if (!currentClient || !currentClient.connected()) {
        currentClient = tcpServer.accept(); 
    }
    if (currentClient && currentClient.available() >= sizeof(InfoPacket)) {
        // 1. Lê os dados para a estrutura temporária
        currentClient.read((uint8_t*)&packet, sizeof(InfoPacket));

        // 2. Verifica a senha
        if (strcmp(packet.password, ACCESS_PASSWORD) == 0) {
            return true; // Senha correta!
        } else {
            // Senha incorreta: log opcional e descarta
            Display::showNotification("Mot de passe incorrect");
            return false;
        }
    }
    return false;
}

bool Server::hasClient() {
    return currentClient && currentClient.connected();
}

void Server::commandHandler(InfoPacket &packet) {
    // 1. Caso seja atualização de TERMINAL (Texto com \n)
    if (packet.type == TERMINAL_TEXT_TYPE) {
        String fullContent = String(packet.payload.terminal_text);
        int lineIdx = 0;
        int startPos = 0;
        
        // Encontra a posição do primeiro \n
        int endPos = fullContent.indexOf('\n');

        // Itera pela string quebrando nos \n até preencher as ROWS
        while (endPos != -1 && lineIdx < ROWS) {
            Display::setTextRow(fullContent.substring(startPos, endPos),lineIdx);

            startPos = endPos + 1;
            endPos = fullContent.indexOf('\n', startPos);
            lineIdx++;
        }

        // Pega o restante da string (caso não termine em \n)
        if (lineIdx < ROWS && startPos < (int)fullContent.length()) {
            Display::setTextRow(fullContent.substring(startPos),lineIdx);
            lineIdx++;
        }

        // Limpa as linhas restantes caso o pacote tenha menos que 6 linhas
        for (int i = lineIdx; i < ROWS; i++) {
            Display::setTextRow("",i);
        }
        
    } 
    
    // 2. Caso seja atualização da TELEMETRIA
    else if (packet.type == TELEMETRY_TYPE) {
        Display::setAll(packet.payload.data);
        Display::showNotification("Info received.");
        FanController::setSpeed(packet.payload.data.fan_speed);
        // Se o display estiver no modo de tela principal, atualiza
        // Display::showMainView(...); 
    }
}