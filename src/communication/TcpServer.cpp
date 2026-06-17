#include "TcpServer.h"
#include <cerrno>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>
#include "ProtocolSerializer.h"

TcpServer::TcpServer(std::uint16_t port,CommandHandler& commandHandler)
    : port(port),
      running(false),
      serverSocket(-1),
      commandHandler(commandHandler)
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
    std::vector<int> sockets;
    {
        std::lock_guard<std::mutex> lock(clientMutex);
        sockets = clientSockets;
    }
    for (int socket:sockets){
        shutdown(socket,SHUT_RDWR);
    }
    for(auto& thread:clientThreads){
        if(thread.joinable()){
            thread.join();
        }
    }
    clientThreads.clear();
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
        clientThreads.emplace_back(
            &TcpServer::handleClient,this,
            clientSocket
        );
        handleClient(clientSocket);
    }
}
void TcpServer::handleClient(int clientSocket)
{
    const std::string welcomeMessage =
        "SEMICONDUCTOR_CONTROLLER_READY\n";

    if (!sendAll(clientSocket, welcomeMessage)) {
        std::cerr << "Failed to send welcome message\n";
        close(clientSocket);
        return;
    }

    char buffer[1024];

    std::string receiveBuffer;

    while (running) {

        const ssize_t bytesReceived =
            recv(
                clientSocket,
                buffer,
                sizeof(buffer),
                0
            );

        // Client disconnected normally
        if (bytesReceived == 0) {
            std::cout << "Client disconnected\n";
            break;
        }

        // Network/transport error
        if (bytesReceived < 0) {

            if (errno == EINTR) {
                continue;
            }

            std::cerr
                << "Receive error: "
                << std::strerror(errno)
                << '\n';

            break;
        }

        // Append exactly the bytes received.
        receiveBuffer.append(
            buffer,
            static_cast<std::size_t>(bytesReceived)
        );

        // Process every complete message.
        while (true) {

            const std::size_t delimiter =
                receiveBuffer.find('\n');

            if (delimiter == std::string::npos) {
                break;
            }

            std::string message =
                receiveBuffer.substr(
                    0,
                    delimiter
                );

            receiveBuffer.erase(
                0,
                delimiter + 1
            );

            // Ignore empty messages
            if (message.empty()) {
                continue;
            }

            std::cout
                << "Received: "
                << message
                << '\n';

            try {
                ProtocolMessage protocolMessage =
                    ProtocolSerializer::deserialize(message);

                Command command =
                    CommandParser::parse(protocolMessage);

                Response response =
                    commandHandler.execute(command);

                std::string responseText;

                if (response.success) {
                    responseText =
                        "OK|" +
                        response.message +
                        "\n";
                }
                else {
                    responseText =
                        "ERROR|" +
                        response.message +
                        "\n";
                }

                if (!sendAll(clientSocket, responseText)) {
                    std::cerr
                        << "Failed to send response\n";
                    break;
                }

            }
            catch (const std::exception& error) {

                std::string response =
                    "ERROR|" +
                    std::string(error.what()) +
                    "\n";

                if (!sendAll(clientSocket, response)) {
                    std::cerr
                        << "Failed to send error response\n";
                    break;
                }
            }
            const std::string response =
                "OK|Message received\n";

            if (!sendAll(clientSocket, response)) {
                std::cerr
                    << "Failed to send response\n";
                break;
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(clientMutex);

        auto it = std::find(
            clientSockets.begin(),
            clientSockets.end(),
            clientSocket
        );

        if (it != clientSockets.end()) {
            clientSockets.erase(it);
        }
    }

    close(clientSocket);

    std::cout
        << "Client connection closed\n";
}

bool TcpServer::sendAll(
    int clientSocket,
    const std::string& data
)
{
    std::size_t totalSent = 0;

    while (totalSent < data.size()) {

        const ssize_t bytesSent =
            send(
                clientSocket,
                data.data() + totalSent,
                data.size() - totalSent,
                0
            );

        if (bytesSent <= 0) {
            return false;
        }

        totalSent +=
            static_cast<std::size_t>(bytesSent);
    }

    return true;
}