
#include "config.hpp"
#include "player.hpp"
#include "stats.hpp" // to increase special move count

#include <array>
#include <limits>
#include <utility>

// Stores: The Stack, 
//         difference needed for special move
//         whether the stack is UP or DOWN
namespace algm {

struct Special {
    config::Stacks stack;
    int diff;
    bool isUp;
};
// ->
constexpr std::array<Special, 4> specialRules {{
    {config::UP1, - config::SPECIAL_RULE_DIFF, true},
    {config::UP2, - config::SPECIAL_RULE_DIFF, true},
    {config::DOWN1, config::SPECIAL_RULE_DIFF, false},
    {config::DOWN2, config::SPECIAL_RULE_DIFF, false}
}};

} // namespace algm

// checks if card is within privilege range of top card
// card: 92, range: 3, top: 89 -> true
bool inPrivRange(int top, int card, bool isUp) {
    if (isUp) {
        return top < card && top + config::PRIVILEGE_RANGE >= card;
    } else {
        return top > card && top - config::PRIVILEGE_RANGE <= card;
    }
}

bool Player::movePrivilege() {
    // Save to spare call each time
    auto currentTopCards = m_game.getTopCards();

    for (auto card : handCards) {

        for (const auto& r : algm::specialRules) {

            const int top = currentTopCards.at(r.stack);
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

    bool isUp = (bestMove.second == config::UP1 || bestMove.second == config::UP2);

    // 12 -> 22 -> 32 can happen only MAX_HANDCARDS times 
    // i is unused, just for loop count
    for (size_t i = 0; i < m_game.getMaxHandCards(); ++i) { 

        bool swapped{false};

        for (const auto& card : handCards) {

            if (bestMove.first == card) { // Optimize, don't check card twice
                continue;
            }
           
            if ((bestMove.first + config::SPECIAL_RULE_DIFF == card && isUp) ||
                (bestMove.first - config::SPECIAL_RULE_DIFF == card && !isUp)) {
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
    auto currentTopCards = m_game.getTopCards();

    // First: Card, Second: Stack
    std::pair<unsigned int, unsigned int> bestMove {};

    // Smallest positive difference found of all handCards
    unsigned int smallestDiff = std::numeric_limits<int>::max();

    bool privilege{false}; // -> store if our move is of type "special"

    // Iterate through every handcard and check privilege / closeness
    for (auto card : handCards) {

        // Special Rule possible ?
        for (const auto& r : algm::specialRules) {
            if (card == currentTopCards.at(r.stack) + r.diff) {
                bestMove = {card, r.stack};
                privilege = true;
            }
        }

        // Privilege has priority, we will perform that regardless
        // of closeness to top cards
        if (privilege) {
            ++stats::specialMove; // we will perform a special move
            break;
        }

        // No privilege -> find closest card to any top card

        std::array<int, 4> allDiffs{
            card - currentTopCards.at(config::UP1),
            card - currentTopCards.at(config::UP2),
            currentTopCards.at(config::DOWN1) - card,
            currentTopCards.at(config::DOWN2) - card
        };

        // Update smallestDiff and bestMove if we found a closer card/pile combination
        for (size_t pile = 0; pile < allDiffs.size(); ++pile) {
            const int diff = allDiffs.at(pile);

            // Ignore negatives
            if (diff < 0) {
                continue;
            }

            // Found a new best move
            if (diff < smallestDiff) {
                smallestDiff = diff;
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

bool Player::playBestMoves() {
    // Adjust Minplay if necessary
    unsigned int minPlays = (handCards.size() >= config::MIN_PLAY ? config::MIN_PLAY : handCards.size());

    // If gameStack is empty players are allowed to only make one move
    if (m_game.stackSize() == 0) {
        minPlays = 1;
    }

    unsigned int plays = 0; // how many plays the Player has done

    while (plays < minPlays || movePrivilege()) {

        // First: Card, Second: Pile; ==> .second == 0 -> no Move found
        std::pair<unsigned int, unsigned int> bestMove;
        bestMove = calculateMove();

        // -> no valid move found 
        if (bestMove.first == 0 && plays < minPlays) {
            return false;
        } else if (bestMove.first == 0) {
            // Player made all necessary moves, so game goes on
            return true;
        }

        stats::usedStack(bestMove.second);

        // Automatically play the best move
        removeHandCard(bestMove.first);
        m_game.setTopCard(bestMove.second, bestMove.first);
        m_game.decrementLeftOver();
        ++plays;
    }
    return true;
}
