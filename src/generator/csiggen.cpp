#include "csiggen.h"

CSigGen::CSigGen(std::string _name, unsigned _in_count, double _const, double _init_out)
    : CFunctionBlock(std::move(_name), _in_count, _const, _init_out), Nadajnik(true) {}

CSigGen::~CSigGen() = default;

bool CSigGen::isNadajnik() const {
    return Nadajnik;
}

void CSigGen::setIsNadajnik(bool _nadajnik) {
    Nadajnik = _nadajnik;
}

//0208260326
//tbh usless nie rozumiem po co nam podklasy w takim zestawie skoro nadajnik będzie nadajnikiem z wyjściem tak czy inaczej
//tym bardziej że przez dziedziczenie w taki sposób mamy nadal możliwość .getInput mimo że to blok czysto źródłowy.
//potem sb szczerze cały projekt zrobię w sporej części od nowa z dokładniejszymi założeniami projektowymi...

//1721300326
//Można to całe od nowa zaprojektować? Najlepiej w innym języku?