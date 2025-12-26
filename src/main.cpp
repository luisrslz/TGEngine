#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include <thread>
#include <atomic>

#include "config.hpp"
#include "game.hpp"
#include "helpers.hpp"
#include "player.hpp" 

// stats
std::atomic<unsigned long long> wins {};
std::atomic<unsigned long long> losses {};
std::atomic<unsigned long long> leftOvers{};

// This function simulates one game
bool runGameLoop(std::vector<Player> &players, unsigned int playerCount, Game &game) {
    int currentPlayer = 0;

    while (true) {
        // Play the best moves
        if (players[currentPlayer].getCardCount() > 0) {
            if (!players[currentPlayer].bestMove()) {
                // -> Game OVER
                break;
            }
        }

        // -> Draw Cards
        if (players[currentPlayer].getCardCount() != MAX_HANDCARDS && game.stackSize() > 0) {
            players[currentPlayer].drawCards();
        }

        if (game.getLeftOver() == 0) {
            break;
            // WON! no cards left.
        }

        // Rotate through players
        currentPlayer = (currentPlayer + 1) % playerCount;
    }
    
    leftOvers += game.getLeftOver();

    if (game.getLeftOver() == 0) {
        return true; // Won
    } else {
        return false; // Lost
    }
}

// Work function for each thread
void threadWork(unsigned long long iterations, unsigned int playerCount) {
    for (unsigned long long i = 0; i < iterations; ++i) {
        Game game;
        std::vector<Player> players = createPlayers(playerCount, game);
        if (runGameLoop(players, playerCount, game)) {
            ++wins;
        } else {
            ++losses;
        }
    }
}

int main() {
    // Welcome Message
    clearScreen();
    printLogo();

    // Amount of players
    unsigned int playerCount;
    askPlayerCount(playerCount);

    // set according to instructions
    MAX_HANDCARDS = (playerCount >= 3 ? 6 : (playerCount == 2 ? 7 : 8));

    // Amount of repetitions
    unsigned long long repetitions;
    std::cout << YELLOW << "Repetions?" << RESET << "\n-> ";
    std::cin >> repetitions;

    // -------------- MULTI-THREAD ----------------

    int numThreads = std::thread::hardware_concurrency();
    // safety
    if (numThreads == 0) numThreads = 4;

    int repsPerThread = repetitions / numThreads;
    int remains = repetitions % numThreads;

    std::vector<std::thread> threads;

    std::cout << "\nCalculating...\n";

    //put all threads to work
    for (int i = 1; i <= numThreads; ++i) {
        int rep = repsPerThread;
        if (i == numThreads) {
            // Last thread gets the remaining games
            rep += remains;
        }
        threads.emplace_back(threadWork, rep, playerCount);
    }
    repsPerThread -= remains; // reset this if needed in the future

    // Print 
    // this thread could also work but whatever...
    while (losses + wins < repetitions) {
        std::cout << "\r" << losses + wins;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // wait for all threads to finish
    for (auto &t : threads) {
        t.join();
    }

    // --------------- END ----------

    // Final output
    std::cout << CYAN << "\n\nFinished.\n"
              << GREEN << "Wins: " << wins
              << RED << "\nLosses: " << losses << RESET 
              << BLUE << "\nWin-Rate: " << std::fixed << std::setprecision(2)
              << (static_cast<double>(wins) / (wins + losses) * 100.0) << "%\n" 
              << "Average leftover cards: " << static_cast<double>(leftOvers) / repetitions
              << RESET;

    return 0;
}