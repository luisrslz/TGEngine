#include "player.hpp"
// #include "controlInput.hpp"
#include "config.hpp"

#include <algorithm>
#include <stdexcept>

Player::Player(Game &game) : m_game(game) {}

unsigned int Player::getCardCount() { return handCards.size(); }

void Player::drawCards() {
    if (handCards.size() == MAX_HANDCARDS) {
        throw std::logic_error("Logic error in drawCard()");
    }

    while (handCards.size() != MAX_HANDCARDS) {
        // Abort drawing if the stack is empty
        if (m_game.stackSize() == 0) {
            break;
        }

        int card = m_game.drawCard();

        handCards.push_back(card);
    }
}

void Player::removeHandCard(int card) {

    handCards.erase(std::remove(handCards.begin(), handCards.end(), card), handCards.end());
}