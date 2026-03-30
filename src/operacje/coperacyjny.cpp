#include "coperacyjny.h"

COperacyjny::COperacyjny(std::string _name,
                         unsigned _in_count,
                         double _const,
                         double _init_out,
                         bool _is_nadawnik,
                         bool _is_odbiornik)
                        : CFunctionBlock(std::move(_name), _in_count, _const, _init_out),
                        FIsNadawnik(_is_nadawnik),
                        FIsOdbiornik(_is_odbiornik) {}

COperacyjny::~COperacyjny() {
}

bool COperacyjny::isNadawnik() const {
    return FIsNadawnik;
}

void COperacyjny::setIsNadawnik(bool _is_nadawnik) {
    FIsNadawnik = _is_nadawnik;
}

bool COperacyjny::isOdbiornik() const {
    return FIsOdbiornik;
}

void COperacyjny::setIsOdbiornik(bool _is_odbiornik) {
    FIsOdbiornik = _is_odbiornik;
}

void COperacyjny::przelicz(STimeStamp _ts) {
    // Placeholder: operacja przeliczana w klasie pochodnej
    (void)_ts;
}
