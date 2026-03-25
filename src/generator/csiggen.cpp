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

