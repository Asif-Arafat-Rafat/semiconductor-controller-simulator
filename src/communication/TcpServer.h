#pragma once

#include <atomic>
#include <cstdint>
#include <thread>

class TcpServer {
public:
    explicit TcpServer(std::uint16_t port);
    ~TcpServer();

    bool start();
    void stop();

private:
    void serverLoop();

    std::uint16_t port;
    std::atomic<bool> running;
    std::thread serverThread;

    int serverSocket;
};