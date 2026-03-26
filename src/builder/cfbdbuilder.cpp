#include "cfbdbuilder.h"

#include "cfunctionblock.h"
#include "cconnection.h"
#include "csingen.h"
#include "cconstval.h"

CFBDBuilder::CFBDBuilder(CContainerFBD* _cont) : FScheme(_cont) {}

// TODO zaimplementować definiowanie konfiguracji z zewnętrznego pliku json

void CFBDBuilder::configureFBD() {
    // Ustawienie czasu próbkowania w ms
    FScheme->setSamplingTime(10);

    // sin(2π·f·t + φ)·A + O
    CSinGen* sinGen = new CSinGen("SinGen1", 1, 1.0, 0.0, 0.0);
    sinGen->setRoundingPrecision(6); // zaokrąglenie do 6 miejsc po przecinku
    FScheme->addFunctionBlock(sinGen);

    // Generator stałej wartości do porównania
    CConstVal* constGen = new CConstVal("ConstGen1", 0.0);
    FScheme->addFunctionBlock(constGen);

    CFunctionBlock* sumBlock = new CFunctionBlock("Sum1", 2, 0.0, 0.0);
    FScheme->addFunctionBlock(sumBlock);

    // Connect SinGen output to Sum input 1
    CConnection* con1 = new CConnection();
    con1->connectBegin(sinGen->getOutput(1));
    con1->connectEnd(sumBlock->getInput(1));
    FScheme->addConnection(con1);

    // Connect ConstGen output to Sum input 2
    CConnection* con2 = new CConnection();
    con2->connectBegin(constGen->getOutput(1));
    con2->connectEnd(sumBlock->getInput(2));
    FScheme->addConnection(con2);
}
