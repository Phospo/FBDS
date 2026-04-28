#include "simulatorbridge.h"

#include "csimulatorfbd.h"

#include <iostream>
#include <sstream>

CSimulatorBridge::CSimulatorBridge(QObject* _parent)
    : QObject(_parent), FSimulator(new CSimulatorFBD()) {}

CSimulatorBridge::~CSimulatorBridge() {
    delete FSimulator;
    FSimulator = nullptr;
}

bool CSimulatorBridge::runDefaultSimulation() {
    if (FSimulator == nullptr) {
        return false;
    }

    FSimulator->run();
    return true;
}

QString CSimulatorBridge::runDefaultSimulationWithOutput() {
    if (FSimulator == nullptr) {
        return {};
    }

    std::ostringstream capturedOutput;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(capturedOutput.rdbuf());
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(capturedOutput.rdbuf());

    FSimulator->run();

    std::cout.rdbuf(oldCoutBuffer);
    std::cerr.rdbuf(oldCerrBuffer);

    return QString::fromStdString(capturedOutput.str());
}

bool CSimulatorBridge::loadConfigurationFromJSON(const QString& _path) {
    if (FSimulator == nullptr) {
        return false;
    }

    return FSimulator->loadConfigurationFromJSON(_path.toStdString());
}

bool CSimulatorBridge::saveConfigurationToJSON(const QString& _path) {
    if (FSimulator == nullptr) {
        return false;
    }

    return FSimulator->saveConfigurationToJSON(_path.toStdString());
}
