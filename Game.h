#ifndef ARKANOID_THE_GAME_GAME_H
#define ARKANOID_THE_GAME_GAME_H
#include "Collisions.h"
#include <sstream>
#include <memory>

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
    void checkBallBlockCollision(std::vector<std::unique_ptr<Block>>& blockType, std::vector<Ball>& balls, Statistics& statistics);
    void deletingBlocks(std::vector<std::unique_ptr<Block>>& blockType);
    void textStream();
    void drawBricks(std::vector<std::unique_ptr<Block>>& blockType);
    void drawObjects();


private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText, hpText, finalPhrase;
    Bogey bogey = Bogey(0, 0);

    std::unique_ptr<Block> savingBottom;

    std::vector<Ball> balls;

    std::vector<std::unique_ptr<Bonus>> bonuses;
    std::vector<std::unique_ptr<Block>> simpleBlocks;
    std::vector<std::unique_ptr<Block>> undestroyableBlocks;
    std::vector<std::unique_ptr<Block>> tankBlocks;
    std::vector<std::unique_ptr<Block>> speedBlocks;
    std::vector<std::unique_ptr<Block>> bonusBlocks;

    Statistics statistics;

};


#endif //ARKANOID_THE_GAME_GAME_H
