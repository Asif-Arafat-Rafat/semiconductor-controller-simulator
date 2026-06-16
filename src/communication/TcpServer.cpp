#include "TcpServer.h"

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

TcpServer::TcpServer(std::uint16_t port)
    : port(port),
      running(false),
      serverSocket(-1)
{
}

TcpServer::~TcpServer()
{
    stop();
}

bool TcpServer::start()
{
    if (running) {
        return false;
    }

    serverSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (serverSocket < 0) {
        std::cerr
            << "Failed to create TCP socket\n";

        return false;
    }

    int reuse = 1;

    setsockopt(
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &reuse,
        sizeof(reuse)
    );

    sockaddr_in address{};

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(
        serverSocket,
        reinterpret_cast<sockaddr*>(&address),
        sizeof(address)
    ) < 0) {

        std::cerr
            << "Failed to bind TCP socket: "
            << std::strerror(errno)
            << '\n';

        close(serverSocket);
        serverSocket = -1;

        return false;
    }

    if (listen(serverSocket, 5) < 0) {

        std::cerr
            << "Failed to listen on TCP socket\n";

        close(serverSocket);
        serverSocket = -1;

        return false;
    }

    running = true;

    serverThread = std::thread(
        &TcpServer::serverLoop,
        this
    );

    return true;
}

void TcpServer::stop()
{
    running = false;

    if (serverSocket >= 0) {
        shutdown(
            serverSocket,
            SHUT_RDWR
        );

        close(serverSocket);
        serverSocket = -1;
    }

    if (serverThread.joinable()) {
        serverThread.join();
    }
}

void TcpServer::serverLoop()
{
    while (running) {

        sockaddr_in clientAddress{};
        socklen_t clientLength =
            sizeof(clientAddress);

        int clientSocket = accept(
            serverSocket,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientLength
        );

        if (clientSocket < 0) {

            if (running) {
                std::cerr
                    << "Failed to accept connection\n";
            }

            continue;
        }

        std::cout
            << "Client connected\n";

        const char* message =
            "SEMICONDUCTOR_CONTROLLER_READY\n";

        send(
            clientSocket,
            message,
            std::strlen(message),
            0
        );

        close(clientSocket);

        std::cout
            << "Client disconnected\n";
    }
}