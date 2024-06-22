#include "Network/NetworkManager.h"

NetworkManager::NetworkManager()
    : tcp_socket_(io_context_), udp_socket_(io_context_), running_(false), tcp_receiving_(false), udp_receiving_(false) {}

NetworkManager::~NetworkManager() {
    stop();
}

void NetworkManager::start(const std::string& host, const std::string& tcpPort, const std::string& udpPort) {
    try {
        spdlog::info("Starting NetworkManager with host={}, tcpPort={}, udpPort={}", host, tcpPort, udpPort);

        boost::asio::ip::tcp::resolver tcp_resolver(io_context_);
        auto tcp_endpoints = tcp_resolver.resolve(host, tcpPort);
        boost::asio::connect(tcp_socket_, tcp_endpoints);

        boost::asio::ip::udp::resolver udp_resolver(io_context_);
        auto udp_endpoints = udp_resolver.resolve(host, udpPort);
        udp_endpoint_ = *udp_endpoints.begin();
        udp_socket_.open(boost::asio::ip::udp::v4());

        running_ = true;
        network_thread_ = std::thread([this]() { io_context_.run(); });

        receiveTCP();
        receiveUDP();

        spdlog::info("NetworkManager started successfully");
    }
    catch (const boost::system::system_error& e) {
        spdlog::error("Failed to start NetworkManager: {}", e.what());
        throw;
    }
}

void NetworkManager::sendTCP(const std::string& message) {
    try {
        boost::asio::write(tcp_socket_, boost::asio::buffer(message));
        spdlog::info("Sent TCP message: {}", message);
    }
    catch (const boost::system::system_error& e) {
        spdlog::error("TCP send error: {}", e.what());
    }
}

void NetworkManager::sendUDP(const std::string& message) {
    try {
        udp_socket_.async_send_to(boost::asio::buffer(message), udp_endpoint_, [this, message](boost::system::error_code ec, std::size_t) {
            if (ec) {
                spdlog::error("UDP send error: {}", ec.message());
            }
            else {
                spdlog::info("Sent UDP message: {}", message);
            }
            });
    }
    catch (const boost::system::system_error& e) {
        spdlog::error("UDP send error: {}", e.what());
    }
}

void NetworkManager::receiveTCP() {
    if (tcp_receiving_.load()) return;
    tcp_receiving_.store(true);
    boost::asio::async_read_until(tcp_socket_, boost::asio::dynamic_buffer(tcp_buffer_), "\n",
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            handleTCPRead(error, bytes_transferred);
            tcp_receiving_.store(false);
            if (!error) {
                receiveTCP();
            }
        });
}

void NetworkManager::receiveUDP() {
    if (udp_receiving_.load()) return;
    udp_receiving_.store(true);
    udp_socket_.async_receive_from(boost::asio::buffer(udp_buffer_), udp_endpoint_,
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            handleUDPRead(error, bytes_transferred);
            udp_receiving_.store(false);
            if (!error) {
                receiveUDP();
            }
        });
}

void NetworkManager::handleTCPRead(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::string message(tcp_buffer_.substr(0, bytes_transferred));
        tcp_buffer_.erase(0, bytes_transferred);
        spdlog::info("Received TCP message: {}", message);
    }
    else {
        spdlog::error("TCP read error: {}", error.message());
        if (error == boost::asio::error::eof) {
            spdlog::warn("TCP connection closed by peer");
        }
        tcp_socket_.close();
    }
}

void NetworkManager::handleUDPRead(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::string message(udp_buffer_.substr(0, bytes_transferred));
        spdlog::info("Received UDP message: {}", message);
    }
    else {
        spdlog::error("UDP read error: {}", error.message());
        udp_socket_.close();
    }
}

void NetworkManager::stop() {
    running_ = false;
    io_context_.stop();
    if (network_thread_.joinable()) {
        network_thread_.join();
    }
    spdlog::info("NetworkManager stopped");
}