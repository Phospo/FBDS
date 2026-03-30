#include <gtest/gtest.h>

#include "cwritetofile.h"
#include "stimestamp.h"

#include <filesystem>
#include <fstream>

// Test sprawdza zapis wyjścia do pliku skonfigurowanej ścieżki.
TEST(CWriteToFileTest, WritesOutputToConfiguredFile) {
    const std::filesystem::path path = std::filesystem::temp_directory_path() / "fbds_write_to_file_test.csv";
    // Plik testowy jest tworzony w katalogu tymczasowym systemu, np. C:\Windows\Temp lub /tmp
    std::filesystem::remove(path);

    CWriteToFile block("WTF1", 0, 0.0, 42.5);
    block.setFilePath(path.string());

    block.initialize();
    block.writeToFile();

    ASSERT_TRUE(std::filesystem::exists(path));

    std::ifstream in(path);
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);
    EXPECT_FALSE(line.empty());
    EXPECT_NE(line.find(",42.5,0"), std::string::npos);

    in.close();
    std::filesystem::remove(path);
}

// Test sprawdza zapis wyjścia do podanej explicite ścieżki pliku.
TEST(CWriteToFileTest, WritesOutputToExplicitPath) {
    const std::filesystem::path path = std::filesystem::temp_directory_path() / "fbds_write_to_file_test2.csv";
    // Plik testowy jest tworzony w katalogu tymczasowym systemu, np. C:\Windows\Temp lub /tmp
    std::filesystem::remove(path);

    CWriteToFile block("WTF2", 0, 0.0, 100.0);
    block.initialize();
    block.writeToFile(path.string());

    ASSERT_TRUE(std::filesystem::exists(path));

    std::ifstream in(path);
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);
    EXPECT_FALSE(line.empty());
    EXPECT_NE(line.find(",100,0"), std::string::npos);

    in.close();
    std::filesystem::remove(path);
}
