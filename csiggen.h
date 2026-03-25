#ifndef CSIGGEN_H
#define CSIGGEN_H

#include "cfunctionblock.h"

/** CSigGen

    Reprezentacja generatora sygnału w schemacie FBD
*/
class CSigGen : public CFunctionBlock
{
    /** Bool nadawania sygnału */
    bool Transmitter{false};

public:
    /**
        Konstruktor podstawowy

        @param _name      Nazwa bloku
        @param _in_count  Liczba wejść bloku
        @param _const     Stała wartość wykorzystywana w obliczeniach
        @param _init_out  Wartość początkowa wyjścia
    */
    CSigGen(std::string _name, unsigned _in_count, double _const, double _init_out);

    /**
        Destruktor podstawowy
    */
    ~CSigGen() override;

    /**
        Sprawdzenie, czy bloczek jest w trybie nadawania.

        @return true, gdy nadawanie jest włączone
    */
    bool getTransmitter() const;

    /**
        Ustawienie trybu nadawania.

        @param _transmitter Nowa wartość trybu nadawania
    */
    void setTransmitter(bool _transmitter);

};

#endif // CSIGGEN_H
