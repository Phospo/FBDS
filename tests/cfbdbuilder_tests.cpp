#include <filesystem>
#include <fstream>

#include <gtest/gtest.h>

#include "src/builder/cfbdbuilder.h"
#include "src/engine/ccontainerfbd.h"

namespace {

std::filesystem::path makeTempPath(const std::string& _name) {
    return std::filesystem::temp_directory_path() / _name;
}

void writeTextFile(const std::filesystem::path& _path, const std::string& _content) {
    std::ofstream out(_path, std::ios::out | std::ios::trunc);
    out << _content;
}

} // namespace

TEST(CFBDBuilderTest, LoadsValidJsonConfiguration) {
    const std::filesystem::path jsonPath = makeTempPath("fbds_load_config_test.json");
    writeTextFile(jsonPath,
                  "{"
                  "\"samplingTime\":10,"
                  "\"simulationSteps\":50,"
                  "\"blocks\":["
                  "{\"name\":\"SinGen1\",\"type\":\"SinGen\",\"params\":{\"frequency\":1.0,\"amplitude\":1.0,\"phase\":0.0,\"offset\":0.0,\"roundingPrecision\":6}},"
                  "{\"name\":\"ConstGen1\",\"type\":\"ConstVal\",\"params\":{\"value\":1.0}},"
                  "{\"name\":\"Sum1\",\"type\":\"FunctionBlock\",\"params\":{\"inputCount\":2,\"constValue\":0.0,\"initialOutput\":0.0}}"
                  "],"
                  "\"connections\":["
                  "{\"from\":{\"block\":\"SinGen1\",\"output\":1},\"to\":{\"block\":\"Sum1\",\"input\":1}},"
                  "{\"from\":{\"block\":\"ConstGen1\",\"output\":1},\"to\":{\"block\":\"Sum1\",\"input\":2}}"
                  "]"
                  "}");

    CContainerFBD scheme;
    CFBDBuilder builder(&scheme);

    unsigned loadedSteps = 0;
    ASSERT_TRUE(builder.loadFromJSON(jsonPath.string(), &loadedSteps));
    EXPECT_EQ(scheme.getSamplingTime(), 10U);
    EXPECT_EQ(scheme.getFunctionBlockCount(), 3U);
    EXPECT_EQ(scheme.getConnectionCount(), 2U);
    EXPECT_EQ(loadedSteps, 50U);
    EXPECT_NE(scheme.getFunctionBlock("SinGen1"), nullptr);
    EXPECT_NE(scheme.getFunctionBlock("ConstGen1"), nullptr);
    EXPECT_NE(scheme.getFunctionBlock("Sum1"), nullptr);

    std::error_code ec;
    std::filesystem::remove(jsonPath, ec);
}

TEST(CFBDBuilderTest, SavesAndReloadsConfiguration) {
    const std::filesystem::path jsonPath = makeTempPath("fbds_save_config_test.json");

    CContainerFBD sourceScheme;
    CFBDBuilder sourceBuilder(&sourceScheme);
    sourceBuilder.configureFBD();

    ASSERT_TRUE(sourceBuilder.saveToJSON(jsonPath.string(), 75));

    CContainerFBD loadedScheme;
    CFBDBuilder loadedBuilder(&loadedScheme);
    unsigned loadedSteps = 0;
    ASSERT_TRUE(loadedBuilder.loadFromJSON(jsonPath.string(), &loadedSteps));

    EXPECT_EQ(loadedScheme.getFunctionBlockCount(), sourceScheme.getFunctionBlockCount());
    EXPECT_EQ(loadedScheme.getConnectionCount(), sourceScheme.getConnectionCount());
    EXPECT_EQ(loadedSteps, 75U);
    EXPECT_NE(loadedScheme.getFunctionBlock("SinGen1"), nullptr);
    EXPECT_NE(loadedScheme.getFunctionBlock("ConstGen1"), nullptr);

    std::error_code ec;
    std::filesystem::remove(jsonPath, ec);
}
