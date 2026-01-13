#include "game.hpp"
#include "config.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <stdexcept>

int Game::stackSize() const { return stackPile.size(); }

std::array<int, 4> Game::getTopCards() const { return topCards; }

void Game::setTopCard(int pile, int card) {

    // Prevent illegal moves
    if (pile == config::UP1 || pile == config::UP2) {
        if (card <= topCards.at(pile) && !(topCards.at(pile) - config::SPECIAL_RULE_DIFF == card)) [[unlikely]] {
            std::cerr << "Tried to set UP stack with lower/equal card: " << card 
                      << " on top of " << topCards.at(pile) << "\n";
            throw std::logic_error("\nError: Tried to set UP stack with lower/equal card.");
        }
    } else {
        if (card >= topCards.at(pile) && !(topCards.at(pile) + config::SPECIAL_RULE_DIFF == card)) [[unlikely]] {
            std::cerr << "Tried to set DOWN stack with higher/equal card: " << card 
                      << " on top of " << topCards.at(pile) << "\n";
            throw std::logic_error("\nError: Tried to set DOWN stack with higher/equal card.");
        }
    }
    
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

void Game::releaseAllBlocks() {
    for (auto& blocked : blockedPiles) {
        blocked = false;
    }
}

bool Game::anyPileBlocked() const {
    for (const auto& pile : blockedPiles) {
        if (pile) {
            return true;
        }
    }
    return false;
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
