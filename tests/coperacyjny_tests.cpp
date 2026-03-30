#include <gtest/gtest.h>

#include "cgain.h"
#include "caddsub.h"
#include "cintegral.h"

static STimeStamp makeTimestamp(unsigned _seconds, unsigned _milliseconds) {
    STimeStamp ts;
    ts.Seconds = _seconds;
    ts.Milliseconds = _milliseconds;
    return ts;
}

TEST(COperacyjnyDerivedTest, CGainConstructionAndPrzelicz) {
    CGain block("GAIN", 0, 0.0, 1.0);
    const STimeStamp ts = makeTimestamp(1, 100);

    block.initialize();
    EXPECT_EQ(block.getOutput(1)->getData().Value, 1.0);

    block.calculate(ts);
    EXPECT_TRUE(block.getOutput(1)->getData().isOK());

    EXPECT_NO_THROW(block.przelicz(ts));
}

TEST(COperacyjnyDerivedTest, CAddSubConstructionAndPrzelicz) {
    CAddSub block("ADDSUB", 0, 0.0, 2.0);
    const STimeStamp ts = makeTimestamp(2, 200);

    block.initialize();
    EXPECT_EQ(block.getOutput(1)->getData().Value, 2.0);

    block.calculate(ts);
    EXPECT_TRUE(block.getOutput(1)->getData().isOK());

    EXPECT_NO_THROW(block.przelicz(ts));
}

TEST(COperacyjnyDerivedTest, CIntegralConstructionAndPrzelicz) {
    CIntegral block("INTEGRAL", 0, 0.0, 3.0);
    const STimeStamp ts = makeTimestamp(3, 300);

    block.initialize();
    EXPECT_EQ(block.getOutput(1)->getData().Value, 3.0);

    block.calculate(ts);
    EXPECT_TRUE(block.getOutput(1)->getData().isOK());

    EXPECT_NO_THROW(block.przelicz(ts));
}