#include <chrono>
#include <iostream>
#include <vector>
#include <limits>
#include <thread>

#include "config.hpp"
#include "helpers.hpp"
#include "stats.hpp"
#include "play.hpp"

int main() {
    // Welcome Message
    clearScreen();
    printLogo();

    // Amount of players
    unsigned int playerCount;
    std::cout << config::YELLOW << "\nPlease enter the amount of player(s)! (1-" 
              << config::MAX_PLAYERS << ")\n"
              << config::RESET << "-> ";
    playerCount = getInput(1, config::MAX_PLAYERS);

    // Amount of repetitions
    unsigned long long repetitions;
    std::cout << config::YELLOW << "\nRepetitions?" << config::RESET << "\n-> ";
    repetitions = getInput(1ull, std::numeric_limits<unsigned long long>::max());

    // -------------- MULTI-THREAD ----------------

    std::cout << "\nCalculating...\n";
    
    std::vector<std::thread> threads; 
    
    multiThread(threads, repetitions, playerCount);
    
    // Print 
    while (stats::losses + stats::wins < repetitions) {
        printProgress(repetitions);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    // Final update
    printProgress(repetitions);

    // wait for all threads to finish
    for (auto &t : threads) {
        t.join();
    }

    // --------------- END ----------

    // Final output
    stats::print(repetitions, playerCount);

    // prevent windows from closing terminal immediately
#ifdef _WIN32
    std::cout << "\nPress Enter to exit...";
    std:: cin.ignore(std::numeric_limits<std:: streamsize>::max(), '\n');
    std::cin.get();
#endif

    return 0;
}
