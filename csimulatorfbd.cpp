#include "csimulatorfbd.h"

CSimulatorFBD::CSimulatorFBD() : FBuilder(&FScheme), FEngine(&FScheme) {}

void CSimulatorFBD::run() {
    FBuilder.configureFBD();
    FEngine.setSimStop(10);
    FEngine.simulateBatch();
}
