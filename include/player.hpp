#pragma once

#include <vector>

#include "game.hpp"

class Player {
  public:
    Player(Game& game);

    unsigned int getCardCount(); // returns length of handCard Vector

    void drawCards(); // --> draw card procedure (inc. text output)

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
    bool bestMove(); // -> prints the best possible move

    /* --------------------  */

    void removeHandCard(int card);

  private:
    Game &m_game; // -> each player has a reference to his game

    //std::string m_name; // name of player

    std::vector<int> handCards;



};
