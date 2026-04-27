#ifndef CSIMULATORFBD_H
#define CSIMULATORFBD_H

#include "csimengine.h"
#include "cfbdbuilder.h"
#include <string>

/** CSimulatorFBD

    Reprezentacja aplikacji symulatora FBD
*/
class CSimulatorFBD {
    /**
        Kontener konfiguracji FBD
    */
    CContainerFBD FScheme;
    /**
        Konstruktor schematów
    */
    CFBDBuilder FBuilder;
    /**
        Silnik obliczeniowy
    */
    CSimEngine FEngine;
    /**
        Liczba kroków symulacji
    */
    unsigned FSimulationSteps{100};

 public:
    /**
        Domyślny konstruktor
    */
    CSimulatorFBD();
    /**
        Realizacja domyślnej symulacji
    */
    void run();
    /**
        Wczytanie konfiguracji symulatora z pliku JSON.

        @param _path Ścieżka do pliku JSON
        @return True, jeśli konfiguracja została poprawnie wczytana
    */
    bool loadConfigurationFromJSON(const std::string& _path);
    /**
        Zapisanie aktualnej konfiguracji symulatora do pliku JSON.

        @param _path Ścieżka do pliku JSON
        @return True, jeśli konfiguracja została poprawnie zapisana
    */
    bool saveConfigurationToJSON(const std::string& _path) const;
    /**
        Pobranie liczby kroków symulacji.

        @return Liczba kroków
    */
    unsigned getSimulationSteps() const;
    /**
        Ustawienie liczby kroków symulacji.

        @param _steps Nowa liczba kroków
    */
    void setSimulationSteps(unsigned _steps);
};

#endif // CSIMULATORFBD_H
