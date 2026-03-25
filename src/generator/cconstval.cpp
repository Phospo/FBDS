#include "cconstval.h"

CConstVal::CConstVal(std::string _name, double _value)
    : CSigGen(std::move(_name), 0, 0.0, _value), FValue(_value) {
    // TODO: zaimplementować inicjalizację wartości stałej dla CConstVal
}

CConstVal::~CConstVal() = default;

double CConstVal::getValue() const {
    // TODO: zwrócić aktualną wartość stałą
    return FValue;
}

void CConstVal::setValue(double _value) {
    // TODO: ustawić nową wartość stałą i przekazać na wyjście
    FValue = _value;
}

void CConstVal::initialize() {
    // TODO: zainicjalizować wyjście wartością stałą
}

void CConstVal::calculate(STimeStamp /*_ts*/) {
    // TODO: wygenerować wyjście ze stałej wartości
}
