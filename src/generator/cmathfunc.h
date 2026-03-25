#ifndef CMATHFUNC_H
#define CMATHFUNC_H

#include <cmath>
#include <string>

#include "csiggen.h"

/** CMathFunc

    Generator obliczający funkcję matematyczną na bazie wejścia
*/
class CMathFunc : public CSigGen {
public:
    enum class EOperator {
        Add,
        Subtract,
        Multiply,
        Divide,
        Sin,
        Cos
    };

private:
    /** Operator matematyczny */
    EOperator FOperator{EOperator::Add};
    /** Stała operandowa */
    double FOperand{0};

public:
    /**
        Konstruktor podstawowy

        @param _name     Nazwa bloku
        @param _operator Operator matematyczny
        @param _operand  Wartość operandowa (tam gdzie dotyczy)
    */
    CMathFunc(std::string _name, EOperator _operator, double _operand);

    /**
        Destruktor podstawowy
    */
    ~CMathFunc() override;

    /**
        Obliczenie nowej wartości wyjściowej.

        @param _ts Aktualny znacznik czasu symulacji
    */
    void calculate(STimeStamp _ts) override;
};

#endif // CMATHFUNC_H
