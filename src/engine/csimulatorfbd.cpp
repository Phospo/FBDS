#include "csimulatorfbd.h"

CSimulatorFBD::CSimulatorFBD() : FBuilder(&FScheme), FEngine(&FScheme) {}

void CSimulatorFBD::run() {
    if (FScheme.getFunctionBlockCount() == 0) {
        FBuilder.configureFBD();
    }

    FEngine.setSimStop(FSimulationSteps);
    FEngine.simulateBatch();
}

bool CSimulatorFBD::loadConfigurationFromJSON(const std::string& _path) {
    unsigned loadedSteps = 0;
    if (FBuilder.loadFromJSON(_path, &loadedSteps)) {
        FSimulationSteps = loadedSteps;
        return true;
    }
    return false;
}

bool CSimulatorFBD::saveConfigurationToJSON(const std::string& _path) const {
    return FBuilder.saveToJSON(_path, FSimulationSteps);
}

unsigned CSimulatorFBD::getSimulationSteps() const {
    return FSimulationSteps;
}

void CSimulatorFBD::setSimulationSteps(unsigned _steps) {
    if (_steps > 0) {
        FSimulationSteps = _steps;
    }
}
