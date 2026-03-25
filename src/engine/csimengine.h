#ifndef CSIMENGINE_H
#define CSIMENGINE_H

#include "ccontainerfbd.h"

enum class SimStatus { stopped = 0, running = 1};

/** CSimEngine

    Silnik realizujący obliczenia i przebieg symulacji schematu FBD
*/
class CSimEngine {

    CContainerFBD* FFBDScheme{nullptr};

    unsigned FSimStep{0};
    STimeStamp FSimTS;
    unsigned FSimStop{0};
    SimStatus FSimStatus{SimStatus::stopped};

public:
    /**
        Konstruktor podstawowy

        @param	_fbd	Wskaźnik do kontenera z konfiguracją schematu
    */
    CSimEngine(CContainerFBD* _fbd);
    /**
        Ustawienie kroku kończącego symulację.

        @param	_stop_step	Numer kroku końcowego symulacji
    */
    void setSimStop(unsigned _stop_step);
    /**
        Inicjalizacja stanu początkowego symulacji.
    */
    void initialize();
    /**
        Wykonanie pojedynczego kroku symulacji.
    */
    void doSimStep();
    /**
        Uruchomienie symulacji wsadowej.
    */
    void simulateBatch();
};

#endif // CSIMENGINE_H
