#include "game.hpp"
#include "config.hpp"

#include <algorithm>
#include <random>
#include <vector>

int Game::stackSize() { return stackPile.size(); }

std::array<int, 4> Game::getTopCards() { return topCards; }

void Game::setTopCard(int pile, int card) {

    topCards.at(pile) = card;
}

void Game::decrementLeftOver() { --leftOver; }

int Game::getLeftOver() { return leftOver; }

int Game::drawCard() {
    int card = stackPile.back();
    stackPile.pop_back();
    return card;
}

Game::Game() {
    for (unsigned int card = LOWEST_CARD; card <= HIGHEST_CARD; ++card) {
        stackPile.push_back(card);
    }
    // Shuffle stackpile
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(stackPile.begin(), stackPile.end(), g);

    leftOver = stackPile.size();
}
