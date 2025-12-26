#include "stats.hpp"
#include "config.hpp"

void stats::usedStack(unsigned int stack) {
    switch (stack) {
        case config::UP1:
            ++stackUP1;
            break;
        case config::UP2:
            ++stackUP2;
            break;
        case config::DOWN1:
            ++stackDOWN1;
            break;
        case config::DOWN2:
            ++stackDOWN2;
            break;
        default:
            break;
    }
}