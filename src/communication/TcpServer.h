#pragma once

#include <atomic>
#include <cstdint>
#include <thread>
#include<mutex>
#include<vector>
#include "MessageSerialization.h"
#include "CommandHandler.h"
#include "CommandParser.h"
class TcpServer {
public:
    TcpServer(
        std::uint16_t port,
        CommandHandler& commandHandler
    );
    ~TcpServer();

    bool start();
    void stop();

private:
    void serverLoop();
    void handleClient(int clientSocket);
    bool sendAll(
        int clientSocket,
        const std::string& data
    );
    std::vector<std::thread> clientThreads;
    std::vector<int> clientSockets;
    std::mutex clientMutex;

    std::uint16_t port;
    std::atomic<bool> running;
    std::thread serverThread;
    CommandHandler& commandHandler;
    MessageSerializer messageSerial;
    int serverSocket;
};