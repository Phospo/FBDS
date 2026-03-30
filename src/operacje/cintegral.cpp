#include "cintegral.h"

CIntegral::CIntegral(std::string _name, unsigned _in_count, double _const, double _init_out)
    : COperacyjny(std::move(_name), _in_count, _const, _init_out) {
}

void CIntegral::przelicz(STimeStamp _ts) {
    // Placeholder: logika całkowania niezaimplementowana
    (void)_ts;
}
