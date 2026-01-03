#pragma once

#include "config.hpp"

#include <array>
#include <vector>

class Game {
  public:
    // constructor initializes the stackPile and shuffles it
    // playerCount needed for maxHandCards
    Game(const unsigned int& playerCount);

    // simple getter with stackPile.size()
    int stackSize() const;

    // leftOver gets decremented when a card is played -= 1
    void decrementLeftOver();

    // getter for leftOver
    int getLeftOver() const;

    // Removes last card from stackPile and returns it
    int drawCard();

    // getter for topCards
    std::array<int, 4> getTopCards() const;

    // set topCards.at(pile) = card (after a card is played)
    void setTopCard(int pile, int card);

    // getter for maxHandCards
    unsigned int getMaxHandCards() const; 

    // ======== FOR TESTING PURPOSES =========
    // sets topCards to a predefined vector (for testing)
    void setTopCards(const std::array<int, 4>& tops) { 
      topCards = tops; 
    }
    // ======================================

  private:
    // stack where players draw from
    std::vector<int> stackPile{};

    // Up: 0, 1 <---> Down: 2, 3
    // stack / pile on which cards are played
    std::array<int, 4> topCards{config::UP_START, config::UP_START, config::DOWN_START,
                                config::DOWN_START};

    // how many cards are left, gets defined in constructor
    unsigned int leftOver{};

    // determines how many handcards ONE player may have
    unsigned int maxHandCards{};


};
