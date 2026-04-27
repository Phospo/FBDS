#include "coutput.h"

COutput::COutput(unsigned _number) {
    if (_number > 0)
        FNumber = _number;
}

unsigned COutput::getNumber() const {
    return FNumber;
}

SDataSample COutput::getData() const {
    return FValue;
}

void COutput::setData(const SDataSample& _val) {
    FValue = _val;
}
