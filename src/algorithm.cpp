
#include "config.hpp"
#include "player.hpp"

#include <algorithm>
#include <array>
#include <limits>
#include <map>
#include <utility>

// Stores: The Stack, 
//         difference needed for special move
//         whether the stack is UP or DOWN
struct Special {
    config::Stacks stack;
    int diff;
    bool isUp;
};
// ->
static constexpr std::array<Special, 4> specialRules {{
    {config::UP1, -10, true},
    {config::UP2, -10, true},
    {config::DOWN1, 10, false},
    {config::DOWN2, 10, false}
}};

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

        for (const auto& r : specialRules) {

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
    for (size_t i = 0; i < config::MAX_HANDCARDS; ++i) { 

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
    auto currentTopCards = m_game.getTopCards();

    // First: Card, Second: Stack
    std::pair<unsigned int, unsigned int> bestMove {};

    // Safes for each card <int, ...> the smallest diff and according stack >>->
    // smallestDiffs.at(32) = {4, UP2}
    std::map<int, std::pair<int, int>> smallestDiff;

    bool privilege{false}; // -> store if our move is of type "special"

    // Iterate through every handcard and set
    // smallestDiff for each
    for (auto card : handCards) {

        // Special Rule possible ?
        for (const auto& r : specialRules) {
            if (card == currentTopCards.at(r.stack) + r.diff) {
                bestMove = {card, r.stack};
                privilege = true;
            }
        }

        // Optimize
        if (privilege) {
            break;
        }

        std::array<int, 4> allDiffs{
            card - currentTopCards.at(config::UP1),
            card - currentTopCards.at(config::UP2),
            currentTopCards.at(config::DOWN1) - card,
            currentTopCards.at(config::DOWN2) - card
        };

        // Now find the closest difference (ignore negative values)
        int closest = std::numeric_limits<int>::max();
        for (size_t pile = 0; pile < allDiffs.size(); ++pile) {
            const int diff = allDiffs.at(pile);

            // Ignore negatives
            if (diff < 0) {
                continue;
            }

            if (diff < closest) {
                // Overwrite the closest until it finally is the closest obv.-
                smallestDiff[card] = {diff, pile};
                closest = diff;
            }
        }
    }

    // Now iterate through the map and find the overall smallest Difference
    if (!privilege) {
        auto temp = std::min_element(
            smallestDiff.begin(), smallestDiff.end(),
            [](const auto &a, const auto &b) { return a.second.first < b.second.first; });

        bestMove = {temp->first, temp->second.second};
    }

    // Check if we can make the best move even better by predicting
    // the special rule: i. e. instead of 67 we lay 77 to lay 67 next move
    // may happen MAX_HANDCARDS times
    predictSpecial(bestMove);

    return bestMove;
}

bool Player::bestMove() {
    // Adjust Minplay if necessary
    unsigned int minPlays = (handCards.size() >= config::MIN_PLAY ? config::MIN_PLAY : handCards.size());

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