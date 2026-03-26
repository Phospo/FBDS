#include "csingen.h"

CSinGen::CSinGen(std::string _name, double _frequency, double _amplitude,
                 double _phase, double _offset)
    : CSigGen(std::move(_name), 0, 0.0, 0.0),
      FFrequency(_frequency), FAmplitude(_amplitude), FPhase(_phase), FOffset(_offset) {
    // Wartość inicjalna dokładnie ustawiana w initialize(),
    // ponieważ calculateSinValue() może użyć niezainicjalizowanych członków przed wykonaniem ciała konstruktora.
}

CSinGen::~CSinGen() = default;

double CSinGen::getFrequency() const {
    return FFrequency;
}

void CSinGen::setFrequency(double _frequency) {
    FFrequency = _frequency;
}

double CSinGen::getAmplitude() const {
    return FAmplitude;
}

void CSinGen::setAmplitude(double _amplitude) {
    FAmplitude = _amplitude;
}

double CSinGen::getPhase() const {
    return FPhase;
}

void CSinGen::setPhase(double _phase) {
    FPhase = _phase;
}

double CSinGen::getOffset() const {
    return FOffset;
}

void CSinGen::setOffset(double _offset) {
    FOffset = _offset;
}

int CSinGen::getRoundingPrecision() const {
    return FRoundingPrecision;
}

void CSinGen::setRoundingPrecision(int _precision) {
    FRoundingPrecision = _precision;
}

double CSinGen::calculateSinValue(double _timeSeconds) const {
    constexpr double PI2 = 2.0 * 3.141592653589793;
    return std::sin(PI2 * FFrequency * _timeSeconds + FPhase) * FAmplitude + FOffset;
}

double CSinGen::applyRounding(double _value) const {
    if (FRoundingPrecision < 0) {
        return _value;
    }
    double factor = std::pow(10.0, FRoundingPrecision);
    return std::round(_value * factor) / factor;
}

void CSinGen::initialize() {
    SDataSample data(applyRounding(calculateSinValue(0.0)));
    getOutput(1)->setData(data);
}

void CSinGen::calculate(STimeStamp _ts) {
    double timeSeconds = _ts.Seconds + _ts.Milliseconds / 1000.0;
    SDataSample data(_ts);
    data.Value = applyRounding(calculateSinValue(timeSeconds));
    getOutput(1)->setData(data);
}
