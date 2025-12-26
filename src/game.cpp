#include "game.hpp"
#include "config.hpp"

#include <algorithm>
#include <random>
#include <vector>

int Game::stackSize() const noexcept { return stackPile.size(); }

const std::array<int, 4>& Game::getTopCards() const { return topCards; }

void Game::setTopCard(int pile, int card) {
    topCards[pile] = card;
}

void Game::decrementLeftOver() noexcept { --leftOver; }

int Game::getLeftOver() const noexcept { return leftOver; }

int Game::drawCard() {
    int card = stackPile.back();
    stackPile.pop_back();
    return card;
}

Game::Game() {
    for (unsigned int card = LOWEST_CARD; card <= HIGHEST_CARD; ++card) {
        stackPile.push_back(card);
    }
    // Shuffle stackpile using thread-local random generator for better performance
    thread_local std::mt19937 g{std::random_device{}()};

    std::shuffle(stackPile.begin(), stackPile.end(), g);

    leftOver = stackPile.size();
}
