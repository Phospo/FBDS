#include "cfromcsv.h"

CFromCSV::CFromCSV(std::string _name, std::string _path)
    : CSigGen(std::move(_name), 0, 0.0, 0.0), FPath(std::move(_path)) {
    // TODO: wczytać CSV
}

CFromCSV::~CFromCSV() = default;

void CFromCSV::loadCSV() {
    // TODO
    FValues.clear();
    FIndex = 0;
}

void CFromCSV::initialize() {
    // TODO
    FIndex = 0;
}

void CFromCSV::calculate(STimeStamp /*_ts*/) {
    // TODO: oj implementacja csv to będzie ból
}

// Spora część osób z tego co widziałem ma problem z samym rozczytaniem tych plików, mi to zajeło ładną chwilę i będąc szczerym się w tym gubię nadal.
