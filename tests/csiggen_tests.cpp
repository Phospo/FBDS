#include <gtest/gtest.h>

#include "cconstval.h"
#include "cconnection.h"
#include "cfromcsv.h"
#include "cmathfunc.h"
#include "csiggen.h"
#include "stimestamp.h"

#include <fstream>
#include <filesystem>

namespace {

STimeStamp makeTimestamp(unsigned _seconds, unsigned _milliseconds) {
    STimeStamp ts;
    ts.Seconds = _seconds;
    ts.Milliseconds = _milliseconds;
    return ts;
}

} // namespace

TEST(CSigGenTest, NadajnikFlag) {
    CSigGen block("SG1", 0, 1.0, 0.0);

    EXPECT_TRUE(block.isNadajnik());
    block.setIsNadajnik(false);
    EXPECT_FALSE(block.isNadajnik());

    const STimeStamp ts = makeTimestamp(0, 0);
    block.calculate(ts);

    const SDataSample output = block.getOutput(1)->getData();
    EXPECT_TRUE(output.isOK());
    EXPECT_DOUBLE_EQ(output.Value, 1.0);
}

TEST(CConstValTest, BazowyKonstruktorIWyjscie) {
    CConstVal block("CV1", 42.0);

    EXPECT_DOUBLE_EQ(block.getValue(), 42.0);
    block.setValue(10.0);
    EXPECT_DOUBLE_EQ(block.getValue(), 10.0);

    // TODO: pełna logika
    block.initialize();
    block.setIsNadajnik(true);
    block.calculate(makeTimestamp(0, 0));
}

TEST(CFromCSVTest, BazowyKonstruktorIWyjscie) {
    const std::filesystem::path path = std::filesystem::temp_directory_path() / "fbds_test_csv.csv";
    {
        std::ofstream ofs(path);
        ofs << "10\n20\n30\n";
    }

    CFromCSV block("CSV1", path.string());
    block.setIsNadajnik(true);

    const STimeStamp ts = makeTimestamp(0, 0);
    block.initialize();
    block.calculate(ts);

    // TODO: pełna logika
    std::filesystem::remove(path);
}

TEST(CMathFuncTest, BazowyKonstruktorIWyjscie) {
    CMathFunc block("M1", CMathFunc::EOperator::Add, 5.0);

    block.setIsNadajnik(true);
    block.calculate(makeTimestamp(0, 1));

    // TODO: pełna logika
    auto out = block.getOutput(1)->getData();
    (void)out;
}
