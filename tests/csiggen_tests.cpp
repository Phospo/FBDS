#include <gtest/gtest.h>

#include "csiggen.h"
#include "stimestamp.h"

namespace {

STimeStamp makeTimestamp(unsigned _seconds, unsigned _milliseconds) {
    STimeStamp ts;
    ts.Seconds = _seconds;
    ts.Milliseconds = _milliseconds;
    return ts;
}

} // namespace

TEST(CSigGenTest, TransmitterFlag) {
    CSigGen block("SG1", 0, 1.0, 0.0);

    EXPECT_FALSE(block.getTransmitter());
    block.setTransmitter(true);
    EXPECT_TRUE(block.getTransmitter());

    const STimeStamp ts = makeTimestamp(0, 0);
    block.calculate(ts);

    const SDataSample output = block.getOutput(1)->getData();
    EXPECT_TRUE(output.isOK());
    EXPECT_DOUBLE_EQ(output.Value, 1.0);
    EXPECT_EQ(output.TimeStamp.Seconds, 0u);
    EXPECT_EQ(output.TimeStamp.Milliseconds, 0u);
}
