#include "codbiornik.h"

COdbiornik::COdbiornik(std::string _name, unsigned _in_count, double _const, double _init_out)
    : CFunctionBlock(_name, _in_count, _const, _init_out), FIsOdbiornik(true) {
}

COdbiornik::~COdbiornik() {
}

bool COdbiornik::isOdbiornik() const {
    return FIsOdbiornik;
}

void COdbiornik::setIsOdbiornik(bool _is_odbiornik) {
    FIsOdbiornik = _is_odbiornik;
}
