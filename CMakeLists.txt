cmake_minimum_required(VERSION 3.16)

project(SemiconductorControllerSimulator
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(

    semiconductor_controller
    src/main.cpp
    src/core/MachineController.cpp
    src/core/StateMachine.cpp
    src/equipment/WaferHandler.cpp
    src/equipment/ProcessChamber.cpp
    src/equipment/VacuumSystem.cpp
    src/sensors/PressureSensor.cpp
    src/sensors/TemperatureSensor.cpp
    src/sensors/SensorManager.cpp
    src/process/ProcessStep.cpp
    src/process/ProcessRecipe.cpp
    src/process/RecipeExecutor.cpp
    src/core/EventBus.cpp
    src/logging/Logger.cpp
    src/process/RecipeLoader.cpp
    src/equipment/MockProcessChamber.cpp

)
add_executable(
    machine_controller_test

    tests/MachineControllerTest.cpp

    src/core/StateMachine.cpp
    src/core/MachineController.cpp
    src/core/EventBus.cpp

    src/equipment/WaferHandler.cpp
    src/equipment/ProcessChamber.cpp
    src/equipment/VacuumSystem.cpp
    src/equipment/MockProcessChamber.cpp

    src/sensors/TemperatureSensor.cpp
    src/sensors/PressureSensor.cpp
    src/sensors/SensorManager.cpp
    src/communication/TcpServer.cpp
)
target_include_directories(
    semiconductor_controller
    PRIVATE
    src
)