#include "cfbdbuilder.h"

#include "cfunctionblock.h"
#include "cconnection.h"

CFBDBuilder::CFBDBuilder(CContainerFBD* _cont) : FScheme(_cont) {}

// TODO zaimplementować definiowanie konfiguracji z zewnętrznego pliku konfiguracyjnego. Pewnie json.

void CFBDBuilder::configureFBD() {
    CFunctionBlock* fb1 = new CFunctionBlock("FB1", 0, 0.5, 0);
    FScheme->addFunctionBlock( fb1 );
    CFunctionBlock* fb2 = new CFunctionBlock("FB2", 0, 0.5, 0);
    FScheme->addFunctionBlock( fb2 );
    CFunctionBlock* fb3 = new CFunctionBlock("FB3", 2, 0, 0);
    FScheme->addFunctionBlock( fb3 );
    CFunctionBlock* fb4 = new CFunctionBlock("FB4", 2, 0, 0);
    FScheme->addFunctionBlock( fb4 );

    CConnection *con;
    con = new CConnection();
    con->connectBegin( fb1->getOutput(1) );
    con->connectEnd( fb3->getInput(1) );
    FScheme->addConnection( con );

    con = new CConnection();
    con->connectBegin( fb2->getOutput(1) );
    con->connectEnd( fb3->getInput(2) );
    FScheme->addConnection( con );

    con = new CConnection();
    con->connectBegin( fb3->getOutput(1) );
    con->connectEnd( fb4->getInput(1) );
    FScheme->addConnection( con );

    con = new CConnection();
    con->connectBegin( fb4->getOutput(1) );
    con->connectEnd( fb4->getInput(2) );
    FScheme->addConnection( con );
}
