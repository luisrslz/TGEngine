#include "play.hpp"
#include "game.hpp"
#include "player.hpp"
#include "stats.hpp"
#include "helpers.hpp"

#include <vector>
#include <thread>

bool runGameLoop(std::vector<Player> &players, const unsigned int& playerCount, Game& game) {
    int currentPlayer = 0;

    while (true) {
        // Play the best moves
        if (players[currentPlayer].getCardCount() > 0) {
            if (!players[currentPlayer].playBestMoves()) {
                // -> Game OVER
                break;
            }
        }

        // -> Draw Cards
        if (game.stackSize() > 0) {
            players[currentPlayer].drawCards();
        }

        if (game.getLeftOver() == 0) {
            break;
            // WON! no cards left.
        }

        // Rotate through players
        currentPlayer = (currentPlayer + 1) % playerCount;
        ++stats::totalRounds; // one round completed
    }
    
    stats::handleLeftOver(game.getLeftOver());

    if (game.getLeftOver() == 0) {
        return true; // Won
    } else {
        return false; // Lost
    }
}

void simulate(const unsigned long long iterations, const unsigned int playerCount) {
    for (unsigned long long i = 0; i < iterations; ++i) {
        Game game(playerCount);
        std::vector<Player> players = createPlayers(playerCount, game);

        if (runGameLoop(players, playerCount, game)) {
            ++stats::wins;
        } else {
            ++stats::losses;
        }

    }
}

void multiThread(std::vector<std::thread>& threads,
                 const unsigned long long& repetitions, const unsigned int& playerCount) {
    int numThreads = std::thread::hardware_concurrency();

    if (numThreads == 0) {
        numThreads = 4;
    } 

    int repsPerThread = repetitions / numThreads;
    int remains = repetitions % numThreads;

    std::cout << "\nCalculating...\n";

    //put all threads to work
    for (int i = 1; i <= numThreads; ++i) {
        int rep = repsPerThread;
        if (i == numThreads) {
            // Last thread gets the remaining games
            rep += remains;
        }
        threads.emplace_back(simulate, rep, playerCount);
    }
}
