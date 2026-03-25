#include "csiggen.h"

CSigGen::CSigGen(std::string _name, unsigned _in_count, double _const, double _init_out)
    : CFunctionBlock(std::move(_name), _in_count, _const, _init_out), Transmitter(false) {}

CSigGen::~CSigGen() = default;

bool CSigGen::getTransmitter() const {
    return Transmitter;
}

void CSigGen::setTransmitter(bool _transmitter) {
    Transmitter = _transmitter;
}

