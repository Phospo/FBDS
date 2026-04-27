#pragma once

#include <QObject>

class CSimulatorFBD;

/** CSimulatorBridge

    Warstwa pośrednicząca między frontendem Qt i silnikiem symulatora FBD.
*/
class CSimulatorBridge : public QObject {
    Q_OBJECT

private:
    /** Instancja backendowego symulatora FBD. */
    CSimulatorFBD* FSimulator{nullptr};

public:
    /**
        Konstruktor podstawowy.

        @param _parent Rodzic obiektu Qt
    */
    explicit CSimulatorBridge(QObject* _parent = nullptr);

    /**
        Destruktor domyślny.
    */
    ~CSimulatorBridge() override;

    /**
        Uruchomienie domyślnej symulacji backendu.

        @return true jeśli uruchomienie zakończyło się sukcesem
    */
    bool runDefaultSimulation();
};
