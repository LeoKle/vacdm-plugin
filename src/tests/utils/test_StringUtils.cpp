#include <gtest/gtest.h>

#include "utils/String.h"

using namespace vacdm::utils;

namespace utils::tests {
TEST(StringUtilTest, Test_findIcao_base) {
    // Test case: only ICAO code
    EXPECT_EQ(String::findIcao("EDDK"), "EDDK");
    EXPECT_EQ(String::findIcao("EDDF"), "EDDF");

    // Test case: ICAO code not in uppercase
    EXPECT_EQ(String::findIcao("eddk"), "");

    // Test case: input is too short
    EXPECT_EQ(String::findIcao("JFK"), "");

    // Test case: no ICAO code in input
    EXPECT_EQ(String::findIcao("This is a test"), "");

    // Test case: empty string
    EXPECT_EQ(String::findIcao(""), "");

    // Test case: spaces before and after words
    EXPECT_EQ(String::findIcao("  EDDK  "), "EDDK");
    EXPECT_EQ(String::findIcao("  KLAX   "), "KLAX");
}

TEST(StringUtilTest, Test_findIcao_operators) {
    /* tests the findIcao function based on airport names defined inside individual vACDM operators EuroScope packages*/

    // most only use ICAOs
    EXPECT_EQ(String::findIcao("EDDK"), "EDDK");
    EXPECT_EQ(String::findIcao("LPPT"), "LPPT");

    // some additionally include names
    EXPECT_EQ(String::findIcao("EGLL London Heathrow"), "EGLL");
    EXPECT_EQ(String::findIcao("EGKK London Gatwick"), "EGKK");
}
}  // namespace utils::tests