#include "core/MachineController.h"
#include "core/EventBus.h"

#include "equipment/ProcessChamber.h"
#include "equipment/WaferHandler.h"

#include "communication/TcpServer.h"
#include "communication/CommandHandler.h"

#include "logging/Logger.h"

#include <iostream>

int main()
{
    Logger logger("logs/machine.log");

    logger.log(
        LogLevel::INFO,
        "System starting"
    );

    // --------------------------------------------------
    // Core event system
    // --------------------------------------------------

    EventBus eventBus;


    // --------------------------------------------------
    // Equipment
    // --------------------------------------------------

    ProcessChamber processChamber;
    WaferHandler waferHandler;


    // --------------------------------------------------
    // Machine controller
    // --------------------------------------------------

    MachineController controller(
        eventBus,
        processChamber,
        waferHandler
    );


    // --------------------------------------------------
    // Communication command handler
    // --------------------------------------------------

    CommandHandler commandHandler(
        controller
    );


    // --------------------------------------------------
    // TCP communication
    // --------------------------------------------------

    TcpServer server(
        9000,
        commandHandler
    );


    if (!server.start()) {

        logger.log(
            LogLevel::ERROR,
            "Failed to start TCP server"
        );

        return 1;
    }

    logger.log(
        LogLevel::INFO,
        "TCP server started on port 9000"
    );


    std::cout
        << "Semiconductor Controller Simulator\n";

    std::cout
        << "TCP server listening on port 9000\n";

    std::cout
        << "Press ENTER to stop...\n";


    std::cin.get();


    // --------------------------------------------------
    // Shutdown
    // --------------------------------------------------

    logger.log(
        LogLevel::INFO,
        "System shutting down"
    );

    server.stop();

    logger.log(
        LogLevel::INFO,
        "System stopped"
    );

    return 0;
}