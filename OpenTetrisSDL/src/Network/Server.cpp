#include "Network/Server.h"

Server::Server(short tcpPort, short udpPort)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), tcpPort)),
    networkManager_(), physicsEngine_(), gameState_(), running_(false) {
    networkManager_.start("0.0.0.0", std::to_string(tcpPort), std::to_string(tcpPort));
}

Server::~Server() {
    stop();
}

void Server::start() {
    running_ = true;
    acceptor_.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
        handleAccept(error);
        });

    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        worker_threads_.emplace_back([this]() { io_context_.run(); });
    }

    // Main loop
    while (running_) {
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 60 TPS
    }
}

void Server::stop() {
    running_ = false;
    io_context_.stop();
    for (auto& thread : worker_threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    networkManager_.stop();
}

void Server::handleAccept(const boost::system::error_code& error) {
    if (!error) {
        //обработка пользователя
        //--------------------------------------------------------
    }
    if (running_) {
        acceptor_.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
            handleAccept(error);
            });
    }
}

void Server::update() {
    physicsEngine_.update();
    gameState_.update();
    // Отправить обновленное состояние клиентам нужно будет ----------------------------------
}
