#include "player.hpp"

#include <algorithm>

Player::Player(Game &game) : m_game(game) {}

unsigned int Player::getCardCount() const { return handCards.size(); }

void Player::drawCards() {

    while (handCards.size() != m_game.getMaxHandCards()) {
        // Abort drawing if the stack is empty
        if (m_game.stackSize() == 0) {
            break;
        }

        int card = m_game.drawCard();

        handCards.push_back(card);
    }
}

void Player::block(int pile) {
    m_game.blockPile(pile);
    blockedPiles.push_back(pile);
    
}

void Player::unblockAll()  {
    for (const auto& p : blockedPiles) {
        m_game.unblockPile(p);
    }
    blockedPiles.clear();
}

void Player::removeHandCard(int card) {
    handCards.erase(std::remove(handCards.begin(), handCards.end(), card), handCards.end());
}