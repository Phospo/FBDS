#include "cconnection.h"

#include "cinput.h"

CConnection::CConnection() {}

void CConnection::connectBegin(COutput* _out) {
    if(_out)
        FBegin = _out;
}

void CConnection::connectEnd(CInput* _in) {
    if(_in) {
        FEnd = _in;
        FEnd->addConnection(this);
    }
}

COutput* CConnection::getBegin() const {
    return FBegin;
}

CInput* CConnection::getEnd() const {
    return FEnd;
}

SDataSample CConnection::getData() const {
    if (FBegin)
        return FBegin->getData();

    return SDataSample();
}
