#include "cgain.h"

CGain::CGain(std::string _name, unsigned _in_count, double _const, double _init_out)
    : COperacyjny(std::move(_name), _in_count, _const, _init_out) {
}

void CGain::przelicz(STimeStamp _ts) {
    // TODO
    (void)_ts;
}
