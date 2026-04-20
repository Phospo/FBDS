#include <QCoreApplication>

#include "csimulatorfbd.h"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    CSimulatorFBD simulator;
    simulator.run();
    return 0;
}
