#ifndef ARKANOID_THE_GAME_STATISTICS_H
#define ARKANOID_THE_GAME_STATISTICS_H
#include <iostream>

class Statistics {
public:
    int getHP() const { return this->healthpoint; }
    void hpPenalty() { this->healthpoint--; }

    int getScore() const { return score; }
    void scorePlusPlus() { score++; }

private:
    int healthpoint = 1;
    int score = 0;
};



#endif //ARKANOID_THE_GAME_STATISTICS_H
