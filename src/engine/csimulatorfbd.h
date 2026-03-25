#ifndef CSIMULATORFBD_H
#define CSIMULATORFBD_H

#include "csimengine.h"
#include "cfbdbuilder.h"

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


 public:
    /**
        Domyślny konstruktor
    */
    CSimulatorFBD();
    /**
        Realizacja domyślnej symulacji
    */
    void run();
};

#endif // CSIMULATORFBD_H
