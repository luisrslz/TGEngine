#include <gtest/gtest.h>
#include "player.hpp"
#include "game.hpp"

// ============== Constructor Tests ==============

TEST(PlayerTest, NewPlayerHasNoCards) {
    Game game {1};
    Player player {game};
    
    EXPECT_EQ(player.getCardCount(), 0);
}

// ============== Draw Cards Tests ==============

TEST(PlayerTest, DrawCardsGivesMaxHandCards) {
    Game game {1}; // maxHandCards = 8
    Player player {game};
    
    player.drawCards();
    
    EXPECT_EQ(player.getCardCount(), 8);
}

TEST(PlayerTest, DrawCardsFor2Players) {
    Game game {2}; // maxHandCards = 7
    Player player {game};
    
    player.drawCards();
    
    EXPECT_EQ(player.getCardCount(), 7);
}

TEST(PlayerTest, DrawCardsFor3Players) {
    Game game {3}; // maxHandCards = 6
    Player player {game};
    
    player.drawCards();
    
    EXPECT_EQ(player.getCardCount(), 6);
}

TEST(PlayerTest, DrawCardsReducesStackSize) {
    Game game {1};
    Player player {game};
    int initialStackSize = game.stackSize();
    
    player.drawCards();
    
    EXPECT_EQ(game.stackSize(), initialStackSize - 8);
}

TEST(PlayerTest, DrawCardsStopsWhenStackEmpty) {
    Game game {1};
    Player player {game};
    
    // Draw all cards from stack
    while (game.stackSize() > 3) {
        game.drawCard();
    }
    
    // Stack now has only 3 cards
    player.drawCards();
    
    EXPECT_EQ(player.getCardCount(), 3);
    EXPECT_EQ(game.stackSize(), 0);
}

// ============== Remove Hand Card Tests ==============

TEST(PlayerTest, RemoveHandCardReducesCount) {
    Game game {1};
    Player player {game};
    player.drawCards();
    
    auto cards = player.getHandCards();
    int cardToRemove = cards[0];
    
    player.removeHandCard(cardToRemove);
    
    EXPECT_EQ(player.getCardCount(), 7);
}

TEST(PlayerTest, RemoveHandCardActuallyRemovesCard) {
    Game game {1};
    Player player {game};
    
    // Set specific hand cards for testing
    player.setHandCards({10, 20, 30, 40, 50});
    
    player.removeHandCard(30);
    
    auto cards = player.getHandCards();
    EXPECT_EQ(cards.size(), 4);
    
    // Verify 30 is not in the hand anymore
    bool found30 = false;
    for (int card : cards) {
        if (card == 30) {
            found30 = true;
            break;
        } 
    }
    EXPECT_FALSE(found30);
}

TEST(PlayerTest, RemoveNonExistentCardDoesNothing) {
    Game game {1};
    Player player {game};
    
    player.setHandCards({10, 20, 30});
    player.removeHandCard(99); // not in hand
    
    EXPECT_EQ(player.getCardCount(), 3);
}