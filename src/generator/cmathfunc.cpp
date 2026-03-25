#include "cmathfunc.h"

CMathFunc::CMathFunc(std::string _name, EOperator _operator, double _operand)
    : CSigGen(std::move(_name), 1, 0.0, 0.0), FOperator(_operator), FOperand(_operand) {
    // TODO: ustawić stan początkowy bloku funkcji matematycznej
}

CMathFunc::~CMathFunc() = default;

void CMathFunc::calculate(STimeStamp /*_ts*/) {
    // TODO: zaimplementować operację matematyczną na danych wejściowych
}
