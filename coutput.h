#ifndef COUTPUT_H
#define COUTPUT_H

#include "sdatasample.h"

/** COutput

    Reprezentacja wyjścia bloku funkcyjnego
*/
class COutput {
    unsigned FNumber{0};
    SDataSample FValue;

  public:
    /**
        Konstruktor podstawowy

        @param	_number	Numer tworzonego wejścia
    */
    COutput(unsigned _number);
    /**
        Pobranie aktualnej wartości wyjścia.

        @return	Próbka danych
    */
    SDataSample getData() const;
    /**
        Ustawienie aktualnej wartości wyjścia.

        @param	_val	Nowa próbka danych
    */
    void setData(const SDataSample& _val);
};

#endif // COUTPUT_H
