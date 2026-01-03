#include <gtest/gtest.h>
#include "game.hpp"

// ============== Game Constructor Tests ==============

TEST(GameTest, ConstructorSetsMaxHandCardsFor1Player) {
    Game game(1);
    EXPECT_EQ(game.getMaxHandCards(), 8);
}

TEST(GameTest, ConstructorSetsMaxHandCardsFor2Players) {
    Game game(2);
    EXPECT_EQ(game.getMaxHandCards(), 7);
}

TEST(GameTest, ConstructorSetsMaxHandCardsFor3Players) {
    Game game(3);
    EXPECT_EQ(game. getMaxHandCards(), 6);
}

TEST(GameTest, ConstructorSetsMaxHandCardsFor4Players) {
    Game game(4);
    EXPECT_EQ(game. getMaxHandCards(), 6);
}

TEST(GameTest, ConstructorSetsMaxHandCardsFor5Players) {
    Game game(5);
    EXPECT_EQ(game. getMaxHandCards(), 6);
}

// ============== Stack Size Tests ==============

TEST(GameTest, InitialStackSizeIs98) {
    // Cards 2-99 = 98 cards
    Game game(1);
    EXPECT_EQ(game.stackSize(), 98);
}

TEST(GameTest, InitialLeftOverIs98) {
    Game game(1);
    EXPECT_EQ(game.getLeftOver(), 98);
}