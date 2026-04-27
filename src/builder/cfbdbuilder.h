#ifndef CFBDBUILDER_H
#define CFBDBUILDER_H

#include "ccontainerfbd.h"

/** CFBDBuilder

    Klasa odpowiedzialna za budowanie przykładowego schematu FBD
*/
class CFBDBuilder {
    /**
        Kontener konfiguracji FBD
    */
    CContainerFBD *FScheme{nullptr};

public:
    /**
        Konstruktor podstawowy

        @param	_cont	Wskaźnik do kontenera konfiguracji FBD
    */
    CFBDBuilder(CContainerFBD* _cont);
    /**
        Utworzenie domyślnego (testowego) schematu
    */
    void configureFBD();
    /**
        Wczytanie konfiguracji schematu z pliku JSON.

        @param _path Ścieżka do pliku JSON
        @param _simulationSteps Wskaźnik do zmiennej, w której zostanie przechowana liczba kroków (opcjonalnie)
        @return True, jeśli konfiguracja została poprawnie wczytana
    */
    bool loadFromJSON(const std::string& _path, unsigned* _simulationSteps = nullptr);
    /**
        Zapisanie aktualnej konfiguracji schematu do pliku JSON.

        @param _path Ścieżka do docelowego pliku JSON
        @param _simulationSteps Liczba kroków do zapisania (opcjonalnie)
        @return True, jeśli konfiguracja została poprawnie zapisana
    */
    bool saveToJSON(const std::string& _path, unsigned _simulationSteps = 100) const;
};

#endif // CFBDBUILDER_H
