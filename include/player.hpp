#pragma once

#include <vector>

#include "game.hpp"

class Player {
  public:
    Player(Game& game);

    // returns length of handCard Vector
    unsigned int getCardCount() const; 

    // --> draw card procedure
    void drawCards(); 

     /* ------- MOVE CALCULATION ----- */

    /* checks if player should make an extra move
     * e.g. because he can perform special rule or because he
     * has a card very close to a top card
     */
    bool movePrivilege(); 

    /* alters bestMove to play a move which enables the player 
     * to perform the special rule next round
     */
    void predictSpecial(std::pair<unsigned int, unsigned int>& bestMove);

    // Main move calculation
    std::pair<unsigned int, unsigned int> calculateMove(); 

    // Interaction with the game loop and final performance of the move
    bool playBestMoves(); // -> prints the best possible move

    /* --------------------  */

    // removes a card from handCards
    void removeHandCard(int card);

    // ========= FOR TESTING PURPOSES =========
    // sets handCards to a predefined vector (for testing)
    void setHandCards(const std::vector<int>& cards) {
      handCards = cards;
    }

    // getter for handCards (for testing)
    std::vector<int> getHandCards() const {
      return handCards;
    }
    // =======================================

  private:
    // -> each player has a reference to his game to interact with it
    Game &m_game; 

    // player's handcards {42, 67, 89, ...}
    std::vector<int> handCards;

};

// Free function declaration for testability (defined in algorithm.cpp)
bool inPrivRange(int top, int card, bool isUp);