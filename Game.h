#ifndef ARKANOID_THE_GAME_GAME_H
#define ARKANOID_THE_GAME_GAME_H
#include "Collisions.h"
#include <sstream>

class Game {
public:
    Game() {}
    ~Game() = default;

    void Init();
    void setText();
    void setBlocks();
    void setBonuses();
    void setBalls();
    void setBogey();
    void updateStats();
    void mainLoop();
    void checkBallBlockCollision(std::vector<Block>& blockType, std::vector<Ball>& balls, Statistics& statistics);
    void deletingBlocks(std::vector<Block>& blockType);
    void textStream();
    void drawBricks(std::vector<Block>& blockType);
    void drawObjects();
    
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText, hpText, finalPhrase;
    Bogey bogey = Bogey(0, 0);
    Block* savingBottom = nullptr;
    std::vector<Ball> balls;

    std::vector<Bonus *> bonuses;
    BonusChangeSpeed bonusChangeSpeed = BonusChangeSpeed(0, 0);
    BonusChangeSize bonusChangeSize = BonusChangeSize(0, 0);
    BonusSavingBottom bonusSavingBottom = BonusSavingBottom(0, 0);
    BonusBall bonusBall = BonusBall(0, 0);
    BonusStickiness bonusStickiness = BonusStickiness(0, 0);

    std::vector<Block> simpleBlocks;
    std::vector<Block> undestroyableBlocks;
    std::vector<Block> tankBlocks;
    std::vector<Block> speedBlocks;
    std::vector<Block> bonusBlocks;
    Statistics statistics;
    int countBlocks = 0;
};


#endif //ARKANOID_THE_GAME_GAME_H
