#pragma once

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include <vector>
#include <atomic>
#include "NetworkManager.h"
#include "PhysicsEngine.h"
#include "GameState.h"

class Server {
public:
    Server(short tcpPort, short udpPort);
    ~Server();
    void start();
    void stop();
    bool isRunning() const;

private:
    void handleAccept(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket);
    void update();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    NetworkManager networkManager_;
    PhysicsEngine physicsEngine_;
    GameState gameState_;
    std::vector<std::thread> worker_threads_;
    std::thread server_thread_;
    std::atomic<bool> running_;
    short tcpPort_;
    short udpPort_;
};