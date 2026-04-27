#include "simulatorbridge.h"

#include "csimulatorfbd.h"

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
