#ifndef CFUNCTIONBLOCK_H
#define CFUNCTIONBLOCK_H

#include <deque>
#include <string>

#include "cinput.h"
#include "coutput.h"

/** CFunctionBlock

    Reprezentacja pojedynczego bloku funkcyjnego w schemacie FBD
*/
class CFunctionBlock {
    std::string FName{""};
    std::deque<CInput> FInputs;
    std::deque<COutput> FOutputs;
    double FConst{0};
    double FInitialOutput{0};

  public:
    /**
        Konstruktor podstawowy

        @param	_name		Nazwa tworzonego bloku
        @param	_in_count	Liczba wejść bloku
        @param	_const		Stała wartość dodawana podczas obliczeń
        @param	_init_out	Wartość początkowa wyjścia
    */
    CFunctionBlock(std::string _name, unsigned _in_count, double _const, double _init_out);
    /**
        Destruktor podstawowy
    */
    virtual ~CFunctionBlock();
    /**
        Pobranie nazwy bloku.

        @return	Nazwa bloku
    */
    std::string getName() const;
    /**
        Pobranie liczby wejść bloku.

        @return Liczba wejść
    */
    unsigned getInputCount() const;
    /**
        Pobranie liczby wyjść bloku.

        @return Liczba wyjść
    */
    unsigned getOutputCount() const;
    /**
        Pobranie wartości stałej bloku.

        @return Wartość stałej
    */
    double getConstValue() const;
    /**
        Pobranie wartości początkowej wyjścia.

        @return Wartość początkowa wyjścia
    */
    double getInitialOutputValue() const;
    /**
        Pobranie wskaźnika do wejścia o zadanym numerze.

        @param	_num	Numer wejścia
        @return	Wskaźnik do wejścia lub nullptr
    */
    CInput* getInput(unsigned _num);
    /**
        Pobranie wskaźnika do wyjścia o zadanym numerze.

        @param	_num	Numer wyjścia
        @return	Wskaźnik do wyjścia lub nullptr
    */
    COutput* getOutput(unsigned _num);
    /**
        Inicjalizacja stanu początkowego bloku.
    */
    virtual void initialize();
    /**
        Obliczenie nowej wartości wyjścia bloku.

        @param	_ts	Aktualny znacznik czasu symulacji
    */
    virtual void calculate(STimeStamp _ts);
};

#endif // CFUNCTIONBLOCK_H
