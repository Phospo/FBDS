#ifndef CADDSUB_H
#define CADDSUB_H

#include "coperacyjny.h"

/** CAddSub

    Reprezentacja bloku dodawania/odejmowania w schemacie FBD.
*/
class CAddSub : public COperacyjny {
public:
    /**
        Konstruktor podstawowy

        @param _name      Nazwa bloku
        @param _in_count  Liczba wejść bloku
        @param _const     Stała wartość wykorzystywana w obliczeniach
        @param _init_out  Wartość początkowa wyjścia
    */
    CAddSub(std::string _name, unsigned _in_count, double _const, double _init_out);

    /**
        Przeliczenie aktualnego stanu bloku.

        @param _ts Aktualny znacznik czasu symulacji
    */
    void przelicz(STimeStamp _ts) override;
};

#endif // CADDSUB_H
