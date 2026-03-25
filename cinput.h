#ifndef CINPUT_H
#define CINPUT_H

#include "sdatasample.h"
class CConnection;

/** CInput

    Reprezentacja wejście bloku funkcyjnego
*/
class CInput {
    /**
        Numer wejścia. Zakładamy, że jest to wartość unikalna
    */
    unsigned FNumber{0};
    /**
        Informacja o podłączonym połączeniu
    */
    CConnection* FConnection{nullptr};

  public:
    /**
        Konstruktor podstawowy

        @param	_number	Numer tworzonego wejścia
    */
    CInput(unsigned _number);
    /**
        Dodanie połączenia do wejścia

        @param	_con Wskaźnik do połączenia
    */
    void addConnection(CConnection* _con);
    /**
        Pobranie aktualnych danych z podłączonego połącznia.

        @return	Próbka danych
    */
    SDataSample getData() const;
};

#endif // CINPUT_H
