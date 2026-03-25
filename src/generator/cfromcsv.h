#ifndef CFROMCSV_H
#define CFROMCSV_H

#include <fstream>
#include <string>
#include <vector>

#include "csiggen.h"

/** CFromCSV

    Generator danych wczytywanych z pliku CSV (po jednej wartości na wiersz)
*/
class CFromCSV : public CSigGen {
    /** Ścieżka pliku CSV z danymi */
    std::string FPath;
    /** Wczytane wartości */
    std::vector<double> FValues;
    /** Indeks następnej próbki */
    std::size_t FIndex{0};

public:
    /**
        Konstruktor podstawowy

        @param _name  Nazwa bloku
        @param _path  Ścieżka do pliku CSV
    */
    CFromCSV(std::string _name, std::string _path);

    /**
        Destruktor podstawowy
    */
    ~CFromCSV() override;

    /**
        Inicjalizacja stanu bloku.
    */
    void initialize() override;

    /**
        Obliczenie nowej wartości wyjściowej.

        @param _ts Aktualny znacznik czasu symulacji
    */
    void calculate(STimeStamp _ts) override;

private:
    /**
        Wczytanie danych z pliku CSV
    */
    void loadCSV();
};

#endif // CFROMCSV_H
