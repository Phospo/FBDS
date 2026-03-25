#ifndef CCONSTVAL_H
#define CCONSTVAL_H

#include "csiggen.h"

/** CConstVal

    Generator stałej wartości wyjściowej
*/
class CConstVal : public CSigGen {
    /** Stała wartość generowana na wyjście */
    double FValue{0};

public:
    /**
        Konstruktor podstawowy

        @param _name  Nazwa bloku
        @param _value Wartość stała do generacji
    */
    CConstVal(std::string _name, double _value);

    /**
        Destruktor podstawowy
    */
    ~CConstVal() override;

    /**
        Pobranie wartości generatora.

        @return Aktualna wartość
    */
    double getValue() const;

    /**
        Ustawienie wartości generatora.

        @param _value Nowa wartość stała
    */
    void setValue(double _value);

    /**
        Inicjalizacja stanu bloku.
    */
    void initialize() override;

    /**
        Obliczenie nowej wartości wyjściowej.

        @param _ts Aktualny znacznik czasu symulacji
    */
    void calculate(STimeStamp _ts) override;
};

#endif // CCONSTVAL_H
