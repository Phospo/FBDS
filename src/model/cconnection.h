#ifndef CCONNECTION_H
#define CCONNECTION_H

class CInput;
#include "coutput.h"

/** CConnection

    Reprezentacja połączenia między wyjściem i wejściem bloków funkcyjnych
*/
class CConnection {
    COutput* FBegin{nullptr};
    CInput* FEnd{nullptr};

  public:
    /**
        Konstruktor podstawowy
    */
    CConnection();
    /**
        Podłączenie początku połączenia do wyjścia bloku.

        @param	_out	Wskaźnik do wyjścia źródłowego
    */
    void connectBegin(COutput* _out);
    /**
        Podłączenie końca połączenia do wejścia bloku.

        @param	_in	Wskaźnik do wejścia docelowego
    */
    void connectEnd(CInput* _in);
    /**
        Pobranie danych przekazywanych przez połączenie.

        @return	Próbka danych
    */
    SDataSample getData() const;
};

#endif // CCONNECTION_H
