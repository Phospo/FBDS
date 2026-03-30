#ifndef COPERACYJNY_H
#define COPERACYJNY_H

#include "cfunctionblock.h"

/** COperacyjny

    Reprezentacja bloku operacyjnego w schemacie FBD.
    Klasa placeholder do późniejszej specjalizacji nadawczego/odbiorczego.
*/
class COperacyjny : public CFunctionBlock {
    /** Flaga oznaczająca, czy blok działa jako nadawnik */
    bool FIsNadawnik{false};

    /** Flaga oznaczająca, czy blok działa jako odbiornik */
    bool FIsOdbiornik{false};

public:
    /**
        Konstruktor podstawowy

        @param _name        Nazwa bloku
        @param _in_count    Liczba wejść bloku
        @param _const       Stała wartość wykorzystywana w obliczeniach
        @param _init_out    Wartość początkowa wyjścia
        @param _is_nadawnik Flaga nadawczy
        @param _is_odbiornik Flaga odbiorczy
    */
    COperacyjny(std::string _name,
                unsigned _in_count,
                double _const,
                double _init_out,
                bool _is_nadawnik = false,
                bool _is_odbiornik = false);

    /**
        Destruktor podstawowy
    */
    ~COperacyjny() override;

    /**
        Przeliczenie stanu bloku operacyjnego.

        @param _ts Aktualny znacznik czasu symulacji
    */
    virtual void przelicz(STimeStamp _ts);

    /**
        Sprawdzenie, czy blok jest nadawczy.

        @return true, gdy blok jest nadawczy
    */
    bool isNadawnik() const;

    /**
        Ustawienie flagi nadawczego bloku.

        @param _is_nadawnik Nowa wartość flagi
    */
    void setIsNadawnik(bool _is_nadawnik);

    /**
        Sprawdzenie, czy blok jest odbiorczy.

        @return true, gdy blok jest odbiorczy
    */
    bool isOdbiornik() const;

    /**
        Ustawienie flagi odbiorczego bloku.

        @param _is_odbiornik Nowa wartość flagi
    */
    void setIsOdbiornik(bool _is_odbiornik);
};

#endif // COPERACYJNY_H
