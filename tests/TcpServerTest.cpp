#include "../src/communication/TcpServer.h"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    TcpServer server(5000);

    if (!server.start()) {
        std::cerr << "Failed to start TCP server\n";
        return 1;
    }

    std::cout
        << "TCP server started on port 5000\n";

    std::this_thread::sleep_for(
        std::chrono::seconds(30)
    );

    server.stop();

    std::cout
        << "TCP server stopped\n";

    return 0;
}