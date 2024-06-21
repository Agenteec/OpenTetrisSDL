#pragma once

#include "Network/NetworkManager.h"

class Client {
public:
    Client(const std::string& host, const std::string& tcpPort, const std::string& udpPort);
    ~Client();
    void sendTCP(const std::string& message);
    void sendUDP(const std::string& message);
    void receiveTCP();
    void receiveUDP();
    GameState& getGameState();

private:
    NetworkManager networkManager_;
    GameState gameState_;
};
