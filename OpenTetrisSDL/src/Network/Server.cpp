#include "Network/Server.h"

Server::Server(short tcpPort, short udpPort)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), tcpPort)),
    networkManager_(), physicsEngine_(), gameState_(), running_(false), tcpPort_(tcpPort), udpPort_(udpPort) {
    networkManager_.start("127.0.0.1", std::to_string(tcpPort), std::to_string(udpPort));
}

Server::~Server() {
    stop();
}

void Server::start() {
    server_thread_ = std::thread([this]() {
        try {
            spdlog::info("Starting server on TCP port {} and UDP port {}", tcpPort_, udpPort_);

            running_ = true;

            acceptor_.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
                handleAccept(error, std::move(socket));
                });

            size_t thread_count = std::max(2u, std::thread::hardware_concurrency());
            for (size_t i = 0; i < thread_count; ++i) {
                worker_threads_.emplace_back([this]() { io_context_.run(); });
            }

            spdlog::info("Server started with {} worker threads", worker_threads_.size());

            while (isRunning()) {
                update();
                std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 60 TPS
            }
        }
        catch (const std::exception& e) {
            spdlog::error("Server encountered an error: {}", e.what());
            stop();
        }
        });
}

void Server::stop() {
    running_ = false;
    io_context_.stop();
    for (auto& thread : worker_threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    if (server_thread_.joinable()) {
        server_thread_.join();
    }
    networkManager_.stop();
}

bool Server::isRunning() const {
    return running_.load();
}

void Server::handleAccept(const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
    if (!error) {
        spdlog::info("Accepted new connection from {}", socket.remote_endpoint().address().to_string());
        if (isRunning()) {
            acceptor_.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
                handleAccept(error, std::move(socket));
                });
        }
    }
    else {
        spdlog::error("Failed to accept new connection: {}", error.message());
        if (isRunning()) {
            acceptor_.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
                handleAccept(error, std::move(socket));
                });
        }
    }
}

void Server::update() {
    physicsEngine_.update();
    gameState_.update();
}
