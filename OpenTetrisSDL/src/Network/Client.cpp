#include "Network/Client.h"

Client::Client(const std::string& host, const std::string& tcpPort, const std::string& udpPort) {
    networkManager_.start(host, tcpPort, udpPort);
}

Client::~Client() {
    networkManager_.stop();
}

void Client::sendTCP(const std::string& message) {
    networkManager_.sendTCP(message);
}

void Client::sendUDP(const std::string& message) {
    networkManager_.sendUDP(message);
}

void Client::receiveTCP() {
    networkManager_.receiveTCP();
}

void Client::receiveUDP() {
    networkManager_.receiveUDP();
}

GameState& Client::getGameState() {
    return gameState_;
}