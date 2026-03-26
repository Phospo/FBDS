#include "cwritetofile.h"
#include <fstream>

CWriteToFile::CWriteToFile(std::string _name, unsigned _in_count, double _const, double _init_out)
    : COdbiornik(std::move(_name), _in_count, _const, _init_out), FFilePath("") {
}

CWriteToFile::~CWriteToFile() = default;

void CWriteToFile::initialize() {
    COdbiornik::initialize();
    // Nie resetujemy ścieżki pliku podczas inicjalizacji, aby zachować konfigurację odbiornika.
}

void CWriteToFile::setFilePath(const std::string& _filePath) {
    FFilePath = _filePath;
}

void CWriteToFile::writeToFile() {
    if (FFilePath.empty()) {
        return;
    }
    writeToFile(FFilePath);
}

void CWriteToFile::writeToFile(const std::string& _filePath) {
    if (_filePath.empty()) {
        return;
    }

    std::ofstream out(_filePath, std::ios::app);
    if (!out.is_open()) {
        return;
    }

    auto output = getOutput(1);
    if (output) {
        const SDataSample data = output->getData();
        out << data.TimeStamp.Seconds << "," << data.TimeStamp.Milliseconds
            << "," << data.Value << "," << static_cast<int>(data.Status) << "\n";
    } else {
        out << "0,0,0,1\n"; // brak wyjścia - brakujący zapis
    }
}
