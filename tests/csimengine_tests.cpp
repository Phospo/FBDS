#include <gtest/gtest.h>

#include "ccontainerfbd.h"
#include "csimengine.h"
#include "cfunctionblock.h"
#include "cconstval.h"
#include "cconnection.h"

namespace {

STimeStamp makeTimestamp(unsigned _seconds, unsigned _milliseconds) {
    STimeStamp ts;
    ts.Seconds = _seconds;
    ts.Milliseconds = _milliseconds;
    return ts;
}

} // namespace

TEST(CSimEngineTest, GeneratorToSumWorkflow) {
    CContainerFBD container;

    CConstVal* constGen = new CConstVal("CV1", 5.0);
    CFunctionBlock* sumBlock = new CFunctionBlock("SUM1", 1, 0.0, 0.0);

    EXPECT_TRUE(container.addFunctionBlock(constGen));
    EXPECT_TRUE(container.addFunctionBlock(sumBlock));

    CConnection* con = new CConnection();
    con->connectBegin(constGen->getOutput(1));
    con->connectEnd(sumBlock->getInput(1));
    EXPECT_TRUE(container.addConnection(con));

    CSimEngine engine(&container);

    engine.initialize();
    // initial values
    auto outInit = sumBlock->getOutput(1)->getData();
    EXPECT_TRUE(outInit.isOK());
    EXPECT_DOUBLE_EQ(outInit.Value, 0.0);

    engine.doSimStep();
    auto out = sumBlock->getOutput(1)->getData();

    EXPECT_TRUE(out.isOK());
    EXPECT_DOUBLE_EQ(out.Value, 5.0);
    EXPECT_EQ(out.TimeStamp.Seconds, 1u);
    EXPECT_EQ(out.TimeStamp.Milliseconds, 0u);
}

TEST(CSimEngineTest, MissingInputMarksBadOutput) {
    CContainerFBD container;

    CFunctionBlock* sumBlock = new CFunctionBlock("SUM2", 1, 0.0, 0.0);
    EXPECT_TRUE(container.addFunctionBlock(sumBlock));

    CSimEngine engine(&container);
    engine.initialize();
    engine.doSimStep();

    auto out = sumBlock->getOutput(1)->getData();
    EXPECT_FALSE(out.isOK());
    EXPECT_DOUBLE_EQ(out.Value, 0.0);
    EXPECT_EQ(out.TimeStamp.Seconds, 1u);
    EXPECT_EQ(out.TimeStamp.Milliseconds, 0u);
}
