
#include "config.hpp"
#include "game.hpp"
#include "player.hpp"

#include <algorithm>
#include <array>
#include <limits>
#include <utility>

// Stores: The Stack, 
//         difference needed for special move
//         whether the stack is UP or DOWN
struct Special {
    Stacks stack;
    int diff;
    bool isUp;
};
// ->
static constexpr std::array<Special, 4> specialRules {{
    {UP1, -10, true},
    {UP2, -10, true},
    {DOWN1, 10, false},
    {DOWN2, 10, false}
}};

bool inPrivRange(int top, int card, bool isUp) {
    if (isUp) {
        return top < card && top + PRIVILEGE_RANGE >= card;
    } else {
        return top > card && top - PRIVILEGE_RANGE <= card;
    }
}

bool Player::movePrivilege() {
    // Save to spare call each time
    const auto& currentTopCards = m_game.getTopCards();

    for (auto card : handCards) {

        for (const auto& r : specialRules) {

            const int top = currentTopCards[r.stack];
            // SPECIAL RULE ? 
            if (card == top + r.diff) {
                return true;
            }
            // PRIVILEGE RANGE?
            if (inPrivRange(top, card, r.isUp)) {
                return true;
            }
        }
    }
    return false;
}

void Player::predictSpecial(std::pair<unsigned int, unsigned int>& bestMove) {

    bool isUp = (bestMove.second == UP1 || bestMove.second == UP2);

    for (size_t i = 0; i < MAX_HANDCARDS; ++i) { // 12 -> 22 -> 32 can happen only MAX_HANDCARDS times 
                                                 // note that this i isn't used, just for how often
                                                 // we should check
        bool swapped{false};

        for (const auto& card : handCards) {

            if (bestMove.first == card) { // Optimize, don't check card twice
                continue;
            }
           
            if ((bestMove.first + 10 == card && isUp) ||
                (bestMove.first - 10 == card && !isUp)) {
                bestMove.first = card;
                swapped = true;
                break;
            }
        }
        if (!swapped) { // Optimize
            break;
        }
    }
}


std::pair<unsigned int, unsigned int> Player::calculateMove() {

    // Save to spare call each time 
    const auto& currentTopCards = m_game.getTopCards();

    // First: Card, Second: Pile
    std::pair<unsigned int, unsigned int> bestMove {};

    // Track the overall smallest difference and its corresponding card/pile
    int overallSmallestDiff = std::numeric_limits<int>::max();

    bool privilege{false}; // -> store if our move is of type "special"

    // Iterate through every handcard and find the best move directly
    for (auto card : handCards) {

        // Special Rule possible ?
        for (const auto& r : specialRules) {
            if (card == currentTopCards[r.stack] + r.diff) {
                bestMove = {card, r.stack};
                privilege = true;
            }
        }

        // Optimize
        if (privilege) {
            break;
        }

        std::array<int, 4> allDiffs{
            card - currentTopCards[UP1],
            card - currentTopCards[UP2],
            currentTopCards[DOWN1] - card,
            currentTopCards[DOWN2] - card
        };

        // Now find the closest difference (ignore negative values) and track overall best
        for (size_t pile = 0; pile < allDiffs.size(); ++pile) {
            const int diff = allDiffs[pile];

            // Ignore negatives
            if (diff < 0) {
                continue;
            }

            if (diff < overallSmallestDiff) {
                overallSmallestDiff = diff;
                bestMove = {card, pile};
            }
        }
    }

    // Check if we can make the best move even better by predicting
    // the special rule: i. e. instead of 67 we lay 77 to lay 67 next move
    // may happen MAX_HANDCARDS times
    predictSpecial(bestMove);

    return bestMove;
}

bool Player::bestMove() {
    // Adjust Minplay if necessary
    unsigned int minPlays = (handCards.size() >= MIN_PLAY ? MIN_PLAY : handCards.size());

    // If gameStack is empty players are allowed to only make one move
    if (m_game.stackSize() == 0) {
        minPlays = 1;
    }

    unsigned int plays = 0; // how many plays the Player has done

    while (plays < minPlays || movePrivilege()) {

        // First: Pile, Second: Card; ==> .first == 0 -> no Move found
        std::pair<unsigned int, unsigned int> bestMove;
        bestMove = calculateMove();

        // -> no valid move found 
        if (bestMove.first == 0 && plays < minPlays) {
            return false;
        } else if (bestMove.first == 0) {
            // Player made all necessary moves, so game goes on
            return true;
        }

        // Automatically play the best move
        removeHandCard(bestMove.first);
        m_game.setTopCard(bestMove.second, bestMove.first);
        m_game.decrementLeftOver();
        ++plays;
    }
    return true;
}