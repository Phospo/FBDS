#include "cfromcsv.h"

CFromCSV::CFromCSV(std::string _name, std::string _path)
    : CSigGen(std::move(_name), 0, 0.0, 0.0), FPath(std::move(_path)) {
    // TODO: wczytać CSV w przyszłej implementacji
}

CFromCSV::~CFromCSV() = default;

void CFromCSV::loadCSV() {
    // TODO: sparsować plik CSV do FValues i zresetować indeks
    FValues.clear();
    FIndex = 0;
}

void CFromCSV::initialize() {
    // TODO: przygotować wyjście początkowe na podstawie wartości z CSV
    FIndex = 0;
}

void CFromCSV::calculate(STimeStamp /*_ts*/) {
    // TODO: iterować po wartościach i ustawiać wyjście według indeksu
}
