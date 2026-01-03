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


// ============== Special Rule Tests (via calculateMove) ==============
// These test the special rule logic indirectly

TEST(SpecialRuleTest, SpecialRuleUpStack) {
    Game game {1};
    Player player {game};

    // UP1 at 50, player has 40 -> can play special rule (50 - 10 = 40)
    game.setTopCards({50, 1, 100, 100});
    player.setHandCards({40}); // within special rule range

    auto move = player.calculateMove();

    EXPECT_EQ(move.first, 40);
    EXPECT_EQ(move.second, config::UP1); 
}

TEST(SpecialRuleTest, SpecialRulePrioritized) {
    Game game {1};
    Player player {game};
    
    // UP1 at 50, player has 40 (special) and 51 (very close)
    // Special rule should be prioritized
    game.setTopCards({50, 1, 100, 100});
    player.setHandCards({40, 51});
    
    auto move = player.calculateMove();
    EXPECT_EQ(move.first, 40); // Special rule was prioritized
}

TEST(SpecialRuleTest, SpecialRulePredicted) {
    Game game {1};
    Player player {game};
    
    // Player should play 46 first to play 56 next move
    game.setTopCards({1, 1, 60, 4});
    player.setHandCards({56, 46});

    auto move = player.calculateMove();
    EXPECT_EQ(move.first, 46);
    EXPECT_EQ(move.second, config::DOWN1);
}

TEST(SpecialRuleTest, PredictedSpecialSwap) {
    Game game {1};
    Player player {game};

    player.setHandCards({37, 27});
    game.setTopCards({99, 98, 40, 23});

    // 37 for DOWN1 has been calculated as its the closest (40 - 37)
    std::pair<unsigned int, unsigned int> move = {37, config::DOWN1};

    player.predictSpecial(move);

    // Predict Special should swap 37 for 27, to play 37 in the next move
    EXPECT_EQ(move.first, 27);
    EXPECT_EQ(move.second, config::DOWN1);
}

// ============== Simple Move Tests ==============

TEST(BestMoveTest, UPStack1) {
    Game game {1};
    Player player {game};

    // Player should play 27 on UP1 (diff 1)
    player.setHandCards({20, 23, 27});
    game.setTopCards({26, 38, 30, 34});

    auto move = player.calculateMove();

    EXPECT_EQ(move.first, 27);
    EXPECT_EQ(move.second, config::UP1);
}

TEST(BestMoveTest, UPStack2) {
    Game game {1};
    Player player {game};

    // Player should play 27 on UP2 (diff 1)
    player.setHandCards({20, 23, 27});
    game.setTopCards({38, 26, 30, 34});

    auto move = player.calculateMove();

    EXPECT_EQ(move.first, 27);
    EXPECT_EQ(move.second, config::UP2);
}

TEST(BestMoveTest, DOWNStack1) {
    Game game {1};
    Player player {game};

    // Player should play 29 on DOWN1 (diff 1)
    player.setHandCards({41, 32, 24, 29});
    game.setTopCards({37, 26, 30, 34});

    auto move = player.calculateMove();

    EXPECT_EQ(move.first, 29);
    EXPECT_EQ(move.second, config::DOWN1);
}

TEST(BestMoveTest, DOWNStack2) {
    Game game {1};
    Player player {game};

    // Player should play 29 on DOWN2 (diff 1)
    player.setHandCards({42, 32, 24, 29});
    game.setTopCards({37, 26, 34, 30});

    auto move = player.calculateMove();

    EXPECT_EQ(move.first, 29);
    EXPECT_EQ(move.second, config::DOWN2);
}

