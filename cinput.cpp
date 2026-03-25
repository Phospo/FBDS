#include "cinput.h"

#include "cconnection.h"

CInput::CInput(unsigned _number) {
    if (_number > 0)
        FNumber = _number;
}

void CInput::addConnection(CConnection* _con) {
    if (_con)
        FConnection = _con;
}

SDataSample CInput::getData() const {
    if (FConnection)
        return FConnection->getData();

    return SDataSample();
}
