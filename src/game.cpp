#include "game.hpp"
#include "config.hpp"

#include <algorithm>
#include <random>
#include <vector>

int Game::stackSize() const { return stackPile.size(); }

std::array<int, 4> Game::getTopCards() const { return topCards; }

void Game::setTopCard(int pile, int card) {
    topCards.at(pile) = card;
}

void Game::decrementLeftOver() { --leftOver; }

int Game::getLeftOver() const { return leftOver; }

int Game::drawCard() {
    int card = stackPile.back();
    stackPile.pop_back();
    return card;
}

unsigned int Game::getMaxHandCards() const {
    return maxHandCards;
}

// maxHandCards gets defined according to instructions
Game::Game(const unsigned int& playerCount) 
          : maxHandCards(playerCount >= 3 ? 6 : (playerCount == 2 ? 7 : 8)) {
    for (unsigned int card = config::LOWEST_CARD; card <= config::HIGHEST_CARD; ++card) {
        stackPile.push_back(card);
    }
    // Shuffle stackpile
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(stackPile.begin(), stackPile.end(), g);

    leftOver = stackPile.size();
}
