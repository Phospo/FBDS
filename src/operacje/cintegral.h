#ifndef CINTEGRAL_H
#define CINTEGRAL_H

#include "coperacyjny.h"

/** CIntegral

    Reprezentacja bloku całkowania w schemacie FBD.
*/
class CIntegral : public COperacyjny {
public:
    /**
        Konstruktor podstawowy

        @param _name      Nazwa bloku
        @param _in_count  Liczba wejść bloku
        @param _const     Stała wartość wykorzystywana w obliczeniach
        @param _init_out  Wartość początkowa wyjścia
    */
    CIntegral(std::string _name, unsigned _in_count, double _const, double _init_out);

    /**
        Przeliczenie aktualnego stanu bloku.

        @param _ts Aktualny znacznik czasu symulacji
    */
    void przelicz(STimeStamp _ts) override;
};

#endif // CINTEGRAL_H
