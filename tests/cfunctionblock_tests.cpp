#include <gtest/gtest.h>

#include "cconnection.h"
#include "cfunctionblock.h"
#include "csiggen.h"

namespace {

class CExternalInputMock {
public:
    explicit CExternalInputMock(CInput* _target) : FOutput(1) {
        FConnection.connectBegin(&FOutput);
        FConnection.connectEnd(_target);
    }

    void publish(const SDataSample& _sample) {
        FOutput.setData(_sample);
    }

private:
    COutput FOutput;
    CConnection FConnection;
};

STimeStamp makeTimestamp(unsigned _seconds, unsigned _milliseconds) {
    STimeStamp ts;
    ts.Seconds = _seconds;
    ts.Milliseconds = _milliseconds;
    return ts;
}

} // namespace

TEST(CFunctionBlockTest, ExposesConfiguredNameAndPorts) {
    CFunctionBlock block("SUM", 2, 0.5, 1.0);

    EXPECT_EQ(block.getName(), "SUM");
    EXPECT_NE(block.getInput(1), nullptr);
    EXPECT_NE(block.getInput(2), nullptr);
    EXPECT_EQ(block.getInput(0), nullptr);
    EXPECT_EQ(block.getInput(3), nullptr);
    EXPECT_NE(block.getOutput(1), nullptr);
    EXPECT_EQ(block.getOutput(0), nullptr);
    EXPECT_EQ(block.getOutput(2), nullptr);
}

TEST(CFunctionBlockTest, InitializeSetsConfiguredInitialOutputValue) {
    CFunctionBlock block("SUM", 0, 1.5, 7.25);

    block.initialize();

    const SDataSample output = block.getOutput(1)->getData();
    EXPECT_TRUE(output.isOK());
    EXPECT_DOUBLE_EQ(output.Value, 7.25);
}

TEST(CFunctionBlockTest, CalculateWithoutInputsReturnsBiasAndTimestamp) {
    CFunctionBlock block("SUM", 0, 1.5, 0.0);
    const STimeStamp ts = makeTimestamp(2, 250);

    block.calculate(ts);

    const SDataSample output = block.getOutput(1)->getData();
    EXPECT_TRUE(output.isOK());
    EXPECT_DOUBLE_EQ(output.Value, 1.5);
    EXPECT_EQ(output.TimeStamp.Seconds, 2u);
    EXPECT_EQ(output.TimeStamp.Milliseconds, 250u);
}

TEST(CFunctionBlockTest, CalculateSumsAllConnectedInputsAndBias) {
    CFunctionBlock block("SUM", 2, 0.5, 0.0);
    CExternalInputMock firstSource(block.getInput(1));
    CExternalInputMock secondSource(block.getInput(2));
    const STimeStamp ts = makeTimestamp(1, 500);

    firstSource.publish(SDataSample(1.25));
    secondSource.publish(SDataSample(2.75));

    block.calculate(ts);

    const SDataSample output = block.getOutput(1)->getData();
    EXPECT_TRUE(output.isOK());
    EXPECT_DOUBLE_EQ(output.Value, 4.5);
    EXPECT_EQ(output.TimeStamp.Seconds, 1u);
    EXPECT_EQ(output.TimeStamp.Milliseconds, 500u);
}

TEST(CFunctionBlockTest, CalculateMarksOutputBadWhenInputIsUnconnected) {
    CFunctionBlock block("SUM", 1, 2.0, 0.0);

    block.calculate(makeTimestamp(0, 100));

    const SDataSample output = block.getOutput(1)->getData();
    EXPECT_FALSE(output.isOK());
    EXPECT_DOUBLE_EQ(output.Value, 2.0);
}

TEST(CFunctionBlockTest, CalculateMarksOutputBadWhenAnyInputIsBad) {
    CFunctionBlock block("SUM", 2, 1.0, 0.0);
    CExternalInputMock firstSource(block.getInput(1));
    CExternalInputMock secondSource(block.getInput(2));

    firstSource.publish(SDataSample(3.0));
    secondSource.publish(SDataSample());

    block.calculate(makeTimestamp(3, 0));

    const SDataSample output = block.getOutput(1)->getData();
    EXPECT_FALSE(output.isOK());
    EXPECT_DOUBLE_EQ(output.Value, 4.0);
}

