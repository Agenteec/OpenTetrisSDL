#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include "NetworkManager.h"
#include "PhysicsEngine.h"
#include "GameState.h"

class Server {
public:
    Server(short tcpPort, short udpPort);
    ~Server();
    void start();
    void stop();

private:
    void handleAccept(const boost::system::error_code& error);
    void update();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    NetworkManager networkManager_;
    PhysicsEngine physicsEngine_;
    GameState gameState_;
    std::vector<std::thread> worker_threads_;
    bool running_;
};
