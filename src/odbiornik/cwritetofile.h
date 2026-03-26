#ifndef CWRITETOFILE_H
#define CWRITETOFILE_H

#include "codbiornik.h"
#include <string>

/** CWriteToFile

    Odbiornik sygnału zapisu do pliku.
*/
class CWriteToFile : public COdbiornik {
    /** Ścieżka pliku docelowego */
    std::string FFilePath{""};

public:
    /**
        Konstruktor podstawowy

        @param _name      Nazwa bloku
        @param _in_count  Liczba wejść bloku
        @param _const     Stała wartość wykorzystywana w obliczeniach
        @param _init_out  Wartość początkowa wyjścia
    */
    CWriteToFile(std::string _name, unsigned _in_count, double _const, double _init_out);

    /**
        Destruktor podstawowy
    */
    ~CWriteToFile() override;

    /**
        Inicjalizacja stanu bloku.
    */
    void initialize() override;

    /**
        Ustawienie docelowej ścieżki pliku.

        @param _filePath Ścieżka pliku
    */
    void setFilePath(const std::string& _filePath);

    /**
        Zapis danych do ustawionego pliku.
        Jeżeli ścieżka jest pusta, operacja jest pomijana.
    */
    void writeToFile();

    /**
        Zapis danych do wskazanego pliku.

        @param _filePath Ścieżka pliku
    */
    void writeToFile(const std::string& _filePath);
};

#endif // CWRITETOFILE_H
