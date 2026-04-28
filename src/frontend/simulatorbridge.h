#pragma once

#include <QObject>
#include <QString>

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

    /**
        Uruchomienie domyślnej symulacji backendu z przechwyceniem wyjścia tekstowego.

        @return Zebrane wyjście z symulacji
    */
    QString runDefaultSimulationWithOutput();
    /**
        Wczytanie konfiguracji z pliku JSON.

        @param _path Ścieżka do pliku JSON
        @return true, jeśli konfiguracja została poprawnie wczytana
    */
    bool loadConfigurationFromJSON(const QString& _path);
    /**
        Zapisanie konfiguracji do pliku JSON.

        @param _path Ścieżka do pliku JSON
        @return true, jeśli konfiguracja została poprawnie zapisana
    */
    bool saveConfigurationToJSON(const QString& _path);
};
