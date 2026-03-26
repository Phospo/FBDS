#include "csimulatorfbd.h"

CSimulatorFBD::CSimulatorFBD() : FBuilder(&FScheme), FEngine(&FScheme) {}

//TODO zaimplementować możliwość konfiguracji symulatora z pliku json
void CSimulatorFBD::run() {
    FBuilder.configureFBD();
    FEngine.setSimStop(100);
    FEngine.simulateBatch();
}
