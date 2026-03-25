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
};

#endif // CFBDBUILDER_H
