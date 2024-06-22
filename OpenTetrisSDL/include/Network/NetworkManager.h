#pragma once

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include <atomic>
#include <string>
#include <mutex>
#include <vector>

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
    void start(const std::string& host, const std::string& tcpPort, const std::string& udpPort);
    void sendTCP(const std::string& message);
    void sendUDP(const std::string& message);
    void receiveTCP();
    void receiveUDP();
    void stop();

private:
    void handleTCPRead(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handleUDPRead(const boost::system::error_code& error, std::size_t bytes_transferred);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket tcp_socket_;
    boost::asio::ip::udp::socket udp_socket_;
    boost::asio::ip::udp::endpoint udp_endpoint_;
    std::thread network_thread_;
    std::atomic<bool> running_;
    std::string tcp_buffer_;
    std::string udp_buffer_;
    std::atomic<bool> tcp_receiving_;
    std::atomic<bool> udp_receiving_;
};