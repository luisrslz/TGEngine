#include <gtest/gtest.h>
#include "player.hpp"
#include "config.hpp"

// Test the inPrivRange function (now declared in player.hpp)
// ============== inPrivRange UP Stack Tests ==============

TEST(InPrivRangeTest, UpStackCardWithinRange) {
    // top = 50, card = 52, range = 3 -> within range
    EXPECT_TRUE(inPrivRange(50, 52, true));
}

TEST(InPrivRangeTest, UpStackCardAtExactRange) {
    // top = 50, card = 53, range = 3 -> exactly at edge
    EXPECT_TRUE(inPrivRange(50, 53, true));
}

TEST(InPrivRangeTest, UpStackCardOutOfRange) {
    // top = 50, card = 55, range = 3 -> out of range
    EXPECT_FALSE(inPrivRange(50, 55, true));
}

TEST(InPrivRangeTest, UpStackCardEqual) {
    // top = 50, card = 50 -> not valid (can't play same card)
    EXPECT_FALSE(inPrivRange(50, 50, true));
}

TEST(InPrivRangeTest, UpStackCardBelow) {
    // top = 50, card = 48 -> below top, invalid for UP stack
    EXPECT_FALSE(inPrivRange(50, 48, true));
}

TEST(InPrivRangeTest, UpStackCardJustAbove) {
    // top = 50, card = 51 -> just above, within range
    EXPECT_TRUE(inPrivRange(50, 51, true));
}

// ============== inPrivRange DOWN Stack Tests ==============

TEST(InPrivRangeTest, DownStackCardWithinRange) {
    // top = 50, card = 48, range = 3 -> within range
    EXPECT_TRUE(inPrivRange(50, 48, false));
}

TEST(InPrivRangeTest, DownStackCardAtExactRange) {
    // top = 50, card = 47, range = 3 -> exactly at edge
    EXPECT_TRUE(inPrivRange(50, 47, false));
}

TEST(InPrivRangeTest, DownStackCardOutOfRange) {
    // top = 50, card = 45, range = 3 -> out of range
    EXPECT_FALSE(inPrivRange(50, 45, false));
}

TEST(InPrivRangeTest, DownStackCardEqual) {
    // top = 50, card = 50 -> not valid
    EXPECT_FALSE(inPrivRange(50, 50, false));
}

TEST(InPrivRangeTest, DownStackCardAbove) {
    // top = 50, card = 52 -> above top, invalid for DOWN stack
    EXPECT_FALSE(inPrivRange(50, 52, false));
}

TEST(InPrivRangeTest, DownStackCardJustBelow) {
    // top = 50, card = 49 -> just below, within range
    EXPECT_TRUE(inPrivRange(50, 49, false));
}

// ============== Edge Cases ==============

TEST(InPrivRangeTest, UpStackTopAtMinimum) {
    // top = 1 (UP_START), card = 2
    EXPECT_TRUE(inPrivRange(1, 2, true));
}

TEST(InPrivRangeTest, DownStackTopAtMaximum) {
    // top = 100 (DOWN_START), card = 99
    EXPECT_TRUE(inPrivRange(100, 99, false));
}

TEST(InPrivRangeTest, UpStackTopNearMaximum) {
    // top = 97, card = 99 -> within range
    EXPECT_TRUE(inPrivRange(97, 99, true));
}

TEST(InPrivRangeTest, DownStackTopNearMinimum) {
    // top = 4, card = 2 -> within range
    EXPECT_TRUE(inPrivRange(4, 2, false));
}