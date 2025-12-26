#pragma once

#include "config.hpp"

#include <array>
#include <vector>

class Game {
  public:
    Game();

    int stackSize() const noexcept;

    void decrementLeftOver() noexcept;

    int getLeftOver() const noexcept;

    // To automatically draw last card from vector
    int drawCard();

    const std::array<int, 4>& getTopCards() const;

    void setTopCard(int pile, int card);

  private:

    std::vector<int> stackPile {}; // stack where players draw from

    // Up: 0, 1 <---> Down: 2, 3
    std::array<int, 4> topCards{UP_START, UP_START, DOWN_START, DOWN_START};

    // How many cards are left
    unsigned int leftOver{98};
};
