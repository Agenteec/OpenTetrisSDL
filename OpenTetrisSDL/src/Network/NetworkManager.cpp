#include "Network/NetworkManager.h"

NetworkManager::NetworkManager()
    : tcp_socket_(io_context_), udp_socket_(io_context_), running_(false) {}

NetworkManager::~NetworkManager() {
    stop();
}

void NetworkManager::start(const std::string& host, const std::string& tcpPort, const std::string& udpPort) {
    boost::asio::ip::tcp::resolver tcp_resolver(io_context_);
    boost::asio::connect(tcp_socket_, tcp_resolver.resolve(host, tcpPort));

    boost::asio::ip::udp::resolver udp_resolver(io_context_);
    udp_endpoint_ = *udp_resolver.resolve(host, udpPort).begin();
    udp_socket_.open(boost::asio::ip::udp::v4());

    running_ = true;
    network_thread_ = std::thread([this]() { io_context_.run(); });

    receiveTCP();
    receiveUDP();
}

void NetworkManager::sendTCP(const std::string& message) {
    boost::asio::write(tcp_socket_, boost::asio::buffer(message));
}

void NetworkManager::sendUDP(const std::string& message) {
    udp_socket_.send_to(boost::asio::buffer(message), udp_endpoint_);
}

void NetworkManager::receiveTCP() {
    boost::asio::async_read_until(tcp_socket_, boost::asio::dynamic_buffer(tcp_buffer_), "\n",
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            handleTCPRead(error, bytes_transferred);
        });
}

void NetworkManager::receiveUDP() {
    udp_socket_.async_receive_from(boost::asio::buffer(udp_buffer_), udp_endpoint_,
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            handleUDPRead(error, bytes_transferred);
        });
}

void NetworkManager::handleTCPRead(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::string message(tcp_buffer_.substr(0, bytes_transferred));
        tcp_buffer_.erase(0, bytes_transferred);
        // TCP -----------------------------------
        //
        //
        receiveTCP();
    }
}

void NetworkManager::handleUDPRead(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::string message(udp_buffer_.substr(0, bytes_transferred));
        // UDP -----------------------------------
        //
        //
        receiveUDP();
    }
}

void NetworkManager::stop() {
    running_ = false;
    io_context_.stop();
    if (network_thread_.joinable()) {
        network_thread_.join();
    }
}