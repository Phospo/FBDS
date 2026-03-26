#ifndef CSINGEN_H
#define CSINGEN_H

#include "csiggen.h"
#include <cmath>

/** CSinGen

    Generator sinusoidalnego sygnału wyjściowego
*/
class CSinGen : public CSigGen {
    /** Częstotliwość sygnału w Hz */
    double FFrequency{1.0};
    
    /** Amplituda sygnału */
    double FAmplitude{1.0};
    
    /** Faza początkowa w radianach */
    double FPhase{0.0};
    
    /** Przesunięcie DC */
    double FOffset{0.0};
    
    /** Liczba miejsc dziesiętnych do zaokrąglenia (-1 = brak zaokrąglenia) */
    int FRoundingPrecision{-1};

public:
    /**
        Konstruktor podstawowy

        @param _name      Nazwa bloku
        @param _frequency Częstotliwość w Hz (domyślnie 1.0)
        @param _amplitude Amplituda sygnału (domyślnie 1.0)
        @param _phase     Faza początkowa w radianach (domyślnie 0.0)
        @param _offset    Przesunięcie DC (domyślnie 0.0)
    */
    CSinGen(std::string _name, double _frequency = 1.0, double _amplitude = 1.0,
            double _phase = 0.0, double _offset = 0.0);

    /**
        Destruktor podstawowy
    */
    ~CSinGen() override;

    /**
        Pobranie częstotliwości generatora.

        @return Aktualna częstotliwość w Hz
    */
    double getFrequency() const;

    /**
        Ustawienie częstotliwości generatora.

        @param _frequency Nowa częstotliwość w Hz
    */
    void setFrequency(double _frequency);

    /**
        Pobranie amplitudy generatora.

        @return Aktualna amplituda
    */
    double getAmplitude() const;

    /**
        Ustawienie amplitudy generatora.

        @param _amplitude Nowa amplituda
    */
    void setAmplitude(double _amplitude);

    /**
        Pobranie fazy początkowej generatora.

        @return Aktualna faza w radianach
    */
    double getPhase() const;

    /**
        Ustawienie fazy początkowej generatora.

        @param _phase Nowa faza w radianach
    */
    void setPhase(double _phase);

    /**
        Pobranie przesunięcia DC.

        @return Aktualne przesunięcie DC
    */
    double getOffset() const;

    /**
        Ustawienie przesunięcia DC.

        @param _offset Nowe przesunięcie DC
    */
    void setOffset(double _offset);

    /**
        Pobranie precyzji zaokrąglenia.

        @return Liczba miejsc dziesiętnych (-1 = brak zaokrąglenia)
    */
    int getRoundingPrecision() const;

    /**
        Ustawienie precyzji zaokrąglenia.

        @param _precision Liczba miejsc dziesiętnych (-1 = brak zaokrąglenia)
    */
    void setRoundingPrecision(int _precision);

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
        Obliczenie wartości sinusoidalnej dla danego czasu.

        @param _timeSeconds Czas w sekundach
        @return Wartość sin(2π·f·t + φ)·A + O
    */
    double calculateSinValue(double _timeSeconds) const;

    /**
        Zaokrąglenie wartości do określonej liczby miejsc dziesiętnych.

        @param _value Wartość do zaokrąglenia
        @return Zaokrąglona wartość
    */
    double applyRounding(double _value) const;
};

#endif // CSINGEN_H
