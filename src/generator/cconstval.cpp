#include "cconstval.h"

CConstVal::CConstVal(std::string _name, double _value)
    : CSigGen(std::move(_name), 0, 0.0, _value), FValue(_value) {
}

CConstVal::~CConstVal() = default;

double CConstVal::getValue() const {
    return FValue;
}

void CConstVal::setValue(double _value) {
    FValue = _value;
}

void CConstVal::initialize() {
    SDataSample data(FValue);
    getOutput(1)->setData(data);
}

void CConstVal::calculate(STimeStamp _ts) {
    SDataSample data(_ts);
    data.Value = FValue;
    getOutput(1)->setData(data);
}
