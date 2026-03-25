#ifndef CODBIORNIK_H
#define CODBIORNIK_H

#include "cfunctionblock.h"

/** COdbiornik

    Reprezentacja odbiornika sygnału w schemacie FBD. Klasa bazowa dla specjalizowanych odbiorników.
*/
class COdbiornik : public CFunctionBlock
{
    /** Flaga oznaczająca, czy blok jest odbiornikiem */
    bool FIsOdbiornik{true};

public:
    /**
        Konstruktor podstawowy

        @param _name      Nazwa bloku
        @param _in_count  Liczba wejść bloku
        @param _const     Stała wartość wykorzystywana w obliczeniach
        @param _init_out  Wartość początkowa wyjścia
    */
    COdbiornik(std::string _name, unsigned _in_count, double _const, double _init_out);

    /**
        Destruktor podstawowy
    */
    ~COdbiornik() override;

    /**
        Sprawdzenie, czy blok jest odbiornikiem.

        @return true, gdy blok jest odbiornikiem
    */
    bool isOdbiornik() const;

    /**
        Ustawienie flagi odbiornika.

        @param _is_odbiornik Nowa wartość flagi
    */
    void setIsOdbiornik(bool _is_odbiornik);
};

#endif // CODBIORNIK_H
